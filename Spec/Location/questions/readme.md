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
  
  
