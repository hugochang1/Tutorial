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
  - GPS antenna performance
  - frequency interference (same frequency band or harmonics from lower frequency bands)
  - GPS HW capability
  - positioning algorithm

# GNSS
- GPS movement
  - https://upload.wikimedia.org/wikipedia/commons/9/9c/ConstellationGPS.gif
- GNSS height
  - https://www.google.com/url?sa=i&url=https%3A%2F%2Fen.wikipedia.org%2Fwiki%2FList_of_orbits&psig=AOvVaw0uOotC3VfngWt87yYVrwO-&ust=1678286485099000&source=images&cd=vfe&ved=0CBAQjRxqFwoTCLj1y7-Gyv0CFQAAAAAdAAAAABAJ

