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

- $ cat /sys/power/state
````
freeze standby mem disk
````

- $ sudo -s
- \# echo -n standby > /sys/power/state
  - enter suspend to RAM
- \# echo -n disk > /sys/power/state
  - enter suspend to disk
