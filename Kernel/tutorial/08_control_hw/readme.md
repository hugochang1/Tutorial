# Memory Barrier
- `barrier()`
  - compile time level barrier
- `wmb()`
  - runtime level barrier for write operation
- `rmb()`
  - runtime level barrier for read operation
- `mb()`
  - runtime level barrier for read and write operation
- `volatile`
  - `volatile int *p`
  - read/write of `p` must be via DRAM instead of CPU's cache

# source code
````
#include <linux/io.h>

	void __iomem *mem;
	int addr = 0x10006004;
	int value = 0x12345678;
	int tmp;
	
	mem = ioremap_nocache(addr, 0x1000);
	if (mem == NULL) {
		pr_err("ioremap_nocache() failed\n");
	} else {
		pr_err("ioremap_nocache() success\n");
		
		writel(value, mem); //write 4 bytes
		tmp = readl(mem);   //read 4 bytes
		pr_err("readl()=0x%x\n", tmp);
		
		iounmap(mem);
	}
````

# IO mapped IO
- `$ sudo cat /proc/ioports`
````
0000-0cf7 : PCI Bus 0000:00
  0000-001f : dma1
  0020-0021 : PNP0001:00
    0020-0021 : pic1
  0040-0043 : timer0
  0050-0053 : timer1
  0060-0060 : keyboard
  0061-0061 : PNP0800:00
  0064-0064 : keyboard
  0070-0071 : rtc0
  0080-008f : dma page reg
  00a0-00a1 : PNP0001:00
    00a0-00a1 : pic2
  00c0-00df : dma2
  00f0-00ff : fpu
  0170-0177 : 0000:00:07.1
    0170-0177 : ata_piix
  01f0-01f7 : 0000:00:07.1
    01f0-01f7 : ata_piix
  0376-0376 : 0000:00:07.1
    0376-0376 : ata_piix
  03c0-03df : vga+
  03f6-03f6 : 0000:00:07.1
    03f6-03f6 : ata_piix
  03f8-03ff : serial
  04d0-04d1 : PNP0001:00
  0cf0-0cf1 : pnp 00:00
0cf8-0cff : PCI conf1
0d00-feff : PCI Bus 0000:00
  1000-103f : 0000:00:07.3
    1000-103f : pnp 00:00
      1000-1003 : ACPI PM1a_EVT_BLK
      1004-1005 : ACPI PM1a_CNT_BLK
      1008-100b : ACPI PM_TMR
      100c-100f : ACPI GPE0_BLK
  1040-104f : 0000:00:07.3
    1040-104f : pnp 00:00
  1060-106f : 0000:00:07.1
    1060-106f : ata_piix
  1070-107f : 0000:00:0f.0
    1070-107f : vmwgfx probe
  1080-10bf : 0000:00:07.7
    1080-10bf : vmw_vmci
  1400-14ff : 0000:00:10.0
  2000-3fff : PCI Bus 0000:02
    2000-203f : 0000:02:01.0
      2000-203f : e1000
    2040-207f : 0000:02:02.0
      2040-207f : Ensoniq AudioPCI
    2080-209f : 0000:02:00.0
      2080-209f : uhci_hcd
  4000-4fff : PCI Bus 0000:03
  5000-5fff : PCI Bus 0000:0b
  6000-6fff : PCI Bus 0000:13
  7000-7fff : PCI Bus 0000:1b
  8000-8fff : PCI Bus 0000:04
  9000-9fff : PCI Bus 0000:0c
  a000-afff : PCI Bus 0000:14
  b000-bfff : PCI Bus 0000:1c
  c000-cfff : PCI Bus 0000:05
  d000-dfff : PCI Bus 0000:0d
  e000-efff : PCI Bus 0000:15
  fce0-fcff : pnp 00:06

...
````

# Memory mapped IO (MMIO)
- `$ sudo cat /proc/iomem`
````
00000000-00000fff : Reserved
00001000-0009e7ff : System RAM
0009e800-0009ffff : Reserved
000a0000-000bffff : PCI Bus 0000:00
000c0000-000c7fff : Video ROM
000ca000-000cafff : Adapter ROM
000cb000-000ccfff : Adapter ROM
000d0000-000d3fff : PCI Bus 0000:00
000d4000-000d7fff : PCI Bus 0000:00
000d8000-000dbfff : PCI Bus 0000:00
000dc000-000fffff : Reserved
  000f0000-000fffff : System ROM
00100000-bfecffff : System RAM
bfed0000-bfefefff : ACPI Tables
bfeff000-bfefffff : ACPI Non-volatile Storage
bff00000-bfffffff : System RAM
c0000000-febfffff : PCI Bus 0000:00
  c0008000-c000bfff : 0000:00:10.0
  e5b00000-e5bfffff : PCI Bus 0000:22
  e5c00000-e5cfffff : PCI Bus 0000:1a
  e5d00000-e5dfffff : PCI Bus 0000:12
  e5e00000-e5efffff : PCI Bus 0000:0a
  e5f00000-e5ffffff : PCI Bus 0000:21
  e6000000-e60fffff : PCI Bus 0000:19
  e6100000-e61fffff : PCI Bus 0000:11
  e6200000-e62fffff : PCI Bus 0000:09
  e6300000-e63fffff : PCI Bus 0000:20
  e6400000-e64fffff : PCI Bus 0000:18
  e6500000-e65fffff : PCI Bus 0000:10
  e6600000-e66fffff : PCI Bus 0000:08
  e6700000-e67fffff : PCI Bus 0000:1f
  e6800000-e68fffff : PCI Bus 0000:17
  e6900000-e69fffff : PCI Bus 0000:0f
  e6a00000-e6afffff : PCI Bus 0000:07
  e6b00000-e6bfffff : PCI Bus 0000:1e
  e6c00000-e6cfffff : PCI Bus 0000:16
  e6d00000-e6dfffff : PCI Bus 0000:0e
  e6e00000-e6efffff : PCI Bus 0000:06
  e6f00000-e6ffffff : PCI Bus 0000:1d
  e7000000-e70fffff : PCI Bus 0000:15
  e7100000-e71fffff : PCI Bus 0000:0d
  e7200000-e72fffff : PCI Bus 0000:05
  e7300000-e73fffff : PCI Bus 0000:1c
  e7400000-e74fffff : PCI Bus 0000:14
  e7500000-e75fffff : PCI Bus 0000:0c
  e7600000-e76fffff : PCI Bus 0000:04
  e7700000-e77fffff : PCI Bus 0000:1b
  e7800000-e78fffff : PCI Bus 0000:13
  e7900000-e79fffff : PCI Bus 0000:0b
  e7a00000-e7afffff : PCI Bus 0000:03
  e7b00000-e7ffffff : PCI Bus 0000:02
  e8000000-efffffff : 0000:00:0f.0
    e8000000-efffffff : vmwgfx probe
  f0000000-f7ffffff : PCI MMCONFIG 0000 [bus 00-7f]
    f0000000-f7ffffff : Reserved
      f0000000-f7ffffff : pnp 00:06
...
````
