## landing SUPL2.0 in 2013
  - study the spec within 1 month and pass all test cases by using Spirent test machine within 2 months

## AOSP AGPS in 2014
  - purpose
    - to remove the dependency of our proprietary modules in Android Framework which our Tier-1 customers didn't like it
  - scope
    - impact modules: Android Framework, GPS Daemon, AGPS Daemon and MD
    - coordinate with 10 colleagues to achieve this architecture change
    - re-design interface between GPS and AGPS, AGPS and MD
  - result
    - complete the architecture change within 3 months including full SQC and success landing to all our next platforms
    - our customer, LG and Samsung, adopted our solutions
	- introduce the unity AGPSD to all of different Android versions (ex: K, L, M, N, O, P, Q, R, S, ...etc.)
	  - it can help reduce the overall effort for maintenance and fully use of AGPS daemon

## AGPSD refactoring in 2015
  - purpose
    - there are too many redundant source codes in AGPS daemon and hard to maintain it
      - the reason of redundant source codes was from porting, ex: AGPS solution was designed in the feature phone with non-Android OS and leverage this SW to Android Smart phone
      - because different OS has different OS API and libraries
    - most AGPS test case need to be performed with the test machine (ex: Spirent or R&S) and it take time to do that
	    - introduce the auto test in AGPS daemon to easy test all SUPL flows and SUPL parameters by itself without using any test machine
  - scope
    - mainly in AGPS Daemon
  - result
    - reduce almost half percentage of source code which we need to change frequently (30,000 lines -> 15,000 lines)
    - design at least 100 test cases including SUPL and control plane 
    - one round auto test can be done within 2 mintues (compare to real lab test > 1 day)

## LPPe development in 2017
  - purpose
    - it's a mandatory requirement for US operators such as VZW, T-TMO, and AT&T for E911 location required by FCC (Federal Communications Commission)
  - scope
    - support WiFi, BT/BLE, Barometer, and IP measurements
    - coordinate with 15 colleagues to achieve this development
	- IODT: 
	  - the test machine vendors: R&S and Spirent
	  - the infra vendor: Ericsson
  - result
    - landing LPPe to our US projects and got the passed record for ATT, VZW, TMO

## USB Tethering Throughput Tuning (CPE/MiFi product) in 2021
  - purpose
    - to improve our product capability on USB Tethering T-put
  - scope
    - design the SKB buffer recycle mechanism architecture between HW packet accelerator and USB tethering protocol (ex: RNDIS, ECM, NCM)
    - cooperate with 10 colleagues to complete this task
  - result
    - improve at least 50% t-put from 4Gbps to 6Gbps (the data path is USB from or to Ethernet)
    - patent gained

## Module-IOT (data card product) in 2021
  - background of data card product
    - we provide a 2G/3G/4G/5G modem solution and connect to external host via PCIe or USB
	  - normally, PCIe or USB will be wrapped into M.2 interface for PC/NB industry
  - purpose
    - my major job of this task is to ensure USB interface can meet our PM's requirements
  - scope
    - coordinate about 30 colleagues and role and responsibility for development to finish this task within 6 months
	  - USB functions: MBIM, GNSS, Logging, remote wakeup, adb, mass storage
	  - Host wakes up the device via UART
    - performance
      - low power
      - booting time
    - coordinate QA resource for SQC and tracking all issues
  - result
    - create a new business for my company to ensure that data card product can also use USB interface

## CPM (CPE/MiFi product) in 2022
  - background of CPE/MiFi product
    - CPE (customer-premises equipment) is any terminal and associated equipment located at a subscriber's premises and connected with a carrier's telecommunication circuit 
    - MiFi is a brand name used to describe a wireless router that acts as a mobile Wi-Fi hotspot.
  - purpose
    - to ensure our customer can achieve the mass production within our schedule
  - scope
    - customer's HW/SW requirement and schedule
    - HW: QVL (Qualified Vendors List), schematic design, simulation, review -> seeking our HW experts to assist these topics
    - SW: SW feature set, T-put, low power, ...etc. -> seeking our SW experts for those requirements
    - operator certification
    - GCF/PTCRB
    - device-IOT (Lab-IOT, Field Test, Acceptance Test)
  - result
    - assist customer to reach MP for 2 projects
