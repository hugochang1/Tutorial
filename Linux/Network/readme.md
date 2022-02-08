# ifconfig
- configure a network interface
- `$ sudo apt install net-tools`
- `$ ifconfig`
  - `$ ifconfig -a` to show all interfaces including the disables
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
- `UP` and `RUNNING` means the interface is enabled
- `$ ifconfig ens33 down` to disable `ens33` interface
- `$ ifconfig ens33 up` to enable `ens33` interface
- 

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
- `$ traceroute -I <IPv4, IPv6 or FQDN>`
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


# host
- DNS lookup utility
- `$ host <FQDN>`
  - `$ host www.google.com`
````
www.google.com has address 172.217.163.36
www.google.com has IPv6 address 2404:6800:4012:4::2004
````

# NetworkManager
- `$ nmcli`
````
ens33: connected to Wired connection 1
        "Intel 82545EM Gigabit Ethernet Controller (Copper) (PRO/1000 MT Single Port Adapter)"
        ethernet (e1000), 00:0C:29:C1:8B:28, hw, mtu 1500
        ip4 default
        inet4 192.168.163.129/24
        route4 0.0.0.0/0
        route4 192.168.163.0/24

lo: unmanaged
        "lo"
        loopback (unknown), 00:00:00:00:00:00, sw, mtu 65536

DNS configuration:
        servers: 192.168.163.2
        domains: localdomain
        interface: ens33

Use "nmcli device show" to get complete information about known devices and
"nmcli connection show" to get an overview on active connection profiles.

Consult nmcli(1) and nmcli-examples(5) manual pages for complete usage details.
````
- `$ nm-online` to check whether your connection is available
  - return 0 `$ echo $?` means your connection is available
- config file is under `/etc/NetworkManager`


# netstat
- Print network connections
- `$ netstat -nt` to show TCP connections
  - `-n` show IP instead of FQDN
  - `-p` show TCP
  - `-u` show UDP
````
Active Internet connections (w/o servers)
Proto Recv-Q Send-Q Local Address           Foreign Address         State      
tcp        0      0 192.168.163.129:36724   34.120.208.123:443      TIME_WAIT  
tcp        0      0 192.168.163.129:46818   35.161.110.36:443       ESTABLISHED
tcp        0      0 192.168.163.129:34384   34.209.131.4:443        ESTABLISHED
tcp        0      0 192.168.163.129:44998   35.244.181.201:443      ESTABLISHED
````

- `$ netstat -ntl` to show TCP servers on this host
````
Active Internet connections (only servers)
Proto Recv-Q Send-Q Local Address           Foreign Address         State      
tcp        0      0 127.0.0.53:53           0.0.0.0:*               LISTEN     
tcp        0      0 127.0.0.1:631           0.0.0.0:*               LISTEN     
tcp6       0      0 ::1:631                 :::*                    LISTEN     
````

- `$ cat /etc/services` to check known port
````
tcpmux          1/tcp                           # TCP port service multiplexer
echo            7/tcp
echo            7/udp
discard         9/tcp           sink null
discard         9/udp           sink null
systat          11/tcp          users
daytime         13/tcp
...
````

# dhclient
- Dynamic Host Configuration Protocol Client
- `$ sudo dhclient <interface`
  - `$ sudo dhclient ens33`
  - need to remove the default gateway before using dhclient


# sysctl
- configure kernel parameters at runtime
- `$ sysctl -a` to show all kernel parameters
- `$ sudo sysctl -w net.ipv4.ip_forward=1` to enable IP forwarding in different subnetwork


# iptables
- administration tool for IPv4/IPv6 packet filtering and NAT
- `$ sudo iptables -L` to show current filters
````
Chain INPUT (policy ACCEPT)
target     prot opt source               destination         

Chain FORWARD (policy ACCEPT)
target     prot opt source               destination         

Chain OUTPUT (policy ACCEPT)
target     prot opt source               destination    
````
- change the policy by `-P`
  - `$ sudo iptables -P FORWARD DROP`
  - `$ sudo iptables -P FORWARD ACCEPT`
  - `$ sudo iptables -P INPUT DROP`
  - `$ sudo iptables -P INPUT ACCEPT`
  - `$ sudo iptables -P OUTPUT DROP`
  - `$ sudo iptables -P OUTPUT ACCEPT`
- add a new rule by `-A` (append)
  - `$ sudo iptables -A INPUT -s 192.168.163.1 -j DROP`
  - `$ sudo iptables -A INPUT -s 192.168.163.1 -j DROP`
  - `$ sudo iptables -A INPUT -s 192.168.163.1 -j ACCEPT`
  - `$ sudo iptables -A INPUT -s 192.168.163.0/24 -j DROP`
  - `$ sudo iptables -A INPUT -s 192.168.163.1 -p tcp -j DROP`
- add a new rule by `-I` (insert)
  - `$ sudo iptables -I INPUT -s 192.168.163.1 -j DROP` insert to first rule
  - `$ sudo iptables -I INPUT 3 -s 192.168.163.3 -j DROP` insert to 3rd rule
- remove the existed rule by `-D`
  - `$ sudo iptables -D INPUT 1` remove 1st rule in INPUT chain

# arp
- manipulate the system ARP cache
- `$ arp -n` to check ARP cache
  - `-n` don't use DNS
````
Address                  HWtype  HWaddress           Flags Mask            Iface
192.168.163.254          ether   00:50:56:e5:89:48   C                     ens33
192.168.163.2            ether   00:50:56:f4:c2:1e   C                     ens33
192.168.163.1            ether   00:50:56:c0:00:08   C                     ens33
````
- `$ arp -i <interface>` to check ARP cache by interface
  - `$ arp -i ens33`
- `$ sudo arp -d <address>` to delete ARP cache
  - `$ sudo arp -d 192.168.163.2`

# tcpdump
- dump traffic on a network
- `$ sudo tcpdump`
````
tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
listening on ens33, link-type EN10MB (Ethernet), capture size 262144 bytes
05:20:18.407688 ARP, Request who-has _gateway tell 192.168.163.1, length 46
05:20:18.408373 IP ubuntu.49933 > _gateway.domain: 34850+ [1au] PTR? 2.163.168.192.in-addr.arpa. (55)
05:20:18.413074 IP _gateway.domain > ubuntu.49933: 34850 NXDomain 0/1/1 (99)
05:20:18.413169 IP ubuntu.49933 > _gateway.domain: 34850+ PTR? 2.163.168.192.in-addr.arpa. (44)
05:20:18.417758 IP _gateway.domain > ubuntu.49933: 34850 NXDomain 0/1/0 (88)
05:20:18.418250 IP ubuntu.41698 > _gateway.domain: 57280+ [1au] PTR? 1.163.168.192.in-addr.arpa. (55)
05:20:18.422609 IP _gateway.domain > ubuntu.41698: 57280 NXDomain 0/1/1 (99)
05:20:18.428585 IP ubuntu.47833 > _gateway.domain: 36994+ [1au] PTR? 129.163.168.192.in-addr.arpa. (57)
05:20:19.532135 IP 192.168.163.1.49849 > 239.255.255.250.1900: UDP, length 137
05:20:19.532511 IP ubuntu.38740 > _gateway.domain: 29047+ [1au] PTR? 250.255.255.239.in-addr.arpa. (57)
05:20:19.537645 IP _gateway.domain > ubuntu.38740: 29047 NXDomain 0/1/1 (114)
05:20:19.537762 IP ubuntu.38740 > _gateway.domain: 29047+ PTR? 250.255.255.239.in-addr.arpa. (46)
05:20:19.563983 ARP, Request who-has _gateway tell 192.168.163.1, length 46
05:20:19.672671 IP _gateway.domain > ubuntu.38740: 29047 NXDomain 0/1/0 (103)
^C
14 packets captured
19 packets received by filter
5 packets dropped by kernel
````
- `$ sudo tcpdump -i <interface> -w <file>`
  - `$ sudo tcpdump -i ens33 -w tcpdump.pcap`
  - use `ctrl+c` to stop tcpdump
  - `$ sudo chmod 777 tcpdump.pcap` to grant the permission


# wireshark
- Interactively dump and analyze network traffic
- `$ sudo apt install wireshark` to install wireshark
- `$ sudo wireshark &` to launch wireshark


# telnet
- user interface to the TELNET protocol
- `$ telnet www.google.com 80`
````
Trying 172.217.163.36...
Connected to www.google.com.
Escape character is '^]'.
````
- input `GET / HTTP/1.0` and click `Enter` twice
````
HTTP/1.0 200 OK
Date: Tue, 08 Feb 2022 14:26:27 GMT
Expires: -1
Cache-Control: private, max-age=0
...
````

# curl
- transfer a URL
- `$ sudo apt install curl`
- `curl --trace-ascii trace_file http://www.google.com/`
````
<!doctype html><html itemscope="" itemtype="http://schema.org/WebPage" lang="zh-TW"><head><meta
...
````
- `$ vi trace_file`
````
== Info:   Trying 172.217.163.36...
== Info: TCP_NODELAY set
== Info: Connected to www.google.com (172.217.163.36) port 80 (#0)
=> Send header, 78 bytes (0x4e)
0000: GET / HTTP/1.1
0010: Host: www.google.com
0026: User-Agent: curl/7.58.0
003f: Accept: */*
...
````

# lsof
- list open files
- `$ sudo lsof -i`
````
COMMAND    PID            USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
systemd-r  879 systemd-resolve   12u  IPv4   1515      0t0  UDP localhost:domain 
systemd-r  879 systemd-resolve   13u  IPv4   1516      0t0  TCP localhost:domain (LISTEN)
avahi-dae 1062           avahi   12u  IPv4  32502      0t0  UDP *:mdns 
avahi-dae 1062           avahi   13u  IPv6  32503      0t0  UDP *:mdns 
avahi-dae 1062           avahi   14u  IPv4  32504      0t0  UDP *:40956 
avahi-dae 1062           avahi   15u  IPv6  32505      0t0  UDP *:37015 
dhclient  1176            root    6u  IPv4  50312      0t0  UDP *:bootpc 
GeckoMain 2165            hugo  126u  IPv4  76871      0t0  TCP ubuntu:54464->ec2-52-35-251-160.us-west-2.compute.amazonaws.com:https (ESTABLISHED)
cupsd     2767            root    6u  IPv6  72029      0t0  TCP ip6-localhost:ipp (LISTEN)
cupsd     2767            root    7u  IPv4  72030      0t0  TCP localhost:ipp (LISTEN)
cups-brow 2768            root    7u  IPv4  69531      0t0  UDP *:ipp 
````

# nmap
- Network exploration tool and security / port scanner
- `$ sudo apt install nmap`
- `$ nmap <ip>`
  - `$ nmap 192.168.163.2`
````
Starting Nmap 7.60 ( https://nmap.org ) at 2022-02-08 06:42 PST
Nmap scan report for _gateway (192.168.163.2)
Host is up (0.00048s latency).
Not shown: 999 closed ports
PORT   STATE SERVICE
53/tcp open  domain

Nmap done: 1 IP address (1 host up) scanned in 0.06 seconds
````

