# How does Bluetooth Work?
- https://www.youtube.com/watch?v=1I1vxu5qIUM

## smartphone and earbuds
- 2.4GHz ~ 2.4835GHz
  - divide up to 79 different sections or channels
  - for example on channel 38
    - use different frequency to represent the 0/1 data
    - 2.44313GHz to represent 0
    - 2.44387GHz to represent 1
    - Frequency-Shift Key (closely related to FM)
- data structure
  - 72-bit access code - like address who should receive it
  - 54-bit header - which information being sent
  - 136-bit ~ 8168-bit payload - data
- frequency-hopping spread spectrum
  - 1600 hops/second
  - every two 625 us the smartphone updates one packet to the earbuds to indicate freqency hopping
  - every two 625 us the earbuds updates one packet to the smartphone to indicate freqency hopping
  - smartphone dictates the sequences of channel it will hop to and the earbuds follow along
    - if some of 79 channels are too noisy, smartphone can avoid using them
- WiFi
  - 2.4GHz ~ 2.4835GHz
    - divide up to 14 channels
- How BT handle the conflict on 2.4GHz?
  - Frequency Hoppping
  - Packets
  - Error Detection
  - Noise filtering
