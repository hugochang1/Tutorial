## GPS
- Q1: what is GPS week number rollover?
  - GPS uses a week counter that enables receivers to calculate the appropriate date
  - That week counter uses 10 bits and needs to be reset every 1,024 weeks, roughly every 20 years
  - in 2019/Apr, the GPS week counter will reset to zero
  - solution 1: for existing GPS devices, we could update the GPS firwmare to fix this issue
  - solution 2: the modernization of GPS increase week number counter from 10-bit to 13-bit to avoid this issue about 160 years
   
- Q2: How GPS receiver calculate the location?
  - To calculate the Longitude, Latitude and Height position, a GPS receiver precisely measures the different speed of light 
  - delays in the signals coming from 4 or more satellites
  - The distance to each satellite is calculated, and then using trilateration, the 3D position of the GPS antenna is calculated
  - Each satellite transmits messages that include 
    - The time the message was transmitted.
    - Precise orbital information, known as the Ephemeris.
    - Approximate orbits of all GPS satellites, known as the Almanac.
    - General satellite health, etc.
  - All of this information takes 12.5 minutes to transmit
  
- Q3: Why GPS need at least 4 satellite for calculate the location?
  - for trilateration, we need to have at least 3 satellites
  - and it's hard for GPS receiver to equip the expensive clock for GPS time synchronization so the time is also unknown
  - and we need to have extra one satellite to resolve this unknown

- Q4: how to calculate pseudorange?
  - The pseudorange is an approximation of the distance between a satellite and a GNSS receiver.
  - pseudorange is calculated by 4 simultaneous equations which latitude, longitude, altitude and GPS time are unknown
  
- Q5: What is GPS L5 and how does it improve the accuracy?
  - L5 is the third civilian GPS signal and works on 1176 MHz 
  - use L5 in combination with L1 C/A (1575.42 MHz) to improve accuracy (via ionospheric correction) and robustness (via signal redundancy)

- Q6: Why GPS is inaccurate?
  - the reasons why GPS is inaccurate could be
    - non-open sky environment and cause multi-path
	- the satellite number in the sky
	- signal interferences
	- GPS receiver antenna performance

- Q7: What is GDOP?
  - Geometric Dilution Precision is tospecify the error propagation as a mathematical effect of navigation satellite geometry on positional measurement precision
  - GDOP < 1 is ideal case
  - GDOP = 1~20 acceptable
  - GDOP > 20 poor

- Q8: What is ephermics?
  - Precise orbital information.

- Q9: What is Almanac?
  - Approximate orbits of all known satellites

- Q10: What is resonable time for GPS cold start? and why?
  - factors
    - environment (ex: open sky, canyon, indoor, ...etc)
	- are GPS assistances data valid (ex: ephermics, time, rough location)?
  - wihtout AGPS 
    - open sky: 30~60 seconds 
	- Canyon (ex: two building): > 1 minutes
	- indoor: cannot get GPS location fix
  - with AGPS
    - open sky and Canyon: < 10 seconds
	- indoor and close windows: < 20 seconds
	- deep indoor: cannot get GPS location fix

- Q11: why GPS CA code?
  - The C/A-code design includes
    - (1) a short (length-1023) spreading code that repeats every 1 ms and 
	- (2) a low (50 bps) data rate

- Q12: give 2 points, how to calculate the distance
  - assume two points are (x1, y1) (x2, y2)
  - the simplest way to calculate the distance is 
  - square root((x1-x2)^2 + (y1-y2)^2)

- Q13: What information contains in Android location?
  - latitude, longitude, altitude, horizontal accuracy, vertical accuracy, UTC time, bearing, bearing accuracy, speed, speed accuracy, age of this location

- Q14: How to adjust GPS environment is good?
  - C/N(carrier-to-noise density)
  - SNR(signal-to-noise ratio)
  - for hot start: >= 4 satellies with > 20 C/N
  - for cold start: >= 4 satellites with > 30 C/N


## SUPL
- Q1: what is SI and NI, respectively?
  - SI is SET initiated, UE trigger AGPS positioning flow
  - NI is NET initiated, NW trigger AGPS positioning flow

Q2: what's the different between SUPL1.0 and SUPL2.0?
  - SUPL2.0 is compatible with SUPL1.0
  - SUPL2.0 extends to support
    - cell: LTE, NR
	- NI trigger: UDP push or SIP push
	- position protoocl: LPP and LPPe
	- Flow: Area ID (in or out), peridoic report, batch report, ..etc.

Q3: explain SUPL flow
  - SI
    - user launches location related application
    - turn on GPS HW and check what GNSS assistance data we have
    - if GPS engineer need assistance data, it may trigger SUPL SI
    - UE connect to SUPL server which is pre-configured in UE (ex: Google SUPL server, supl.google.com/7275)
    - once UE connect to SUPL server, UE starts TLS handshaking
    - once TLS handshaking done, UE sends SUPL_START msg to SUPL server for UE's capability, current cell info
    - SUPL server sends SUPL_RESPONSE msg to UE to negotiate positioning method (MSA,MBS)
    - UE sends SUPL_POS_INIT msg to SUPL server
    - SUPL server sends SUPL_POS msg which includes GNSS assistance data over RRLP, RRC, LPP, LPPe, ...etc.
    - UE inject the GNSS assistance data to GPS engine to speed up GPS time to first fix (TTFF)
    - SUPL server sends SUPL_END to terminate this connection
  - NI
    - normally, it is triggered by e911 location
    - NW sends SUPL_INIT over either UDP push, SIP push, OMA push or SMS
    - UE check SUPL_INIT msg and show notification/verification to end user if needed
    - once this request is agreed, GPS should be opened
    - UE connects to SUPL server specified in SUPL_INIT msg
    - UE tries to setup a SUPL dedicated APN if needed
    - once UE connect to SUPL server, UE starts TLS handshaking
    - UE sends SUPL_POS_INIT msg to SUPL server
    - SUPL server sends SUPL_POS msg which includes GNSS assistance data over RRLP, RRC, LPP, LPPe, ...etc.
    - UE provides its location or mesurements based on position method tell in SUPL_INIT and sends SUPL_POS to SUPL server
    - SUPL server sends SUPL_END to UE to terminate this connection
    - UE closes GPS HW 
    - UE release SUPL dedicated APN

## Framework
- Q1: Android location architect stack?
  - Android Application
  - Android Location Framework
  - Android JNI (Java Native Interface)
  - Android HIDL
  - user space daemon (GNSS/AGNSS SW)
  - GNSS HW

- Q2: what is ADB?
  - Android Debug Bridge is a programming tool used for the debugging of Android-based devices
  - The daemon on the Android device connects with the server on the host PC over USB or TCP

- Q3: What is JNI, HIDL and AIDL
  - JNI (Java Native Interface): 
  - HIDL (Hardware Interface Definition Language) : Android O re-architects the Android OS to define clear interfaces between the device-independent Android platform and device- and vendor-specific code
  - AIDL (Android Interface Definition Language)
    - allows you to define the programming interface that both the client and service agree upon in order to communicate with each other using interprocess communication (IPC).
	- On Android, one process cannot normally access the memory of another process.
	- So to talk, they need to decompose their objects into primitives that the operating system can understand, and marshall the objects across that boundary for you
	- The code to do that marshalling is tedious to write, so Android handles it for you with AIDL

- Q4: What data type can be supported by AIDL
  - String, CharSequence, List, Map

## GPS application
- Q1: what is ANR
- Q2: what is bundle
- Q3: How to debug application crash?
