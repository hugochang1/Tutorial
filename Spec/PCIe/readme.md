### Background
- PCIe (Peripheral Component Interconnect Express) is the standard high-speed interface used to connect internal hardware components—such as graphics cards (GPUs), NVMe solid-state drives (SSDs), Wi-Fi cards, and capture cards—directly to a computer's motherboard.

### Generations & Bandwidth
- PCIe 3.0, 2010, 1GB (1 lane) ~ 16GB (16 lanes)
- PCIe 4.0, 2019, 2GB (1 lane) ~ 32GB (16 lanes)
- PCIe 5.0, 2021, 4GB (1 lane) ~ 64GB (16 lanes)
- PCIe 6.0, 2022, 8GB (1 lane) ~ 128GB (16 lanes)

### Software Stack
- **User Space Applications** (CUDA, Games, File System)
  - read(), write(), ioctl()
- **Specific Device Drivers** (e.g., nvidia.ko, nvme.ko)
  - maps device registers into virtual memory space via MMIO
  - allocates DMA buffers for direct data transfers between System RAM and the PCIe endpoint
  - handles device interrupts via ISR (Interrupt Service Routine)
- **PCIe Core Bus Driver** (pci-core, PCIe AER, MSIs)
  - Enumeration & Discovery
  - BAR (Base Address Register)
  - Interrupt Management
  - Power Management
  - Advanced Error Reporting (AER)
- **Host Conroller Driver**
  - setup PHY layer clocks and link training

### PCIe Core Bus Driver API for device driver
- **Registration**: Registers its table of supported PCIe Vendor ID/Device IDs with pci_register_driver()
- **Hardware Enablement**: Asks the core to wake up the device and enable its bus-mastering capabilities (pci_enable_device(), pci_set_master()).
- **Resource Mapping**: Queries BAR (Base Address Register) addresses and sizes using core APIs like pci_resource_start() and pci_iomap()
- **Interrupt Binding**: Requests MSI/MSI-X vectors through pci_alloc_irq_vectors()



