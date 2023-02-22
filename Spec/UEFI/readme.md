# file type
|name|Description|Note|
|-|-|-|
|.c .cpp .h|Source Code and header file|
|.asm|Assembly Language|
|.uni|string resouce|
|.inf|Module Information File|like a makefile. to make a module (.efi)|
|.dsc|Platform Descrption File|like a makefile to make a package|
|.dec|Package Declaration File|define public data and interface for other module use|
|.fdf|Flash Description Files|
````
.dsc .dec .inf ... .inf
       |
       V
   build command
       |
       V
.elf ... .elf + .dec .fdf
       |
       V
   GenFW command
       |
       V
    ROM Image
````

# Term
|Term|Full|Description|
|-|-|-|
|PI|Platform Initialization|SEC + PEI + DXE + BSD|
|EDK|EFI Developer Kit|A modern, feature-rich, cross-platform firmware development environment for the UEFI and PI specifications|
|SEC|Security||
|PEI|Pre-EFI Initialization||
|PEIM|PEI Module|modular chunks of firwmare in PEI|
|PPI|PEIM-to-PEIM Interface|in DXE|
|PHIT|PEI Hand-off Information Table|PEI generated -> DXE used|
|HOBs|Hand-off blocks|PEI generated -> DXE used|
|DXE|Driver Execution Environment||
|BDS|Boot Device Selection||
|TSL|Transient System Load||
|BS|Boot Service||
|RT|Runtime||
|AL|After Life||
|FV|Firmware Volume|a logical repository for FW data + code|
|BFV|Boot Firmware Volume|where PEI code is stored|
|AP|Architectureal Protocol|in DEX|
|CAR|Cache as RAM|in PEI|
|T-RAM|temporary RAM|in PEI|
|XIP|Execute In Place|PEIM run on flash instaed of RAM|
|DEPEX|Dependency Expression||
|DXE IPL|DXE Initial Program Loader|the code that transitions the DXE core code into memory|
|BSP|Boot Strap Processor||
|ESP|EFI System Partition||
|SMM|System Management Mode|in DXE|
|HII|Human Interface Infrastucture|in BDS|
|IFR|Internal Form Representation|in BDS|
|VFR|Visual Form Representation|in BDS|
|OVMF|Open Virtual Machine Firmware||
|PCD|Platform Configuration Database||


# Reference
- EDK2
  - https://github.com/tianocore/edk2
- UEFITool
  - https://github.com/LongSoft/UEFITool/releases/tag/A59


# dump GUID
````
void dump_EFI_GUID(IN CONST EFI_GUID* guid)
{
  DEBUG ((DEBUG_INFO, "hugo dump_EFI_GUID %x-%x-%x-%02x%02x%02x%02x%02x%02x%02x%02x\n",
  	guid->Data1, guid->Data2, guid->Data3,
  	guid->Data4[0], guid->Data4[1], guid->Data4[2], guid->Data4[3], 
  	guid->Data4[4], guid->Data4[5], guid->Data4[6], guid->Data4[7]));
}
dump_EFI_GUID(&gEfiDxeIplPpiGuid);
````

# compare GUID
````
//return 0 menas guid1 and guid2 are same, otherwise return 1
BOOLEAN is_equal_EFI_GUID(IN CONST EFI_GUID* guid1, IN CONST EFI_GUID* guid2)
{
	if ( ((INT32 *)guid1)[0] == ((INT32 *)guid2)[0] &&
		((INT32 *)guid1)[1] == ((INT32 *)guid2)[1] &&
		((INT32 *)guid1)[2] == ((INT32 *)guid2)[2] &&
		((INT32 *)guid1)[3] == ((INT32 *)guid2)[3]	) {
		return FALSE;
	}
	return TRUE;
}
is_equal_EFI_GUID(&guid1, &guid2);
````

# How to use GUID
- use `gEfiDxeIplPpiGuid` as example
- defined in `MdePkg\MdePkg.dec`
````
[Ppis]
  ## Include/Ppi/DxeIpl.h
  gEfiDxeIplPpiGuid = {0xae8ce5d, 0xe448, 0x4437, {0xa8, 0xd7, 0xeb, 0xf5, 0xf1, 0x94, 0xf7, 0x31 }}
````

- used by `MdeModulePkg\Core\Pei\PeiMain.inf`
````
[Ppis]
  ..
  gEfiDxeIplPpiGuid                             ## CONSUMES
````

- used by `MdeModulePkg\Core\DxeIplPeim\DxeIpl.inf`
````
[Ppis]
  gEfiDxeIplPpiGuid                      ## PRODUCES
````

- source code `MdeModulePkg\Core\Pei\PeiMain\PeiMain.c`
````
  //
  // Lookup DXE IPL PPI
  //
  Status = PeiServicesLocatePpi (
             &gEfiDxeIplPpiGuid,
             0,
             NULL,
             (VOID **)&TempPtr.DxeIpl
             );
  ASSERT_EFI_ERROR (Status);
````

# Spec
|Term|Full|Note|
|-|-|-|
|APM|Advanced Power Management|an API developed by Intel and Microsoft|
|ACPI|Advanced Configuration and Power Interface|an open standard that operating systems can use to discover and configure computer hardware components, to perform power management e.g. putting unused hardware components to sleep|
|ACPICA|ACPI Component Architecture|provides an operating system (OS)-independent reference implementation of ACPI|
|AML|ACPI Machine Language||
|ASL|ACPI Source Language||
|APIC|Advanced Programmable Interrupt Controller|a family of interrupt controllers|
|OSPM|Operating System-directed configuration and Power Management|a computer specification for device configuration and power management by the operating system|

# Bus
|Term|Full|Note|
|-|-|-|
|PCI|Peripheral Component Interconnect or Personal Computer Interface|a local computer bus for attaching hardware devices in a computer|
|PCIe|PCI Express| a high-speed serial computer expansion bus standard, designed to replace the older PCI|
|USB|Universal Serial Bus|an industry standard that establishes specifications for cables|
|UART|Universal Asynchronous Receiver/Transmitter|a computer hardware device for asynchronous serial communication in which the data format and transmission speeds are configurable|
|I2C|Inter-Integrated Circuit|a synchronous, multi-controller/multi-target (master/slave), packet switched, single-ended, serial communication bus|
|I3C|an inter-circuit protocol evolved from I2C|a specification[1] to enable communication between computer chips by defining the electrical connection between the chips and signaling patterns to be used|
|SMBus|System Management Bus|a single-ended simple two-wire bus for the purpose of lightweight communication|
|SPI|Serial Peripheral Interface|a synchronous serial communication interface specification used for short-distance communication|
|NoC|network-on-chip|a network-based communications subsystem on an integrated circuit|
|AMBA|Advanced Microcontroller Bus Architecture|open-standard, on-chip interconnect specification for the connection and management of functional blocks in system-on-a-chip (SoC) designs|
|AXI|Advanced eXtensible Interface|a parallel high-performance, synchronous, high-frequency, multi-master, multi-slave communication interface, mainly designed for on-chip communication|
|IDE|Integrated Drive Electronics||
|ATA|Advanced Technology Attachment||
|PATA|Parallel ATA||
|SATA|Serial ATA|a computer bus interface that connects host bus adapters to mass storage devices such as hard disk drives, optical drives, and solid-state drives|
|SCSI|Small Computer System Interface|一種用於電腦及其週邊裝置之間（硬碟、軟碟機、光碟機、印表機、掃描器等）系統級介面的獨立處理器標準|
|SAS|Serial Attached SCSI||
|NVMe|NVM Express|an open, logical-device interface specification for accessing a computer's non-volatile storage media usually attached via PCI Express (PCIe) bus|
|M.2|Next Generation Form Factor (NGFF)|a specification for internally mounted computer expansion cards and associated connectors|

# HW
|Term|Full|Note|
|-|-|-|
|RGU|Reset Generation Unit||
|PSU|power supply unit|converts mains AC to low-voltage regulated DC power for the internal components of a computer|
|JTAG|Joint Test Action Group|an industry standard for verifying designs and testing printed circuit boards after manufacture|
|ICE|In-Circuit Emulator|a hardware device or in-circuit emulator used to debug the software of an embedded system|

# File Format
|Term|Full|Note|
|-|-|-|
|FAT|File Allocation Table||
|NTFS|New Technology File System|developed by Microsoft|
|ext2|second extended filesystem|commonly used by the Linux kernel|
|ext3|Third extended filesystem|commonly used by the Linux kernel|
|tmpfs|temporary file storage|data is stored in volatile memory instead of a persistent storage device|
|NFS|Network File System|allowing a user on a client computer to access files over a computer network|
|VFS|Virtual File System||
|ELF|Executable and Linking Format|common standard file format for executable files, object code, shared libraries, and core dumps|

# Storage
|Term|Full|Note|
|-|-|-|
|LP4|Low Power DDR4||
|LP5|Low Power DDR5||
|eMMC|embedded MultiMedia Card|採用「並行傳輸」技術製成，讀寫必須分開執行|
|NVM|Non-Volatile Memory|an retain stored information even after power is removed|

|UFS|Universal Flash Storage|採用全新「串行傳輸」技術，可同時讀寫操作|
|RFS|Remote File System||
|SSD|Solid State Disk||


# Boot
|Term|Full|Note|
|-|-|-|
|MBR|Master Boot Record|a special type of boot sector at the very beginning of partitioned computer mass storage devices|
|GPT|Globally Unique Identifier Partition Table|a standard for the layout of partition tables of a physical computer storage device|
|LBR|logical block addressing|a common scheme used for specifying the location of blocks of data stored on computer storage devices|
|ASLR|Address space layout randomization|a computer security technique involved in preventing exploitation of memory corruption vulnerabilities|
|grub|GRand Unified Bootloader|a boot loader package from the GNU Project|
