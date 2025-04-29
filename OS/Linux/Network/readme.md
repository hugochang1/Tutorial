### Initial Environment
- 00_Vitrual_netdev

### enable IP forwarding for IPv4 and IPv6
- `# vi /etc/sysctl.conf`
- `net.ipv4.ip_forward = 1`
- `net.ipv6.conf.all.forwarding = 1`
- `# sysctl -p`
- to apply the changed settings in /etc/sysctl.conf

### check ipv4 status
- `# ip -4 -br a`
- `# ip route`

### check ip route
- `# ip route get 8.8.8.8`
- `8.8.8.8 via 192.168.80.1 dev eth0 src 192.168.80.51 uid 0`

### check routing table
- `# ip route show scope host table all`
- `# ip route show scope link table all`
- `# ip route show scope global`
- `# ip route show table local`
- `# ip route show table main`
- `# ip route show`

### add routing rule
- `# ip route add 8.8.8.8 via 192.168.10.200`
- `# ip route add 1.1.1.1 via 192.168.12.254`
- `# ip route show scope global`
- `default via 192.168.80.1 dev eth0 proto static`
- `1.1.1.1 via 192.168.12.254 dev eth2`
- `8.8.8.8 via 192.168.10.200 dev eth1`

### delete routing rule
- `# ip route del 1.1.1.1 via 192.168.12.254`

### add routing rule with metric
- `# ip route 1.1.1.1 via 192.168.12.254 metric 100`
- `# ip route 1.1.1.1 via 192.168.10.200 metric 200`

### trace route
- `# traceroute -n 1.1.1.1`
