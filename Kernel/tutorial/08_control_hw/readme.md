# IO mapped IO
- `$cat /proc/ioports`
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
...
````

# Memory mapped IO (MMIO)
- `$cat /proc/iomem`
````
00000000-00000fff : reserved
00001000-0009f3ff : System RAM
0009f400-0009ffff : reserved
000a0000-000bffff : PCI Bus 0000:00
000c0000-000c7fff : Video ROM
000cc000-000ccfff : Adapter ROM
000d0000-000d3fff : PCI Bus 0000:00
000d4000-000d7fff : PCI Bus 0000:00
000d8000-000dbfff : PCI Bus 0000:00
000dc000-000fffff : reserved
  000f0000-000fffff : System ROM
00100000-bfedffff : System RAM
  01000000-0176ff92 : Kernel code
  0176ff93-01d1ad3f : Kernel data
  01e78000-01fbcfff : Kernel bss
...
````
