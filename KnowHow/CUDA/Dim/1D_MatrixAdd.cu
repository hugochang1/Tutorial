#include <iostream>
#include <cuda_runtime.h>

// CUDA Kernel: 一維陣列加法
__global__ void matrixAdd1D(const float* a, const float* b, float* c, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    printf("blockIdx=%d, threadIdx=%d blockDim.x=%d\n", blockIdx.x, threadIdx.x, blockDim.x);
    if (idx < n) {
        c[idx] = a[idx] + b[idx];
    }
}

int main() {
    int n = 32;
    size_t size = n * sizeof(float);
    float* h_a = new float[n], * h_b = new float[n], * h_c = new float[n];
    for (int i = 0; i < n; ++i) { h_a[i] = i; h_b[i] = i * 2; }

    float* d_a, * d_b, * d_c;
    cudaMalloc(&d_a, size); cudaMalloc(&d_b, size); cudaMalloc(&d_c, size);
    cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;
    matrixAdd1D << <blocksPerGrid, threadsPerBlock >> > (d_a, d_b, d_c, n);

    cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);
    std::cout << "Success!" << std::endl;

    cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
    delete[] h_a; delete[] h_b; delete[] h_c;
    return 0;
}
/*
blockIdx=0, threadIdx=224 blockDim.x=256
blockIdx=0, threadIdx=225 blockDim.x=256
blockIdx=0, threadIdx=226 blockDim.x=256
blockIdx=0, threadIdx=227 blockDim.x=256
blockIdx=0, threadIdx=228 blockDim.x=256
blockIdx=0, threadIdx=229 blockDim.x=256
blockIdx=0, threadIdx=230 blockDim.x=256
blockIdx=0, threadIdx=231 blockDim.x=256
blockIdx=0, threadIdx=232 blockDim.x=256
blockIdx=0, threadIdx=233 blockDim.x=256
blockIdx=0, threadIdx=234 blockDim.x=256
blockIdx=0, threadIdx=235 blockDim.x=256
blockIdx=0, threadIdx=236 blockDim.x=256
blockIdx=0, threadIdx=237 blockDim.x=256
blockIdx=0, threadIdx=238 blockDim.x=256
blockIdx=0, threadIdx=239 blockDim.x=256
blockIdx=0, threadIdx=240 blockDim.x=256
blockIdx=0, threadIdx=241 blockDim.x=256
blockIdx=0, threadIdx=242 blockDim.x=256
blockIdx=0, threadIdx=243 blockDim.x=256
blockIdx=0, threadIdx=244 blockDim.x=256
blockIdx=0, threadIdx=245 blockDim.x=256
blockIdx=0, threadIdx=246 blockDim.x=256
blockIdx=0, threadIdx=247 blockDim.x=256
blockIdx=0, threadIdx=248 blockDim.x=256
blockIdx=0, threadIdx=249 blockDim.x=256
blockIdx=0, threadIdx=250 blockDim.x=256
blockIdx=0, threadIdx=251 blockDim.x=256
blockIdx=0, threadIdx=252 blockDim.x=256
blockIdx=0, threadIdx=253 blockDim.x=256
blockIdx=0, threadIdx=254 blockDim.x=256
blockIdx=0, threadIdx=255 blockDim.x=256
blockIdx=0, threadIdx=128 blockDim.x=256
blockIdx=0, threadIdx=129 blockDim.x=256
blockIdx=0, threadIdx=130 blockDim.x=256
blockIdx=0, threadIdx=131 blockDim.x=256
blockIdx=0, threadIdx=132 blockDim.x=256
blockIdx=0, threadIdx=133 blockDim.x=256
blockIdx=0, threadIdx=134 blockDim.x=256
blockIdx=0, threadIdx=135 blockDim.x=256
blockIdx=0, threadIdx=136 blockDim.x=256
blockIdx=0, threadIdx=137 blockDim.x=256
blockIdx=0, threadIdx=138 blockDim.x=256
blockIdx=0, threadIdx=139 blockDim.x=256
blockIdx=0, threadIdx=140 blockDim.x=256
blockIdx=0, threadIdx=141 blockDim.x=256
blockIdx=0, threadIdx=142 blockDim.x=256
blockIdx=0, threadIdx=143 blockDim.x=256
blockIdx=0, threadIdx=144 blockDim.x=256
blockIdx=0, threadIdx=145 blockDim.x=256
blockIdx=0, threadIdx=146 blockDim.x=256
blockIdx=0, threadIdx=147 blockDim.x=256
blockIdx=0, threadIdx=148 blockDim.x=256
blockIdx=0, threadIdx=149 blockDim.x=256
blockIdx=0, threadIdx=150 blockDim.x=256
blockIdx=0, threadIdx=151 blockDim.x=256
blockIdx=0, threadIdx=152 blockDim.x=256
blockIdx=0, threadIdx=153 blockDim.x=256
blockIdx=0, threadIdx=154 blockDim.x=256
blockIdx=0, threadIdx=155 blockDim.x=256
blockIdx=0, threadIdx=156 blockDim.x=256
blockIdx=0, threadIdx=157 blockDim.x=256
blockIdx=0, threadIdx=158 blockDim.x=256
blockIdx=0, threadIdx=159 blockDim.x=256
blockIdx=0, threadIdx=160 blockDim.x=256
blockIdx=0, threadIdx=161 blockDim.x=256
blockIdx=0, threadIdx=162 blockDim.x=256
blockIdx=0, threadIdx=163 blockDim.x=256
blockIdx=0, threadIdx=164 blockDim.x=256
blockIdx=0, threadIdx=165 blockDim.x=256
blockIdx=0, threadIdx=166 blockDim.x=256
blockIdx=0, threadIdx=167 blockDim.x=256
blockIdx=0, threadIdx=168 blockDim.x=256
blockIdx=0, threadIdx=169 blockDim.x=256
blockIdx=0, threadIdx=170 blockDim.x=256
blockIdx=0, threadIdx=171 blockDim.x=256
blockIdx=0, threadIdx=172 blockDim.x=256
blockIdx=0, threadIdx=173 blockDim.x=256
blockIdx=0, threadIdx=174 blockDim.x=256
blockIdx=0, threadIdx=175 blockDim.x=256
blockIdx=0, threadIdx=176 blockDim.x=256
blockIdx=0, threadIdx=177 blockDim.x=256
blockIdx=0, threadIdx=178 blockDim.x=256
blockIdx=0, threadIdx=179 blockDim.x=256
blockIdx=0, threadIdx=180 blockDim.x=256
blockIdx=0, threadIdx=181 blockDim.x=256
blockIdx=0, threadIdx=182 blockDim.x=256
blockIdx=0, threadIdx=183 blockDim.x=256
blockIdx=0, threadIdx=184 blockDim.x=256
blockIdx=0, threadIdx=185 blockDim.x=256
blockIdx=0, threadIdx=186 blockDim.x=256
blockIdx=0, threadIdx=187 blockDim.x=256
blockIdx=0, threadIdx=188 blockDim.x=256
blockIdx=0, threadIdx=189 blockDim.x=256
blockIdx=0, threadIdx=190 blockDim.x=256
blockIdx=0, threadIdx=191 blockDim.x=256
blockIdx=0, threadIdx=32 blockDim.x=256
blockIdx=0, threadIdx=33 blockDim.x=256
blockIdx=0, threadIdx=34 blockDim.x=256
blockIdx=0, threadIdx=35 blockDim.x=256
blockIdx=0, threadIdx=36 blockDim.x=256
blockIdx=0, threadIdx=37 blockDim.x=256
blockIdx=0, threadIdx=38 blockDim.x=256
blockIdx=0, threadIdx=39 blockDim.x=256
blockIdx=0, threadIdx=40 blockDim.x=256
blockIdx=0, threadIdx=41 blockDim.x=256
blockIdx=0, threadIdx=42 blockDim.x=256
blockIdx=0, threadIdx=43 blockDim.x=256
blockIdx=0, threadIdx=44 blockDim.x=256
blockIdx=0, threadIdx=45 blockDim.x=256
blockIdx=0, threadIdx=46 blockDim.x=256
blockIdx=0, threadIdx=47 blockDim.x=256
blockIdx=0, threadIdx=48 blockDim.x=256
blockIdx=0, threadIdx=49 blockDim.x=256
blockIdx=0, threadIdx=50 blockDim.x=256
blockIdx=0, threadIdx=51 blockDim.x=256
blockIdx=0, threadIdx=52 blockDim.x=256
blockIdx=0, threadIdx=53 blockDim.x=256
blockIdx=0, threadIdx=54 blockDim.x=256
blockIdx=0, threadIdx=55 blockDim.x=256
blockIdx=0, threadIdx=56 blockDim.x=256
blockIdx=0, threadIdx=57 blockDim.x=256
blockIdx=0, threadIdx=58 blockDim.x=256
blockIdx=0, threadIdx=59 blockDim.x=256
blockIdx=0, threadIdx=60 blockDim.x=256
blockIdx=0, threadIdx=61 blockDim.x=256
blockIdx=0, threadIdx=62 blockDim.x=256
blockIdx=0, threadIdx=63 blockDim.x=256
blockIdx=0, threadIdx=96 blockDim.x=256
blockIdx=0, threadIdx=97 blockDim.x=256
blockIdx=0, threadIdx=98 blockDim.x=256
blockIdx=0, threadIdx=99 blockDim.x=256
blockIdx=0, threadIdx=100 blockDim.x=256
blockIdx=0, threadIdx=101 blockDim.x=256
blockIdx=0, threadIdx=102 blockDim.x=256
blockIdx=0, threadIdx=103 blockDim.x=256
blockIdx=0, threadIdx=104 blockDim.x=256
blockIdx=0, threadIdx=105 blockDim.x=256
blockIdx=0, threadIdx=106 blockDim.x=256
blockIdx=0, threadIdx=107 blockDim.x=256
blockIdx=0, threadIdx=108 blockDim.x=256
blockIdx=0, threadIdx=109 blockDim.x=256
blockIdx=0, threadIdx=110 blockDim.x=256
blockIdx=0, threadIdx=111 blockDim.x=256
blockIdx=0, threadIdx=112 blockDim.x=256
blockIdx=0, threadIdx=113 blockDim.x=256
blockIdx=0, threadIdx=114 blockDim.x=256
blockIdx=0, threadIdx=115 blockDim.x=256
blockIdx=0, threadIdx=116 blockDim.x=256
blockIdx=0, threadIdx=117 blockDim.x=256
blockIdx=0, threadIdx=118 blockDim.x=256
blockIdx=0, threadIdx=119 blockDim.x=256
blockIdx=0, threadIdx=120 blockDim.x=256
blockIdx=0, threadIdx=121 blockDim.x=256
blockIdx=0, threadIdx=122 blockDim.x=256
blockIdx=0, threadIdx=123 blockDim.x=256
blockIdx=0, threadIdx=124 blockDim.x=256
blockIdx=0, threadIdx=125 blockDim.x=256
blockIdx=0, threadIdx=126 blockDim.x=256
blockIdx=0, threadIdx=127 blockDim.x=256
blockIdx=0, threadIdx=0 blockDim.x=256
blockIdx=0, threadIdx=1 blockDim.x=256
blockIdx=0, threadIdx=2 blockDim.x=256
blockIdx=0, threadIdx=3 blockDim.x=256
blockIdx=0, threadIdx=4 blockDim.x=256
blockIdx=0, threadIdx=5 blockDim.x=256
blockIdx=0, threadIdx=6 blockDim.x=256
blockIdx=0, threadIdx=7 blockDim.x=256
blockIdx=0, threadIdx=8 blockDim.x=256
blockIdx=0, threadIdx=9 blockDim.x=256
blockIdx=0, threadIdx=10 blockDim.x=256
blockIdx=0, threadIdx=11 blockDim.x=256
blockIdx=0, threadIdx=12 blockDim.x=256
blockIdx=0, threadIdx=13 blockDim.x=256
blockIdx=0, threadIdx=14 blockDim.x=256
blockIdx=0, threadIdx=15 blockDim.x=256
blockIdx=0, threadIdx=16 blockDim.x=256
blockIdx=0, threadIdx=17 blockDim.x=256
blockIdx=0, threadIdx=18 blockDim.x=256
blockIdx=0, threadIdx=19 blockDim.x=256
blockIdx=0, threadIdx=20 blockDim.x=256
blockIdx=0, threadIdx=21 blockDim.x=256
blockIdx=0, threadIdx=22 blockDim.x=256
blockIdx=0, threadIdx=23 blockDim.x=256
blockIdx=0, threadIdx=24 blockDim.x=256
blockIdx=0, threadIdx=25 blockDim.x=256
blockIdx=0, threadIdx=26 blockDim.x=256
blockIdx=0, threadIdx=27 blockDim.x=256
blockIdx=0, threadIdx=28 blockDim.x=256
blockIdx=0, threadIdx=29 blockDim.x=256
blockIdx=0, threadIdx=30 blockDim.x=256
blockIdx=0, threadIdx=31 blockDim.x=256
blockIdx=0, threadIdx=192 blockDim.x=256
blockIdx=0, threadIdx=193 blockDim.x=256
blockIdx=0, threadIdx=194 blockDim.x=256
blockIdx=0, threadIdx=195 blockDim.x=256
blockIdx=0, threadIdx=196 blockDim.x=256
blockIdx=0, threadIdx=197 blockDim.x=256
blockIdx=0, threadIdx=198 blockDim.x=256
blockIdx=0, threadIdx=199 blockDim.x=256
blockIdx=0, threadIdx=200 blockDim.x=256
blockIdx=0, threadIdx=201 blockDim.x=256
blockIdx=0, threadIdx=202 blockDim.x=256
blockIdx=0, threadIdx=203 blockDim.x=256
blockIdx=0, threadIdx=204 blockDim.x=256
blockIdx=0, threadIdx=205 blockDim.x=256
blockIdx=0, threadIdx=206 blockDim.x=256
blockIdx=0, threadIdx=207 blockDim.x=256
blockIdx=0, threadIdx=208 blockDim.x=256
blockIdx=0, threadIdx=209 blockDim.x=256
blockIdx=0, threadIdx=210 blockDim.x=256
blockIdx=0, threadIdx=211 blockDim.x=256
blockIdx=0, threadIdx=212 blockDim.x=256
blockIdx=0, threadIdx=213 blockDim.x=256
blockIdx=0, threadIdx=214 blockDim.x=256
blockIdx=0, threadIdx=215 blockDim.x=256
blockIdx=0, threadIdx=216 blockDim.x=256
blockIdx=0, threadIdx=217 blockDim.x=256
blockIdx=0, threadIdx=218 blockDim.x=256
blockIdx=0, threadIdx=219 blockDim.x=256
blockIdx=0, threadIdx=220 blockDim.x=256
blockIdx=0, threadIdx=221 blockDim.x=256
blockIdx=0, threadIdx=222 blockDim.x=256
blockIdx=0, threadIdx=223 blockDim.x=256
blockIdx=0, threadIdx=64 blockDim.x=256
blockIdx=0, threadIdx=65 blockDim.x=256
blockIdx=0, threadIdx=66 blockDim.x=256
blockIdx=0, threadIdx=67 blockDim.x=256
blockIdx=0, threadIdx=68 blockDim.x=256
blockIdx=0, threadIdx=69 blockDim.x=256
blockIdx=0, threadIdx=70 blockDim.x=256
blockIdx=0, threadIdx=71 blockDim.x=256
blockIdx=0, threadIdx=72 blockDim.x=256
blockIdx=0, threadIdx=73 blockDim.x=256
blockIdx=0, threadIdx=74 blockDim.x=256
blockIdx=0, threadIdx=75 blockDim.x=256
blockIdx=0, threadIdx=76 blockDim.x=256
blockIdx=0, threadIdx=77 blockDim.x=256
blockIdx=0, threadIdx=78 blockDim.x=256
blockIdx=0, threadIdx=79 blockDim.x=256
blockIdx=0, threadIdx=80 blockDim.x=256
blockIdx=0, threadIdx=81 blockDim.x=256
blockIdx=0, threadIdx=82 blockDim.x=256
blockIdx=0, threadIdx=83 blockDim.x=256
blockIdx=0, threadIdx=84 blockDim.x=256
blockIdx=0, threadIdx=85 blockDim.x=256
blockIdx=0, threadIdx=86 blockDim.x=256
blockIdx=0, threadIdx=87 blockDim.x=256
blockIdx=0, threadIdx=88 blockDim.x=256
blockIdx=0, threadIdx=89 blockDim.x=256
blockIdx=0, threadIdx=90 blockDim.x=256
blockIdx=0, threadIdx=91 blockDim.x=256
blockIdx=0, threadIdx=92 blockDim.x=256
blockIdx=0, threadIdx=93 blockDim.x=256
blockIdx=0, threadIdx=94 blockDim.x=256
blockIdx=0, threadIdx=95 blockDim.x=256
Success!
*/
