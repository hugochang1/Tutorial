# Ethernet Header
###### https://en.wikipedia.org/wiki/Ethernet_frame
![network_ethernet_header.png not found.](./img/network_ethernet_header.png)
###### https://en.wikipedia.org/wiki/EtherType
- 0x0800: IPv4
- 0x86DD: IPv6

# IPv4 Header
![network_ipv4_header.png not found.](./img/network_ipv4_header.png)
- Version
  - IPv4 is 4
- Header Length
  - minimum is value=5 = 5 x 4 bytes = 20 bytes
  - maximum is value=15 = 15 x 4 bytes = 60 bytes 
- Type of service (Tos)
- Total Length
  - the entire packet size in bytes, including header and data
  - minimum size is 20 bytes 
  - maximum is 65,535 bytes
- Identifier
  - the group of fragments of a single IP datagram
- Protocol
  - https://en.wikipedia.org/wiki/List_of_IP_protocol_numbers
  - TCP is 0x06
  - UDP is 0x11

# IPv6 Header

# TCP Header
![network_tcp_header.png not found.](./img/network_tcp_header.png)
- https://en.wikipedia.org/wiki/Transmission_Control_Protocol
- 
