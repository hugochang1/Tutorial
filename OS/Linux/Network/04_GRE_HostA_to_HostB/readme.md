### Topology
- Host A/ha_eth0 (ns1)
  - IP: 192.168.20.2/24
- Router A/ra_eth0
  - IP: 192.168.20.1/24
- Router A/ra_eth1
  - IP: 192.168.10.1/24
  - Tunnel IP: 10.0.0.1
- Router B/rb_eth1 (ns2)
  - IP: 192.168.10.2/24
  - Tunnel IP: 10.0.0.2

### Setup the simulated Ethernet Hosts
```
# Create veth pair
sudo ip link add ra_eth0 type veth peer name ha_eth0
sudo ip link add ra_eth1 type veth peer name rb_eth1

# Create namespace
sudo ip netns add ns1
sudo ip netns add ns2

# Move into the namespaces
sudo ip link set ha_eth0 netns ns1
sudo ip link set rb_eth1 netns ns2

# Assign IP addresses
sudo ip addr add 192.168.20.1/24 dev ra_eth0
sudo ip addr add 192.168.10.1/24 dev ra_eth1
sudo ip netns exec ns1 ip addr add 192.168.20.2/24 dev ha_eth0
sudo ip netns exec ns2 ip addr add 192.168.10.2/24 dev rb_eth1

# Bring interfaces up
sudo ip link set ra_eth0 up
sudo ip netns exec ns1 ip link set ha_eth0 up
sudo ip netns exec ns1 ip link set lo up

sudo ip link set ra_eth1 up
sudo ip netns exec ns2 ip link set rb_eth1 up
sudo ip netns exec ns2 ip link set lo up
```

### Login to Network Namespace 1 and check the connection between Host A and Router A
```
sudo ip netns exec ns1 bash
ping -I ha_eth0 192.168.20.1
```

### Login to Network Namespace 2 and check the connection between Router A and Router B
```
sudo ip netns exec ns2 bash
ping -I rb_eth1 192.168.10.1
```

### Setup GRE on Router A
```
sudo ip tunnel add gre1 mode gre remote 192.168.10.2 local 192.168.10.1 ttl 255
sudo ip addr add 10.0.0.1/24 dev gre1
sudo ip link set gre1 up
```

### Setup GRE on Router B
```
# sudo ip netns exec ns2 bash
ip tunnel add gre1 mode gre remote 192.168.10.1 local 192.168.10.2 ttl 255
ip addr add 10.0.0.2/24 dev gre1
ip link set gre1 up
```

### check GRE connection on Router A
```
ping -I gre1 10.0.0.2
```

### check GRE connection on Router B
```
# sudo ip netns exec ns2 bash
ping -I gre1 10.0.0.1
```

### Add the routing rule on Router B
```
# sudo ip netns exec ns2 bash
ip route add 192.168.20.0/24 via 10.0.0.1 dev gre1
```

### check the connection from Router B to Router A via GRE
```
# sudo ip netns exec ns2 bash
ping -I gre1 192.168.20.1
```

### Add the routing rule on Host A
```
# sudo ip netns exec ns1 bash
ip route add 10.0.0.0/24 via 192.168.20.1 dev ha_eth0
```

### check the connection between Router B and Host A via GRE
```
# sudo ip netns exec ns2 bash
ping -I gre1 192.168.20.2
```

