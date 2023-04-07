# Good
- LTE transport channel mapping
  - https://www.youtube.com/watch?v=ZSNt2qUuU_U
- RnS 5G
  - https://www.youtube.com/watch?v=qerqp69ojQw&t=85s
- 1G~5G introduction
  - https://www.youtube.com/watch?v=g-gGeAe-PJA
- LTE tutorials
  - https://www.tutorialspoint.com/lte/index.htm
- RF
  - Modulation & QAM Basics
    - https://www.youtube.com/watch?v=vzIk9ungyvc
  - Understanding APSK and QAM
    - https://www.youtube.com/watch?v=1xGncBvWv6U
# NR air interface
- ![image](https://user-images.githubusercontent.com/6143237/224556390-9cfe8fe6-a1ce-4c4c-962b-c2b4df66f8a4.png)
# Modulation schemes
- QPSK, 16QAM, 64QAM, 128QAM, ... 2048QAM
- Quadrature Amplitude Modulation
- https://www.youtube.com/watch?v=YnWCRUoTEAI
- higher QAM required high SNR
  - 16QAM: 16 db
  - 256QAM: 30 db
  - 1024QAM: 35 db
# Carrier Aggregation (CA)
- https://www.youtube.com/watch?v=tZ50CSADKIY&list=PLE6yE0jB6BTOY6Z1DKEkQ8yZ8fFPUiCD8&index=9
- Terms
  - CC (Component Carrier)
  - SCC (Second Component Carrier)
  - ATBC (Aggregated Transmission Bandwidth Configuration
  - PRB (Physical Resource Blocks)
- CA bandwidth class
  - Class A: ATBC <= 100, max number of CC=1
  - Class B: ATBC <= 100, max number of CC=2
  - Class C: 100 < ATBC <= 200, max number of CC=2
- CA configuration
  - CA_40C: Intra Band Contiguous
  - CA_3A_3A: Intra Band Non-Contiguous
  - CA_3A-5B: Inter Band CA
# LTE transport channel mapping
- Radio Link Control Layer
  - PCCH (Paging Control Channel) - eNB -> UE: idle/sleep state
  - BCCH (Broadcast Control Channel) - eNB -> UE: DL BW, Antenna config, Ref Signal Power, ...etc.
    - MIB (Master Information Block) - System critical info to accquire the cell
    - SIB (System Information Block) - Dynamic information to access the cell
  - CCCH (Common Control Channel) - UE -> eNB: to establish radio connection
  - DCCH (Dedicated Control Channel) - eNB -> UE: use to tranfer control info after bearer setup
  - MCCH (Multicast Control Channel) - eNB -> UE: for multicast or broadcast message
  - DTCH (Dedicated Traffic Channel) - eNB <-> UE: for DL/UL of user data
  - MTCH (Multicast Traffic Channel) - eNB -> UE: real time broadcasting of sports, events, ...etc.
- Physical layer
  - PCH (Paging Channel)
    - no uplink direction
    - MIB
  - BCH (Broadcast Channel)
    - no uplink direction
    - SIB
  - DL-SCH (Downlink Shared Channel)
  - UL-SCH (Uplink Shared Channel)
  - RACH (Random Access Channel)
    - for uplink direction for the initiated phase 
  - MCH (Multicast Channel)
    - no uplink direction

# Terms
- 3rd Generation Partnership Project (3GPP)
  - Global System for Mobile Communications (GSM)
  - Universal Mobile Telecommunication System (UMTS)
  - Long-Term Evolution (LTE)
  - New Radio (NR)
- Radio Frequency (RF)
  - Time Division Duplex (TDD)
  - Frequency Division Duplex (FDD)
  - Code Division Multiple Access (CDMA)
  - Orthogonal Frequency Division Multiple Access (OFDMA)
  - Multiple Input Multiple Output (MIMO)
  - Transmit Antenna Array (TxAA)
  - Spatial multiplexing (SM)
  - space-division multiplexing (SDM)
  - Cyclic Delay Diversity (CDD)
  - Number of Resource Block (NRB)
- User Equipment (UE)
  - Universal Integrated Circuit Card (UICC)
  - Universal Subscriber Identity Module (USIM)
  - international mobile equipment identity (IMEI)
  - International Mobile Subscriber Identity (IMSI)
- Base Station/BS (2G)
  - NodeB/NB (3G)
  - eNodeB/eNB (4G)
  - gNodeB/gNB (5G)
  - evolved UMTS terrestrial radio access (E-UTRA)
  - evolved UMTS terrestrial radio access network (E-UTRAN)
  - home eNB (HeNB)
  - closed subscriber group (CSG)
  - Public Land Mobile Network (PLMN)
- Core Network (CN)
  - 4G/System Architecture Evolution (SAE)
  - 4G/Evolved Packet Core (EPC)
  - 5G/5G Core (NGC)
  - Home Subscriber Server (HSS)
  - Earthquake and Tsunami Warning System (ETWS)
  - Equipment Identity Register (EIR)
  - Policy Control and Charging Rules Function (PCRF)
  - Call Detail Records (CDR)
  - 4G/MME (Mobility Management Entity)
  - 5G/AMF (Access and Mobility Management Function)
  - MME code (MMEC)
  - MME Group Identity (MMEGI)
  - MME identifier (MMEI) = MMEC + MMEGI
  - 4G/SGW (Serving Gateway)
  - 5G/UPF (User Plane Function)
  - PGW (Packet Data Network Gateway)
  - ANDSF (Access Network Discovery and Selection Function)
  - ePDG (Evolved Packet Data Gateway)
  - Packet Data Network (PDN)
  - access point name (APN)
  - Policy Control Enforcement Function (PCEF)
  - tracking area code (TAC)
  - Tracking Area Identity (TAI) = PLMN-ID + TAC
  - E-UTRAN cell global identifier (ECGI)
- Protocol layers
  - Access Stratum (AS) 
  - Non Access Stratum (NAS)
  - Service Data Unit (SDU)
  - Protocol Data Unit (PDU)
  - radio resource control (RRC)
  - packet data convergence protocol (PDCP)
  - radio link control (RLC)
    - Transparent Mode (TM)
    - Unacknowledged Mode (UM)
    - Acknowledged Mode (AM)
  - medium access control (MAC)
    - transport blocks (TB)
- Misc
  - SCTP (Stream Control Transmission Protocol)
  - Quality of Service (QoS)
  - guaranteed bit rate (GBR)
  - Traffic Flow Templates (TFT)
  - Home-PLMN
    - a subscribed user uses his operator's PLMN
  - Visited-PLMN
    - use the outside of home network
  - primary synchronization signal (PSS)
  - secondary synchronization signal (SSS)
  - Transmission Time Interval (TTI)
  - inter symbol interference (ISI)
  - single frequency networks (SFNs)
  - Peak to Average Power Ratio (PAPR)
  - IMS (IP Multimedia Subsystem)
    - Call Session Control Function (CSCF)