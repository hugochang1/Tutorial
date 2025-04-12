### Background
- on Windows, if you're trying to ping a destination from a specific source IP address that's in a different subnet, there are some key things to ensure for it to work properly
- Windows IPv4 address: `192.168.1.116`
- Ping target: `192.168.2.1`
- `ping -S <source_address> <target_address>`
- `ping -S 192.168.1.116 192.168.2.1`

### Run Command Prompt as Administrator
- You need to have adminstrator permission to do `route add` in command line
- Press `Start`
- Type `cmd`
- Right-click on Command Prompt
- Select "Run as administrator"

### route print
- `route print`
```
===========================================================================
介面清單
  7...xx xx xx xx xx xx ......Realtek PCIe GbE Family Controller
  3...xx xx xx xx xx xx ......Microsoft Wi-Fi Direct Virtual Adapter
 17...xx xx xx xx xx xx ......Microsoft Wi-Fi Direct Virtual Adapter #2
 11...xx xx xx xx xx xx ......VMware Virtual Ethernet Adapter for VMnet1
 12...xx xx xx xx xx xx ......VMware Virtual Ethernet Adapter for VMnet8
 14...xx xx xx xx xx xx ......Realtek RTL8852AE WiFi 6 802.11ax PCIe Adapter
  8...xx xx xx xx xx xx ......Bluetooth Device (Personal Area Network)
  1...........................Software Loopback Interface 1
===========================================================================

IPv4 路由表
===========================================================================
使用中的路由:
網路目的地                 網路遮罩         閘道          介面       計量
          0.0.0.0          0.0.0.0      192.168.1.1    192.168.1.116     45
        127.0.0.0        255.0.0.0            在連結上         127.0.0.1    331
        127.0.0.1  255.255.255.255            在連結上         127.0.0.1    331
  127.255.255.255  255.255.255.255            在連結上         127.0.0.1    331
      192.168.1.0    255.255.255.0            在連結上     192.168.1.116    301
    192.168.1.116  255.255.255.255            在連結上     192.168.1.116    301
    192.168.1.255  255.255.255.255            在連結上     192.168.1.116    301
      192.168.2.0    255.255.255.0            在連結上     192.168.1.116     46
    192.168.163.0    255.255.255.0            在連結上     192.168.163.1    291
    192.168.163.1  255.255.255.255            在連結上     192.168.163.1    291
  192.168.163.255  255.255.255.255            在連結上     192.168.163.1    291
    192.168.248.0    255.255.255.0            在連結上     192.168.248.1    291
    192.168.248.1  255.255.255.255            在連結上     192.168.248.1    291
  192.168.248.255  255.255.255.255            在連結上     192.168.248.1    291
        224.0.0.0        240.0.0.0            在連結上         127.0.0.1    331
        224.0.0.0        240.0.0.0            在連結上     192.168.1.116    301
        224.0.0.0        240.0.0.0            在連結上     192.168.163.1    291
        224.0.0.0        240.0.0.0            在連結上     192.168.248.1    291
  255.255.255.255  255.255.255.255            在連結上         127.0.0.1    331
  255.255.255.255  255.255.255.255            在連結上     192.168.1.116    301
  255.255.255.255  255.255.255.255            在連結上     192.168.163.1    291
  255.255.255.255  255.255.255.255            在連結上     192.168.248.1    291
===========================================================================
```
- interface number `14` is our source interface
- `192.168.1.0    255.255.255.0            在連結上     192.168.1.116` is our source route

### route add
- `route add 192.168.2.0 MASK 255.255.255.0 192.168.1.116 IF 14`
- `route print`
```
      192.168.2.0    255.255.255.0            在連結上     192.168.1.116     46
```

### route delete
- `route -p delete 192.168.2.0`
