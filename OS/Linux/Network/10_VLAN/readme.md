### Create a virtual network device
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

### create a VLAN interface
```
# create a VLAN interface
sudo ip link add link veth0 name veth0.100 type vlan id 100
sudo ip netns exec ns1 ip link add link veth1 name veth1.100 type vlan id 100

# assign an IP address to the VLAN interface
sudo ip addr add 192.168.30.1/24 dev veth0.100
sudo ip netns exec ns1 ip addr add 192.168.30.2/24 dev veth1.100

# bring the VLAN interface up
sudo ip link set dev veth0.100 up
sudo ip netns exec ns1 ip link set dev veth1.100 up
```

### ping
```
ping -I veth0.100 192.168.30.2
sudo ip netns exec ns1 ping -I veth1.100 192.168.30.1
```

### tcpdump veth0 (has VLAN ID)
```
sudo tcpdump -i veth0 -n -w tcpdump.pcap
```
![image](https://github.com/user-attachments/assets/18ff2f5b-0cc2-4a25-a6c0-cc876a46a6d0)

### tcpdump veth0.100 (no VLAN ID)
```
sudo tcpdump -i veth0.100 -n -w tcpdump.pcap
```
![image](https://github.com/user-attachments/assets/dab9efd7-71c0-44fa-956c-267f44aeb490)
