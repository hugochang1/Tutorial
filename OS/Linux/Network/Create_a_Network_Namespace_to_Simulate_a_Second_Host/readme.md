### Create a Network Namespace to Simulate a Second Host
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

