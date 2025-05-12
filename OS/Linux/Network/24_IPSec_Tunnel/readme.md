### Initial Environment
- None

### TBD

### Create IPSec tunnel
```
# Topology
# Host A
#  ping/iperf
#  br-lan 192.168.1.1
#  eth1 10.10.10.2
# Router
#  eth1 10.10.10.1
#  br-lan 192.168.2.1
#  ping/iperf

# Host A setting
ifconfig eth1 10.10.10.2 netmask 255.255.255.0
ip route add 192.168.2.0/24 via 10.10.10.1 dev eth1
ip xfrm policy add src 192.168.1.0/24 dst 192.168.2.0/24 dir out tmpl src 10.10.10.2 dst 10.10.10.1 proto esp reqid 0 mode tunnel
ip xfrm policy add src 192.168.2.0/24 dst 192.168.1.0/24 dir in tmpl src 10.10.10.1 dst 10.10.10.2 proto esp reqid 0 mode tunnel
ip xfrm policy add src 192.168.2.0/24 dst 192.168.1.0/24 dir fwd tmpl src 10.10.10.1 dst 10.10.10.2 proto esp reqid 0 mode tunnel
ip xfrm state add src 10.10.10.2 dst 10.10.10.1 proto esp spi 0xc8a985e0 mode tunnel auth sha1 0xa5af42bfcc58e1086f53cd389f3d19ab727f5a9f enc aes 0xcf1da8df12139105e36bcc45290bce1e
ip xfrm state add src 10.10.10.1 dst 10.10.10.2 proto esp spi 0xc8a985e0 mode tunnel auth sha1 0xa5af42bfcc58e1086f53cd389f3d19ab727f5a9f enc aes 0xcf1da8df12139105e36bcc45290bce1e

# Router setting
ip addr add 192.168.2.1/24 dev br-lan
ifconfig eth1 10.10.10.1 netmask 255.255.255.0
ip route add 192.168.1.0/24 via 10.10.10.2 dev eth1
ip xfrm policy add src 192.168.2.0/24 dst 192.168.1.0/24 dir out tmpl src 10.10.10.1 dst 10.10.10.2 proto esp reqid 0 mode tunnel
ip xfrm policy add src 192.168.1.0/24 dst 192.168.2.0/24 dir in tmpl src 10.10.10.2 dst 10.10.10.1 proto esp reqid 0 mode tunnel
ip xfrm policy add src 192.168.1.0/24 dst 192.168.2.0/24 dir fwd tmpl src 10.10.10.2 dst 10.10.10.1 proto esp reqid 0 mode tunnel
ip xfrm state add src 10.10.10.1 dst 10.10.10.2 proto esp spi 0xc8a985e0 mode tunnel auth sha1 0xa5af42bfcc58e1086f53cd389f3d19ab727f5a9f enc aes 0xcf1da8df12139105e36bcc45290bce1e
ip xfrm state add src 10.10.10.2 dst 10.10.10.1 proto esp spi 0xc8a985e0 mode tunnel auth sha1 0xa5af42bfcc58e1086f53cd389f3d19ab727f5a9f enc aes 0xcf1da8df12139105e36bcc45290bce1e
```

### Ping
```
# Host A
ping -I 192.168.1.1 192.168.2.1
```
```
# Router
ping -I 192.168.2.1 192.168.1.1
```
