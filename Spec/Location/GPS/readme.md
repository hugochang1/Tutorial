# GPS equations
- UE **latitude, longitude and altitude** are unknown
- UE does not know the **accurate GPS time** is also unknown
- The position of GPS satellites are known from their **ephemric**
- because all GPS satellites are synced together by using the atomic clocks
  - If UE receives 3 satellites then latitude, longitude and accurate GPS time can be calculated
  - If UE receives 4 satellites then altitude can also be calculated

# The reasons cause GPS inaccurate
- GPS satellite
  - GPS clock
  - GPS ephemeric
- GPS signal traval
  - Atmosphere delay (e.g. ionospheric and tropospheric)
  - multipath (e.g. path loss, reflection, ...etc.)
- UE
  - GDOP (Geometric Dilution of Precision)
  - GPS antenna performance
  - frequency interference (same frequency band or harmonics from lower frequency bands)
  - GPS HW capability
  - positioning algorithm

# GNSS
- GPS movement
  - https://upload.wikimedia.org/wikipedia/commons/9/9c/ConstellationGPS.gif
- GNSS height
  - https://www.google.com/url?sa=i&url=https%3A%2F%2Fen.wikipedia.org%2Fwiki%2FList_of_orbits&psig=AOvVaw0uOotC3VfngWt87yYVrwO-&ust=1678286485099000&source=images&cd=vfe&ved=0CBAQjRxqFwoTCLj1y7-Gyv0CFQAAAAAdAAAAABAJ

# GPS L5
- GPS L1: 1575.42 MHz
  - 1.023 million chips per second
- GPS L5: 1176.45 MHz
  - 10.23 million chips per second -> has better anti-interference compared with GPS L1
  - this frequency (1176.45 MHz) only reserve for space satellite to use, it means the interference in the air is less
  - signal strength is better than GPS L1 about 6dB
  - different radio frequency has different travel speed in ionospheric, it means ionospheric can be corrected by using GPS L1 and GPS L5 at the same time

# TBS (Terrestrial Beacon System)
- it's similar with GPS but deploy on terrestrial instead of in the space
- it also uses trilateration to get location fix just same as GPS

# AGNSS
- DGPS (Differential GPS)
  - use a fixed GPS receiver and know its precision location to correct GPS errors and send this GPS erros to the nearby UE (ex: SUPL, LPP, ...etc.)
- RTK (Real Time Kinematic)
  - one of DGPS but it can provide the GPS correction level in the carrier phase 
- PPP (Precise Point Positioning)
  - PPP is a positioning technique that removes or models GNSS system errors to provide a high level of position accuracy from a single receiver
  - A PPP solution depends on GNSS satellite clock and orbit corrections, generated from a network of global reference stations
  - Once the corrections are calculated, they are delivered to the end user via satellite or over the Internet
