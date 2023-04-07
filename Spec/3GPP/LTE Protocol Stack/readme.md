# LTE Protocol Stack
- https://www.youtube.com/watch?v=PpK5MP78zL8

### Layer 3
- PS NAS (Non-Access-Stratum)
  - EMM (EPS Mobility Management)
    - Tracking Area Update
    - Paging
    - Security Mode Control
    - Authentication
  - ESM (EPS Session Management)
    - Default EPS bearer context activation
    - EPS bearer context modification
    - PDN connectivity procedure
    - PDN disconnect procedure
- RRC (Radio Resource Control)
  - initiate PDCP, RLC, MAC, PHY
  - Broadcast of system information
  - RRC connection control (no RRC connection, then UE is in idle mode)
  - State transition (idle mode or connected mode)
  - Paging
  - Initial security activation
  - measurement configuration and reporting
### Layer 2
- PDCP (Packet Data Convergence Protocol)
  - ROCH (Robust Header Compression/Decompression of IP data packet)
  - maintain PDCP sequence number
  - Security
- RLC (Radio Link Control)
  - Segmentation/Concatenation (the bandwidth of the air interface could be changed dynamically)
  - Retransmission (only for Acknowledge Mode (AM) data transfer)
  - Reordering of RLC data (only for UM and AM data transfer)
- MAC (Medium Access Control)
  - Prioritisation among data streams
  - Error correction through HARQ (Hybrid Automatic Repeat reQuest)
### Layer 1
- PHY (DL-OFDM, UP-SC-FDMA)
  - Encodes raw data before modulation
  - Measures the air interface to know channel quality (due to mobility, air interference)

### Misc
- UE (User Equipment)
- E-UTRAN (Evolved Universal Terrestrial Radio Access Network)
- EPC (Evolved Packet Core)
- EPS (Evolved Packet System) = UE + E-UTRAN + EPC
