#include <iostream>
#include <vector>
#include <cuda_runtime.h>

// CUDA 核心函數 (Kernel Function)：在 GPU 上執行
__global__ void vectorAdd(const float* A, const float* B, float* C, int numElements) {
    int i = blockDim.x * blockIdx.x + threadIdx.x;
	printf("i=%d, A[i]=%f B[i]=%f\n", i, A[i], B[i]); // 印出每個執行緒的索引
    //if (i < numElements) {
        C[i] = A[i] + B[i];
    //}
}

int main() {
    // 1. 設定向量大小
    int n = 16;
    size_t size = n * sizeof(float);

    // 2. 在 Host (CPU) 配置記憶體並初始化資料
    std::vector<float> h_A(n, 1.0f); // A 陣列全為 1.0
    std::vector<float> h_B(n, 2.0f); // B 陣列全為 2.0
    std::vector<float> h_C(n, 0.0f); // 用來存放結果

    // 3. 在 Device (GPU) 配置記憶體空間
    float* d_A = nullptr;
    float* d_B = nullptr;
    float* d_C = nullptr;
    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);

    // 4. 將資料從 Host 複製到 Device
    cudaMemcpy(d_A, h_A.data(), size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B.data(), size, cudaMemcpyHostToDevice);

    // 5. 設定 CUDA 執行參數 (Grid 與 Block 大小)
    int threadsPerBlock = 32;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

    // 6. 呼叫 Kernel 函數
    vectorAdd << <blocksPerGrid, threadsPerBlock >> > (d_A, d_B, d_C, n);

    // 7. 將結果從 Device 複製回 Host
    cudaMemcpy(h_C.data(), d_C, size, cudaMemcpyDeviceToHost);

    // 8. 驗證結果
    bool success = true;
    for (int i = 0; i < n; i++) {
        if (abs(h_C[i] - 3.0f) > 1e-5) {
            success = false;
            break;
        }
    }

    if (success) {
        std::cout << "CUDA 一維矩陣加法驗證成功！(1.0 + 2.0 = 3.0)" << std::endl;
    }
    else {
        std::cout << "CUDA 一維矩陣加法驗證失敗！" << std::endl;
    }

    // 9. 釋放 Device 記憶體
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
/*
i=0, A[i]=1.000000 B[i]=2.000000
i=1, A[i]=1.000000 B[i]=2.000000
i=2, A[i]=1.000000 B[i]=2.000000
i=3, A[i]=1.000000 B[i]=2.000000
i=4, A[i]=1.000000 B[i]=2.000000
i=5, A[i]=1.000000 B[i]=2.000000
i=6, A[i]=1.000000 B[i]=2.000000
i=7, A[i]=1.000000 B[i]=2.000000
i=8, A[i]=1.000000 B[i]=2.000000
i=9, A[i]=1.000000 B[i]=2.000000
i=10, A[i]=1.000000 B[i]=2.000000
i=11, A[i]=1.000000 B[i]=2.000000
i=12, A[i]=1.000000 B[i]=2.000000
i=13, A[i]=1.000000 B[i]=2.000000
i=14, A[i]=1.000000 B[i]=2.000000
i=15, A[i]=1.000000 B[i]=2.000000
i=16, A[i]=0.000000 B[i]=0.000000
i=17, A[i]=0.000000 B[i]=0.000000
i=18, A[i]=0.000000 B[i]=0.000000
i=19, A[i]=0.000000 B[i]=0.000000
i=20, A[i]=0.000000 B[i]=0.000000
i=21, A[i]=0.000000 B[i]=0.000000
i=22, A[i]=0.000000 B[i]=0.000000
i=23, A[i]=0.000000 B[i]=0.000000
i=24, A[i]=0.000000 B[i]=0.000000
i=25, A[i]=0.000000 B[i]=0.000000
i=26, A[i]=0.000000 B[i]=0.000000
i=27, A[i]=0.000000 B[i]=0.000000
i=28, A[i]=0.000000 B[i]=0.000000
i=29, A[i]=0.000000 B[i]=0.000000
i=30, A[i]=0.000000 B[i]=0.000000
i=31, A[i]=0.000000 B[i]=0.000000
CUDA 一維矩陣加法驗證成功！(1.0 + 2.0 = 3.0)
*/
