#include <iostream>
#include <vector>
#include <cuda_runtime.h>

// 檢查 CUDA 錯誤的巨集
#define CHECK_CUDA(call) { \
    cudaError_t err = call; \
    if (err != cudaSuccess) { \
        std::cerr << "CUDA Error: " << cudaGetErrorString(err) << " at line " << __LINE__ << std::endl; \
        exit(EXIT_FAILURE); \
    } \
}

// CUDA Kernel: 每個 Block 使用共用記憶體進行區域歸約 (Reduction)
__global__ void matrixSumKernel(const float* d_mat, float* d_block_sums, int total_elements) {
    //宣告動態共用記憶體
    extern __shared__ float sdata[];

    int tid = threadIdx.x;
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    printf("tid=%d idx=%d\n", tid, idx);

    // 載入資料至共用記憶體，若超出範圍則補 0
    sdata[tid] = (idx < total_elements) ? d_mat[idx] : 0.0f;
    __syncthreads();

    // 樹狀歸約 (Tree-based reduction) 於共用記憶體中進行
    for (unsigned int s = blockDim.x / 2; s > 0; s >>= 1) {
        if (tid < s) {
            printf("  tid=%d idx=%d s=%d (tid+s)=%d sdata[tid]=%f sdata[tid+s]=%f\n",
                tid, idx, s, tid+s, sdata[tid], sdata[tid+s]);
            sdata[tid] += sdata[tid + s];
        }
        __syncthreads();
    }

    // 每個 Block 將其總和寫入該 Block 對應的輸出位置
    if (tid == 0) {
        d_block_sums[blockIdx.x] = sdata[0];
    }
}

int main() {
    int rows = 32;
    int cols = 1;
    int total_elements = rows * cols;
    size_t size_bytes = total_elements * sizeof(float);

    // 1. 初始化主機端 (Host) 記憶體與資料
    std::vector<float> h_mat(total_elements, 1.0f); // 每個元素設為 1.0，方便驗證總和應為 total_elements
    float h_total_sum = 0.0f;

    // 2. 配置裝置端 (Device) 記憶體
    float *d_mat = nullptr;
    float *d_block_sums = nullptr;

    int threadsPerBlock = 16;
    int blocksPerGrid = (total_elements + threadsPerBlock - 1) / threadsPerBlock;

    CHECK_CUDA(cudaMalloc(&d_mat, size_bytes));
    CHECK_CUDA(cudaMalloc(&d_block_sums, blocksPerGrid * sizeof(float)));

    // 3. 將資料從 Host 複製到 Device
    CHECK_CUDA(cudaMemcpy(d_mat, h_mat.data(), size_bytes, cudaMemcpyHostToDevice));

    // 4. 執行第一階段 Kernel (計算每個 Block 的總和)
    size_t sharedMemSize = threadsPerBlock * sizeof(float);
    matrixSumKernel<<<blocksPerGrid, threadsPerBlock, sharedMemSize>>>(d_mat, d_block_sums, total_elements);
    CHECK_CUDA(cudaGetLastError());

    // 5. 若有超過 1 個 Block，將結果抓回 CPU 做最後加總 (或者再寫一個小 Kernel 歸約)
    std::vector<float> h_block_sums(blocksPerGrid);
    CHECK_CUDA(cudaMemcpy(h_block_sums.data(), d_block_sums, blocksPerGrid * sizeof(float), cudaMemcpyDeviceToHost));

    for (int i = 0; i < blocksPerGrid; ++i) {
        h_total_sum += h_block_sums[i];
    }

    // 6. 輸出結果
    std::cout << "矩陣總元素個數: " << total_elements << std::endl;
    std::cout << "GPU 計算矩陣元素總和: " << h_total_sum << std::endl;

    // 7. 釋放記憶體
    CHECK_CUDA(cudaFree(d_mat));
    CHECK_CUDA(cudaFree(d_block_sums));

    return 0;
}

/*
tid=0 idx=0
tid=1 idx=1
tid=2 idx=2
tid=3 idx=3
tid=4 idx=4
tid=5 idx=5
tid=6 idx=6
tid=7 idx=7
tid=8 idx=8
tid=9 idx=9
tid=10 idx=10
tid=11 idx=11
tid=12 idx=12
tid=13 idx=13
tid=14 idx=14
tid=15 idx=15
  tid=0 idx=0 s=8 (tid+s)=8 sdata[tid]=1.000000 sdata[tid+s]=1.000000
  tid=1 idx=1 s=8 (tid+s)=9 sdata[tid]=1.000000 sdata[tid+s]=1.000000
  tid=2 idx=2 s=8 (tid+s)=10 sdata[tid]=1.000000 sdata[tid+s]=1.000000
  tid=3 idx=3 s=8 (tid+s)=11 sdata[tid]=1.000000 sdata[tid+s]=1.000000
  tid=4 idx=4 s=8 (tid+s)=12 sdata[tid]=1.000000 sdata[tid+s]=1.000000
  tid=5 idx=5 s=8 (tid+s)=13 sdata[tid]=1.000000 sdata[tid+s]=1.000000
  tid=6 idx=6 s=8 (tid+s)=14 sdata[tid]=1.000000 sdata[tid+s]=1.000000
  tid=7 idx=7 s=8 (tid+s)=15 sdata[tid]=1.000000 sdata[tid+s]=1.000000
  tid=0 idx=0 s=4 (tid+s)=4 sdata[tid]=2.000000 sdata[tid+s]=2.000000
  tid=1 idx=1 s=4 (tid+s)=5 sdata[tid]=2.000000 sdata[tid+s]=2.000000
  tid=2 idx=2 s=4 (tid+s)=6 sdata[tid]=2.000000 sdata[tid+s]=2.000000
  tid=3 idx=3 s=4 (tid+s)=7 sdata[tid]=2.000000 sdata[tid+s]=2.000000
  tid=0 idx=0 s=2 (tid+s)=2 sdata[tid]=4.000000 sdata[tid+s]=4.000000
  tid=1 idx=1 s=2 (tid+s)=3 sdata[tid]=4.000000 sdata[tid+s]=4.000000
  tid=0 idx=0 s=1 (tid+s)=1 sdata[tid]=8.000000 sdata[tid+s]=8.000000
tid=0 idx=16
tid=1 idx=17
tid=2 idx=18
tid=3 idx=19
tid=4 idx=20
tid=5 idx=21
tid=6 idx=22
tid=7 idx=23
tid=8 idx=24
tid=9 idx=25
tid=10 idx=26
tid=11 idx=27
tid=12 idx=28
tid=13 idx=29
tid=14 idx=30
tid=15 idx=31
  tid=0 idx=16 s=8 (tid+s)=8 sdata[tid]=1.000000 sdata[tid+s]=1.000000
  tid=1 idx=17 s=8 (tid+s)=9 sdata[tid]=1.000000 sdata[tid+s]=1.000000
  tid=2 idx=18 s=8 (tid+s)=10 sdata[tid]=1.000000 sdata[tid+s]=1.000000
  tid=3 idx=19 s=8 (tid+s)=11 sdata[tid]=1.000000 sdata[tid+s]=1.000000
  tid=4 idx=20 s=8 (tid+s)=12 sdata[tid]=1.000000 sdata[tid+s]=1.000000
  tid=5 idx=21 s=8 (tid+s)=13 sdata[tid]=1.000000 sdata[tid+s]=1.000000
  tid=6 idx=22 s=8 (tid+s)=14 sdata[tid]=1.000000 sdata[tid+s]=1.000000
  tid=7 idx=23 s=8 (tid+s)=15 sdata[tid]=1.000000 sdata[tid+s]=1.000000
  tid=0 idx=16 s=4 (tid+s)=4 sdata[tid]=2.000000 sdata[tid+s]=2.000000
  tid=1 idx=17 s=4 (tid+s)=5 sdata[tid]=2.000000 sdata[tid+s]=2.000000
  tid=2 idx=18 s=4 (tid+s)=6 sdata[tid]=2.000000 sdata[tid+s]=2.000000
  tid=3 idx=19 s=4 (tid+s)=7 sdata[tid]=2.000000 sdata[tid+s]=2.000000
  tid=0 idx=16 s=2 (tid+s)=2 sdata[tid]=4.000000 sdata[tid+s]=4.000000
  tid=1 idx=17 s=2 (tid+s)=3 sdata[tid]=4.000000 sdata[tid+s]=4.000000
  tid=0 idx=16 s=1 (tid+s)=1 sdata[tid]=8.000000 sdata[tid+s]=8.000000
矩陣總元素個數: 32
GPU 計算矩陣元素總和: 32
*/
