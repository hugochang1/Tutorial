### create the virtual netdev with namespace 
#### Topology
- Host A (ns1)
  - etha
    - 192.168.100.2
    - fe80:100::2
- Router
  - r_etha
    - 192.168.100.1
    - fe80:100::1
  - r_ethb
    - 192.168.200.1
    - fe80:200::1
- Host B (ns2)
  - ethb
    - 192.168.200.2
    - fe80:200::2

#### Create the virtual network devices
```
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
sudo ip addr add fe80:100::1/64 dev r_etha
sudo ip addr add 192.168.200.1/24 dev r_ethb
sudo ip addr add fe80:200::1/64 dev r_ethb
sudo ip netns exec ns1 ip addr add 192.168.100.2/24 dev etha
sudo ip netns exec ns1 ip addr add fe80:100::2/64 dev etha
sudo ip netns exec ns2 ip addr add 192.168.200.2/24 dev ethb
sudo ip netns exec ns2 ip addr add fe80:200::2/64 dev ethb

# Bring interfaces up
sudo ip link set r_etha up
sudo ip link set r_ethb up
sudo ip netns exec ns1 ip link set etha up
sudo ip netns exec ns1 ip link set lo up
sudo ip netns exec ns2 ip link set ethb up
sudo ip netns exec ns2 ip link set lo up

# add the routing rule
#   to ensure Host A ping Router different subnet
sudo ip netns exec ns1 ip route add 192.168.200.0/24 via 192.168.100.1 dev etha
#   to ensure Host B ping ROuter's different subnet
sudo ip netns exec ns2 ip route add 192.168.100.0/24 via 192.168.200.1 dev ethb
```

#### Login to Network Namespace
```
sudo ip netns exec ns1 bash
sudo ip netns exec ns2 bash
```

#### ping
```
# Router to Host A
ping -I r_etha 192.168.100.2
ping -I r_etha fe80:100::2

# Host A to Router
sudo ip netns exec ns1 ping -I etha 192.168.100.1
sudo ip netns exec ns1 ping -I etha fe80:100::1

# Router to Host B
ping -I r_ethb 192.168.200.2
ping -I r_ethb fe80:200::2

# Host B to Router
sudo ip netns exec ns2 ping -I ethb 192.168.200.1
sudo ip netns exec ns2 ping -I ethb fe80:200::1
```

#### Remove the virtual network devices
```
sudo ip netns delete ns1
sudo ip netns delete ns2
```

