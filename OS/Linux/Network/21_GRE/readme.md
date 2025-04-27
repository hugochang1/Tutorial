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
sudo ip tunnel add gre1 mode gre remote 192.168.200.2 local 192.168.200.1 ttl 255
# sudo ip tunnel add gre1 mode ip6gre remote fd80:200::2 local fd80:200::1 ttl 255
sudo ip addr add 10.0.0.1/24 dev gre1
sudo ip addr add fd80:202::1/64 dev gre1
sudo ip link set gre1 up

sudo ip netns exec ns2 ip tunnel add gre1 mode gre remote 192.168.200.1 local 192.168.200.2 ttl 255
# sudo ip netns exec ns2 ip tunnel add gre1 mode ip6gre remote fd80:200::1 local fd80:200::2 ttl 255
sudo ip netns exec ns2 ip addr add 10.0.0.2/24 dev gre1
sudo ip netns exec ns2 ip addr add fd80:202::2/64 dev gre1
sudo ip netns exec ns2 ip link set gre1 up

# add the routing rule on Router
sudo ip route add fd80:202::0/64 dev gre1

# add the routing rule on Host B
#  to router gre1
sudo ip netns exec ns2 ip route add fd80:202::0/64 dev gre1
#  to router r_etha and Host A
sudo ip netns exec ns2 ip route del 192.168.100.0/24 via 192.168.200.1 dev ethb
sudo ip netns exec ns2 ip route add 192.168.100.0/24 dev gre1
sudo ip netns exec ns2 ip route del fd80:100::/64 via fd80:200::1 dev ethb
sudo ip netns exec ns2 ip route add fd80:100::/64 dev gre1

# add the routing rule on Host A
#  to Host B
sudo ip netns exec ns1 ip route add 10.0.0.0/24 via 192.168.100.1 dev etha
sudo ip netns exec ns1 ip route add fd80:202::/64 via fd80:100::1 dev etha
```
### ping
```
# ping from Router to Host B
ping -I gre1 10.0.0.2 -c 3
ping -I gre1 fd80:202::2 -c 3

# ping from Host B to Router
sudo ip netns exec ns2 ping -I gre1 10.0.0.1 -c 3
sudo ip netns exec ns2 ping -I gre1 fd80:202::1 -c 3

# ping from Host B to Host A
sudo ip netns exec ns2 ping -I gre1 192.168.100.2 -c 3
sudo ip netns exec ns2 ping -I gre1 fd80:100::2 -c 3

# ping from Host A to Host B
sudo ip netns exec ns1 ping -I etha 10.0.0.2 -c 3
sudo ip netns exec ns1 ping -I etha fd80:202::2 -c 3
```

### tcpdump
##### Outer IPv4
```
sudo tcpdump -i r_ethb -n -w tcpdump.pcap
```
![image](https://github.com/user-attachments/assets/3b29cf6e-e4c5-45d0-989a-796de5ed4136)

```
sudo tcpdump -i gre1 -n -w tcpdump.pcap
```
![image](https://github.com/user-attachments/assets/84fa5bec-8d9e-4a90-b29f-910197f183bc)


##### Outer IPv6
```
sudo tcpdump -i r_ethb -n -w tcpdump.pcap
```
![image](https://github.com/user-attachments/assets/60ed92cf-904a-48f9-9002-4b79729d8c7e)

```
sudo tcpdump -i gre1 -n -w tcpdump.pcap
```
![image](https://github.com/user-attachments/assets/fd8e77f5-608d-4ee6-8674-cc162bce6097)


### Remove GRE
```
sudo ip tunnel del gre1
```
