### Create GRE
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
#  gre1
#   10.0.0.1
#   fd80:202::1
#  r_ethb
#   192.168.200.1
#   fd80:200::1
#
# Host B (ns2)
#  ethb
#   192.168.200.2
#   fd80:200::2
#  gre1
#   10.0.0.2
#   fd80:202::2

# create GRE
sudo ip link add gre1 type gretap remote 192.168.200.2 local 192.168.200.1 ttl 255
sudo ip addr add 10.0.0.1/24 dev gre1
sudo ip addr add fd80:202::1/64 dev gre1
sudo ip link set gre1 up

sudo ip netns exec ns2 ip link add gre1 type gretap remote 192.168.200.1 local 192.168.200.2 ttl 255
sudo ip netns exec ns2 ip addr add 10.0.0.2/24 dev gre1
sudo ip netns exec ns2 ip addr add fd80:202::2/64 dev gre1
sudo ip netns exec ns2 ip link set gre1 up
```

### ping
```
# ping from Router to Host B
ping -I gre1 10.0.0.2 -c 3
ping -I gre1 fd80:202::2 -c 3

# ping from Host B to Router
sudo ip netns exec ns2 ping -I gre1 10.0.0.1 -c 3
sudo ip netns exec ns2 ping -I gre1 fd80:202::1 -c 3
```

### tcpdump
```
sudo tcpdump -i r_ethb -n -w tcpdump.pcap
```
![image](https://github.com/user-attachments/assets/8b399e29-7d6f-4c52-a20a-f004e9cfac5c)

```
sudo tcpdump -i gre1 -n -w tcpdump.pcap
```
![image](https://github.com/user-attachments/assets/1c888b12-2800-4696-b6cd-0cffd90f8188)


### Remove GRE
```
sudo ip link del gre1
```

