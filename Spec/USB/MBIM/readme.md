![aaa](https://user-images.githubusercontent.com/6143237/130644632-d0a3cc77-5a80-4ec5-b4e5-94f64f19dc3c.png)
# MBIM (Mobile Broadband Interface Model)

## Overview
#### MBIM v1.0
- release date: 2011-10-25
- rename from NCM 2.0
- MBIM is a protocol based on NCM 1.0
- USB hosts and Mobile Broadband devices can efficiently exchange control commands and data frames
- defines control commands, raw IP usage and Communications Device Class subclass specification

#### OTHER USB NETWORKING SPECIFICATIONS
###### Ethernet Control Model (ECM)
- IEEE 802.3 type 
- no header, no aggregation, 1-on-1 packet delivery
###### Network Control Model (NCM)
- IEEE 802.3 type 
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
  - Alternate setting 0 is MBIM
    - When alternate setting 1 is selected, the function shall operate according to MBIM spec
#### DESCRIPTOR REQUIREMENTS
- 
