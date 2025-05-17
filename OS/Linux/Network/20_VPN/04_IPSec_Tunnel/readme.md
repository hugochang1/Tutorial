### Initial Environment
- None

### TBD

### Create IPSec tunnel
```
# Topology
# Host A (ns1)
#  ping/iperf
#  br-lan 192.168.100.1
#  etha 10.10.10.2
# Router
#  r_etha 10.10.10.1
#  br-lan 192.168.200.1
#  ping/iperf

# Create veth pair
sudo ip link add r_etha type veth peer name etha
# Create namespace
sudo ip netns add ns1
# Move etha and ethb into the namespace
sudo ip link set etha netns ns1

# Host A setting
sudo ip netns exec ns1 ip link add name br-lan type bridge
sudo ip netns exec ns1 ip link set dev br-lan up
sudo ip netns exec ns1 ip addr add 192.168.100.1/24 dev br-lan

sudo ip netns exec ns1 ifconfig etha 10.10.10.2 netmask 255.255.255.0
sudo ip netns exec ns1 ip route add 192.168.200.0/24 via 10.10.10.1 dev etha
sudo ip netns exec ns1 ip xfrm policy add src 192.168.100.0/24 dst 192.168.200.0/24 dir out tmpl src 10.10.10.2 dst 10.10.10.1 proto esp reqid 0 mode tunnel
sudo ip netns exec ns1 ip xfrm policy add src 192.168.200.0/24 dst 192.168.100.0/24 dir in tmpl src 10.10.10.1 dst 10.10.10.2 proto esp reqid 0 mode tunnel
sudo ip netns exec ns1 ip xfrm policy add src 192.168.200.0/24 dst 192.168.100.0/24 dir fwd tmpl src 10.10.10.1 dst 10.10.10.2 proto esp reqid 0 mode tunnel
sudo ip netns exec ns1 ip xfrm state add src 10.10.10.2 dst 10.10.10.1 proto esp spi 0xc8a985e0 mode tunnel auth sha1 0xa5af42bfcc58e1086f53cd389f3d19ab727f5a9f enc aes 0xcf1da8df12139105e36bcc45290bce1e
sudo ip netns exec ns1 ip xfrm state add src 10.10.10.1 dst 10.10.10.2 proto esp spi 0xc8a985e0 mode tunnel auth sha1 0xa5af42bfcc58e1086f53cd389f3d19ab727f5a9f enc aes 0xcf1da8df12139105e36bcc45290bce1e

# Router setting
sudo ip link add name br-lan type bridge
sudo ip link set dev br-lan up
sudo ip addr add 192.168.200.1/24 dev br-lan
sudo ifconfig r_etha 10.10.10.1 netmask 255.255.255.0
sudo ip route add 192.168.100.0/24 via 10.10.10.2 dev r_etha
sudo ip xfrm policy add src 192.168.200.0/24 dst 192.168.100.0/24 dir out tmpl src 10.10.10.1 dst 10.10.10.2 proto esp reqid 0 mode tunnel
sudo ip xfrm policy add src 192.168.100.0/24 dst 192.168.200.0/24 dir in tmpl src 10.10.10.2 dst 10.10.10.1 proto esp reqid 0 mode tunnel
sudo ip xfrm policy add src 192.168.100.0/24 dst 192.168.200.0/24 dir fwd tmpl src 10.10.10.2 dst 10.10.10.1 proto esp reqid 0 mode tunnel
sudo ip xfrm state add src 10.10.10.1 dst 10.10.10.2 proto esp spi 0xc8a985e0 mode tunnel auth sha1 0xa5af42bfcc58e1086f53cd389f3d19ab727f5a9f enc aes 0xcf1da8df12139105e36bcc45290bce1e
sudo ip xfrm state add src 10.10.10.2 dst 10.10.10.1 proto esp spi 0xc8a985e0 mode tunnel auth sha1 0xa5af42bfcc58e1086f53cd389f3d19ab727f5a9f enc aes 0xcf1da8df12139105e36bcc45290bce1e
```

### Ping
```
# Host A to Router
sudo ip netns exec ns1 ping -I 192.168.100.1 192.168.200.1
```
```
# Router
ping -I 192.168.200.1 192.168.100.1
```

### tcpdump
```
# Router
# Host A to Router
sudo ip netns exec ns1 ping -I 192.168.100.1 192.168.200.1
sudo tcpdump -i r_etha -n -w tcpdump.pcap
```
![image](https://github.com/user-attachments/assets/3a7d1e1f-9a18-4f6b-a6b3-d00a77fea65c)
![image](https://github.com/user-attachments/assets/2a915053-1ebe-4d09-b5cd-fe70012b2023)
![image](https://github.com/user-attachments/assets/3b91852a-f0b6-4c8c-8013-0e19cf92e4c1)

### Remove
```
sudo ip netns delete ns1

sudo ip xfrm state del src 10.10.10.2 dst 10.10.10.1 proto esp spi 0xc8a985e0
sudo ip xfrm state del src 10.10.10.1 dst 10.10.10.2 proto esp spi 0xc8a985e0

sudo ip xfrm policy del src 192.168.100.0/24 dst 192.168.200.0/24 dir fwd
sudo ip xfrm policy del src 192.168.100.0/24 dst 192.168.200.0/24 dir in
sudo ip xfrm policy del src 192.168.200.0/24 dst 192.168.100.0/24 dir out

sudo ip link del dev br-lan
```
