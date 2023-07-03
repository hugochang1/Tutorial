## Forum

#### SAE (Society of Automotive Engineers)
- an international professional association and standards organization that focuses on advancing mobility engineering and related technologies.

#### 5GAA (5G Automotive Association)
- a global, cross-industry organization that brings together leading companies from the automotive, technology, and telecommunications industries to accelerate the development and deployment of 5G and Cellular Vehicle-to-Everything (C-V2X) technologies in the transportation ecosystem.
- https://5gaa.org/

#### IEFT (Internet Engineering Task Force)
- an open international community of network designers, operators, vendors, and researchers who contribute to the development and standardization of protocols and technologies for the internet

#### ETSI (European Telecommunications Standards Institute)

#### GCF (Global Certification Forum)

#### ARIB T-109 (Association of Radio Industries and Businesses)
- a technical standard developed by the Association of Radio Industries and Businesses (ARIB) in Japan

#### ETSI ITS-G5 (European Telecommunications Standards Institute, Intelligent Transportation Systems)
- ITS-G5 is based on the IEEE 802.11p standard, which is a modification of the IEEE 802.11 Wi-Fi standard specifically designed for vehicular communication

#### AEC (Automotive Electronics Council) Q-100 grade 2
- a set of stress test qualification requirements for integrated circuits (ICs) used in automotive applications
- Operating temperature range: -40°C to +105°C

--------------------------------------------------------------
## Automotive
- https://www.qualcomm.com/content/dam/qcomm-martech/dm-assets/documents/c-v2x_intro.pdf
  - page 12 done

#### WAVE (Wireless Access in Vehicular Environment)
- a set of communication standards and protocols specifically designed to support wireless communication between vehicles and infrastructure in vehicular environments

#### DSRC (Dedicated Short Range Communication)
- a wireless communication technology designed for vehicle-to-vehicle (V2V) and vehicle-to-infrastructure (V2I) communication in intelligent transportation systems (ITS)

#### BSM (Basic Safety Messages)
- contain the positions, velocities, and other information about the vehicles
- transmitted up to once every 100 ms

#### C-V2X (Cellular Vehicle-to-everything)
- a wireless communication technology designed to enable vehicles to communicate with each other, as well as with infrastructure, pedestrians, and other devices in the transportation ecosystem
- goals
  - improve road safety
  - increase the efficient flow of traffic
  - reduce environmental impacts
  - provide additional communications
  - traveler information services
- 4 types of communications
  - Vehicle-to-vehicle (V2V)
    - mostly for safety and ADAS services
  - Vehicle–to-infrastructure (V2I)
    - allows RSUs (Road Side Unit) to monitor traffic
    - RSUs can be eNodeBs or standalone roadside devices
  - Vehicle-to-pedestrian (V2P)
    - safety alerts to pedestrians, bicyclists
    - provides over-the-top cloud services
- 2 interface
  - PC5 interface for V2V, V2I, V2P operating in ITS bands (e.g., 5.9 GHz)
    - direct communications
    - Operates both in-coverage (within eNodeB) and out-of-coverage (without eNodeB)
    - Latency-sensitive use cases
  - Uu interface for V2N
    - Wide area networks communications
    - Leverages existing LTE networks
    - More latency tolerant use cases

#### ASIL (Automotive Safety Integrity Level)
- a risk classification system used in the automotive industry to assess the safety requirements of electronic and electrical systems in vehicles
- ISO 26262 standard (an international standard for functional safety in road vehicles)
- consider 3 factors
  - Severity (S)
    - The potential severity of harm that could result from a system failure, ranging from no injuries to fatal injuries
  - Exposure (E)
    - The probability of the hazardous situation occurring during the system's operational lifetime
  - Controllability (C)
    - The ability of the driver or other vehicle occupants to control or mitigate the hazardous situation
- Rating 
  - ASIL A: Low safety requirements, with minimal impact on vehicle safety in case of a failure.
  - ASIL B: Moderate safety requirements, with some potential impact on vehicle safety if the system fails. 
  - ASIL C: High safety requirements, with significant potential impact on vehicle safety in case of a failure.
  - ASIL D: The highest safety requirements, with critical potential impact on vehicle safety if the system fails

#### ISO/SAE 21434
- an international standard for cybersecurity in road vehicles, jointly developed by the International Organization for Standardization (ISO) and the Society of Automotive Engineers (SAE)
  - Risk-based approach
  - Cybersecurity management system
  - Security by design
  - Supply chain management
  - Incident response and vulnerability management
  - Continuous improvement

#### ISO 26262
- an international standard for functional safety in road vehicles, specifically focusing on the safety of electrical and electronic systems
  - Risk-based approach
  - Safety lifecycle management
  - Safety integrity levels
  - Safety by design
  - Validation and confirmation
  - Continuous improvement

#### ITS (Intelligent Transportation System)
- based on IEEE 802.11p
- the integration of advanced information and communication technologies into transportation infrastructure and vehicles to improve the safety, efficiency, and sustainability of transportation networks

#### Radar (Radio Detection and Ranging) vs Lidar (光達使用多重紅外光脈衝來量測物體的距離和速度)
- accuarcy: Lidar is good
- weather impact: Radar is good

#### ECU (Engine Control Unit)
- control engine's performance including fuel injection, ignition timing, and air-to-fuel ratio

#### TCU (Transmission Control Unit)
- an electronic control unit responsible for managing the operation of the vehicle's transmission

#### T-Box (Telematics Box)
- an electronic device installed in vehicles to enable various telematics functions, such as remote diagnostics, vehicle tracking, emergency assistance, and connectivity services

#### C-NCAP (China New Car Assessment Program)
- a car safety assessment program in China that evaluates the safety performance of new vehicles sold in the Chinese market

#### ADAS (Advanced Driver Assistance Systems)
- a set of electronic systems and technologies designed to improve vehicle safety, comfort, and driving experience
- Adaptive Cruise Control (ACC)
- Lane Departure Warning (LDW)
- Lane Keeping Assist (LKA)
- Automatic Emergency Braking (AEB)
- Blind Spot Monitoring (BSM)
- Rear Cross-Traffic Alert (RCTA)
- Traffic Sign Recognition (TSR)
- Parking Assistance

#### CSMS (cybersecurity management system)

#### Proximity Services (ProSe)
- a feature introduced in LTE networks to enable direct communication between devices without relying on the cellular network infrastructure
- equals to Device-to-Device (D2D) or Sidelink (SL)

#### PSSCH (Physical Sidelink Shared Channel)
- a component of the sidelink communication technology in LTE networks

#### CACC (Cooperative Adaptive Cruise Control)
- an extension to the adaptive cruise control (ACC) concept using Vehicle-to-Everything (V2X) communication

#### IVT (Intelligent Vehicle Telematics)
#### IVI (In-Vehicle Infotainment)
#### IVS (Integrated Vehicle Systems)
#### NAD (Network Access Device)
- a term used to describe a device that provides connectivity between a user's device and a network, such as the internet or a local area network (LAN)

#### MCU (Microcontroller Unit)
- a small, integrated computer chip that contains a processor core, memory, and programmable input/output (I/O) peripherals

#### OmniAir Consortium 
- a non-profit organization that focuses on the certification and testing of connected vehicle technologies, such as Dedicated Short-Range Communications (DSRC), Cellular Vehicle-to-Everything (C-V2X), and other Vehicle-to-Infrastructure (V2I) and Vehicle-to-Vehicle (V2V) communication systems

#### TCU (Telematics Control Unit)
- an electronic device used in vehicles to enable various telematics functions, such as remote diagnostics, vehicle tracking, emergency assistance, and infotainment services

#### IEEE1609
- a family of standards for Wireless Access in Vehicular Environments (WAVE), which defines the architecture, communication protocols, and security mechanisms for vehicle-to-vehicle (V2V) and vehicle-to-infrastructure (V2I) communications

#### CAN bus (Controller Area Network)
- a communication protocol used in automotive and industrial applications for transmitting data between electronic control units (ECUs) and devices within a system. 

#### RSU (Road Side Unit)
- a critical component of Intelligent Transportation Systems (ITS) and Vehicle-to-Infrastructure (V2I) communication systems
- RSUs are fixed infrastructure devices installed along roads, at intersections, or other strategic locations to facilitate communication between vehicles and the transportation infrastructure
