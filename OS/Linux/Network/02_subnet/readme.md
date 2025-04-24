### Topology
- veth0
  - 192.168.10.1/24
  - 192.168.10.101/24
  - 192.168.101.1/24
  - fd00::1/64
  - fe01::1/64
- veth1 (ns1)
  - 192.168.10.2/24
  - 192.168.10.102/24
  - 192.168.102.2/24
  - fd00::2/64
  - fe02::2/64

#### Create a virtual network device
```
# Create veth pair
sudo ip link add veth0 type veth peer name veth1

# Create namespace
sudo ip netns add ns1

# Move veth1 into the namespace
sudo ip link set veth1 netns ns1

# Assign IP addresses
sudo ip addr add 192.168.10.1/24 dev veth0
sudo ip addr add 192.168.10.101/24 dev veth0
sudo ip addr add 192.168.101.1/24 dev veth0
sudo ip addr add fd00::1/64 dev veth0
sudo ip addr add fe01::1/64 dev veth0
sudo ip netns exec ns1 ip addr add 192.168.10.2/24 dev veth1
sudo ip netns exec ns1 ip addr add 192.168.10.102/24 dev veth1
sudo ip netns exec ns1 ip addr add 192.168.102.2/24 dev veth1
sudo ip netns exec ns1 ip addr add fd00::2/64 dev veth1
sudo ip netns exec ns1 ip addr add fe02::2/64 dev veth1

# Bring interfaces up
sudo ip link set veth0 up
sudo ip netns exec ns1 ip link set veth1 up
sudo ip netns exec ns1 ip link set lo up
```

#### add routing rule
```
# veth0
sudo ip route add 192.168.102.0/24 dev veth0
sudo ip route add fe02::2/64 dev veth0

# veth1
sudo ip netns exec ns1 ip route add 192.168.101.0/24 dev veth1
sudo ip netns exec ns1 ip route add fe01::1/64 dev veth1
```

#### ping test
```
# veth0
ping -I veth0 192.168.10.2
ping -I veth0 192.168.10.102
ping -I veth0 192.168.102.2
ping -I veth0 fd00::2
ping -I veth0 fe02::2

# veth1
sudo ip netns exec ns1 bash
ping -I veth1 192.168.10.1
ping -I veth1 192.168.10.101
ping -I veth1 192.168.101.1
ping -I veth1 fd00::1
ping -I veth1 fe01::1
```

#### tcpdump for debugging
```
# veth0
sudo tcpdump -i veth0 -n
```
