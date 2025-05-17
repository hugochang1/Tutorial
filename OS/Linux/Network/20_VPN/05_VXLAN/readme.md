### Initial Environment
- None


### Create the VXLAN
```
# [Topology]
# Host A (ns1)
#  etha
#   192.168.100.2
#   fd80:100::2
#
# Router
#  br-lan (r_etha, vxlan42)
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
#  vxlan42
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

# create VXLAN
sudo modprobe vxlan
sudo ip link add vxlan42 type vxlan id 42 remote 192.168.200.2 local 192.168.200.1 dev r_ethb dstport 4789
sudo ip link set up dev vxlan42

sudo ip netns exec ns2 ip link add vxlan42 type vxlan id 42 remote 192.168.200.1 local 192.168.200.2 dev ethb dstport 4789
sudo ip netns exec ns2 ip addr add 192.168.100.3/24 dev vxlan42
sudo ip netns exec ns2 ip addr add fd80:100::3/64 dev vxlan42
sudo ip netns exec ns2 ip link set up dev vxlan42

# Add physical interfaces to the bridge
sudo ip link set dev r_etha master br-lan
sudo ip link set dev vxlan42 master br-lan
```

### ping from Host B to Host A
```
sudo ip netns exec ns2 ping 192.168.100.2 -c 3
sudo ip netns exec ns2 ping -I vxlan42 fd80:100::2 -c 3
```

### tcpdump
```
sudo tcpdump -i r_ethb -n -w tcpdump.pcap
```
![image](https://github.com/user-attachments/assets/7419803c-4162-48ec-a150-02e775cd1b46)
![image](https://github.com/user-attachments/assets/9bd23f3a-c977-4d58-9346-92fdf2531405)


### ifconfig
```
# Host A ifconfig
sudo ip netns exec ns1 ifconfig
etha: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.100.2  netmask 255.255.255.0  broadcast 0.0.0.0
        inet6 fe80::b882:54ff:fe9b:32e5  prefixlen 64  scopeid 0x20<link>
        inet6 fd80:100::2  prefixlen 64  scopeid 0x0<global>
        ether ba:82:54:9b:32:e5  txqueuelen 1000  (Ethernet)

# Router ifconfig
ifconfig
br-lan: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1450
        inet 192.168.100.1  netmask 255.255.255.0  broadcast 0.0.0.0
        inet6 fe80::a8bf:f0ff:fe7a:41a  prefixlen 64  scopeid 0x20<link>
        inet6 fd80:100::1  prefixlen 64  scopeid 0x0<global>
        ether 26:fe:bd:2d:9b:5a  txqueuelen 1000  (Ethernet)
r_etha: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet6 fe80::d02b:a7ff:fefd:a5c6  prefixlen 64  scopeid 0x20<link>
        ether d2:2b:a7:fd:a5:c6  txqueuelen 1000  (Ethernet)
r_ethb: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.200.1  netmask 255.255.255.0  broadcast 0.0.0.0
        inet6 fe80::284c:2bff:fe00:f06b  prefixlen 64  scopeid 0x20<link>
        inet6 fd80:200::1  prefixlen 64  scopeid 0x0<global>
        ether 2a:4c:2b:00:f0:6b  txqueuelen 1000  (Ethernet)
vxlan42: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1450
        inet6 fe80::24fe:bdff:fe2d:9b5a  prefixlen 64  scopeid 0x20<link>
        ether 26:fe:bd:2d:9b:5a  txqueuelen 1000  (Ethernet)


# Host B ifconfig
sudo ip netns exec ns2 ifconfig
ethb: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.200.2  netmask 255.255.255.0  broadcast 0.0.0.0
        inet6 fd80:200::2  prefixlen 64  scopeid 0x0<global>
        inet6 fe80::90e8:44ff:fe79:3679  prefixlen 64  scopeid 0x20<link>
        ether 92:e8:44:79:36:79  txqueuelen 1000  (Ethernet)
vxlan42: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1450
        inet 192.168.100.3  netmask 255.255.255.0  broadcast 0.0.0.0
        inet6 fe80::b497:1dff:fef7:1e78  prefixlen 64  scopeid 0x20<link>
        inet6 fd80:100::3  prefixlen 64  scopeid 0x0<global>
        ether b6:97:1d:f7:1e:78  txqueuelen 1000  (Ethernet)
```

### clean
```
sudo ip link del dev br-lan
sudo ip netns delete ns1
sudo ip netns delete ns2
```

