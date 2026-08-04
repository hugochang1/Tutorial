### Background
- PCIe (Peripheral Component Interconnect Express) is the standard high-speed interface used to connect internal hardware components—such as graphics cards (GPUs), NVMe solid-state drives (SSDs), Wi-Fi cards, and capture cards—directly to a computer's motherboard.

### Generations & Bandwidth
- PCIe 3.0, 2010, 1GB (1 lane) ~ 16GB (16 lanes)
- PCIe 4.0, 2019, 2GB (1 lane) ~ 32GB (16 lanes)
- PCIe 5.0, 2021, 4GB (1 lane) ~ 64GB (16 lanes)
- PCIe 6.0, 2022, 8GB (1 lane) ~ 128GB (16 lanes)

### PCIe Host Software Stack
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

### PCIe Endpoint Software Stack
- Device Application / Firmware Logic (e.g., NVMe Flash Translation Layer, SmartNIC Offload)
  - This is the top layer where the actual work of the peripheral happens
  - NVMe SSD: Firmware handles the FTL (Flash Translation Layer), processes host Submission Queue (SQ) entries from host DMA memory, writes completion queue entries, and triggers a host MSI.
  - SmartNIC / DPU: Runs a full user-space stack (e.g., DPDK, Open vSwitch) or embedded OS handling packet acceleration and offloading network processing away from the host CPU.
- Endpoint Subsystem Framework (Linux configfs, PCI Endpoint Framework - pci-epf)
  - The framework abstracts the local hardware IP into a standard software interface. For example, in Linux, the PCI Endpoint Framework (pci-epf) allows the endpoint to present itself to the host as different physical device types
  - ConfigFS Integration: Enables software to dynamically expose device functions to the Host before linking the PCIe bus up
- PCIe Endpoint Controller Driver (pci-epc / IP Driver, e.g., Cadence EP, DWC EP)
  - Initialization: Sets up physical BAR sizes, configures maximum payload size (MPS), and programs the local iATU tables.
  - Interrupt Handlers: Listens for host events like PCIe Link Up, Bus Master Enable, or Host Inbound Flushes.
  - Doorbell / MSI Generation: Provides APIs for the local software stack to trigger outbound interrupts (MSI/MSI-X) back to the Host Root Complex.
- === HARDWARE BOUNDARY ===
- PCIe Controller IP Core (Hardware / PHY) (Manages 4KB Config Space Registers, BARs, Inbound)
  - Config Space Register Block: Hardware automatically handles basic host read/writes to the 4KB Configuration Space (Vendor ID, Device ID, BAR registers)
  - Inbound/Outbound Address Translation (iATU): Hardware block that maps host physical memory addresses (System DRAM) to endpoint local internal bus addresses (AXI/AHB).




