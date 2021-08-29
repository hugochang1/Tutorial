# MBIM (Mobile Broadband Interface Model)

## Overview
#### MBIM v1.0
- release date: 2011-10-25
- rename from NCM 2.0
- MBIM is a protocol based on NCM 1.0
- USB hosts and Mobile Broadband devices can efficiently exchange control commands and data frames
- defines control commands, raw IP usage and Communications Device Class subclass specification

#### OTHER USB NETWORKING SPECIFICATIONS
###### Remote-NDIS (RNDIS)
- IEEE 802.3 type + RNDIS header (44 bytes)
- RNDIS supports aggregation for DL/UL
###### Ethernet Control Model (ECM)
- IEEE 802.3 type 
- no extra header, no aggregation, 1-on-1 packet delivery
###### Network Control Model (NCM)
- IEEE 802.3 type + NCM Transfer Block (NTB)
- define NCM header and data structure for packet alignment and aggregation
- it lacks the definition of control commands
- overhead to carry the raw IP encapsulated in an Ethernet frame
###### Ethernet Emulation Model (EEM)
- EEM is intended for use in communicating with devices
###### ATM Networking Control Model
- expose ATM traffic directly

## COMPATIBILITY WITH NCM 1.0
-  devices transfer raw IP packets instead of packets with 802.3 headers
#### IMPLEMENTING FUNCTIONS THAT SUPPORT NCM 1.0 AND MBIM
- For backwards compatibility, a device vendor may need to build a device that will work with hosts that support only NCM 1.0, and with hosts that support MBIM
- device provides two alternate settings for the Communication Interface
  - Alternate setting 0 is NCM 1.0
    - When alternate setting 0 is selected, NTBs shall transport Ethernet frames, not IP datagrams
  - Alternate setting 1 is MBIM
    - When alternate setting 1 is selected, the function shall operate according to MBIM spec
- DATA CLASS
  - Alternate setting 0: no endpoints
  - Alternate setting 1: two endpoints (IN/OUT bulk for NCM)
  - Alternate setting 2: two endpoints (IN/OUT bulk for MBIM)
- If Communication Interface is 0 (NCM), the only valid settings for the data interface is setting 0 and 1
- If Communication Interface is 1 (MBIM), the only valid settings for the data interface is setting 0 and 2
#### FUNCTIONAL DESCRIPTORS FOR NCM AND MBIM FUNCTIONS
![mbim_functional_descriptor](https://user-images.githubusercontent.com/6143237/131255748-b3e40de9-cf43-4de5-bd99-f8047669392e.png)
#### CLASS SPECIFIC CODES
- Subclass
  - Mobile Broadband Interface Model: 0x0E
- Protocol Code
  - Mobile Broadband Interface Model Protocol: 0x00
- Descriptor Code
  - Mobile Broadband Interface Model Functional Descriptor: 0x1B
  - Extended Mobile Broadband Interface Model Functional Descriptor: 0x1C
- Request code
  - RESET_FUNCTION: 0x05

## FUNCTIONAL CHARACTERISTICS
![mbim_block_diagram](https://user-images.githubusercontent.com/6143237/131255973-9242f221-eafc-4ece-b12e-e9405cfabc4c.png)
- data channel: similar to the NCM data transport, the only difference is that instead of transporting Ethernet frames, MBIM transports IPS and DSS
  - IPS: raw IP data streams
  - DSS: Device Service Stream
- control channel:  for transporting MBIM control messages
  - CID: Command Identifier
#### default pipe
![mbim_default_pipe](https://user-images.githubusercontent.com/6143237/131256276-90f65b6d-d0c3-4bb9-b263-1924690d69b6.png)
#### interrupt pipe
![mbim_interrupt_pipe](https://user-images.githubusercontent.com/6143237/131256306-365a0e4a-1888-4311-8e43-d41a3ec6d2bc.png)
#### BULK-IN AND BULK-OUT PIPES
- It is recommended that the values of dwNtbInMaxSize and dwNtbOutMaxSize be multiples of the wMaxPacketSize of the bulk pipes
- If the transfer is a less than the configured Max NTB size and is a multiple of the wMaxPacketSize the sender must terminate the transfer with a ZLP
#### OPERATIONAL MODEL
##### command response sequence
![mbim_command_response_sequence](https://user-images.githubusercontent.com/6143237/131256587-cd53a23a-907b-417a-8d21-1ad72113ab0f.png)
- This model allows the host to issue multiple control messages to the device without waiting for previous message to complete
##### unsolicited event sequence
![mbim_unsolicited_event_sequence](https://user-images.githubusercontent.com/6143237/131256673-394cd4ea-e711-41a6-bd1a-10bd200263ae.png)
- whenever the device needs to notify the host of an unsolicited device events, it uses the interrupt end-point

