#include <iostream>
#include <cuda_runtime.h>
#include <cmath>
#include <cstdio> // 核心函數中使用 printf 需要此標頭檔

// CUDA 核心函數：2D 矩陣相加並列印執行緒資訊
__global__ void matrixAdd2DWithDebug(const float* A, const float* B, float* C, int width, int height) {
    // 計算當前執行緒在 2D 網格中的全域列索引 (Row) 與行索引 (Col)
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;

    /**/
    printf("[Block(%d,%d)][Thread(%d,%d)] -> blockDim(%d,%d) | Global(Row:%d, Col:%d)\n",
        blockIdx.x, blockIdx.y,
        threadIdx.x, threadIdx.y,
        blockDim.x, blockDim.y,
        row, col);

    // 確保索引沒有超出矩陣邊界
    if (row < height && col < width) {
        int idx = row * width + col;
        C[idx] = A[idx] + B[idx];
    }
}

int main() {
    const int WIDTH = 16;
    const int HEIGHT = 16;
    const int SIZE = WIDTH * HEIGHT;
    const size_t bytes = SIZE * sizeof(float);

    float* h_A = (float*)malloc(bytes);
    float* h_B = (float*)malloc(bytes);
    float* h_C = (float*)malloc(bytes);

    for (int i = 0; i < SIZE; ++i) {
        h_A[i] = 1.0f;
        h_B[i] = 2.0f;
    }

    float* d_A, * d_B, * d_C;
    cudaMalloc(&d_A, bytes);
    cudaMalloc(&d_B, bytes);
    cudaMalloc(&d_C, bytes);

    cudaMemcpy(d_A, h_A, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, bytes, cudaMemcpyHostToDevice);

    // 定義 2D Block 與 Grid 大小
    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks((WIDTH + threadsPerBlock.x - 1) / threadsPerBlock.x,
        (HEIGHT + threadsPerBlock.y - 1) / threadsPerBlock.y);

    std::cout << "啟動 Kernel..." << std::endl;
    std::cout << "Grid 大小: (" << numBlocks.x << ", " << numBlocks.y << ")" << std::endl;
    std::cout << "Block 大小: (" << threadsPerBlock.x << ", " << threadsPerBlock.y << ")\n" << std::endl;

    // 調用核心函數
    matrixAdd2DWithDebug << <numBlocks, threadsPerBlock >> > (d_A, d_B, d_C, WIDTH, HEIGHT);

    // 【重要】同步裝置，確保 GPU 上的 printf 內容在 CPU 結束前被完全排空（Flush）到控制台
    cudaDeviceSynchronize();

    cudaMemcpy(h_C, d_C, bytes, cudaMemcpyDeviceToHost);

    // 釋放記憶體
    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    free(h_A); free(h_B); free(h_C);

    return 0;
}
/*
Grid 大小: (1, 1)
Block 大小: (16, 16)

[Block(0,0)][Thread(0,12)] -> blockDim(16,16) | Global(Row:12, Col:0)
[Block(0,0)][Thread(1,12)] -> blockDim(16,16) | Global(Row:12, Col:1)
[Block(0,0)][Thread(2,12)] -> blockDim(16,16) | Global(Row:12, Col:2)
[Block(0,0)][Thread(3,12)] -> blockDim(16,16) | Global(Row:12, Col:3)
[Block(0,0)][Thread(4,12)] -> blockDim(16,16) | Global(Row:12, Col:4)
[Block(0,0)][Thread(5,12)] -> blockDim(16,16) | Global(Row:12, Col:5)
[Block(0,0)][Thread(6,12)] -> blockDim(16,16) | Global(Row:12, Col:6)
[Block(0,0)][Thread(7,12)] -> blockDim(16,16) | Global(Row:12, Col:7)
[Block(0,0)][Thread(8,12)] -> blockDim(16,16) | Global(Row:12, Col:8)
[Block(0,0)][Thread(9,12)] -> blockDim(16,16) | Global(Row:12, Col:9)
[Block(0,0)][Thread(10,12)] -> blockDim(16,16) | Global(Row:12, Col:10)
[Block(0,0)][Thread(11,12)] -> blockDim(16,16) | Global(Row:12, Col:11)
[Block(0,0)][Thread(12,12)] -> blockDim(16,16) | Global(Row:12, Col:12)
[Block(0,0)][Thread(13,12)] -> blockDim(16,16) | Global(Row:12, Col:13)
[Block(0,0)][Thread(14,12)] -> blockDim(16,16) | Global(Row:12, Col:14)
[Block(0,0)][Thread(15,12)] -> blockDim(16,16) | Global(Row:12, Col:15)
[Block(0,0)][Thread(0,13)] -> blockDim(16,16) | Global(Row:13, Col:0)
[Block(0,0)][Thread(1,13)] -> blockDim(16,16) | Global(Row:13, Col:1)
[Block(0,0)][Thread(2,13)] -> blockDim(16,16) | Global(Row:13, Col:2)
[Block(0,0)][Thread(3,13)] -> blockDim(16,16) | Global(Row:13, Col:3)
[Block(0,0)][Thread(4,13)] -> blockDim(16,16) | Global(Row:13, Col:4)
[Block(0,0)][Thread(5,13)] -> blockDim(16,16) | Global(Row:13, Col:5)
[Block(0,0)][Thread(6,13)] -> blockDim(16,16) | Global(Row:13, Col:6)
[Block(0,0)][Thread(7,13)] -> blockDim(16,16) | Global(Row:13, Col:7)
[Block(0,0)][Thread(8,13)] -> blockDim(16,16) | Global(Row:13, Col:8)
[Block(0,0)][Thread(9,13)] -> blockDim(16,16) | Global(Row:13, Col:9)
[Block(0,0)][Thread(10,13)] -> blockDim(16,16) | Global(Row:13, Col:10)
[Block(0,0)][Thread(11,13)] -> blockDim(16,16) | Global(Row:13, Col:11)
[Block(0,0)][Thread(12,13)] -> blockDim(16,16) | Global(Row:13, Col:12)
[Block(0,0)][Thread(13,13)] -> blockDim(16,16) | Global(Row:13, Col:13)
[Block(0,0)][Thread(14,13)] -> blockDim(16,16) | Global(Row:13, Col:14)
[Block(0,0)][Thread(15,13)] -> blockDim(16,16) | Global(Row:13, Col:15)
[Block(0,0)][Thread(0,2)] -> blockDim(16,16) | Global(Row:2, Col:0)
[Block(0,0)][Thread(1,2)] -> blockDim(16,16) | Global(Row:2, Col:1)
[Block(0,0)][Thread(2,2)] -> blockDim(16,16) | Global(Row:2, Col:2)
[Block(0,0)][Thread(3,2)] -> blockDim(16,16) | Global(Row:2, Col:3)
[Block(0,0)][Thread(4,2)] -> blockDim(16,16) | Global(Row:2, Col:4)
[Block(0,0)][Thread(5,2)] -> blockDim(16,16) | Global(Row:2, Col:5)
[Block(0,0)][Thread(6,2)] -> blockDim(16,16) | Global(Row:2, Col:6)
[Block(0,0)][Thread(7,2)] -> blockDim(16,16) | Global(Row:2, Col:7)
[Block(0,0)][Thread(8,2)] -> blockDim(16,16) | Global(Row:2, Col:8)
[Block(0,0)][Thread(9,2)] -> blockDim(16,16) | Global(Row:2, Col:9)
[Block(0,0)][Thread(10,2)] -> blockDim(16,16) | Global(Row:2, Col:10)
[Block(0,0)][Thread(11,2)] -> blockDim(16,16) | Global(Row:2, Col:11)
[Block(0,0)][Thread(12,2)] -> blockDim(16,16) | Global(Row:2, Col:12)
[Block(0,0)][Thread(13,2)] -> blockDim(16,16) | Global(Row:2, Col:13)
[Block(0,0)][Thread(14,2)] -> blockDim(16,16) | Global(Row:2, Col:14)
[Block(0,0)][Thread(15,2)] -> blockDim(16,16) | Global(Row:2, Col:15)
[Block(0,0)][Thread(0,3)] -> blockDim(16,16) | Global(Row:3, Col:0)
[Block(0,0)][Thread(1,3)] -> blockDim(16,16) | Global(Row:3, Col:1)
[Block(0,0)][Thread(2,3)] -> blockDim(16,16) | Global(Row:3, Col:2)
[Block(0,0)][Thread(3,3)] -> blockDim(16,16) | Global(Row:3, Col:3)
[Block(0,0)][Thread(4,3)] -> blockDim(16,16) | Global(Row:3, Col:4)
[Block(0,0)][Thread(5,3)] -> blockDim(16,16) | Global(Row:3, Col:5)
[Block(0,0)][Thread(6,3)] -> blockDim(16,16) | Global(Row:3, Col:6)
[Block(0,0)][Thread(7,3)] -> blockDim(16,16) | Global(Row:3, Col:7)
[Block(0,0)][Thread(8,3)] -> blockDim(16,16) | Global(Row:3, Col:8)
[Block(0,0)][Thread(9,3)] -> blockDim(16,16) | Global(Row:3, Col:9)
[Block(0,0)][Thread(10,3)] -> blockDim(16,16) | Global(Row:3, Col:10)
[Block(0,0)][Thread(11,3)] -> blockDim(16,16) | Global(Row:3, Col:11)
[Block(0,0)][Thread(12,3)] -> blockDim(16,16) | Global(Row:3, Col:12)
[Block(0,0)][Thread(13,3)] -> blockDim(16,16) | Global(Row:3, Col:13)
[Block(0,0)][Thread(14,3)] -> blockDim(16,16) | Global(Row:3, Col:14)
[Block(0,0)][Thread(15,3)] -> blockDim(16,16) | Global(Row:3, Col:15)
[Block(0,0)][Thread(0,8)] -> blockDim(16,16) | Global(Row:8, Col:0)
[Block(0,0)][Thread(1,8)] -> blockDim(16,16) | Global(Row:8, Col:1)
[Block(0,0)][Thread(2,8)] -> blockDim(16,16) | Global(Row:8, Col:2)
[Block(0,0)][Thread(3,8)] -> blockDim(16,16) | Global(Row:8, Col:3)
[Block(0,0)][Thread(4,8)] -> blockDim(16,16) | Global(Row:8, Col:4)
[Block(0,0)][Thread(5,8)] -> blockDim(16,16) | Global(Row:8, Col:5)
[Block(0,0)][Thread(6,8)] -> blockDim(16,16) | Global(Row:8, Col:6)
[Block(0,0)][Thread(7,8)] -> blockDim(16,16) | Global(Row:8, Col:7)
[Block(0,0)][Thread(8,8)] -> blockDim(16,16) | Global(Row:8, Col:8)
[Block(0,0)][Thread(9,8)] -> blockDim(16,16) | Global(Row:8, Col:9)
[Block(0,0)][Thread(10,8)] -> blockDim(16,16) | Global(Row:8, Col:10)
[Block(0,0)][Thread(11,8)] -> blockDim(16,16) | Global(Row:8, Col:11)
[Block(0,0)][Thread(12,8)] -> blockDim(16,16) | Global(Row:8, Col:12)
[Block(0,0)][Thread(13,8)] -> blockDim(16,16) | Global(Row:8, Col:13)
[Block(0,0)][Thread(14,8)] -> blockDim(16,16) | Global(Row:8, Col:14)
[Block(0,0)][Thread(15,8)] -> blockDim(16,16) | Global(Row:8, Col:15)
[Block(0,0)][Thread(0,9)] -> blockDim(16,16) | Global(Row:9, Col:0)
[Block(0,0)][Thread(1,9)] -> blockDim(16,16) | Global(Row:9, Col:1)
[Block(0,0)][Thread(2,9)] -> blockDim(16,16) | Global(Row:9, Col:2)
[Block(0,0)][Thread(3,9)] -> blockDim(16,16) | Global(Row:9, Col:3)
[Block(0,0)][Thread(4,9)] -> blockDim(16,16) | Global(Row:9, Col:4)
[Block(0,0)][Thread(5,9)] -> blockDim(16,16) | Global(Row:9, Col:5)
[Block(0,0)][Thread(6,9)] -> blockDim(16,16) | Global(Row:9, Col:6)
[Block(0,0)][Thread(7,9)] -> blockDim(16,16) | Global(Row:9, Col:7)
[Block(0,0)][Thread(8,9)] -> blockDim(16,16) | Global(Row:9, Col:8)
[Block(0,0)][Thread(9,9)] -> blockDim(16,16) | Global(Row:9, Col:9)
[Block(0,0)][Thread(10,9)] -> blockDim(16,16) | Global(Row:9, Col:10)
[Block(0,0)][Thread(11,9)] -> blockDim(16,16) | Global(Row:9, Col:11)
[Block(0,0)][Thread(12,9)] -> blockDim(16,16) | Global(Row:9, Col:12)
[Block(0,0)][Thread(13,9)] -> blockDim(16,16) | Global(Row:9, Col:13)
[Block(0,0)][Thread(14,9)] -> blockDim(16,16) | Global(Row:9, Col:14)
[Block(0,0)][Thread(15,9)] -> blockDim(16,16) | Global(Row:9, Col:15)
[Block(0,0)][Thread(0,10)] -> blockDim(16,16) | Global(Row:10, Col:0)
[Block(0,0)][Thread(1,10)] -> blockDim(16,16) | Global(Row:10, Col:1)
[Block(0,0)][Thread(2,10)] -> blockDim(16,16) | Global(Row:10, Col:2)
[Block(0,0)][Thread(3,10)] -> blockDim(16,16) | Global(Row:10, Col:3)
[Block(0,0)][Thread(4,10)] -> blockDim(16,16) | Global(Row:10, Col:4)
[Block(0,0)][Thread(5,10)] -> blockDim(16,16) | Global(Row:10, Col:5)
[Block(0,0)][Thread(6,10)] -> blockDim(16,16) | Global(Row:10, Col:6)
[Block(0,0)][Thread(7,10)] -> blockDim(16,16) | Global(Row:10, Col:7)
[Block(0,0)][Thread(8,10)] -> blockDim(16,16) | Global(Row:10, Col:8)
[Block(0,0)][Thread(9,10)] -> blockDim(16,16) | Global(Row:10, Col:9)
[Block(0,0)][Thread(10,10)] -> blockDim(16,16) | Global(Row:10, Col:10)
[Block(0,0)][Thread(11,10)] -> blockDim(16,16) | Global(Row:10, Col:11)
[Block(0,0)][Thread(12,10)] -> blockDim(16,16) | Global(Row:10, Col:12)
[Block(0,0)][Thread(13,10)] -> blockDim(16,16) | Global(Row:10, Col:13)
[Block(0,0)][Thread(14,10)] -> blockDim(16,16) | Global(Row:10, Col:14)
[Block(0,0)][Thread(15,10)] -> blockDim(16,16) | Global(Row:10, Col:15)
[Block(0,0)][Thread(0,11)] -> blockDim(16,16) | Global(Row:11, Col:0)
[Block(0,0)][Thread(1,11)] -> blockDim(16,16) | Global(Row:11, Col:1)
[Block(0,0)][Thread(2,11)] -> blockDim(16,16) | Global(Row:11, Col:2)
[Block(0,0)][Thread(3,11)] -> blockDim(16,16) | Global(Row:11, Col:3)
[Block(0,0)][Thread(4,11)] -> blockDim(16,16) | Global(Row:11, Col:4)
[Block(0,0)][Thread(5,11)] -> blockDim(16,16) | Global(Row:11, Col:5)
[Block(0,0)][Thread(6,11)] -> blockDim(16,16) | Global(Row:11, Col:6)
[Block(0,0)][Thread(7,11)] -> blockDim(16,16) | Global(Row:11, Col:7)
[Block(0,0)][Thread(8,11)] -> blockDim(16,16) | Global(Row:11, Col:8)
[Block(0,0)][Thread(9,11)] -> blockDim(16,16) | Global(Row:11, Col:9)
[Block(0,0)][Thread(10,11)] -> blockDim(16,16) | Global(Row:11, Col:10)
[Block(0,0)][Thread(11,11)] -> blockDim(16,16) | Global(Row:11, Col:11)
[Block(0,0)][Thread(12,11)] -> blockDim(16,16) | Global(Row:11, Col:12)
[Block(0,0)][Thread(13,11)] -> blockDim(16,16) | Global(Row:11, Col:13)
[Block(0,0)][Thread(14,11)] -> blockDim(16,16) | Global(Row:11, Col:14)
[Block(0,0)][Thread(15,11)] -> blockDim(16,16) | Global(Row:11, Col:15)
[Block(0,0)][Thread(0,0)] -> blockDim(16,16) | Global(Row:0, Col:0)
[Block(0,0)][Thread(1,0)] -> blockDim(16,16) | Global(Row:0, Col:1)
[Block(0,0)][Thread(2,0)] -> blockDim(16,16) | Global(Row:0, Col:2)
[Block(0,0)][Thread(3,0)] -> blockDim(16,16) | Global(Row:0, Col:3)
[Block(0,0)][Thread(4,0)] -> blockDim(16,16) | Global(Row:0, Col:4)
[Block(0,0)][Thread(5,0)] -> blockDim(16,16) | Global(Row:0, Col:5)
[Block(0,0)][Thread(6,0)] -> blockDim(16,16) | Global(Row:0, Col:6)
[Block(0,0)][Thread(7,0)] -> blockDim(16,16) | Global(Row:0, Col:7)
[Block(0,0)][Thread(8,0)] -> blockDim(16,16) | Global(Row:0, Col:8)
[Block(0,0)][Thread(9,0)] -> blockDim(16,16) | Global(Row:0, Col:9)
[Block(0,0)][Thread(10,0)] -> blockDim(16,16) | Global(Row:0, Col:10)
[Block(0,0)][Thread(11,0)] -> blockDim(16,16) | Global(Row:0, Col:11)
[Block(0,0)][Thread(12,0)] -> blockDim(16,16) | Global(Row:0, Col:12)
[Block(0,0)][Thread(13,0)] -> blockDim(16,16) | Global(Row:0, Col:13)
[Block(0,0)][Thread(14,0)] -> blockDim(16,16) | Global(Row:0, Col:14)
[Block(0,0)][Thread(15,0)] -> blockDim(16,16) | Global(Row:0, Col:15)
[Block(0,0)][Thread(0,1)] -> blockDim(16,16) | Global(Row:1, Col:0)
[Block(0,0)][Thread(1,1)] -> blockDim(16,16) | Global(Row:1, Col:1)
[Block(0,0)][Thread(2,1)] -> blockDim(16,16) | Global(Row:1, Col:2)
[Block(0,0)][Thread(3,1)] -> blockDim(16,16) | Global(Row:1, Col:3)
[Block(0,0)][Thread(4,1)] -> blockDim(16,16) | Global(Row:1, Col:4)
[Block(0,0)][Thread(5,1)] -> blockDim(16,16) | Global(Row:1, Col:5)
[Block(0,0)][Thread(6,1)] -> blockDim(16,16) | Global(Row:1, Col:6)
[Block(0,0)][Thread(7,1)] -> blockDim(16,16) | Global(Row:1, Col:7)
[Block(0,0)][Thread(8,1)] -> blockDim(16,16) | Global(Row:1, Col:8)
[Block(0,0)][Thread(9,1)] -> blockDim(16,16) | Global(Row:1, Col:9)
[Block(0,0)][Thread(10,1)] -> blockDim(16,16) | Global(Row:1, Col:10)
[Block(0,0)][Thread(11,1)] -> blockDim(16,16) | Global(Row:1, Col:11)
[Block(0,0)][Thread(12,1)] -> blockDim(16,16) | Global(Row:1, Col:12)
[Block(0,0)][Thread(13,1)] -> blockDim(16,16) | Global(Row:1, Col:13)
[Block(0,0)][Thread(14,1)] -> blockDim(16,16) | Global(Row:1, Col:14)
[Block(0,0)][Thread(15,1)] -> blockDim(16,16) | Global(Row:1, Col:15)
[Block(0,0)][Thread(0,4)] -> blockDim(16,16) | Global(Row:4, Col:0)
[Block(0,0)][Thread(1,4)] -> blockDim(16,16) | Global(Row:4, Col:1)
[Block(0,0)][Thread(2,4)] -> blockDim(16,16) | Global(Row:4, Col:2)
[Block(0,0)][Thread(3,4)] -> blockDim(16,16) | Global(Row:4, Col:3)
[Block(0,0)][Thread(4,4)] -> blockDim(16,16) | Global(Row:4, Col:4)
[Block(0,0)][Thread(5,4)] -> blockDim(16,16) | Global(Row:4, Col:5)
[Block(0,0)][Thread(6,4)] -> blockDim(16,16) | Global(Row:4, Col:6)
[Block(0,0)][Thread(7,4)] -> blockDim(16,16) | Global(Row:4, Col:7)
[Block(0,0)][Thread(8,4)] -> blockDim(16,16) | Global(Row:4, Col:8)
[Block(0,0)][Thread(9,4)] -> blockDim(16,16) | Global(Row:4, Col:9)
[Block(0,0)][Thread(10,4)] -> blockDim(16,16) | Global(Row:4, Col:10)
[Block(0,0)][Thread(11,4)] -> blockDim(16,16) | Global(Row:4, Col:11)
[Block(0,0)][Thread(12,4)] -> blockDim(16,16) | Global(Row:4, Col:12)
[Block(0,0)][Thread(13,4)] -> blockDim(16,16) | Global(Row:4, Col:13)
[Block(0,0)][Thread(14,4)] -> blockDim(16,16) | Global(Row:4, Col:14)
[Block(0,0)][Thread(15,4)] -> blockDim(16,16) | Global(Row:4, Col:15)
[Block(0,0)][Thread(0,5)] -> blockDim(16,16) | Global(Row:5, Col:0)
[Block(0,0)][Thread(1,5)] -> blockDim(16,16) | Global(Row:5, Col:1)
[Block(0,0)][Thread(2,5)] -> blockDim(16,16) | Global(Row:5, Col:2)
[Block(0,0)][Thread(3,5)] -> blockDim(16,16) | Global(Row:5, Col:3)
[Block(0,0)][Thread(4,5)] -> blockDim(16,16) | Global(Row:5, Col:4)
[Block(0,0)][Thread(5,5)] -> blockDim(16,16) | Global(Row:5, Col:5)
[Block(0,0)][Thread(6,5)] -> blockDim(16,16) | Global(Row:5, Col:6)
[Block(0,0)][Thread(7,5)] -> blockDim(16,16) | Global(Row:5, Col:7)
[Block(0,0)][Thread(8,5)] -> blockDim(16,16) | Global(Row:5, Col:8)
[Block(0,0)][Thread(9,5)] -> blockDim(16,16) | Global(Row:5, Col:9)
[Block(0,0)][Thread(10,5)] -> blockDim(16,16) | Global(Row:5, Col:10)
[Block(0,0)][Thread(11,5)] -> blockDim(16,16) | Global(Row:5, Col:11)
[Block(0,0)][Thread(12,5)] -> blockDim(16,16) | Global(Row:5, Col:12)
[Block(0,0)][Thread(13,5)] -> blockDim(16,16) | Global(Row:5, Col:13)
[Block(0,0)][Thread(14,5)] -> blockDim(16,16) | Global(Row:5, Col:14)
[Block(0,0)][Thread(15,5)] -> blockDim(16,16) | Global(Row:5, Col:15)
[Block(0,0)][Thread(0,14)] -> blockDim(16,16) | Global(Row:14, Col:0)
[Block(0,0)][Thread(1,14)] -> blockDim(16,16) | Global(Row:14, Col:1)
[Block(0,0)][Thread(2,14)] -> blockDim(16,16) | Global(Row:14, Col:2)
[Block(0,0)][Thread(3,14)] -> blockDim(16,16) | Global(Row:14, Col:3)
[Block(0,0)][Thread(4,14)] -> blockDim(16,16) | Global(Row:14, Col:4)
[Block(0,0)][Thread(5,14)] -> blockDim(16,16) | Global(Row:14, Col:5)
[Block(0,0)][Thread(6,14)] -> blockDim(16,16) | Global(Row:14, Col:6)
[Block(0,0)][Thread(7,14)] -> blockDim(16,16) | Global(Row:14, Col:7)
[Block(0,0)][Thread(8,14)] -> blockDim(16,16) | Global(Row:14, Col:8)
[Block(0,0)][Thread(9,14)] -> blockDim(16,16) | Global(Row:14, Col:9)
[Block(0,0)][Thread(10,14)] -> blockDim(16,16) | Global(Row:14, Col:10)
[Block(0,0)][Thread(11,14)] -> blockDim(16,16) | Global(Row:14, Col:11)
[Block(0,0)][Thread(12,14)] -> blockDim(16,16) | Global(Row:14, Col:12)
[Block(0,0)][Thread(13,14)] -> blockDim(16,16) | Global(Row:14, Col:13)
[Block(0,0)][Thread(14,14)] -> blockDim(16,16) | Global(Row:14, Col:14)
[Block(0,0)][Thread(15,14)] -> blockDim(16,16) | Global(Row:14, Col:15)
[Block(0,0)][Thread(0,15)] -> blockDim(16,16) | Global(Row:15, Col:0)
[Block(0,0)][Thread(1,15)] -> blockDim(16,16) | Global(Row:15, Col:1)
[Block(0,0)][Thread(2,15)] -> blockDim(16,16) | Global(Row:15, Col:2)
[Block(0,0)][Thread(3,15)] -> blockDim(16,16) | Global(Row:15, Col:3)
[Block(0,0)][Thread(4,15)] -> blockDim(16,16) | Global(Row:15, Col:4)
[Block(0,0)][Thread(5,15)] -> blockDim(16,16) | Global(Row:15, Col:5)
[Block(0,0)][Thread(6,15)] -> blockDim(16,16) | Global(Row:15, Col:6)
[Block(0,0)][Thread(7,15)] -> blockDim(16,16) | Global(Row:15, Col:7)
[Block(0,0)][Thread(8,15)] -> blockDim(16,16) | Global(Row:15, Col:8)
[Block(0,0)][Thread(9,15)] -> blockDim(16,16) | Global(Row:15, Col:9)
[Block(0,0)][Thread(10,15)] -> blockDim(16,16) | Global(Row:15, Col:10)
[Block(0,0)][Thread(11,15)] -> blockDim(16,16) | Global(Row:15, Col:11)
[Block(0,0)][Thread(12,15)] -> blockDim(16,16) | Global(Row:15, Col:12)
[Block(0,0)][Thread(13,15)] -> blockDim(16,16) | Global(Row:15, Col:13)
[Block(0,0)][Thread(14,15)] -> blockDim(16,16) | Global(Row:15, Col:14)
[Block(0,0)][Thread(15,15)] -> blockDim(16,16) | Global(Row:15, Col:15)
[Block(0,0)][Thread(0,6)] -> blockDim(16,16) | Global(Row:6, Col:0)
[Block(0,0)][Thread(1,6)] -> blockDim(16,16) | Global(Row:6, Col:1)
[Block(0,0)][Thread(2,6)] -> blockDim(16,16) | Global(Row:6, Col:2)
[Block(0,0)][Thread(3,6)] -> blockDim(16,16) | Global(Row:6, Col:3)
[Block(0,0)][Thread(4,6)] -> blockDim(16,16) | Global(Row:6, Col:4)
[Block(0,0)][Thread(5,6)] -> blockDim(16,16) | Global(Row:6, Col:5)
[Block(0,0)][Thread(6,6)] -> blockDim(16,16) | Global(Row:6, Col:6)
[Block(0,0)][Thread(7,6)] -> blockDim(16,16) | Global(Row:6, Col:7)
[Block(0,0)][Thread(8,6)] -> blockDim(16,16) | Global(Row:6, Col:8)
[Block(0,0)][Thread(9,6)] -> blockDim(16,16) | Global(Row:6, Col:9)
[Block(0,0)][Thread(10,6)] -> blockDim(16,16) | Global(Row:6, Col:10)
[Block(0,0)][Thread(11,6)] -> blockDim(16,16) | Global(Row:6, Col:11)
[Block(0,0)][Thread(12,6)] -> blockDim(16,16) | Global(Row:6, Col:12)
[Block(0,0)][Thread(13,6)] -> blockDim(16,16) | Global(Row:6, Col:13)
[Block(0,0)][Thread(14,6)] -> blockDim(16,16) | Global(Row:6, Col:14)
[Block(0,0)][Thread(15,6)] -> blockDim(16,16) | Global(Row:6, Col:15)
[Block(0,0)][Thread(0,7)] -> blockDim(16,16) | Global(Row:7, Col:0)
[Block(0,0)][Thread(1,7)] -> blockDim(16,16) | Global(Row:7, Col:1)
[Block(0,0)][Thread(2,7)] -> blockDim(16,16) | Global(Row:7, Col:2)
[Block(0,0)][Thread(3,7)] -> blockDim(16,16) | Global(Row:7, Col:3)
[Block(0,0)][Thread(4,7)] -> blockDim(16,16) | Global(Row:7, Col:4)
[Block(0,0)][Thread(5,7)] -> blockDim(16,16) | Global(Row:7, Col:5)
[Block(0,0)][Thread(6,7)] -> blockDim(16,16) | Global(Row:7, Col:6)
[Block(0,0)][Thread(7,7)] -> blockDim(16,16) | Global(Row:7, Col:7)
[Block(0,0)][Thread(8,7)] -> blockDim(16,16) | Global(Row:7, Col:8)
[Block(0,0)][Thread(9,7)] -> blockDim(16,16) | Global(Row:7, Col:9)
[Block(0,0)][Thread(10,7)] -> blockDim(16,16) | Global(Row:7, Col:10)
[Block(0,0)][Thread(11,7)] -> blockDim(16,16) | Global(Row:7, Col:11)
[Block(0,0)][Thread(12,7)] -> blockDim(16,16) | Global(Row:7, Col:12)
[Block(0,0)][Thread(13,7)] -> blockDim(16,16) | Global(Row:7, Col:13)
[Block(0,0)][Thread(14,7)] -> blockDim(16,16) | Global(Row:7, Col:14)
[Block(0,0)][Thread(15,7)] -> blockDim(16,16) | Global(Row:7, Col:15)
*/
