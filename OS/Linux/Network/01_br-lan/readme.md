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
sudo ip link set gre1 up

sudo ip netns exec ns2 ip link add gre1 type gretap remote 192.168.200.1 local 192.168.200.2 ttl 255
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

### tcpdump
```

```
