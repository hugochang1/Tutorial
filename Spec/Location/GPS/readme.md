# Good Reference
- GPS background
  - https://www.youtube.com/watch?v=8eTlI19_57g

# GPS equations
- UE **latitude, longitude and altitude** are unknown
- UE does not know the **accurate GPS time**
- The position of GPS satellites are known from their **ephemeris**
- because all GPS satellites are synced together by using the atomic clocks
  - If UE receives 3 satellites then latitude, longitude and accurate GPS time can be calculated
  - If UE receives 4 satellites then altitude can also be calculated
- math
  - Unknown
    - UE position = x, y, z
    - GPS time = t
    - the distance between UE and GPS satellite i = di
  - Known
    - GPS satellite i position = Gix, Giy, Giz (known)
    - speed of the light = c = 3x10^8
    - the time which UE receives GPS satellite i = ti
  - Equation
    - di = (ti - t) x c = sqrt((x-Gix)^2 + (y-Giy)^2 + (z-Giz)^2)

# The reasons cause GPS inaccurate
- GPS satellite
  - GPS satellite clock drift
    - although atomic clock is accurate but not perfect
  - GPS satellite ephemeric inaccurate
  - GPS satellite signal bias
- GPS signal traval
  - Atmosphere delay (e.g. ionospheric and tropospheric)
  - multipath (e.g. path loss, reflection, ...etc.)
- UE
  - bad GDOP (Geometric Dilution of Precision)
  - GPS antenna performance
  - frequency interference (same frequency band or harmonics from lower frequency bands)
  - GPS HW capability
  - positioning algorithm
  - Geodetic System (ex: WGS84, BJZ54, 安西80)

# GNSS
- the animation of GPS satellites and earth
  - https://upload.wikimedia.org/wikipedia/commons/9/9c/ConstellationGPS.gif
- the height between GNSS satellites and earth
  - https://www.google.com/url?sa=i&url=https%3A%2F%2Fen.wikipedia.org%2Fwiki%2FList_of_orbits&psig=AOvVaw0uOotC3VfngWt87yYVrwO-&ust=1678286485099000&source=images&cd=vfe&ved=0CBAQjRxqFwoTCLj1y7-Gyv0CFQAAAAAdAAAAABAJ

# GNSS Technology
### GPS L5
- GPS L1: 1575.42 MHz
  - 1.023 million chips per second
- GPS L5: 1176.45 MHz
  - 10.23 million chips per second -> has better anti-interference compared with GPS L1
  - this frequency (1176.45 MHz) only reserve for space satellite to use, it means the interference in the air is less
  - signal strength is better than GPS L1 about 6dB
  - different radio frequency has different travel speed in ionospheric, it means ionospheric can be corrected by using GPS L1 and GPS L5 at the same time
### TBS (Terrestrial Beacon System)
- it's similar with GPS but deploy on terrestrial instead of in the space
- it also uses trilateration to get location fix just same as GPS
### PPP (Precise Point Positioning)
- GPS receiver observe the carrier phase instead of GPS pseudo code
- use GPS L1 + L5 to elimiate ionospheric delay


# AGNSS
- User Plane (SUPL)
- Control Plane (3GPP)
- Download the orbit data from proprietary server
  - Q: XTRA
  - M: EPO (extended predicted orbit)
- calculate the extended predicted orbit at UE
  - M: hot still
- DGPS (Differential GPS)
  - use a fixed base GPS receiver with knowing its precision location to correct GPS errors and send this GPS correction info to the nearby UE (ex: SUPL, LPP, ...etc.)
- RTK (Real Time Kinematic)
  - one of DGPS but it can provide the GPS correction level in the carrier phase 
  - SSR vs OSR
    - https://www.geopp.de/ssr-vs-osr/
    - **OSR** is Observation Space Representation
      - provide the lump sum of all these errors is observed by a network of reference stations
      - require the rover to send its approximate position to the service provide to generate the correction periodically
    - **SSR** is State Space Representation
      - provide the different GNSS error components respectively such as satellite clocks, satellite orbits, satellite signal biases, ionospheric delay, tropospheric delay
      - require the rover to send its approximate position to the service provide to generate the correction once
