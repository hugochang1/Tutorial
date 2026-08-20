#include <iostream>
#include <chrono>
#include <cmath>
#include <cuda_runtime.h>

#define N 4096 // 矩陣大小為 4096 x 4096 (約 1600 萬個元素)
#define BLOCK_SIZE 16 // 執行緒區塊大小 (16x16)

// 1. CPU 版本 (序列轉置)
void matrixTransposeCPU(float* in, float* out, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out[j * n + i] = in[i * n + j];
        }
    }
}

// 2. GPU Global Memory 版本 (因非合併寫入，效能較差)
__global__ void matrixTransposeGlobal(float* in, float* out, int n) {
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;

    if (row < n && col < n) {
        // 讀取是連續的 (Coalesced)，但寫入到 out 是跨步的 (Non-coalesced)
        out[col * n + row] = in[row * n + col];
    }
}

// 3. GPU Shared Memory 版本 (利用 Shared Memory 重新排列，達到完美合併存取)
// 為了避免 Shared Memory Bank Conflict，將欄位大小加 1 (BLOCK_SIZE + 1)
__global__ void matrixTransposeShared(float* in, float* out, int n) {
    // 宣告 Shared Memory 區塊 (加上1 可以有效避免 Bank Conflict)
    __shared__ float tile[BLOCK_SIZE][BLOCK_SIZE + 1];

    // 計算原本在輸入矩陣中的座標
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;

    // 將資料連續地從 Global Memory 讀入到 Shared Memory 中
    if (row < n && col < n) {
        tile[threadIdx.y][threadIdx.x] = in[row * n + col];
    }

    // 必須同步，確保整個區塊的 Thread 都把資料寫入 Shared Memory 了
    __syncthreads();

    // 重新計算輸出矩陣的座標 (轉置區塊的對調)
    int new_col = blockIdx.y * blockDim.x + threadIdx.x;
    int new_row = blockIdx.x * blockDim.y + threadIdx.y;

    // 從 Shared Memory 讀取時對調索引，寫回 Global Memory 時又是連續寫入！
    if (new_row < n && new_col < n) {
        out[new_row * n + new_col] = tile[threadIdx.x][threadIdx.y];
    }
}

int main() {
    size_t size = (size_t)N * N * sizeof(float);

    std::cout << "矩陣大小: " << N << " x " << N << " (" << (size / (1024 * 1024)) << " MB)\n\n";

    // 配置主機 (CPU) 記憶體
    float* h_in = (float*)malloc(size);
    float* h_out_CPU = (float*)malloc(size);
    float* h_out_GPU_G = (float*)malloc(size);
    float* h_out_GPU_S = (float*)malloc(size);

    // 初始化資料
    for (int i = 0; i < N * N; ++i) {
        h_in[i] = (float)i;
    }

    // 配置裝置 (GPU) 記憶體
    float* d_in, * d_out;
    cudaMalloc(&d_in, size);
    cudaMalloc(&d_out, size);

    // 將原始資料複製到 GPU
    cudaMemcpy(d_in, h_in, size, cudaMemcpyHostToDevice);

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
    matrixTransposeCPU(h_in, h_out_CPU, N);
    auto cpu_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> cpu_duration = cpu_end - cpu_start;
    std::cout << "1. CPU 執行時間: " << cpu_duration.count() << " ms\n";

    // ==========================================
    // 測試 2：GPU Global Memory 版本計時
    // ==========================================
    // 清空輸出記憶體，確保測試乾淨
    cudaMemset(d_out, 0, size);

    cudaEventRecord(start);
    matrixTransposeGlobal << <dimGrid, dimBlock >> > (d_in, d_out, N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&gpu_time, start, stop);
    std::cout << "2. GPU Global Memory 執行時間: " << gpu_time << " ms\n";

    // 將結果傳回主機
    cudaMemcpy(h_out_GPU_G, d_out, size, cudaMemcpyDeviceToHost);

    // ==========================================
    // 測試 3：GPU Shared Memory 版本計時
    // ==========================================
    // 清空輸出記憶體，確保測試乾淨
    cudaMemset(d_out, 0, size);

    cudaEventRecord(start);
    matrixTransposeShared << <dimGrid, dimBlock >> > (d_in, d_out, N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&gpu_time, start, stop);
    std::cout << "3. GPU Shared Memory 執行時間: " << gpu_time << " ms\n";

    // 將結果傳回主機
    cudaMemcpy(h_out_GPU_S, d_out, size, cudaMemcpyDeviceToHost);

    // ==========================================
    // 驗證正確性 (Verification)
    // ==========================================
    bool correct_global = true;
    bool correct_shared = true;
    float epsilon = 1e-5f; // 浮點數容許誤差值

    for (int i = 0; i < N * N; ++i) {
        // 驗證 Global Memory 版本
        if (std::abs(h_out_CPU[i] - h_out_GPU_G[i]) > epsilon) {
            correct_global = false;
            std::cout << "⚠️ Global Memory 錯誤在索引 " << i
                << " -> CPU: " << h_out_CPU[i]
                << ", GPU_G: " << h_out_GPU_G[i] << "\n";
            break;
        }
        // 驗證 Shared Memory 版本
        if (std::abs(h_out_CPU[i] - h_out_GPU_S[i]) > epsilon) {
            correct_shared = false;
            std::cout << "⚠️ Shared Memory 錯誤在索引 " << i
                << " -> CPU: " << h_out_CPU[i]
                << ", GPU_S: " << h_out_GPU_S[i] << "\n";
            break;
        }
    }

    // 輸出最終驗證結果
    std::cout << "\n==========================================\n";
    if (correct_global) {
        std::cout << "[PASS] GPU Global Memory 版本結果完全正確！\n";
    }
    else {
        std::cout << "[FAIL] GPU Global Memory 版本結果錯誤。\n";
    }

    if (correct_shared) {
        std::cout << "[PASS] GPU Shared Memory 版本結果完全正確！\n";
    }
    else {
        std::cout << "[FAIL] GPU Shared Memory 版本結果錯誤。\n";
    }
    std::cout << "==========================================\n";

    // 釋放資源與記憶體
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaFree(d_in);
    cudaFree(d_out);
    free(h_in);
    free(h_out_CPU);
    free(h_out_GPU_G);
    free(h_out_GPU_S);

    return 0;
}
/*
2D Matrix Transpose Performance result
矩陣大小: 4096 x 4096 (64 MB)

1. CPU 執行時間: 104.884 ms
2. GPU Global Memory 執行時間: 2.65606 ms
3. GPU Shared Memory 執行時間: 4.0713 ms

==========================================
[PASS] GPU Global Memory 版本結果完全正確！
[PASS] GPU Shared Memory 版本結果完全正確！
==========================================
*/
