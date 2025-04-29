### Initial Environment
- 00_Vitrual_netdev

### create a VLAN interface
```
# Host A (ns1)
#  etha.100
#   192.168.101.1
#  etha
#   192.168.100.2
#   fd80:100::2
#
# Router
#  r_etha
#   192.168.100.1
#   fd80:100::1
#  r_etha.100
#   192.168.101.1

# create a VLAN interface
sudo ip link add link r_etha name r_etha.100 type vlan id 100
sudo ip netns exec ns1 ip link add link etha name etha.100 type vlan id 100

# assign an IP address to the VLAN interface
sudo ip addr add 192.168.101.1/24 dev r_etha.100
sudo ip netns exec ns1 ip addr add 192.168.101.2/24 dev etha.100

# bring the VLAN interface up
sudo ip link set dev r_etha.100 up
sudo ip netns exec ns1 ip link set dev etha.100 up
```

### ping
```
ping -I r_etha.100 192.168.101.2 -c 3
sudo ip netns exec ns1 ping -I etha.100 192.168.101.1 -c 3
```

### tcpdump
```
sudo tcpdump -i r_etha -n -w tcpdump.pcap
```
![image](https://github.com/user-attachments/assets/b5790dab-f127-41a2-a9f8-885482e4474f)

```
sudo tcpdump -i r_etha.100 -n -w tcpdump.pcap
```
![image](https://github.com/user-attachments/assets/6797121b-98b2-45b2-bada-400a73fd00b5)

### Remove VLAN interface
```
sudo ip link del dev r_etha.100
```
