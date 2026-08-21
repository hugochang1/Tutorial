#include <iostream>
#include <iomanip>
#include <chrono>
#include <cmath>
#include <cuda_runtime.h>

#define CHECK_CUDA(call)                                                      \
    do {                                                                      \
        cudaError_t err = call;                                               \
        if (err != cudaSuccess) {                                             \
            std::cerr << "CUDA Error: " << cudaGetErrorString(err)            \
                      << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
            exit(EXIT_FAILURE);                                               \
        }                                                                     \
    } while (0)

constexpr int ROWS = 128;
constexpr int COLS = 128;
constexpr int BLOCK_DIM_X = 32;
constexpr int BLOCK_DIM_Y = 32;

// 1. CPU 版本
void matrixAddCPU(const float* A, const float* B, float* C, int rows, int cols) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int idx = r * cols + c;
            C[idx] = A[idx] + B[idx];
        }
    }
}

// 2. GPU Global Memory 存取版本
__global__ void matrixAddGlobalKernel(const float* A, const float* B, float* C, int rows, int cols) {
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;

    if (row < rows && col < cols) {
        int idx = row * cols + col;
        C[idx] = A[idx] + B[idx];
    }
}

// 3. GPU Shared Memory 版本
__global__ void matrixAddSharedKernel(const float* A, const float* B, float* C, int rows, int cols) {
    __shared__ float s_A[BLOCK_DIM_Y][BLOCK_DIM_X];
    __shared__ float s_B[BLOCK_DIM_Y][BLOCK_DIM_X];

    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int tx = threadIdx.x;
    int ty = threadIdx.y;

    // 將 Global Memory 載入至 Shared Memory
    if (row < rows && col < cols) {
        int idx = row * cols + col;
        s_A[ty][tx] = A[idx];
        s_B[ty][tx] = B[idx];
    } else {
        s_A[ty][tx] = 0.0f;
        s_B[ty][tx] = 0.0f;
    }

    __syncthreads();

    // 在 Shared Memory 進行運算並寫回 Global Memory
    if (row < rows && col < cols) {
        int idx = row * cols + col;
        C[idx] = s_A[ty][tx] + s_B[ty][tx];
    }
}

// 結果驗證
bool verifyResult(const float* ref, const float* target, int size, float tol = 1e-4f) {
    for (int i = 0; i < size; ++i) {
        if (std::fabs(ref[i] - target[i]) > tol) {
            return false;
        }
    }
    return true;
}

int main() {
    int deviceId = 0;
    CHECK_CUDA(cudaGetDevice(&deviceId));

    cudaDeviceProp prop;
    CHECK_CUDA(cudaGetDeviceProperties(&prop, deviceId));
    std::cout << "GPU Device: " << prop.name << "\n";
    std::cout << "Matrix Size: " << ROWS << " x " << COLS 
              << " (" << (static_cast<size_t>(ROWS) * COLS * sizeof(float)) / (1024 * 1024) << " MB per matrix)\n\n";

    size_t totalElements = static_cast<size_t>(ROWS) * COLS;
    size_t totalBytes = totalElements * sizeof(float);

    // 使用 cudaMallocManaged 配置 Unified Memory
    float *A = nullptr, *B = nullptr;
    float *C_cpu = nullptr, *C_global = nullptr, *C_shared = nullptr;

    CHECK_CUDA(cudaMallocManaged(&A, totalBytes));
    CHECK_CUDA(cudaMallocManaged(&B, totalBytes));
    CHECK_CUDA(cudaMallocManaged(&C_cpu, totalBytes));
    CHECK_CUDA(cudaMallocManaged(&C_global, totalBytes));
    CHECK_CUDA(cudaMallocManaged(&C_shared, totalBytes));

    // 初始化資料
    for (size_t i = 0; i < totalElements; ++i) {
        A[i] = static_cast<float>(i % 100) * 0.1f;
        B[i] = static_cast<float>(i % 50) * 0.2f;
    }

    // -------------------------------------------------------------
    // 1. CPU 測試
    // -------------------------------------------------------------
    auto cpuStart = std::chrono::high_resolution_clock::now();
    matrixAddCPU(A, B, C_cpu, ROWS, COLS);
    auto cpuEnd = std::chrono::high_resolution_clock::now();
    double cpuLatencyMs = std::chrono::duration<double, std::milli>(cpuEnd - cpuStart).count();

    // -------------------------------------------------------------
    // 設置 GPU Grid 與 Block 維度
    // -------------------------------------------------------------
    dim3 block(BLOCK_DIM_X, BLOCK_DIM_Y);
    dim3 grid((COLS + block.x - 1) / block.x, (ROWS + block.y - 1) / block.y);

    cudaEvent_t start, stop;
    CHECK_CUDA(cudaEventCreate(&start));
    CHECK_CUDA(cudaEventCreate(&stop));

    // Warm-up
    matrixAddGlobalKernel<<<grid, block>>>(A, B, C_global, ROWS, COLS);
    CHECK_CUDA(cudaDeviceSynchronize());

    // -------------------------------------------------------------
    // 2. GPU Global Memory 測試
    // -------------------------------------------------------------
    CHECK_CUDA(cudaEventRecord(start));
    matrixAddGlobalKernel<<<grid, block>>>(A, B, C_global, ROWS, COLS);
    CHECK_CUDA(cudaEventRecord(stop));
    CHECK_CUDA(cudaEventSynchronize(stop));

    float gpuGlobalLatencyMs = 0.0f;
    CHECK_CUDA(cudaEventElapsedTime(&gpuGlobalLatencyMs, start, stop));

    // -------------------------------------------------------------
    // 3. GPU Shared Memory 測試
    // -------------------------------------------------------------
    CHECK_CUDA(cudaEventRecord(start));
    matrixAddSharedKernel<<<grid, block>>>(A, B, C_shared, ROWS, COLS);
    CHECK_CUDA(cudaEventRecord(stop));
    CHECK_CUDA(cudaEventSynchronize(stop));

    float gpuSharedLatencyMs = 0.0f;
    CHECK_CUDA(cudaEventElapsedTime(&gpuSharedLatencyMs, start, stop));

    // 同步並驗證結果
    CHECK_CUDA(cudaDeviceSynchronize());
    bool globalValid = verifyResult(C_cpu, C_global, totalElements);
    bool sharedValid = verifyResult(C_cpu, C_shared, totalElements);

    // -------------------------------------------------------------
    // 輸出結果與倍數計算
    // -------------------------------------------------------------
    double speedupGlobal = cpuLatencyMs / gpuGlobalLatencyMs;
    double speedupShared = cpuLatencyMs / gpuSharedLatencyMs;

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "================== Execution Results ==================\n";
    std::cout << "1. CPU Latency           : " << cpuLatencyMs << " ms\n";
    std::cout << "2. GPU Global Latency    : " << gpuGlobalLatencyMs << " ms (Valid: " 
              << (globalValid ? "PASSED" : "FAILED") << ")\n";
    std::cout << "3. GPU Shared Latency    : " << gpuSharedLatencyMs << " ms (Valid: " 
              << (sharedValid ? "PASSED" : "FAILED") << ")\n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << "Speedup (GPU Global / CPU) : " << speedupGlobal << " x\n";
    std::cout << "Speedup (GPU Shared / CPU) : " << speedupShared << " x\n";
    std::cout << "=======================================================\n";

    // 釋放資源
    CHECK_CUDA(cudaEventDestroy(start));
    CHECK_CUDA(cudaEventDestroy(stop));
    CHECK_CUDA(cudaFree(A));
    CHECK_CUDA(cudaFree(B));
    CHECK_CUDA(cudaFree(C_cpu));
    CHECK_CUDA(cudaFree(C_global));
    CHECK_CUDA(cudaFree(C_shared));

    return 0;
}
