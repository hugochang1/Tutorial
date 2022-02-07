# ifconfig
- configure a network interface
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
- show the IP routing table
- `$ route -n`
  - `-n` means don't change IP to domain name
````
Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
0.0.0.0         192.168.163.2   0.0.0.0         UG    100    0        0 ens33
169.254.0.0     0.0.0.0         255.255.0.0     U     1000   0        0 ens33
192.168.163.0   0.0.0.0         255.255.255.0   U     100    0        0 ens33
````

# ping
- send ICMP ECHO_REQUEST to network hosts
- `$ ping <IPv4, IPv6 or FQDN>`
  - `$ ping -c2 127.0.0.1`
  - `$ ping www.google.com`
````
PING 127.0.0.1 (127.0.0.1) 56(84) bytes of data.
64 bytes from 127.0.0.1: icmp_seq=1 ttl=64 time=0.032 ms
64 bytes from 127.0.0.1: icmp_seq=2 ttl=64 time=0.057 ms

--- 127.0.0.1 ping statistics ---
2 packets transmitted, 2 received, 0% packet loss, time 1024ms
rtt min/avg/max/mdev = 0.032/0.044/0.057/0.014 ms
````

# traceroute
- Trace the route to a host
- `$ sudo apt install inetutils-traceroute`
- `$ traceroute -I <FQDN>`
  - `$ traceroute -I www.google.com`
  - `-I` use ICMP ECHO as probe
````
traceroute to www.google.com (172.217.163.36), 64 hops max
  1   192.168.163.2  0.045ms  0.058ms  0.001ms 
  2   192.168.50.1  42.711ms  0.872ms  1.025ms 
  3   168.95.98.254  4.529ms  4.297ms  4.330ms 
  4   168.95.24.50  5.623ms  4.117ms  4.132ms 
  5   *  *  * 
  6   220.128.12.189  5.233ms  4.041ms  3.908ms 
  7   72.14.202.34  5.074ms  5.026ms  5.230ms 
  8   142.251.55.131  8.234ms  7.882ms  7.129ms 
  9   142.251.226.169  5.316ms  5.314ms  6.194ms 
 10   172.217.163.36  5.236ms  5.172ms  5.012ms 
````
