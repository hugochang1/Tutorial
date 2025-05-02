### What is proxy ARP
- Proxy ARP allows a router to answer ARP requests on behalf of another device.
- This is useful when two devices are on different subnets or VLANs but believe they’re on the same LAN.
- IPv6 uses proxy neighboring discovery protocol (proxy NDP)

### notice
- still need to add the routing rule, but next hop can be ignored
- IPv4 is work
- IPv6 is TBD
- suggest the method which configures the next-hop in the routing rule

### enable proxy ARP and IP forward
```
# on the router
echo 1 | sudo tee /proc/sys/net/ipv4/conf/all/proxy_arp
echo 1 | sudo tee /proc/sys/net/ipv6/conf/all/proxy_ndp
echo 1 | sudo tee /proc/sys/net/ipv4/ip_forward
echo 1 | sudo tee /proc/sys/net/ipv6/conf/all/forwarding
```

### Create the virtual network devices
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
#  r_ethb
#   192.168.200.1
#   fd80:200::1
#
# Host B (ns2)
#  ethb
#   192.168.200.2
#   fd80:200::2

# Create veth pair
sudo ip link add r_etha type veth peer name etha
sudo ip link add r_ethb type veth peer name ethb

# Create namespace
sudo ip netns add ns1
sudo ip netns add ns2

# Move etha and ethb into the namespace
sudo ip link set etha netns ns1
sudo ip link set ethb netns ns2

# Assign IP addresses
sudo ip addr add 192.168.100.1/24 dev r_etha
sudo ip addr add fd80:100::1/64 dev r_etha
sudo ip addr add 192.168.200.1/24 dev r_ethb
sudo ip addr add fd80:200::1/64 dev r_ethb
sudo ip netns exec ns1 ip addr add 192.168.100.2/24 dev etha
sudo ip netns exec ns1 ip addr add fd80:100::2/64 dev etha
sudo ip netns exec ns2 ip addr add 192.168.200.2/24 dev ethb
sudo ip netns exec ns2 ip addr add fd80:200::2/64 dev ethb

# Bring interfaces up
sudo ip link set r_etha up
sudo ip link set r_ethb up
sudo ip netns exec ns1 ip link set etha up
sudo ip netns exec ns1 ip link set lo up
sudo ip netns exec ns2 ip link set ethb up
sudo ip netns exec ns2 ip link set lo up

# add the routing rule (the next hop can be ignored)
# sudo ip netns exec ns1 ip route add 192.168.200.0/24 via 192.168.100.1 dev etha
# sudo ip netns exec ns1 ip route add fd80:200::0/64 via fd80:100::1 dev etha
# sudo ip netns exec ns2 ip route add 192.168.100.0/24 via 192.168.200.1 dev ethb
# sudo ip netns exec ns2 ip route add fd80:100::0/64 via fd80:200::1 dev ethb
sudo ip netns exec ns1 ip route add 192.168.200.0/24 dev etha
sudo ip netns exec ns1 ip route add fd80:200::0/64 dev etha
sudo ip netns exec ns2 ip route add 192.168.100.0/24 dev ethb
sudo ip netns exec ns2 ip route add fd80:100::0/64 dev ethb

# Add the proxy neighbor entry
sudo ip -6 neigh add proxy fd80:200::1 dev r_etha
sudo ip -6 neigh add proxy fd80:200::2 dev r_etha
sudo ip -6 neigh add proxy fd80:100::1 dev r_ethb
sudo ip -6 neigh add proxy fd80:100::2 dev r_ethb
```

#### ping
```
# Host A to Host B
sudo ip netns exec ns1 ping -I etha 192.168.200.2 -c 3
sudo ip netns exec ns1 ping -I fd80:100::2 fd80:200::2 -c 3

# Host B to Host A
sudo ip netns exec ns2 ping -I ethb 192.168.100.2 -c 3
sudo ip netns exec ns2 ping -I fd80:200::2 fd80:100::2 -c 3
```
