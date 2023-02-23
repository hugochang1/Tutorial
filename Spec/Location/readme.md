# Good reference
- https://scdn.rohde-schwarz.com/ur/pws/dl_downloads/dl_common_library/dl_brochures_and_datasheets/pdf_1/LTE_LBS_White_Paper.pdf

# Questions
* What is RTK (real-time Kinematic)
* What is PPP (Precise Point Positioning)

# Terms
* BTS: Base Transceiver Station
* ADR: Accumulated Delta-Range
* ARFCN: Absolute Radio Frequency Channel Number
* ARP: Antenna Reference Point
* EPDU: External Protocol Data Unit
* FTA: Fine Time Assistance
* HA GNSS: High-Accuracy GNSS (RTK, PPP)
* LLA: Latitude Longitude Altitude
* MO-LR: Mobile Originated Location Request
* MT-LR: Mobile Terminated Location Request
* NI-LR: Network Induced Location Request
* Multi-RTT: Multiple-Round Trip Time
* NB-IoT: NarrowBand Internet of Things
* PPP: Precise Point Positioning
* PRS: Positioning Reference Signals
* posSIB: Positioning System Information Block
* RSTD: Reference Signal Time Difference
* RTK: Real-Time Kinematic
* RTD: Relative Time Difference
* SFN: System Frame Number 
* TOA: Time Of Arrival
* TOD: Time Of Day
* TOW: Time Of Week
* WGS-84: World Geodetic System 1984

# Terms
- Android Framework
  - It is a layer between Android application and Hardware abstract layer (HAL)
  - It define SDK APIs to Android application layer and design its logical and implementation to handle it to HAL
  - It defines serval different doamin such Location Framework, WiFi Framework, BT Framework, ...etc.
- E911
  - It's short for enhanced 911
  - It's a system used in North America to automatically provide the caller's location to 911 dispatchers
  - flow: Public Safety Answering Point (PSAP) -> SMLC (Serving Mobile Location Center) -> NW triggers UE location procedure
    - AML (Advanced Mobile Location): send UE location via SMS
    - Control plane (RRLP, RRC, LPP)
    - User plane (SUPL1.0, SUPL2.0)
- GPS
  - Global Positioning System maintained by US
  - It provides geolocation and time information to GPS receiver in outdoor
- GNSS
  - Global Navigation Satellite System contains GPS (US), GLONASS (Russia), BeiDou (China), Galileo (EU) and QZSS (Japan)
- AGPS/AGNSS
  - It's short for assisted GPS or assisted GNSS
  - It's a GNSS augmentation system that often significantly improves the startup performance
- Application
  - It's a computer program designed to carry out a specific task other than one relating to the operation of the computer itself
  - The sample of the application can be the engineer test tool, Google Map, Gmail, ...etc.
- SELinux
  - Security-Enhanced Linux (SELinux) is a Linux kernel security module that provides a mechanism for supporting access control security policies
  - A Linux kernel integrating SELinux enforces mandatory access control policies that confine user programs and system services, as well as access to files and network resources
- HIDL C++
  - Android O re-architects the Android OS to define clear interfaces between the device-independent Android platform and device- and vendor-specific code


# GPS
- GPS messages
  - subframe 1: Satellite clock
  - subframe 2-3: Ephemeris (precise satellite orbit)
  - subframe 4-5: Almanac (satellite network synopsis, error correction)
- start type
  - Hot start: all GPS/GNSS assistance data are valid
  - Warm start: only ephemeris data is invalid
  - Cold start: all GNSS assistance data are invalid
- NMEA (National Marine Electronics Association): it's an ASCII string to represent the location, time and satellite information
  - $GPGGA,055148,2407.8945,N,12041.7649,E,1,00,1.0,155.2,M,16.6,M,X.X,xxxx,*47
    - provide UTC, latitude, Longitude and altitude 
  - $GPGSA,A,3,01,05,09,17,21,2,26,39,,,,1.9,1.0,1.7,*33
    - provide fix type (unavailable, 2D, 3D),  PRN (satellite IDs),  PDOP, HDOP, VDOP
  - $GPGSV,3,1,09,01,27,299,43,………*70
    - provide satellite information such as num of satellite, num of satellite used in location fixed, each satellite ID (GPS: 32, Galileo: 36, Beidou: 63, NavIC: 14, QZSS:10, Glonass: 65-96), elevation (0-90), azimuth (0-359), SRN (0-99)
- When GPS is started, it can choose which AGNSS procedure is needed
  - SUPL: get the assist from SUPL server
  - EPO (Extended Prediction Orbit)
    - it's enhanced ephemeris data which can last at least 1 day and data is calculated by a powerful PC
    - UE can download EPO data from vendor specific servers
  - NLP (network location provider) location: to assist the first location
  - NTP (Network Time Protocol) time: to assist UTC time
  - EPO + NLP + NLP can almost get the similar performance compiared with SUPL

# AGPS
- Control Plane (3GPP, RRLP, RRC, LPP, LPPe)
  - SMLC (Serving Mobile Location Center): It's a location server for control plane in cellular core network
  - Protocols
    - RRLP (Radio Resource Location service Protocol): support in 2G for AGPS, CID, ECID
    - RRC (Radio Resource Control): support in 3G for AGPS
    - LPP (LTE Positioning Protocol): support in 4G and 5G for AGNSS and OTDOA
    - LPPe (LPP extension): support in 4G and 5G for Indoor positioning (WiFi, BT, Sensors)
  - User Scenarios
    - MO-LR (Mobile Oriented Location Request)
    - MT-LR (Mobile Terminated Location Request) notification only or verification (yes or no)
    - NI-LR (Network Initiated Location Request) for E911 (no notification and verification)
  - positioning method
    - MSB (RRLP, RRC, IS801, LPP): NW provides the GNSS assistance data and request UE to calculate the location and report to NW
    - MSA (RRLP, RRC, IS801, LPP): NW provides the GNSS assistance data and request UE to report GNSS measurement data to NW, NW calculate the location
    - Autonomous (RRLP, RRC, IS801, LPP): NW does not provide any GNSS assistance data and request UE to calculate the location and report to NW
    - ECID (RRLP, RRC, LPP): UE measures CID and neighbor cell list and report to NW, NW calculate the location
    - OTDOA (LPP): UE measures the distance of eNB or gNB and report to NW, NW calculate the location
    - AFLT (IS801): similar to OTDOA but it's in C2K
    - WiFi (LPPe): UE scans WiFi info and report to NW, NW calcalate the location based on its database
    - BT (LPPe): similar to WiFi, but it uses BT
    - Sensor/Barometer (LPPe): UE measures the pressure from Barometer and report to NW, NW calculate the altitude based on its database
- User Plane (OMA, SUPL1.0, SUPL2.0)
  - SUPL Server is a TCP/IP server in Internet
  - SUPL1.0 (Secure User Plane Location)
    - User Scenarios
      - SI (SET Initiated)
      - NI (Network Inititated) over OMA Push or SMS
        - no notification and verification, used in E911
        - notification only
        - verification (yes or no)
  - SUPL2.0 (Secure User Plane Location)
    - compitable with SUPL1.0
    - support 4G cell, LPP and LPPe
    - SUPL2.0.4 support 5G cell
    - User Scenarios
      - NI can support over UDP push or SIP push
      - Area ID: like geofence but based on PLMN (Public land mobile network) instead, when user enter or leave then it reports (not popular)
      - support periodic report (not popular)
      - batch report (not popular)
    
