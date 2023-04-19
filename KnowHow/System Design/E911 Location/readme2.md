# # Design a AGNSS system which can support E911 location (GNSS HW and MD HW are on the same SoC)
### Requirement
- are GNSS HW and MD on the same SoC?
  - yes
- OS?
  - Android
- user scenarios?
  - E911 NILR
  - MTLR
  - MOLR
- which positioning protocol we should support?
  - SUPL
  - RRLP
  - RRC
  - LPP/LPPe
- which positioning technologies need to be supported?
  - AGNSS
  - ECID
  - OTDOA
  - WIFI RSSI
  - BT RSSI
  - Pressure sensor
  - 5G DL AoD
  - 5G DL RTT
- non-functional requirements
  - recovery for crash case
  - test methodology

### Architecture
- Location Framework (receive SUPL_INIT)   LPPe Service
- GNSS daemon (SUPL connection send/receive)
- MD SW (PE, SUPL, RRC, LPP/LPPe stack)
- GNSS HW (ME) & MD HW

### Interface
- Location Framework / GNSS daemon (HIDL)
  - Location Framework -> GNSS daemon: recevice_supl_init(raw_data, raw_data_len)
  - Location Framework <- GNSS daemon: request apn connection(apn_name)
  - Location Framework <- GNSS daemon: release apn connection(apn_name)
  - Location Framework -> GNSS daemon: provide apn connection status(status)
  - Location Framework <- GNSS daemon: bind_supl_fqdn_to_apn(supl_fqdn)
  - Location Framework -> GNSS daemon: bind_supl_fqdn_to_apn_result(ret, ip)

- LPPe Servie / WiFi/BT/Sensor Framework (Android SDK API)
  - LPPe Servie -> WiFi/BT/Sensor Framework: start measurement()
  - LPPe Servie -> WiFi/BT/Sensor Framework: stop measurement()
  - LPPe Servie <- WiFi/BT/Sensor Framework: provide measurement(scan_result or pressure_raw_data)

- LPPe Service / GNSS daemon (HIDL)
  - LPPe Servie <- GNSS daemon: WiFi/BT/Sensor start measurement()
  - LPPe Servie <- GNSS daemon: WiFi/BT/Sensor stop measurement()
  - LPPe Servie -> GNSS daemon: WiFi/BT/Sensor provide measurement(scan_result or pressure_raw_data)
  - LPPe Service -> GNSS daemon: clear ongoing session()
  - LPPe Service <- GNSS daemon: clear ongoing session()

- GNSS daemon / MD SW (IPC e.g. shared memory + event trigger)
  - GNSS daemon <- MD SW: WiFi/BT/Sensor start measurement()
  - GNSS daemon <- MD SW: WiFi/BT/Sensor stop measurement()
  - GNSS daemon -> MD SW: WiFi/BT/Sensor provide measurement(scan_result or pressure_raw_data)
  - GNSS daemon -> MD SW: receive supl init (raw_data)
  - GNSS daemon <- MD SW: request apn connection(apn_name)
  - GNSS daemon <- MD SW: release apn connection(apn_name)
  - GNSS daemon -> MD SW: provide apn connection status(status)
  - GNSS daemon <- MD SW: bind_supl_fqdn_to_apn(supl_fqdn)
  - GNSS daemon -> MD SW: bind_supl_fqdn_to_apn_result(ret, ip)
  - GNSS daemon <- MD SW: supl_data_send(supl_raw_data)
  - GNSS daemon -> MD SW: supl_data_receive(supl_raw_data)
  - GNSS daemon <- MD SW: supl_connection_close_request(reason)
  - GNSS daemon -> MD SW: supl_connection_status_report(status)
  - GNSS daemon -> MD SW: clear ongoing session()
  - GNSS daemon <- MD SW: clear ongoing session()

### Flow
- user dials E911 call
  - NW sends SUPL INIT msg to UE
  - Location Framework receives SUPL INIT msg
  - Location Framework -> GNSS daemon: recevice_supl_init(raw_data, raw_data_len)
  - GNSS daemon -> MD SW: receive supl init (raw_data)
  - MD start AGNSS session
    - MD turns on GNSS HW
    - GNSS daemon <- MD SW: request apn connection(apn_name)
    - GNSS daemon -> MD SW: provide apn connection status(status)
    - GNSS daemon <- MD SW: bind_supl_fqdn_to_apn(supl_fqdn)
    - GNSS daemon -> MD SW: bind_supl_fqdn_to_apn_result(ret, ip)
    - GNSS daemon <- MD SW: supl_data_send(supl_raw_data)
      - UE connect with SLP through TCP connection
        - TLS handshake
          - UE -> SLP: SUPL POS INIT
            - GNSS daemon <- MD SW: supl_data_send(supl_raw_data)
          - UE <-> SLP: SUPL POS (RRLP, RRC, LPP/LPPe)
            - GNSS daemon <- MD SW: supl_data_send(supl_raw_data)
            - GNSS daemon -> MD SW: supl_data_receive(supl_raw_data)
            
            - depends on what position technologies needed by NW (ex: AGNSS, ECID, OTDOA, WiFi, BT, Sensor, 5G DL AoD, 5G DL RTT)
            - MD SW collect ECID, OTDOA, 5G DL AoD, 5G DL RTT
            
            - GNSS daemon <- MD SW: WiFi/BT/Sensor start measurement()
              - LPPe Servie <- GNSS daemon: WiFi/BT/Sensor start measurement()
              - LPPe Servie -> WiFi/BT/Sensor Framework: start measurement()
            
            - LPPe Servie <- WiFi/BT/Sensor Framework: provide measurement(scan_result or pressure_raw_data)
              - LPPe Servie -> GNSS daemon: WiFi/BT/Sensor provide measurement(scan_result or pressure_raw_data)
              - GNSS daemon -> MD SW: WiFi/BT/Sensor provide measurement(scan_result or pressure_raw_data)
            
            - GNSS daemon <- MD SW: WiFi/BT/Sensor stop measurement()
              - LPPe Servie <- GNSS daemon: WiFi/BT/Sensor stop measurement()
              - LPPe Servie -> WiFi/BT/Sensor Framework: stop measurement()

          - UE <- SLP: SUPL END
    
  - MD stop AGNSS session
    - GNSS daemon <- MD SW: supl_connection_close_request(reason)
    - GNSS daemon -> MD SW: supl_connection_status_report(status)
    - GNSS daemon <- MD SW: release apn connection(apn_name)
    - MD turns off GNSS HW

### non-functional requirements
- recovery for crash case
  - if Android Framework crash
    - Android framework reboot
    - LPPe Service -> GNSS daemon: clear ongoing session()
    - GNSS daemon -> MD SW: clear ongoing session()
  - if GNSS daemon crash
    - LPPe Service <- GNSS daemon: clear ongoing session()
    - GNSS daemon -> MD SW: clear ongoing session()
  - if MD SW crash
    - GNSS daemon <- MD SW: clear ongoing session()
    - LPPe Service <- GNSS daemon: clear ongoing session()

- test methodology
  - field test
  - machine test
    - pros
      - to save the time and effort to go to the field test
    - cons
      - need a lot of money to buy the machine
  - device self test for GNSS daemon and MD SW
    - pros
      - to save the time and effort to go to the field tes
      - to save the time and effort on machine test effort
    - cons
      - require RD effort to develop self testing
      - collect all test scenario input data and expect flows
