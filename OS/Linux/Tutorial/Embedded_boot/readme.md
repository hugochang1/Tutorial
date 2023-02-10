# ROM code
- programmed SW in SoC and cannot be changed
- use the processor's SRAM (e.g. cached), the size could be 4KB to 100KB
- load the second stage program loader from one of following
  - NAND: 前幾個page
  - flash over SPI
  - eMMC: first block
  - Ethernet
  - USB
  - UART
  - etc.

# Second stage program loader
- Initial external memory (ex: DRAM)
- load the third stage program loader (ex: U-boot or Barebox) in the fixed flash block to DRAM

# Third stage program loader
- load kernel, dts and initramfs
- provide some command interface for user to do the configuration
