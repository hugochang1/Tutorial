#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

// 定義 TILE 大小
#define TILE_DIM 16

// 1. 全域記憶體轉置（Global Memory Access）
__global__ void transposeGlobal(float* out, const float* in, int width, int height) {
    int x = blockIdx.x * TILE_DIM + threadIdx.x;
    int y = blockIdx.y * TILE_DIM + threadIdx.y;

    if (x < width && y < height) {
        out[x * height + y] = in[y * width + x];
    }
}

// 2. 共享記憶體轉置（Shared Memory Access）
__global__ void transposeShared(float* out, const float* in, int width, int height) {
    __shared__ float tile[TILE_DIM][TILE_DIM];

    int x = blockIdx.x * TILE_DIM + threadIdx.x;
    int y = blockIdx.y * TILE_DIM + threadIdx.y;

    if (x < width && y < height) {
        tile[threadIdx.y][threadIdx.x] = in[y * width + x];
    }

    __syncthreads();

    x = blockIdx.y * TILE_DIM + threadIdx.x;
    y = blockIdx.x * TILE_DIM + threadIdx.y;

    if (x < height && y < width) {
        out[y * height + x] = tile[threadIdx.x][threadIdx.y];
    }
}

int main() {
    const int width = 1024 * 1;
    const int height = 1024 * 1;
    const int size = width * height;
    const size_t bytes = size * sizeof(float);

    float* h_in = (float*)malloc(bytes);
    float* h_out = (float*)malloc(bytes);
    for (int i = 0; i < size; i++) {
        h_in[i] = (float)i;
    }

    float* d_in, * d_out;
    cudaMalloc(&d_in, bytes);
    cudaMalloc(&d_out, bytes);
    cudaMemcpy(d_in, h_in, bytes, cudaMemcpyHostToDevice);

    dim3 dimBlock(TILE_DIM, TILE_DIM);
    dim3 dimGrid((width + TILE_DIM - 1) / TILE_DIM, (height + TILE_DIM - 1) / TILE_DIM);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    float time_global = 0.0f;
    float time_shared = 0.0f;

    printf("==========================================\n");
    printf("Matrix Size : %d x %d\n", width, height);
    printf("Tile Dimension: %d x %d\n", TILE_DIM, TILE_DIM);
    printf("Grid Size     : %d x %d\n", dimGrid.x, dimGrid.y);
    printf("Block Size    : %d x %d\n", dimBlock.x, dimBlock.y);

    // ==========================================
    // 測試一：測試 Global Memory 版本
    // ==========================================
    cudaEventRecord(start);
    transposeGlobal << <dimGrid, dimBlock >> > (d_out, d_in, width, height);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&time_global, start, stop);
    printf("Global Memory Transpose Time: %f ms\n", time_global);

    // ==========================================
    // 測試二：測試 Shared Memory 版本
    // ==========================================
    cudaEventRecord(start);
    transposeShared << <dimGrid, dimBlock >> > (d_out, d_in, width, height);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&time_shared, start, stop);
    printf("Shared Memory Transpose Time: %f ms\n", time_shared);

    // 💡 新增：計算並打印執行時間倍數
    float speedup = time_global / time_shared;
    printf("Speedup (Global / Shared)   : %.2f x\n", speedup);

    // 4. 驗證資料正確性
    cudaMemcpy(h_out, d_out, bytes, cudaMemcpyDeviceToHost);
    bool success = true;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (h_out[x * height + y] != h_in[y * width + x]) {
                success = false;
                break;
            }
        }
    }
    printf("Verification result         : %s\n", success ? "PASS" : "FAIL");
    printf("==========================================\n");

    // 5. 釋放資源
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaFree(d_in);
    cudaFree(d_out);
    free(h_in);
    free(h_out);

    return 0;
}
/*

==========================================
Matrix Size : 1024 x 1024
Tile Dimension: 16 x 16
Grid Size     : 64 x 64
Block Size    : 16 x 16
Global Memory Transpose Time: 0.501216 ms
Shared Memory Transpose Time: 0.313728 ms
Speedup (Global / Shared)   : 1.60 x
Verification result         : PASS
==========================================

==========================================
Matrix Size : 2048 x 2048
Tile Dimension: 16 x 16
Grid Size     : 128 x 128
Block Size    : 16 x 16
Global Memory Transpose Time: 1.034080 ms
Shared Memory Transpose Time: 0.974848 ms
Speedup (Global / Shared)   : 1.06 x
Verification result         : PASS
==========================================

==========================================
Matrix Size : 4096 x 4096
Tile Dimension: 16 x 16
Grid Size     : 256 x 256
Block Size    : 16 x 16
Global Memory Transpose Time: 3.240832 ms
Shared Memory Transpose Time: 3.772320 ms
Speedup (Global / Shared)   : 0.86 x
Verification result         : PASS
==========================================

==========================================
Matrix Size : 8192 x 8192
Tile Dimension: 16 x 16
Grid Size     : 512 x 512
Block Size    : 16 x 16
Global Memory Transpose Time: 11.304864 ms
Shared Memory Transpose Time: 15.184992 ms
Speedup (Global / Shared)   : 0.74 x
Verification result         : PASS
==========================================

==========================================
Matrix Size : 1024 x 1024
Tile Dimension: 32 x 32
Grid Size     : 32 x 32
Block Size    : 32 x 32
Global Memory Transpose Time: 0.793632 ms
Shared Memory Transpose Time: 0.399904 ms
Speedup (Global / Shared)   : 1.98 x
Verification result         : PASS
==========================================

==========================================
Matrix Size : 2048 x 2048
Tile Dimension: 32 x 32
Grid Size     : 64 x 64
Block Size    : 32 x 32
Global Memory Transpose Time: 2.174720 ms
Shared Memory Transpose Time: 1.669120 ms
Speedup (Global / Shared)   : 1.30 x
Verification result         : PASS
==========================================

==========================================
Matrix Size : 4096 x 4096
Tile Dimension: 32 x 32
Grid Size     : 128 x 128
Block Size    : 32 x 32
Global Memory Transpose Time: 6.242944 ms
Shared Memory Transpose Time: 5.107520 ms
Speedup (Global / Shared)   : 1.22 x
Verification result         : PASS
==========================================

==========================================
Matrix Size : 8192 x 8192
Tile Dimension: 32 x 32
Grid Size     : 256 x 256
Block Size    : 32 x 32
Global Memory Transpose Time: 23.618816 ms
Shared Memory Transpose Time: 18.996449 ms
Speedup (Global / Shared)   : 1.24 x
Verification result         : PASS
==========================================
*/
