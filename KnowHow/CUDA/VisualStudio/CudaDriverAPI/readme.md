## Create a CUDA runtime project
- <img width="1905" height="994" alt="image" src="https://github.com/user-attachments/assets/32f2b24c-2747-4883-b170-d09d4b71cd4c" />

## Build PTX (Parallel Thread Execution)
- add a file ```vector_add.cu```
```
extern "C" __global__ void vectorAdd(const float* A, const float* B, float* C, int numElements) {
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < numElements) {
        C[i] = A[i] + B[i];
    }
}
```
- mouse right click on ```vector_add.cu``` and select ```Property```
- <img width="1201" height="680" alt="image" src="https://github.com/user-attachments/assets/1603aec9-ce92-44fa-91e2-b3cca93be342" />
- <img width="466" height="713" alt="image" src="https://github.com/user-attachments/assets/738a767b-b103-4983-9d9e-69f8a4639c66" />
- After compiling ```vector_add.cu```, ```vector_add.ptx``` will be generated


## Build Host code
- <img width="437" height="287" alt="image" src="https://github.com/user-attachments/assets/1c8f0766-aded-4838-b571-eabc2a173d4e" />
- mouse right click and select ```Property```
- <img width="1299" height="682" alt="image" src="https://github.com/user-attachments/assets/4e39536c-2b53-41f0-93e1-6ead9c35d7e4" />
- <img width="1328" height="682" alt="image" src="https://github.com/user-attachments/assets/e818d4d2-dc92-4c84-8bc4-c2d8418baf4f" />
- <img width="1443" height="682" alt="image" src="https://github.com/user-attachments/assets/6013fcd1-2400-4460-9b45-35e13c2a9650" />
- ```kernel.cu```
```
#include <iostream>
#include <vector>
#include <cuda.h>

// 巨集：檢查 CUDA Driver API 錯誤
#define checkCudaErrors(err) __checkCudaErrors(err, __FILE__, __LINE__)
void __checkCudaErrors(CUresult err, const char* file, const int line) {
    if (err != CUDA_SUCCESS) {
        std::cerr << "CUDA Error " << err << " at " << file << ":" << line << std::endl;
        exit(-1);
    }
}

int main() {
    const int numElements = 50000;
    size_t size = numElements * sizeof(float);

    // 1. 初始化主機資料
    std::vector<float> h_A(numElements, 1.0f);
    std::vector<float> h_B(numElements, 2.0f);
    std::vector<float> h_C(numElements, 0.0f);

    // 2. 初始化 Driver API 與建立 Context
    checkCudaErrors(cuInit(0));
    CUdevice device;
    checkCudaErrors(cuDeviceGet(&device, 0));
    CUcontext context;
    checkCudaErrors(cuCtxCreate(&context, 0, 0, device));

    // 3. 載入 PTX 模組與獲取 Kernel 函式
    CUmodule module;
    // 確保 vector_add.ptx 放在執行檔同目錄下，或填寫絕對路徑
    checkCudaErrors(cuModuleLoad(&module, "vector_add.ptx"));
    CUfunction kernel;
    checkCudaErrors(cuModuleGetFunction(&kernel, module, "vectorAdd"));

    // 4. 配置 GPU 記憶體 (Device Memory)
    CUdeviceptr d_A, d_B, d_C;
    checkCudaErrors(cuMemAlloc(&d_A, size));
    checkCudaErrors(cuMemAlloc(&d_B, size));
    checkCudaErrors(cuMemAlloc(&d_C, size));

    // 5. 複製資料到 GPU
    checkCudaErrors(cuMemcpyHtoD(d_A, h_A.data(), size));
    checkCudaErrors(cuMemcpyHtoD(d_B, h_B.data(), size));

    // 6. 設定 Kernel 參數
    // Driver API 必須透過指標陣列傳遞參數
    void* args[] = { &d_A, &d_B, &d_C, (void*)&numElements };

    // 7. 啟動 Kernel (Launch Kernel)
    int threadsPerBlock = 256;
    int blocksPerGrid = (numElements + threadsPerBlock - 1) / threadsPerBlock;

    std::cout << "啟動 Kernel，Grid 大小: " << blocksPerGrid << ", Block 大小: " << threadsPerBlock << std::endl;
    checkCudaErrors(cuLaunchKernel(
        kernel,
        blocksPerGrid, 1, 1,    // Grid 尺寸 (X, Y, Z)
        threadsPerBlock, 1, 1,  // Block 尺寸 (X, Y, Z)
        0, nullptr,             // 共享記憶體大小, Stream
        args, nullptr           // 參數陣列
    ));

    // 8. 同步等待 GPU 計算完成
    checkCudaErrors(cuCtxSynchronize());

    // 9. 將結果複製回主機
    checkCudaErrors(cuMemcpyDtoH(h_C.data(), d_C, size));

    // 10. 驗證結果
    bool success = true;
    for (int i = 0; i < numElements; i++) {
        if (h_C[i] != 3.0f) {
            success = false;
            break;
        }
    }
    std::cout << "計算結果: " << (success ? "成功 (1.0 + 2.0 = 3.0)" : "失敗") << std::endl;

    // 11. 釋放資源
    cuMemFree(d_A);
    cuMemFree(d_B);
    cuMemFree(d_C);
    cuModuleUnload(module);
    cuCtxDestroy(context);

    return 0;
}
```
