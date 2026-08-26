// =============================================================================
//  matrix_sum_cg.cu
//
//  使用 <cooperative_groups.h> 計算矩陣所有元素總和 (matrix sum) 的完整範例。
//
//  範例包含兩種常見作法：
//    (A) kernel_sum_atomic  : thread_block_tile<32> 做 warp 內 reduce，
//                             block 內再用 shared memory 收斂，最後 atomicAdd。
//                             → 一般 launch 即可，最通用、相容性最好。
//    (B) kernel_sum_gridsync: 用 cg::grid_group 的 grid.sync() 在「單一 kernel」
//                             內完成兩階段 reduction（不需要第二次 launch，也
//                             不需要 atomic）。
//                             → 必須用 cudaLaunchCooperativeKernel 啟動，
//                               且編譯需加 -rdc=true。
//
//  編譯 (依實際 GPU 調整 sm_XX)：
//      nvcc -O3 -std=c++14 -arch=sm_80 -rdc=true matrix_sum_cg.cu -o matrix_sum_cg
//
//  執行：
//      ./matrix_sum_cg            // 預設 4096 x 4096
//      ./matrix_sum_cg 8192 4096  // rows cols
// =============================================================================

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <cuda_runtime.h>
#include <cooperative_groups.h>
#include <cooperative_groups/reduce.h>   // cg::reduce / cg::plus (CUDA 11.0+)

namespace cg = cooperative_groups;

// -----------------------------------------------------------------------------
// 錯誤檢查
// -----------------------------------------------------------------------------
#define CUDA_CHECK(call)                                                       \
    do {                                                                       \
        cudaError_t _err = (call);                                             \
        if (_err != cudaSuccess) {                                             \
            fprintf(stderr, "[CUDA ERROR] %s:%d '%s' -> %s\n",                 \
                    __FILE__, __LINE__, #call, cudaGetErrorString(_err));      \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
    } while (0)

static const int kBlockSize = 256;                 // 必須是 32 的倍數
static const int kMaxWarpsPerBlock = 32;           // 1024 threads / 32

// -----------------------------------------------------------------------------
// device helper：把「單一 block 內所有 thread 的 val」加總，回傳值只在
//                block.thread_rank() == 0 有效。
//
// 這裡示範 cooperative groups 的三個核心概念：
//   1. cg::this_thread_block()        取得 block group
//   2. cg::tiled_partition<32>(block) 把 block 切成 warp 大小的 tile
//   3. tile.meta_group_rank()/size()  這個 tile 在 block 中是第幾個 / 共幾個
// -----------------------------------------------------------------------------
__device__ float block_reduce_sum(const cg::thread_block &block, float val)
{
    // warp 層級 tile：tile 內的 reduce 由 shuffle 指令完成，不需要 shared memory
    cg::thread_block_tile<32> tile = cg::tiled_partition<32>(block);

    // 第一階段：warp 內 reduce
    val = cg::reduce(tile, val, cg::plus<float>());

    // 每個 warp 的 leader 把結果寫進 shared memory
    __shared__ float warp_sums[kMaxWarpsPerBlock];
    if (tile.thread_rank() == 0) {
        warp_sums[tile.meta_group_rank()] = val;
    }

    // block 層級同步（等價於 __syncthreads()，但語意更明確）
    block.sync();

    // 第二階段：由第 0 個 warp 把所有 warp 的部分和再 reduce 一次
    float block_sum = 0.0f;
    if (tile.meta_group_rank() == 0) {
        float v = (tile.thread_rank() < tile.meta_group_size())
                      ? warp_sums[tile.thread_rank()]
                      : 0.0f;
        block_sum = cg::reduce(tile, v, cg::plus<float>());
    }
    return block_sum;   // 只有 thread_rank()==0 的值是正確的
}

// -----------------------------------------------------------------------------
// (A) grid-stride loop + block reduce + atomicAdd
//     mat 以 row-major 連續存放，n = rows * cols
// -----------------------------------------------------------------------------
__global__ void kernel_sum_atomic(const float *__restrict__ mat,
                                  size_t n,
                                  float *__restrict__ result)
{
    cg::thread_block block = cg::this_thread_block();

    // grid-stride loop：讓 block 數量與資料量解耦，任意 n 都正確
    float local = 0.0f;
    size_t stride = static_cast<size_t>(gridDim.x) * blockDim.x;
    for (size_t i = static_cast<size_t>(blockIdx.x) * blockDim.x + threadIdx.x;
         i < n; i += stride) {
        local += mat[i];
    }

    float block_sum = block_reduce_sum(block, local);

    if (block.thread_rank() == 0) {
        atomicAdd(result, block_sum);
    }
}

// -----------------------------------------------------------------------------
// (B) 單 kernel 兩階段 reduction，用 cg::grid_group::sync() 做 grid 層級同步
//
//     ⚠ 前提：
//       - device 必須支援 cooperativeLaunch
//       - 必須用 cudaLaunchCooperativeKernel 啟動
//       - grid 中所有 block 必須「同時常駐」，所以 block 數要用 occupancy 算
//       - 編譯需 -rdc=true
// -----------------------------------------------------------------------------
__global__ void kernel_sum_gridsync(const float *__restrict__ mat,
                                    size_t n,
                                    float *__restrict__ partial,
                                    float *__restrict__ result)
{
    cg::grid_group   grid  = cg::this_grid();
    cg::thread_block block = cg::this_thread_block();

    // ---- Phase 1：每個 block 算出自己的部分和，寫進 partial[blockIdx.x] ----
    float local = 0.0f;
    size_t stride = static_cast<size_t>(gridDim.x) * blockDim.x;
    for (size_t i = static_cast<size_t>(blockIdx.x) * blockDim.x + threadIdx.x;
         i < n; i += stride) {
        local += mat[i];
    }

    float block_sum = block_reduce_sum(block, local);
    if (block.thread_rank() == 0) {
        partial[blockIdx.x] = block_sum;
    }

    // ---- 整個 grid 對齊：保證所有 partial[] 都已寫入且對其他 block 可見 ----
    grid.sync();

    // ---- Phase 2：由 block 0 把 gridDim.x 個部分和收成最終答案 ----
    if (grid.block_rank() == 0) {
        float v = 0.0f;
        for (unsigned int i = block.thread_rank(); i < gridDim.x;
             i += block.num_threads()) {
            v += partial[i];
        }
        float total = block_reduce_sum(block, v);
        if (block.thread_rank() == 0) {
            *result = total;
        }
    }
}

// -----------------------------------------------------------------------------
// CPU 參考解（用 double 累加，避免浮點誤差干擾正確性判斷）
// -----------------------------------------------------------------------------
static double cpu_matrix_sum(const float *mat, size_t n)
{
    double s = 0.0;
    for (size_t i = 0; i < n; ++i) s += mat[i];
    return s;
}

int main(int argc, char **argv)
{
    int rows = (argc > 1) ? atoi(argv[1]) : 4096;
    int cols = (argc > 2) ? atoi(argv[2]) : 4096;
    if (rows <= 0 || cols <= 0) {
        fprintf(stderr, "usage: %s [rows] [cols]\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t n     = static_cast<size_t>(rows) * cols;
    size_t bytes = n * sizeof(float);

    printf("Matrix: %d x %d  (%zu elements, %.2f MB)\n",
           rows, cols, n, bytes / (1024.0 * 1024.0));

    // ---------------- device 能力查詢 ----------------
    int dev = 0;
    CUDA_CHECK(cudaSetDevice(dev));
    cudaDeviceProp prop;
    CUDA_CHECK(cudaGetDeviceProperties(&prop, dev));
    printf("Device: %s (sm_%d%d, %d SMs), cooperativeLaunch = %d\n\n",
           prop.name, prop.major, prop.minor,
           prop.multiProcessorCount, prop.cooperativeLaunch);

    // ---------------- 準備資料 ----------------
    float *h_mat = static_cast<float *>(malloc(bytes));
    if (!h_mat) { fprintf(stderr, "host malloc failed\n"); return EXIT_FAILURE; }
    for (size_t i = 0; i < n; ++i) {
        // 用小數值填充，讓 float 累加誤差可控
        h_mat[i] = static_cast<float>((i % 13) - 6) * 0.25f;
    }
    double ref = cpu_matrix_sum(h_mat, n);

    float *d_mat = nullptr, *d_result = nullptr, *d_partial = nullptr;
    CUDA_CHECK(cudaMalloc(&d_mat, bytes));
    CUDA_CHECK(cudaMalloc(&d_result, sizeof(float)));
    CUDA_CHECK(cudaMemcpy(d_mat, h_mat, bytes, cudaMemcpyHostToDevice));

    // =========================================================================
    // (A) atomicAdd 版本
    // =========================================================================
    {
        int grid_size = 0;
        // 讓 block 數大約覆蓋整張卡，同時不超過資料量所需
        int blocks_per_sm = 0;
        CUDA_CHECK(cudaOccupancyMaxActiveBlocksPerMultiprocessor(
            &blocks_per_sm, kernel_sum_atomic, kBlockSize, 0));
        grid_size = blocks_per_sm * prop.multiProcessorCount;
        size_t need = (n + kBlockSize - 1) / kBlockSize;
        if (static_cast<size_t>(grid_size) > need) grid_size = static_cast<int>(need);
        if (grid_size < 1) grid_size = 1;

        CUDA_CHECK(cudaMemset(d_result, 0, sizeof(float)));
        kernel_sum_atomic<<<grid_size, kBlockSize>>>(d_mat, n, d_result);
        CUDA_CHECK(cudaGetLastError());
        CUDA_CHECK(cudaDeviceSynchronize());

        float gpu_sum = 0.0f;
        CUDA_CHECK(cudaMemcpy(&gpu_sum, d_result, sizeof(float),
                              cudaMemcpyDeviceToHost));

        double tol = fabs(ref) * 1e-4 + 1e-3;
        printf("[A] tile<32> reduce + atomicAdd  (grid = %d blocks x %d threads)\n",
               grid_size, kBlockSize);
        printf("    GPU = %.6f  CPU = %.6f  -> %s\n\n",
               gpu_sum, ref,
               (fabs(gpu_sum - ref) <= tol) ? "PASS" : "FAIL");
    }

    // =========================================================================
    // (B) grid.sync() 單 kernel 版本
    // =========================================================================
    if (!prop.cooperativeLaunch) {
        printf("[B] skipped: device does not support cooperative launch.\n");
    } else {
        // cooperative launch 要求所有 block 同時常駐，因此 grid 上限由 occupancy 決定
        int blocks_per_sm = 0;
        CUDA_CHECK(cudaOccupancyMaxActiveBlocksPerMultiprocessor(
            &blocks_per_sm, kernel_sum_gridsync, kBlockSize, 0));
        int grid_size = blocks_per_sm * prop.multiProcessorCount;
        size_t need = (n + kBlockSize - 1) / kBlockSize;
        if (static_cast<size_t>(grid_size) > need) grid_size = static_cast<int>(need);
        if (grid_size < 1) grid_size = 1;
        // Phase 2 用一個 block 掃 partial[]，這裡不限制 grid_size 上限，
        // 因為 block 0 內部已用 stride loop 處理任意長度。

        CUDA_CHECK(cudaMalloc(&d_partial, grid_size * sizeof(float)));
        CUDA_CHECK(cudaMemset(d_result, 0, sizeof(float)));

        void *args[] = { (void *)&d_mat, (void *)&n,
                         (void *)&d_partial, (void *)&d_result };
        CUDA_CHECK(cudaLaunchCooperativeKernel(
            (void *)kernel_sum_gridsync,
            dim3(grid_size), dim3(kBlockSize),
            args, /*sharedMem=*/0, /*stream=*/0));
        CUDA_CHECK(cudaDeviceSynchronize());

        float gpu_sum = 0.0f;
        CUDA_CHECK(cudaMemcpy(&gpu_sum, d_result, sizeof(float),
                              cudaMemcpyDeviceToHost));

        double tol = fabs(ref) * 1e-4 + 1e-3;
        printf("[B] grid.sync() single-kernel     (grid = %d blocks x %d threads)\n",
               grid_size, kBlockSize);
        printf("    GPU = %.6f  CPU = %.6f  -> %s\n\n",
               gpu_sum, ref,
               (fabs(gpu_sum - ref) <= tol) ? "PASS" : "FAIL");
    }

    // ---------------- 清理 ----------------
    if (d_partial) CUDA_CHECK(cudaFree(d_partial));
    CUDA_CHECK(cudaFree(d_result));
    CUDA_CHECK(cudaFree(d_mat));
    free(h_mat);
    return EXIT_SUCCESS;
}
