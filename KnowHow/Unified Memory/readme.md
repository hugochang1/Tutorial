### Unified Memory (UM)
- a single, shared pool of physical memory (RAM) that is directly accessed by both the central processing unit (CPU) and the graphics processing unit (GPU), rather than keeping them separated

| Phase | Architectures | How It Operates Under the Hood | Related Features |
| :--- | :--- | :--- | :--- |
| **Early UM (Coarse-grained)** | Kepler, Maxwell (CUDA 6–7) | **No hardware page faulting.** All managed memory had to be synchronized and migrated in bulk at kernel boundaries; CPU and GPU could not access data concurrently. | N/A |
| **Software Coherence**<br>**Page-Fault UM (Demand Paging)** | Pascal through Blackwell (dGPUs) | **Hardware Page Faulting Engine + UVM Driver.** Fine-grained demand paging over PCIe/NVLink. True concurrency and memory oversubscription supported. | Heterogeneous Managed Memory (HMM) |
| **Hardware Coherence** | Grace Hopper (GH200), Grace Blackwell (GB200) | **NVLink-C2C (Chip-to-Chip)** connects CPU and GPU directly. Both processors can directly load/store into each other's memory with hardware-level cache coherence, minimizing the need for software page migration. | Address Translation Services (ATS) |

- **Heterogeneous Managed Memory (HMM)**
  - A feature of the Linux kernel that enables software coherency for full unified memory
- **Address Translation Services (ATS)**
  - A hardware feature, available when GPUs are connected to the CPU by the NVLink Chip-to-Chip (C2C) interconnect, which provides hardware coherency for full unified memory

### Unified Virtual Address (UVM) Space
- Gives the central processing unit (CPU) and graphics processing unit (GPU) a single, shared virtual address space
- CPU memory and each GPU’s memory have a distinct range within a single virtual address space

### explicit managed memory allocations
- need to use explicit memory managed API provided by CUDA such as cudaMallocManaged()

### software coherence
- use page fault to sync between CPU and GPU
- cost of conflict: page transfer (bigger >= 4KB)

### hardware coherence
- CPU 和 GPU 擁有各自獨立的頁表結構。但雙方的 MMU 透過硬體協議（如 ATS）保持同步，或由驅動程式在背後進行鏡像複製。
- cost of conflict: cache line (smaller)

### Terms
- Heterogeneous Managed Memory (HMM) - A feature of the Linux kernel that enables software coherency for full unified memory
- Address Translation Services (ATS) - A hardware feature, available when GPUs are connected to the CPU by the NVLink Chip-to-Chip (C2C) interconnect, which provides hardware coherency for full unified memory
- Process Address Space ID (PASID)
