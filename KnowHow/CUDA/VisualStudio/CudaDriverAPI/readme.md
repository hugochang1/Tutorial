### Build PTX (Parallel Thread Execution)
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
