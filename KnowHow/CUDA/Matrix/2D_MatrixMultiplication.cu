#include <iostream>
#include <iomanip>
#include <chrono>
#include <cuda_runtime.h>

// 定義矩陣大小與 Tile 大小
const int MATRIX_SIZE = 128; // 矩陣大小為 1024 x 1024
const int TILE_SIZE = 32;     // Shared memory 的 Tile 大小為 32 x 32

// 檢查 CUDA 錯誤的輔助函式
void checkCudaError(cudaError_t err, const char* msg) {
    if (err != cudaSuccess) {
        std::cerr << "CUDA Error at " << msg << ": " << cudaGetErrorString(err) << std::endl;
        exit(EXIT_FAILURE);
    }
}

// 1. CPU 矩陣乘法 (基準點)
void matrixMulCPU(const float* A, const float* B, float* C, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < N; ++k) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}

// 2. GPU Global Memory 矩陣乘法
__global__ void matrixMulGlobalKernel(const float* A, const float* B, float* C, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; ++k) {
            sum += A[row * N + k] * B[k * N + col];
        }
        C[row * N + col] = sum;
    }
}

// 3. GPU Shared Memory 矩陣乘法 (Tiled)
__global__ void matrixMulSharedKernel(const float* A, const float* B, float* C, int N) {
    // 分配共享記憶體
    __shared__ float s_A[TILE_SIZE][TILE_SIZE + 1];
    __shared__ float s_B[TILE_SIZE][TILE_SIZE + 1];

    int bx = blockIdx.x;  int by = blockIdx.y;
    int tx = threadIdx.x; int ty = threadIdx.y;

    int row = by * TILE_SIZE + ty;
    int col = bx * TILE_SIZE + tx;

    float sum = 0.0f;

    // 循序將矩陣切成多個 Tile 並載入 Shared Memory
    for (int m = 0; m < (N + TILE_SIZE - 1) / TILE_SIZE; ++m) {
        // 載入 A 矩陣的 Tile 到 Shared Memory (考慮邊界條件)
        if (row < N && (m * TILE_SIZE + tx) < N) {
            s_A[ty][tx] = A[row * N + m * TILE_SIZE + tx];
        }
        else {
            s_A[ty][tx] = 0.0f;
        }

        // 載入 B 矩陣的 Tile 到 Shared Memory
        if ((m * TILE_SIZE + ty) < N && col < N) {
            s_B[ty][tx] = B[(m * TILE_SIZE + ty) * N + col];
        }
        else {
            s_B[ty][tx] = 0.0f;
        }

        // 同步確保整個 Block 的執行緒都已將資料載入完畢
        __syncthreads();

        // 利用 Shared Memory 計算部分乘積
        for (int k = 0; k < TILE_SIZE; ++k) {
            sum += s_A[ty][k] * s_B[k][tx];
        }

        // 同步確保下一輪載入前，當前的 Shared Memory 資料已使用完畢
        __syncthreads();
    }

    // 將結果寫回 Global Memory
    if (row < N && col < N) {
        C[row * N + col] = sum;
    }
}

int main() {
    int N = MATRIX_SIZE;
    size_t size = N * N * sizeof(float);

    // 打印矩陣大小與 Tile 大小
    std::cout << "- Matrix Size: " << N << " x " << N << std::endl;
    std::cout << "- Tile Size  : " << TILE_SIZE << " x " << TILE_SIZE << std::endl;

    // 配置 Host 記憶體
    float* h_A = (float*)malloc(size);
    float* h_B = (float*)malloc(size);
    float* h_C_CPU = (float*)malloc(size);
    float* h_C_Global = (float*)malloc(size);
    float* h_C_Shared = (float*)malloc(size);

    // 初始化矩陣
    for (int i = 0; i < N * N; ++i) {
        h_A[i] = static_cast<float>(rand()) / RAND_MAX;
        h_B[i] = static_cast<float>(rand()) / RAND_MAX;
    }

#if 0
    // --- CPU 計算 ---
    auto start_cpu = std::chrono::high_resolution_clock::now();
    matrixMulCPU(h_A, h_B, h_C_CPU, N);
    auto end_cpu = std::chrono::high_resolution_clock::now();
    double time_cpu = std::chrono::duration<double, std::milli>(end_cpu - start_cpu).count();
#endif

    // 配置 Device 記憶體
    float* d_A, * d_B, * d_C;
    checkCudaError(cudaMalloc(&d_A, size), "cudaMalloc d_A");
    checkCudaError(cudaMalloc(&d_B, size), "cudaMalloc d_B");
    checkCudaError(cudaMalloc(&d_C, size), "cudaMalloc d_C");

    // 複製資料到 Device
    checkCudaError(cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice), "cudaMemcpy h_A");
    checkCudaError(cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice), "cudaMemcpy h_B");

    // 定義 Thread Block 和 Grid 维度
    dim3 dimBlock(TILE_SIZE, TILE_SIZE);
    dim3 dimGrid((N + TILE_SIZE - 1) / TILE_SIZE, (N + TILE_SIZE - 1) / TILE_SIZE);

    // CUDA Event 用於精準測量 GPU 時間
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    float time_global = 0.0f;
    float time_shared = 0.0f;

    // --- GPU Global Memory 計算 ---
    cudaEventRecord(start);
    matrixMulGlobalKernel << <dimGrid, dimBlock >> > (d_A, d_B, d_C, N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&time_global, start, stop);
    checkCudaError(cudaMemcpy(h_C_Global, d_C, size, cudaMemcpyDeviceToHost), "cudaMemcpy h_C_Global");

    // --- GPU Shared Memory 計算 ---
    // 清空重置輸出記憶體
    cudaMemset(d_C, 0, size);

    cudaEventRecord(start);
    matrixMulSharedKernel << <dimGrid, dimBlock >> > (d_A, d_B, d_C, N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&time_shared, start, stop);
    checkCudaError(cudaMemcpy(h_C_Shared, d_C, size, cudaMemcpyDeviceToHost), "cudaMemcpy h_C_Shared");

    // 驗證 GPU 結果是否正確 (與 CPU 比對)
    bool correct = true;
    for (int i = 0; i < N * N; ++i) {
        if (abs(h_C_Global[i] - h_C_Shared[i]) > 1e-2) {
            correct = false;
            break;
        }
    }

    // --- 打印結果與效能比較 ---
    std::cout << std::fixed << std::setprecision(3);
    //std::cout << "- CPU               : " << time_cpu << " ms" << std::endl;
    std::cout << "- GPU Global Memory : " << time_global << " ms" << std::endl;
    std::cout << "- GPU Shared Memory : " << time_shared << " ms" << std::endl;

    //std::cout << "- GPU Global vs CPU          : " << (time_cpu / time_global) << " 倍加速" << std::endl;
    //std::cout << "- GPU Shared vs CPU          : " << (time_cpu / time_shared) << " 倍加速" << std::endl;
    std::cout << "- GPU Shared vs GPU Global   : " << (time_global / time_shared) << " x" << std::endl;

    std::cout << "\n結果驗證 : " << (correct ? "成功 (PASS)" : "失敗 (FAIL)") << std::endl;

    // 釋放資源
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    free(h_A); free(h_B); free(h_C_CPU); free(h_C_Global); free(h_C_Shared);

    return 0;
}
