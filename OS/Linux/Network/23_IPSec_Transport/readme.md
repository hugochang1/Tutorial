### Initial Environment
- None

### Create IPSec transport
```
# [Topology]
# Host A (ns1)
#  etha
#   192.168.100.2
#   fd80:100::2
#
# Router
#  r_etha
#   192.168.100.1
#   fd80:100::1

# Create veth pair
sudo ip link add r_etha type veth peer name etha
# Create namespace
sudo ip netns add ns1
# Move etha and ethb into the namespace
sudo ip link set etha netns ns1
# Assign IP addresses
sudo ip addr add 192.168.100.1/24 dev r_etha
sudo ip addr add fd80:100::1/64 dev r_etha
sudo ip netns exec ns1 ip addr add 192.168.100.2/24 dev etha
sudo ip netns exec ns1 ip addr add fd80:100::2/64 dev etha
# Bring interfaces up
sudo ip link set r_etha up
sudo ip netns exec ns1 ip link set etha up
sudo ip netns exec ns1 ip link set lo up

# create IPSec transport
sudo ip xfrm state add src 192.168.100.2 dst 192.168.100.1 proto esp spi 0x100 mode transport auth sha1 0x1111111111111111111111111111111111111111 enc aes 0x22222222222222222222222222222222
sudo ip xfrm state add src 192.168.100.1 dst 192.168.100.2 proto esp spi 0x100 mode transport auth sha1 0x1111111111111111111111111111111111111111 enc aes 0x22222222222222222222222222222222
sudo ip xfrm policy add src 192.168.100.1 dst 192.168.100.2 dir out tmpl src 192.168.100.1 dst 192.168.100.2 proto esp mode transport
sudo ip xfrm policy add src 192.168.100.2 dst 192.168.100.1 dir in tmpl src 192.168.100.2 dst 192.168.100.1 proto esp mode transport

sudo ip netns exec ns1 ip xfrm state add src 192.168.100.1 dst 192.168.100.2 proto esp spi 0x100 mode transport auth sha1 0x1111111111111111111111111111111111111111 enc aes 0x22222222222222222222222222222222
sudo ip netns exec ns1 ip xfrm state add src 192.168.100.2 dst 192.168.100.1 proto esp spi 0x100 mode transport auth sha1 0x1111111111111111111111111111111111111111 enc aes 0x22222222222222222222222222222222
sudo ip netns exec ns1 ip xfrm policy add src 192.168.100.2 dst 192.168.100.1 dir out tmpl src 192.168.100.2 dst 192.168.100.1 proto esp mode transport
sudo ip netns exec ns1 ip xfrm policy add src 192.168.100.1 dst 192.168.100.2 dir in tmpl src 192.168.100.1 dst 192.168.100.2 proto esp mode transport
```

### ping
```
ping 192.168.100.2
```

### tcpdump
```
sudo tcpdump -i r_etha -n -w tcpdump.pcap
```
![image](https://github.com/user-attachments/assets/9fe6f1db-a8eb-4f6a-a9bf-596b0067d93a)
![image](https://github.com/user-attachments/assets/ed5a7572-cf0b-4f04-b77e-0afe56cbbf23)

### Remove
```
sudo ip netns delete ns1
sudo ip xfrm state del src 192.168.100.2 dst 192.168.100.1 proto esp spi 0x100
sudo ip xfrm state del src 192.168.100.1 dst 192.168.100.2 proto esp spi 0x100
sudo ip xfrm policy del src 192.168.100.1 dst 192.168.100.2 dir out
sudo ip xfrm policy del src 192.168.100.2 dst 192.168.100.1 dir in
```
