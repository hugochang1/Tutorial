### Create a Network Namespace to Simulate a Second Host
#### Topology
- Host A (ns1)
  - etha
    - 192.168.100.2
    - 
- Router
  - r_etha
    - 192.168.100.1
    - 
  - r_ethb
    - 192.168.200.1
    - 
- Host B (ns2)
  - ethb
    - 192.168.200.2

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
sudo ip addr add 192.168.200.1/24 dev r_ethb
sudo ip netns exec ns1 ip addr add 192.168.100.2/24 dev etha
sudo ip netns exec ns2 ip addr add 192.168.200.2/24 dev ethb

# Bring interfaces up
sudo ip link set r_etha up
sudo ip link set r_ethb up
sudo ip netns exec ns1 ip link set etha up
sudo ip netns exec ns1 ip link set lo up
sudo ip netns exec ns2 ip link set ethb up
sudo ip netns exec ns2 ip link set lo up
```

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
sudo ip netns exec ns1 ip addr add 192.168.10.2/24 dev veth1

# Bring interfaces up
sudo ip link set veth0 up
sudo ip netns exec ns1 ip link set veth1 up
sudo ip netns exec ns1 ip link set lo up
```

#### Login to Network Namespace
```
sudo ip netns exec ns1 bash
```

#### Ping from network namesapce to the real host
```
ping 192.168.10.1
```

#### List Network Namespace
```
ip netns list
ns1 (id: 0)
```

#### Delete Network Namespace
```
sudo ip netns delete ns1
```

#### Delete a virtual network device
```
sudo ip link del veth0
```

