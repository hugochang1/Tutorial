# NCM (Network Control Model)
###### The Network Control Model (NCM) Subclass is a protocol by which USB hosts and devices can efficiently exchange Ethernet frames.

# Terms
###### Network Control Model (NCM)
###### NCM Transfer Block (NTB)
###### NTB Header (NTH)
###### NCM Datagram Pointer (NDP)
# NTB layout details (16 bit)
![image not found.](./img/ntb_layout_16.png)
# NTB layout details (32 bit)
![image not found.](./img/ntb_layout_32.png)
# Datagram Formatting
###### The datagram always starts with a 14-byte [IEEE802.3] header, and then continues with the appropriate payload.
###### NDP16 or NDP32 must choose whether a CRC-32 will be appended to the payload.
###### NDP16.Sig="NCM0" if [IEEE802.3], no CRC-32
###### NDP16.Sig="NCM1" if [IEEE802.3], with CRC-32
###### NDP32.Sig=ncm0" if [IEEE802.3], no CRC-32
###### NDP32.Sig="ncm1" if [IEEE802.3], with CRC-32


# Reference
###### breakdown article: https://markdownlivepreview.com/
