### VPN Protocol
|Tunneling Protocol|Full Name|Protocol Stack|
|-|-|-|
|IP-in-IP|IP-in-IP|Outer IPv4, IPv4|
|GRE|Generic Routing Encapsulation|Outer IP, **GRE**, IPv4/IPv6|
|EoGRE|Ethernet over Generic Routing Encapsulation|Outer IP, **GRE**, ETH, IPv4/IPv6|
|IPSec - Tunnel|Internet Protocol Security|Outer IP, **ESP**, IP|
|IPSec - Transport|Internet Protocol Security|Original IP, **ESP**, TCP/UDP|
|PPTP|Point-to-Point Tunneling Protocol|Outer IPv4, **GRE**, PPP, IP|
|L2TP|Layer 2 Tunneling Protocol|Outer UDP, **L2TP**, PPP, IP|
|VXLAN|Virtual Extensible LAN|Outer UDP, **VXLAN**, ETH|
|WireGuard||Outer UDP, **WireGuard**, IP|
|OpenVPN||Outer TCP/UDP, **OpenVPN**, TLS|
|SSTP|Secure Socket Tunneling Protocol|Outer TLS/HTTPS, **SSTP**, PPP|
|SoftEther VPN||Outer HTTPS, ETH (TBD)|
