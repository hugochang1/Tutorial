### Topology
- Host A/ha_eth0
  - IP: 192.168.100.1/24
- Router A/ra_eth0
  - IP: 192.168.10.1/24
  - Tunnel IP: 10.0.0.1
- Router B/rb_eth0
  - IP: 192.168.10.2/24
  - Tunnel IP: 10.0.0.2
- Host B/ha_eth0
  - IP 192.168.200.1/24

### Setup the simulated Ethernet Hosts
```
# Create veth pair
sudo ip link add veth0 type veth peer name veth1

# Create namespace
sudo ip netns add ns1

# Move veth1 into the namespace
sudo ip link set veth1 netns ns1

# Assign IP addresses
sudo ip addr add 192.168.10.1/24 dev veth0
sudo ip netns exec ns1 ip addr add 192.168.10.2/24 dev veth1

# Bring interfaces up
sudo ip link set veth0 up
sudo ip netns exec ns1 ip link set veth1 up
sudo ip netns exec ns1 ip link set lo up

# Login to Network Namespace
sudo ip netns exec ns1 bash

# check the connection
ping -I veth1 192.168.10.1
```

### Setup GRE on Host A
```
sudo ip tunnel add gre1 mode gre remote 192.168.10.2 local 192.168.10.1 ttl 255
sudo ip addr add 10.0.0.1/24 dev gre1
sudo ip link set gre1 up
```

### Setup GRE on Host B
```
ip tunnel add gre1 mode gre remote 192.168.10.1 local 192.168.10.2 ttl 255
ip addr add 10.0.0.2/24 dev gre1
ip link set gre1 up
```

### check GRE connection on Host A
```
ping -I gre1 10.0.0.2
```

### check GRE connection on Host B
```
ping -I gre1 10.0.0.1
```
