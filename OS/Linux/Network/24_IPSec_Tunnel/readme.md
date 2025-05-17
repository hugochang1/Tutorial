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

sudo ip netns exec ns1 ifconfig eth1 10.10.10.2 netmask 255.255.255.0
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
sudo ifconfig eth1 10.10.10.1 netmask 255.255.255.0
sudo ip route add 192.168.100.0/24 via 10.10.10.2 dev r_etha
sudo ip xfrm policy add src 192.168.200.0/24 dst 192.168.100.0/24 dir out tmpl src 10.10.10.1 dst 10.10.10.2 proto esp reqid 0 mode tunnel
sudo ip xfrm policy add src 192.168.100.0/24 dst 192.168.200.0/24 dir in tmpl src 10.10.10.2 dst 10.10.10.1 proto esp reqid 0 mode tunnel
sudo ip xfrm policy add src 192.168.100.0/24 dst 192.168.200.0/24 dir fwd tmpl src 10.10.10.2 dst 10.10.10.1 proto esp reqid 0 mode tunnel
sudo ip xfrm state add src 10.10.10.1 dst 10.10.10.2 proto esp spi 0xc8a985e0 mode tunnel auth sha1 0xa5af42bfcc58e1086f53cd389f3d19ab727f5a9f enc aes 0xcf1da8df12139105e36bcc45290bce1e
sudo ip xfrm state add src 10.10.10.2 dst 10.10.10.1 proto esp spi 0xc8a985e0 mode tunnel auth sha1 0xa5af42bfcc58e1086f53cd389f3d19ab727f5a9f enc aes 0xcf1da8df12139105e36bcc45290bce1e
```

### Ping
```
# Host A
sudo ip netns exec ns1 ping -I 192.168.100.1 192.168.200.1
```
```
# Router
ping -I 192.168.200.1 192.168.100.1
```
