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
- Class
  - Communication Interface Class code: 0x02
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
- control functions
  - MBIM_CID_DEVICE_CAPS
  - MBIM_CID_SUBSCRIBER_READY_STATUS
  - MBIM_CID_RADIO_STATE
  - MBIM_CID_PIN
  - MBIM_CID_PIN_LIST
  - MBIM_CID_HOME_PRROVIDER
  - MBIM_CID_SMS_XXX
  - MBIM_CID_PHONEBOOK_XXX
  - **MBIM_CID_CONNECT**
  - **MBIM_CID_DSS_CONNECT**
  - ...
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

### DEVICE SERVICE
- A logical group of functionality supported by the device constitutes a "device service"
- Each device service is uniquely identified by a 128-bit UUID (Universally Unique Identifier)
- All CIDs exchanged between the host and the device carry the UUID to identify the device service associated with the transfer
#### DEVICE SERVICE STREAMS
- The transfer of high-bandwidth data over the control channel is not supported. Instead, Device Service Streams over bulk are recommended
- Device Service Stream is a best effort service
- The protocol layer and/or application above MBIM shall be responsible for flow control and recovery from data loss
- Doing flow control by throttling the bulk IN/OUT pipes is strongly discouraged, because the pipes are shared by multiple services
#### CUSTOM DEVICE SERVICES
- Vendors are free to define additional device services by generating a UUID of their own. These services shall not be IP-protocol based

## USB DEVICE MODEL
#### MBIM Communication Interface Descriptor Requirements
![mbim_communication_interface_descriptor](https://user-images.githubusercontent.com/6143237/131257138-e6af1088-bbe9-44bb-b137-ee521cdf446d.png)
#### MBIM FUNCTIONAL DESCRIPTOR
| Offset | Field | Size | Value | Description |
| ------ | ----- | ---- | ----- | ----------- |
| 0 | bFunctionLength | 1 | 12 | Size of Descriptor in bytes |
| 1 | bDescriptorType | 1 | Constant | CS_INTERFACE (0x24) |
| 2 | bDescriptorSubtype | 1 | Constant | MBIM Functional Descriptor code (0x1B) |
| 3 | bcdMBIMVersion | 2 | Number 0x0100  | Release number of this specification in BCD |
| 5 | wMaxControlMessage | 2 | Number | Maximum segment size in bytes a function can handle |
| 7 | bNumberFilters | 1 | Number | Contains the number of PacketFilters that are available in total for all SessionIds. These filters are potentially capable of causing wakeup of the host |
| 8 | bMaxFilterSize | 1 | Number | The maximum size of the PacketFilters in bytes |
| 9 | wMaxSegmentSize | 2 | Number | The Maximum segment size in bytes that the function is capable of supporting. This number has to be larger than the MTU set for IP traffic by the network |
| 11 | bmNetworkCapabilities | 1 | Bitmap | Specifies the capabilities of this function <br> D5: Function can process 8-byte forms of GetNtbInputSize and SetNtbInputSize requests  <br> D3: Function can process SetMaxDatagramSize and GetMaxDatagramSize requests. |
- the default and minimum value of wMaxSegmentSize is 2048
#### MBIM EXTENDED FUNCTIONAL DESCRIPTOR
| Offset | Field | Size | Value | Description |
| ------ | ----- | ---- | ----- | ----------- |
| 0 | bFunctionLength | 1 | 8 | Size of Descriptor in bytes |
| 1 | bDescriptorType | 1 | Constant | CS_INTERFACE (0x24)  |
| 2 | bDescriptorSubtype | 1 | Constant | 0x1C |
| 3 | bcdMBIMExtendedVersion | 2 | Number 0x0100  | Release number of MBIM extensions in BCD |
| 5 | bMaxOutstandingCommandMessages | 1 | Number | Max number of outstanding Command Messages the device can handle simultaneously.  |
| 6 | wMTU | 2 | Number | Operator preferred MTU for home network. wMTU applies to IP Data Streams. <br> If no specific requirements exist the recommended value should be 1500. |
#### DATA CLASS INTERFACE DESCRIPTOR
| Offset | Field | Size | Value | Description |
| ------ | ----- | ---- | ----- | ----------- |
| 5 | bInterfaceClass | 1 | 0Ah | Data Interface Class code |
| 6 | bInterfaceSubClass | 1 | 00h | Data Class SubClass code |
| 7 | bInterfaceProtocol | 1 | 02h | Data Class Protocol code, Network transfer block-MB |

## DATA TRANSPORT
- The data packets will be passed to and from the device using the standard NCM 1.0 transfer headers and datagram pointers
  - NCM: transport IEEE 802.3 frames
  - MBIM: “raw” IP (both IPv4 and IPv6) and Device Service Streams are transported
- MBIM Data Transport signature values for NDP structures

| Protocol | NDP16 | NDP32 |
| ------ | ----- | ---- |
| Raw IPv4 or IPv6 | “IPS”\<SessionId\> | “ips”\<SessionId\> |
| Device Service Stream | “DSS”\<DssSessionId\>  | “dss”\<DssSessionId\> |
- SessionId: specified by the host in the MBIM_CID_CONNECT command
- DssSessionId specified by the host in the MBIM_CID_DSS_OPEN command
- The minimum values for wDatagramLength
  - For IPv4: >= 20 
  - For IPv6: >= 40
  - For DSS: >= 0
### DATA FORMATTING
- IPV4
  - The datagrams starts with the IPv4 header
- IPV6
  - The datagrams starts with the IPv6 header
- DEVICE SERVICE STREAM
  - The format of the Device Service Stream payload depends on the device service that is used when opening the data stream
- MBIM FRAME ALIGNMENT
  - MBIM allows a function to align transmitted datagrams on any convenient boundary within the NTB in both directions
  - This alignment is specified by indicating a constraint as a divisor and a remainder
    - IN: wNdpInDivisor & wNdpInPayloadRemainder (in byte)
    - OUT: wNdpOutDivisor & wNdpOutPayloadRemainder (in byte)
- MBIM ALLOWS MULTIPLE NDPS WITHIN ONE NTB

| 6 | wNextNdpIndex | 2 | Number | Byte index, in little endian, of the next NDP. The index is from byte zero of the NTB |
| - | - | - | - | - |

# Control Message
- **RESET FUNCTION**
  - RESET_FUNCTION resets the function to its initial state
  - all IP data stream connections are disconnected
  - all Device Service Streams are closed
  - The function shall abandon all outstanding transactions that are awaiting completion
  - No notifications shall be sent
  - The alternate settings of interfaces are not changed
  - remote-wakeup enable for the function is not affected
  - only the MBIM function is affected by this request
  - Other functions in a composite device are not affected by this request

| bmRequestType | bRequestCode | wValue | wIndex | wLength | Data |
| - | - | - | - | - | - |
| 00100001B | RESET_FUNCTION | Zero | Interface | Zero | Zero |

- **MBIM_CID_CONNECT**
  - This command activates or deactivates a particular IP data stream session
  - The set operation requests an IP data stream session (to a specific APN) to be made available to the host
  - MBIM_SET_CONNECT

| Offset | Size| Field | Type | Description |
| - | - | - | - | - |
| 0 | 4 | SessionId | UINT32 | Host specifies this member to uniquely identify the session for the IP data stream and its corresponding state. |
| 4 | 4 | ActivationCommand | MBIM_ACTIVATION_COMMAND | Deactivate=0<br>Activate=1 |
| 8 | 4 | AccessStringOffset | OFFSET | Offset in bytes, calculated from the beginning of this structure, to a string AccessString to access the network (APN) |
| 12 | 4 | AccessStringSize | SIZE (0..200) | Size used for AccessString |
| 16 | 4 | UserNameOffset | OFFSET | UserName, can be NULL |
| 20 | 4 | UserNameSize | SIZE (0..510)  | Size used for UserName |
| 24 | 4 | PasswordOffset | OFFSET | Password that represents the username's password, can be NULL |
| 28 | 4 | PasswordSize | SIZE (0..510) | Size used for Password |
| 32 | 4 | Compression | MBIM_COMPRESSION | none=0<br>enable=1 |
| 36 | 4 | AuthProtocol | MBIM_AUTH_PROTOCOL | none=0<br>pap=1<br>chap=2<br>ImsChapV2=3 |
| 40 | 4 | IPType | MBIM_CONTEXT_IP_TYPE | default=0 (mandatory)<br>IPv4=1<br>IPv6=2<br>IPv4v6=3<br>IPv4AndIPv6=4 |
| 44 | 16 | ContextType | MBIM_CONTEXT_TYPES | None<br>Internet<br>Vpn<br>Voice<br>VideoShare<br>Purchase<br>IMS<br>MMS<br>Local |
| 60 |  | DataBuffer | DATABUFFER | AccessString<br>UserName<br>Password<br> |

  - MBIM_CONNECT_INFO (Unsolicited Event)

| Offset | Size| Field | Type | Description |
| - | - | - | - | - |
| 0 | 4 | SessionId | UINT32 | The Host specifies a value for this member at the time of the connect request by using MBIM_CID_CONNECT. Devices must copy this value and use it when they notify the MB Service on subsequent connection state changes. |
| 4 | 4 | ActivationState | MBIM_ACTIVATION_STATE | UNKNOWN=0<br>Activated=1<br>Activating=2<br>Deactivated=3<br>Deactivating=4 |
| 8 | 4 | VoiceCallState | MBIM_VOICE_CALL_STATE | None=0<br>InProgress=1<br>HangUp=2 |
| 12 | 4 | IPType | MBIM_CONTEXT_IP_TYPE | default=0 (mandatory)<br>IPv4=1<br>IPv6=2<br>IPv4v6=3<br>IPv4AndIPv6=4 |
| 16 | 16 | ContextType | MBIM_CONTEXT_TYPES | None<br>Internet<br>Vpn<br>Voice<br>VideoShare<br>Purchase<br>IMS<br>MMS<br>Local |
| 32 | 4 | NwError | UINT32 | A network-specific error. |

  - NOTIFICATION

| Status code | Description |
| - | - |
| MBIM_STATUS_SUCCESS | The operation succeeded |
| MBIM_STATUS_RADIO_POWER_OFF | The operation failed because the radio is currently turned off |
| MBIM_STATUS_SERVICE_NOT_ACTIVATED | The operation failed because either the subscription has expired, or the device does not allow PDP activation |
| MBIM_STATUS_PROVIDER_NOT_VISIBLE | The operation failed because the service provider is not currently visible |
| MBIM_STATUS_MAX_ACTIVATED_CONTEXTS | The operation failed because the maximum number of activated contexts has been reached. |
| MBIM_STATUS_INVALID_ACCESS_STRING | The operation failed because the access string is invalid |
| MBIM_STATUS_INVALID_USER_NAME_PWD | The operation failed because the user name and/or password supplied are invalid |
| MBIM_STATUS_PACKET_SERVICE_DETACHED | The operation failed because packet service is detached |
| MBIM_STATUS_NOT_REGISTERED | The operation failed because the device is not in the registered state  |
| MBIM_STATUS_VOICE_CALL_IN_PROGRESS | The operation failed and cannot proceed with PDP activation because a voice call is currently in progress. Thisvalue applies only to devices with voice class is set to MBIMVoiceClassSeparateVoiceData |
| MBIM_STATUS_CONTEXT_NOT_ACTIVATED | The operation failed because the context identified by SessionId is not the currently activated context |
| MBIM_STATUS_CONTEXT_NOT_SUPPORTED | The operation failed because it could not support the typeof context identified by ContextType |
| MBIM_STATUS_OPERATION_NOT_ALLOWED | If the device receives an activation request for an additional IP data stream to the same APN the device may reject the activation with this error code |


- **MBIM_CID_DSS_CONNECT**
  - This CID activates and deactivates a data stream channel over the bulk pipe for a non-IP based Device Service
  - The host might open several Device Service Streams up to the maximum number of sessions as specified in MaxDssSessions in MBIM_DEVICE_SERVICES_INFO
  - MBIM_SET_DSS_CONNECT

| Offset | Size| Field | Type | Description |
| - | - | - | - | - |
| 0 | 16 | DeviceServiceId | UUID | A 16 byte UUID that identifies the Device Service for provided DssSessionId |
| 16 | 4 | DssSessionId | UINT32 | Host specifies this member to uniquely identify the session for the Device Service Stream. |
| 20 | 4 | DssLinkState | UINT32 | Deactivate=0<br>kActivate=1 |

  - RESPONSE

| Status code | Description |
| - | - |
| MBIM_STATUS_SUCCESS | The DSS is successfully opened |
| MBIM_STATUS_BUSY | If the function temporarily cannot open the DSS it shall return this error code |
| MBIM_STATUS_FAILURE | An unknown error where encountered during opening of the DSS |
| MBIM_STATUS_DSS_INSTANCE_LIMIT | If the function cannot open a new session due to instance limit, it shall reply with this status code. |

# MBIM LOOPBACK TESTMODE
- Loopback testing ensures that the link between host and device is verified with no dependency on the network, SIM, or air interfaces
- loopback functionality is tested only for IP data traffic
- MB device firmware should implement “loopback” APN 
- Enter/Exit loopback mode
  - On getting MBIM_CID_CONNECT set request with an ActivationCommand of MBIMActivationCommandActivate and an access string loopback, the firmware should do the following
  - If the device is already connected, it should respond with an MBIM_STATUS_MAX_ACTIVATED_CONTEXTS
  - The device should be able to enter loopback mode without registering with a provider
  - The device should be able to enter loopback mode when its packet service state is detached
  - The device should respond with an MBIM_CID_CONNECT response using the SessionId, IPType, and ContextType specified in the MBIM_CID_CONNECT request. ActivationState should be MBIMActivationStateActivated, and VoiceCallState should be MBIMVoiceCallStateNone
  - Enter into loopback mode
  - The device should respond to additional MBIM_CID_CONNECT set requests with MBIM_STATUS_MAX_ACTIVATE_CONTEXTS until loopback mode is deactivated
- While in loopback mode
  - Listen for NTBs (NCM Transfer Block) on the BULK OUT pipe from the host
    - The device should unpack the datagrams from the NTB and send them back to the host on the MBIM Bulk-IN pipe
    - The device should swap the Source and Destination addresses of IPv4 and IPv6 datagrams. The device should not need to modify the IPv4 checksum and vendor datagrams
    - NTBs sent on the MBIM Bulk-IN pipe should conform to the NTB parameters specified by the device in the NCM GetNtbParameters function. Datagrams can be sent on the Bulk-IN pipe in one or more NTBs as required by the NTB parameters for the Bulk-IN pipe
