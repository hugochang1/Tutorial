# OTDOA
* OTDOA equations
  * RSTD(i,1) = sqrt((xt-xi)^2 + (yt-yi)^2)/c - sqrt((xt-x1)^2 + (yt-y1)^2)/c + (Ti -T1) + (ni - n1)
    * xt, yt are UE's coordinate which is unknown
    * RSTD(i,1) is the time difference between an eNB i and the reference cell 1 measured at the UE
    * (Ti - T1) is the transmit time offset between the two eNB
    * ni n1 are the UE TOA measurement errors
    * c is the speed of light 3x10^8 m/s

* Multilateration
* ![image](https://user-images.githubusercontent.com/6143237/221404174-4b6bafd2-25b9-4220-9869-7fd557204476.png)
* ![image](https://user-images.githubusercontent.com/6143237/221404200-90e2b225-d3b3-4b9d-8825-ef92819ee774.png)
* Factors influencing OTDOA accuracy
  * RSTD measurement performance
    * PRS SINR (Signal to Interference plus Noise ratio) for reference cell >= -6dB
    * PRS SINR for neighbor cell >= -13dB
  * Radio Environment (ex: multipath)
  * eNodeB synchronization
  * Cell database accuracy
    * antenna altitude
  * measurement Geometry (GDOP)
    * how many neighbor cell UE can do RSTD
    * ![image](https://user-images.githubusercontent.com/6143237/221885834-4e896f13-32b6-46c4-b193-c143b2d55e82.png)
    * ![image](https://user-images.githubusercontent.com/6143237/221885916-3971f0c5-204f-4c4f-852c-8c7cb73984ba.png)
