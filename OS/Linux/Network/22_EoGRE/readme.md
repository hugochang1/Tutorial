### Initial Environment
- None

### Create the bridge interface
```
# [Topology]
# Host A (ns1)
#  etha
#   192.168.100.2
#   fd80:100::2
#
# Router
#  br-lan (r_etha, gre1)
#   192.168.100.1
#   fd80:100::1
#  r_ethb
#   192.168.200.1
#   fd80:200::1
#
# Host B (ns2)
#  ethb
#   192.168.200.2
#   fd80:200::2
#  gre1
#   192.168.100.3
#   fd80:100::3

# Create veth pair
sudo ip link add r_etha type veth peer name etha
sudo ip link add r_ethb type veth peer name ethb
# Create namespace
sudo ip netns add ns1
sudo ip netns add ns2
# Move etha and ethb into the namespace
sudo ip link set etha netns ns1
sudo ip link set ethb netns ns2
# Bring interfaces up
sudo ip link set r_etha up
sudo ip link set r_ethb up
sudo ip netns exec ns1 ip link set etha up
sudo ip netns exec ns1 ip link set lo up
sudo ip netns exec ns2 ip link set ethb up
sudo ip netns exec ns2 ip link set lo up

# Create the bridge interface
sudo ip link add name br-lan type bridge
sudo ip link set dev br-lan up

# Assign IP addresses
sudo ip addr add 192.168.200.1/24 dev r_ethb
sudo ip addr add fd80:200::1/64 dev r_ethb
sudo ip addr add 192.168.100.1/24 dev br-lan
sudo ip addr add fd80:100::1/64 dev br-lan
sudo ip netns exec ns1 ip addr add 192.168.100.2/24 dev etha
sudo ip netns exec ns1 ip addr add fd80:100::2/64 dev etha
sudo ip netns exec ns2 ip addr add 192.168.200.2/24 dev ethb
sudo ip netns exec ns2 ip addr add fd80:200::2/64 dev ethb

# create GRE
sudo ip link add gre1 type gretap remote 192.168.200.2 local 192.168.200.1 ttl 255
# sudo ip link add gre1 type ip6gretap remote fd80:200::2 local fd80:200::1 ttl 255
sudo ip link set gre1 up

sudo ip netns exec ns2 ip link add gre1 type gretap remote 192.168.200.1 local 192.168.200.2 ttl 255
# sudo ip netns exec ns2 ip link add gre1 type ip6gretap remote fd80:200::1 local fd80:200::2 ttl 255
sudo ip netns exec ns2 ip addr add 192.168.100.3/24 dev gre1
sudo ip netns exec ns2 ip addr add fd80:100::3/64 dev gre1
sudo ip netns exec ns2 ip link set gre1 up


# Add physical interfaces to the bridge
sudo ip link set dev r_etha master br-lan
sudo ip link set dev gre1 master br-lan

```

### To check the members (i.e., slave interfaces) of the br-lan
```
ip link show master br-lan

# 5: r_etha@if4: <BROADCAST,MULTICAST> mtu 1500 qdisc noop master br-lan state DOWN mode DEFAULT group default qlen 1000
#     link/ether c2:3f:0c:03:44:74 brd ff:ff:ff:ff:ff:ff link-netnsid 0
# 7: r_ethb@if6: <BROADCAST,MULTICAST> mtu 1500 qdisc noop master br-lan state DOWN mode DEFAULT group default qlen 1000
#     link/ether da:22:32:a6:44:06 brd ff:ff:ff:ff:ff:ff link-netnsid 1
```

### ping from Host A to Host B
```
sudo ip netns exec ns1 ping 192.168.100.3
```

### delete br-lan
```
sudo ip link del dev br-lan
```

### ifconfig
```
# Host A
sudo ip netns exec ns1 ifconfig
```
```
etha: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.100.2  netmask 255.255.255.0  broadcast 0.0.0.0
        inet6 fd80:100::2  prefixlen 64  scopeid 0x0<global>
        inet6 fe80::a0c7:81ff:fe59:2c38  prefixlen 64  scopeid 0x20<link>
        ether a2:c7:81:59:2c:38  txqueuelen 1000  (Ethernet)
        RX packets 89  bytes 10370 (10.3 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 34  bytes 2816 (2.8 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
```

```
# Router
ifconfig
```
```
br-lan: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1462
        inet 192.168.100.1  netmask 255.255.255.0  broadcast 0.0.0.0
        inet6 fd80:100::1  prefixlen 64  scopeid 0x0<global>
        inet6 fe80::10c4:84ff:fe22:fb7  prefixlen 64  scopeid 0x20<link>
        ether 0a:68:95:de:da:f1  txqueuelen 1000  (Ethernet)
        RX packets 31  bytes 2180 (2.1 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 41  bytes 5337 (5.3 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

gre1: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1462
        inet6 fe80::c44d:35ff:fe6a:7c3d  prefixlen 64  scopeid 0x20<link>
        ether c6:4d:35:6a:7c:3d  txqueuelen 1000  (Ethernet)
        RX packets 33  bytes 2726 (2.7 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 89  bytes 9124 (9.1 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

r_etha: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet6 fe80::868:95ff:fede:daf1  prefixlen 64  scopeid 0x20<link>
        ether 0a:68:95:de:da:f1  txqueuelen 1000  (Ethernet)
        RX packets 34  bytes 2816 (2.8 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 89  bytes 10370 (10.3 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

r_ethb: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.200.1  netmask 255.255.255.0  broadcast 0.0.0.0
        inet6 fd80:200::1  prefixlen 64  scopeid 0x0<global>
        inet6 fe80::2079:7aff:fe4f:9b17  prefixlen 64  scopeid 0x20<link>
        ether 22:79:7a:4f:9b:17  txqueuelen 1000  (Ethernet)
        RX packets 60  bytes 5852 (5.8 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 137  bytes 18784 (18.7 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
```

```
# Host B
sudo ip netns exec ns2 ifconfig
```
```
ethb: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.200.2  netmask 255.255.255.0  broadcast 0.0.0.0
        inet6 fd80:200::2  prefixlen 64  scopeid 0x0<global>
        inet6 fe80::28bd:1ff:fea4:a1bb  prefixlen 64  scopeid 0x20<link>
        ether 2a:bd:01:a4:a1:bb  txqueuelen 1000  (Ethernet)
        RX packets 144  bytes 19477 (19.4 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 64  bytes 6114 (6.1 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

gre1: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1462
        inet 192.168.100.3  netmask 255.255.255.0  broadcast 0.0.0.0
        inet6 fe80::80c9:6fff:fe85:f574  prefixlen 64  scopeid 0x20<link>
        inet6 fd80:100::3  prefixlen 64  scopeid 0x0<global>
        ether 82:c9:6f:85:f5:74  txqueuelen 1000  (Ethernet)
        RX packets 91  bytes 10561 (10.5 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 34  bytes 2320 (2.3 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
```

### tcpdump
```
# ping from Host A to Host B
sudo ip netns exec ns1 ping 192.168.100.3
```
```
# Router
sudo tcpdump -i r_ethb -n -w tcpdump.pcap
```
![image](https://github.com/user-attachments/assets/25dae905-b7d2-4d0d-8cc0-30ec5c062bb3)
![image](https://github.com/user-attachments/assets/24993b2b-8e26-4bf2-8388-f17460c123ba)

```
# Router
sudo tcpdump -i br-lan -n -w tcpdump.pcap
```
![image](https://github.com/user-attachments/assets/93ca127b-4071-49a1-a96a-1d8de60b6513)
![image](https://github.com/user-attachments/assets/fd630326-7ae2-4fd7-bb97-8dba0ecfef5e)


