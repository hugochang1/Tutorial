# USB Descriptors
![usb_descriptors.png not found.](./img/usb_descriptors.png)

### DEVICE DESCRIPTOR
- bLength: 18
- bDescriptorType: 0x01 (DEVICE)
- bcdUSB: 0x0200
- bDeviceClass: Device (0x00)
- bDeviceSubClass: 0
- bDeviceProtocol: 0 (Use class code info from Interface Descriptors)
- bMaxPacketSize0: 64
- idVendor: HTC (High Tech Computer Corp.) (0x0bb4)
- idProduct: Desire HD (modem mode) (0x0ffe)
- bcdDevice: 0x0404
- iManufacturer: 1
- iProduct: 2
- iSerialNumber: 3
- bNumConfigurations: 1

### CONFIGURATION DESCRIPTOR
- bLength: 9
- bDescriptorType: 0x02 (CONFIGURATION)
- wTotalLength: 75
- bNumInterfaces: 2
- bConfigurationValue: 1
- iConfiguration: 4
- Configuration bmAttributes: 0x80  NOT SELF-POWERED  NO REMOTE-WAKEUP
- bMaxPower: 250  (500mA)

### INTERFACE ASSOCIATION DESCRIPTOR (IAD)
- bLength: 8
- bDescriptorType: 0x0b (INTERFACE ASSOCIATION)
- bFirstInterface: **0**
- bInterfaceCount: **2**
- bFunctionClass: **Wireless Controller (0xe0)**
- bFunctionSubClass: **0x01**
- bFunctionProtocol: **0x03**
- iFunction: 7
  - Class (0xe0), SubClass (0x01), Protocol (0x03) is RNDIS
  - https://www.usb.org/defined-class-codes#anchor_BaseClassE0h
  - IAD is used for association two or more interfaces together as one function (ex: RNDIS)
    - assoicate wireless controller and CDC-Data

### INTERFACE DESCRIPTOR (0.0): class Wireless Controller
- bLength: 9
- bDescriptorType: 0x04 (INTERFACE)
- bInterfaceNumber: 0
- bAlternateSetting: 0
- bNumEndpoints: 1
- bInterfaceClass: **Wireless Controller (0xe0)**
- bInterfaceSubClass: **0x01**
- bInterfaceProtocol: **0x03**
- iInterface: 5
  - Class (0xe0), SubClass (0x01), Protocol (0x03) is RNDIS
  - https://www.usb.org/defined-class-codes#anchor_BaseClassE0h

#### ENDPOINT DESCRIPTOR
- bLength: 7
- bDescriptorType: 0x05 (ENDPOINT)
- bEndpointAddress: 0x81  IN  Endpoint:1
- bmAttributes: 0x03
- wMaxPacketSize: 8
- bInterval: 9
  - for device to notify the host RNDIS control message is ready to be read

### INTERFACE DESCRIPTOR (1.0): class CDC-Data
- bLength: 9
- bDescriptorType: 0x04 (INTERFACE)
- bInterfaceNumber: 1
- bAlternateSetting: 0
- bNumEndpoints: 2
- bInterfaceClass: **CDC-Data (0x0a)**
- bInterfaceSubClass: **0x00**
- bInterfaceProtocol: **No class specific protocol required (0x00)**
- iInterface: 6
  - https://www.usb.org/defined-class-codes#anchor_BaseClass0Ah

### ENDPOINT DESCRIPTOR
- bLength: 7
- bDescriptorType: 0x05 (ENDPOINT)
- bEndpointAddress: 0x8e  IN  Endpoint:14
- bmAttributes: 0x02
- wMaxPacketSize: 512
- bInterval: 0
  - device to host data endpoint

### ENDPOINT DESCRIPTOR
- bLength: 7
- bDescriptorType: 0x05 (ENDPOINT)
- bEndpointAddress: 0x0f  OUT  Endpoint:15
- bmAttributes: 0x02
- wMaxPacketSize: 512
- bInterval: 0
  - host to device data endpoint

### RNDIS data message
#### RNDIS data message header
- https://docs.microsoft.com/zh-hk/windows-hardware/drivers/network/remote-ndis-packet-msg
- normally, the RNDIS packet size is **44** bytes without using OOBData and PerPacketInfo
#### RNDIS data message stack
- protocol stack over this interface is RNDIS header (44 bytes), Ethernet header (14 bytes), IP header, ...
![tcp_ip_stack.png not found.](./img/tcp_ip_stack.png)
![ethernet_stack.png not found.](./img/ethernet_stack.png)

# Kernel.org
- u_ether.c
  - https://github.com/torvalds/linux/blame/master/drivers/usb/gadget/function/u_ether.c
  - 2021 https://github.com/torvalds/linux/commit/63d152149b2d0860ccf8c4e6596b6175b2b7ace6
  - 2020 https://github.com/torvalds/linux/commit/0a88fa221ce911c331bf700d2214c5b2f77414d3
  - 2020 https://github.com/torvalds/linux/commit/a74005ab91856276ca5e424a239ebe73347079d8
  - 2019 https://github.com/torvalds/linux/commit/d29fcf7078bc8be2b6366cbd4418265b53c94fac
  - 2018 https://github.com/torvalds/linux/commit/c9287fa657b3328b4549c0ab39ea7f197a3d6a50
- f_rndis.c
  - https://github.com/torvalds/linux/blame/master/drivers/usb/gadget/function/f_rndis.c
  - 2021 https://github.com/torvalds/linux/commit/90c4d05780d47e14a50e11a7f17373104cd47d25
  - 2019 https://github.com/torvalds/linux/commit/e5b5da96da50ef30abb39cb9f694e99366404d24
  - 2017 https://github.com/torvalds/linux/commit/5fd54ace4721fc5ce2bb5aef6318fcf17f421460
  - 2016 https://github.com/torvalds/linux/commit/80d1642d7640ef00d8823f17a529785331aceb96
  - 2015 https://github.com/torvalds/linux/commit/83210e59ee1527f229af6aef78c95b747bdcf9c4
