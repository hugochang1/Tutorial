# ifconfig
- `$ sudo apt install net-tools`
- `$ ifconfig`
````
ens33: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.163.129  netmask 255.255.255.0  broadcast 192.168.163.255
        inet6 fe80::a136:1861:9471:dac4  prefixlen 64  scopeid 0x20<link>
        ether 00:0c:29:c1:8b:28  txqueuelen 1000  (Ethernet)
        RX packets 5584  bytes 7208787 (7.2 MB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 4075  bytes 300479 (300.4 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 1000  (Local Loopback)
        RX packets 303  bytes 24973 (24.9 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 303  bytes 24973 (24.9 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
````

# route
- `$ route -n`
````
Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
0.0.0.0         192.168.163.2   0.0.0.0         UG    100    0        0 ens33
169.254.0.0     0.0.0.0         255.255.0.0     U     1000   0        0 ens33
192.168.163.0   0.0.0.0         255.255.255.0   U     100    0        0 ens33
````

