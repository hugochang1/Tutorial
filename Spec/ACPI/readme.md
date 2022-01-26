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
