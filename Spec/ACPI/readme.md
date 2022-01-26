# Gx and Sx state
|Gx|Name|Sx|Description|
|-|-|-|-|
|G0|Wokring|S0|1. The computer is running (monitor can be on/off)|
|G1|Sleeping|S0ix|Partial processor SoC sleep|
|G1|Sleeping|S1|CPU(s) stops executing instructions and The power to the CPU(s) and RAM is maintained|
|G1|Sleeping|S2|same as S1 except CPU powered off|
|G1|Sleeping|S3|Suspend to RAM, RAM remains powered|
|G1|Sleeping|S4|Suspend to Disk, the system is powered down|
|G2|Soft Off|S5|same as G3 except the power supply unit (PSU) still supplies power, at a minimum. Other components may remain powered so the computer can "wake" on input from the keyboard, clock, modem, LAN, or USB device|
|G3|Mechanical Off||The computer's power has been totally removed|

# Term
|Term|Full|Description|
|-|-|-|
|APM|Advanced Power Management||
|ACPI|Advanced Configuration and Power Interface|作業系統電源管理、硬體組態介面，是一種開放標準，取代了進階電源管理、多處理器規範、舊式隨插即用規範|
|OSPM|Operating System-directed configuration and Power Management||
|APIC|Advanced Programmable Interrupt Controller||
|ASL|ACPI Source Language||
|FACS|Firmware ACPI Control Structure|在讀寫記憶體中的一種結構，BIOS用它來實現韌體和OS之間的資訊交換|
|DSDT|Differentiated System Description Table||
|FADT|Fixed ACPI Description Table||
|RSDP|Root System Description Pointer||
|RSDT|Root System Description Table||
|I/O APIC|Input/Output Advanced Programmable Interrupt Controller||
|I/O SAPIC|Input/Output Streamlined Advanced Programmable Interrupt Controller||

# ACPI Tables
- RSDP (Root System Description Pointer)
  - RSDT (Root System Description Table)
    - APIC (Multiple APIC Description Table)
    - MCFG (PCIe memory mapped configuration space base address description table)
    - BOOT (Simple Boot Flag Table)
    - SSDT (Secondary System Description Table)
      - AML (ACPI Machine Language)
    - FADT (Fixed ACPI Description Table)
      - FACS (Firmware ACPI Control Structure)
      - DSDT (Differentiated System Description Table)
        - AML (ACPI Machine Language)

# Linux Command
- $ cat /sys/power/state
````
freeze standby mem disk
````

- $ sudo -s
- \# echo -n standby > /sys/power/state
  - enter suspend to RAM
- \# echo -n disk > /sys/power/state
  - enter suspend to disk
- $ cat /proc/interrupts
````
            CPU0       CPU1       CPU2       CPU3       CPU4 
   0:          4          0          0          0          0          0          0          0          0   IO-APIC    2-edge      timer
   1:          0          0          0         16          0          0        326          0          0   IO-APIC    1-edge      i8042
   8:          0          0          0          0          1          0          0          0          0   IO-APIC    8-edge      rtc0
   9:          0          0          0          0          0          0          0          0          0   IO-APIC    9-fasteoi   acpi
...
````

- $ ls -al /sys/firmware/acpi/tables/
````
total 0
drwxr-xr-x 4 root root      0 Jan 26 07:40 .
drwxr-xr-x 5 root root      0 Jan 26 07:40 ..
-r-------- 1 root root   1858 Jan 26 08:14 APIC
-r-------- 1 root root     40 Jan 26 08:14 BOOT
drwxr-xr-x 2 root root      0 Jan 26 08:14 data
-r-------- 1 root root 138866 Jan 26 08:14 DSDT
drwxr-xr-x 2 root root      0 Jan 26 08:14 dynamic
-r-------- 1 root root    244 Jan 26 08:14 FACP
-r-------- 1 root root     64 Jan 26 08:14 FACS
-r-------- 1 root root     56 Jan 26 08:14 HPET
-r-------- 1 root root     60 Jan 26 08:14 MCFG
-r-------- 1 root root   2256 Jan 26 08:14 SRAT
-r-------- 1 root root     40 Jan 26 08:14 WAET
````

- $ sudo apt-get install acpidump
- $ sudo acpidump -o acpidump.txt
- $ cat acpidump.txt
````MCFG @ 0x0000000000000000
  0000: 4D 43 46 47 3C 00 00 00 01 6E 50 54 4C 54 44 20  MCFG<....nPTLTD 
  0010: 24 50 43 49 54 42 4C 24 00 00 04 06 20 4C 54 50  $PCITBL$.... LTP
  0020: 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 F0  ................
  0030: 00 00 00 00 00 00 00 7F 00 00 00 00              ............

APIC @ 0x0000000000000000
  0000: 41 50 49 43 42 07 00 00 01 DA 50 54 4C 54 44 20  APICB.....PTLTD 
  0010: 09 20 41 50 49 43 20 20 00 00 04 06 20 4C 54 50  . APIC  .... LTP
  0020: 00 00 00 00 00 00 E0 FE 01 00 00 00 00 08 00 00  ................
  0030: 01 00 00 00 00 08 01 01 01 00 00 00 00 08 02 02  ................
  0040: 01 00 00 00 00 08 03 04 01 00 00 00 00 08 04 05  ................
  0050: 01 00 00 00 00 08 05 06 01 00 00 00 00 08 06 08  ................
  0060: 01 00 00 00 00 08 07 09 01 00 00 00 00 08 08 0A  ................
...
````


# Kernel Doc
- Documentation/admin-guide/kernel-parameters.txt
````
	acpi=		[HW,ACPI,X86,ARM64]
			Advanced Configuration and Power Interface
			Format: { force | on | off | strict | noirq | rsdt |
				  copy_dsdt }
			force -- enable ACPI if default was off
			on -- enable ACPI but allow fallback to DT [arm64]
			off -- disable ACPI if default was on
			noirq -- do not use ACPI for IRQ routing
			strict -- Be less tolerant of platforms that are not
				strictly ACPI specification compliant.
			rsdt -- prefer RSDT over (default) XSDT
			copy_dsdt -- copy DSDT to memory
			For ARM64, ONLY "acpi=off", "acpi=on" or "acpi=force"
			are available

			See also Documentation/power/runtime_pm.rst, pci=noacpi

	acpi_apic_instance=	[ACPI, IOAPIC]
			Format: <int>
			2: use 2nd APIC table, if available
			1,0: use 1st APIC table
			default: 0
...
````

# Kernel Source Code
- arch/x86/kernel/acpi/boot.c
  - acpi_boot_table_init()
