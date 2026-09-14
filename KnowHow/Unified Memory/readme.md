### Unified memory
- a single, shared pool of physical memory (RAM) that is directly accessed by both the central processing unit (CPU) and the graphics processing unit (GPU), rather than keeping them separated

### explicit managed memory allocations
- need to use explicit memory managed API provided by CUDA such as cudaMallocManaged()

### software coherence
- use page fault to sync between CPU and GPU

### hardware coherence
- CPU 和 GPU 擁有各自獨立的頁表結構。但雙方的 MMU 透過硬體協議（如 ATS）保持同步，或由驅動程式在背後進行鏡像複製。

### Terms
- Heterogeneous Managed Memory (HMM) - A feature of the Linux kernel that enables software coherency for full unified memory
- Address Translation Services (ATS) - A hardware feature, available when GPUs are connected to the CPU by the NVLink Chip-to-Chip (C2C) interconnect, which provides hardware coherency for full unified memory
- Process Address Space ID (PASID)
