#include <iostream>
#include <chrono>
#include <cuda_runtime.h>

#define N 4096 // 矩陣大小為 4096 x 4096
#define BLOCK_SIZE 16 // 執行緒區塊大小 (16x16)

// 1. CPU 版本
void matrixAddCPU(float* A, float* B, float* C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int idx = i * n + j;
            C[idx] = A[idx] + B[idx];
        }
    }
}

// 2. GPU Global Memory 版本
__global__ void matrixAddGlobal(float* A, float* B, float* C, int n) {
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;

    if (row < n && col < n) {
        int idx = row * n + col;
        C[idx] = A[idx] + B[idx];
    }
}

// 3. GPU Shared Memory 版本
__global__ void matrixAddShared(float* A, float* B, float* C, int n) {
    // 宣告 Shared Memory 空間
    __shared__ float s_A[BLOCK_SIZE][BLOCK_SIZE];
    __shared__ float s_B[BLOCK_SIZE][BLOCK_SIZE];

    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;

    int tx = threadIdx.x;
    int ty = threadIdx.y;

    // 將資料從 Global Memory 載入到 Shared Memory
    if (row < n && col < n) {
        int idx = row * n + col;
        s_A[ty][tx] = A[idx];
        s_B[ty][tx] = B[idx];
    }
    else {
        s_A[ty][tx] = 0.0f;
        s_B[ty][tx] = 0.0f;
    }

    // 同步區塊內所有執行緒，確保資料都已寫入 Shared Memory
    __syncthreads();

    // 從 Shared Memory 讀取並計算，寫回 Global Memory
    if (row < n && col < n) {
        int idx = row * n + col;
        C[idx] = s_A[ty][tx] + s_B[ty][tx];
    }
}

int main() {
    int size = N * N * sizeof(float);

    // 配置主機 (CPU) 記憶體
    float* h_A = (float*)malloc(size);
    float* h_B = (float*)malloc(size);
    float* h_C_CPU = (float*)malloc(size);
    float* h_C_GPU_G = (float*)malloc(size);
    float* h_C_GPU_S = (float*)malloc(size);

    // 初始化資料
    for (int i = 0; i < N * N; ++i) {
        h_A[i] = 1.0f;
        h_B[i] = 2.0f;
    }

    // 配置裝置 (GPU) 記憶體
    float* d_A, * d_B, * d_C;
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    // 將資料複製到 GPU
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // 設定 CUDA 網格與區塊維度
    dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
    dim3 dimGrid((N + BLOCK_SIZE - 1) / BLOCK_SIZE, (N + BLOCK_SIZE - 1) / BLOCK_SIZE);

    // CUDA Timer 設定
    cudaEvent_t start, stop;
    float gpu_time = 0.0f;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // ==========================================
    // 測試 1：CPU 版本計時
    // ==========================================
    auto cpu_start = std::chrono::high_resolution_clock::now();
    matrixAddCPU(h_A, h_B, h_C_CPU, N);
    auto cpu_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> cpu_duration = cpu_end - cpu_start;
    std::cout << "CPU Time: " << cpu_duration.count() << " ms\n";

    // ==========================================
    // 測試 2：GPU Global Memory 版本計時
    // ==========================================
    cudaEventRecord(start);
    matrixAddGlobal << <dimGrid, dimBlock >> > (d_A, d_B, d_C, N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&gpu_time, start, stop);
    std::cout << "GPU Global Memory Time: " << gpu_time << " ms\n";
    cudaMemcpy(h_C_GPU_G, d_C, size, cudaMemcpyDeviceToHost);

    // ==========================================
    // 測試 3：GPU Shared Memory 版本計時
    // ==========================================
    cudaEventRecord(start);
    matrixAddShared << <dimGrid, dimBlock >> > (d_A, d_B, d_C, N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&gpu_time, start, stop);
    std::cout << "GPU Shared Memory Time: " << gpu_time << " ms\n";
    cudaMemcpy(h_C_GPU_S, d_C, size, cudaMemcpyDeviceToHost);

    // 釋放記憶體
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(h_A); free(h_B); free(h_C_CPU); free(h_C_GPU_G); free(h_C_GPU_S);

    return 0;
}
/*
2D Matrix Addition Performance Test
CPU Time: 41.7484 ms
GPU Global Memory Time: 3.53245 ms
GPU Shared Memory Time: 5.0289 ms
*/
