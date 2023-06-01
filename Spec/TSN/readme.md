
# Precision Time Protocol (PTP)
- How a PTP slave syncs with a PTP master
  - https://www.youtube.com/watch?v=Forh3XfD_Ec
- there are two delays
  - the delay from system to really send SYNC from the master to the slave
    - when the system really send out the SYNC msg, then record its timestamp and send the FOLLO UP msg for this timestmp to the slave
  - the propagation delay between the master and the slave
    - the slave uses the timestamp received from SYNC msg and send out DELAY REQ msg to the master to eliminate the propagation delay
- PTP msg flow
  - master to slave: SYNC msg
  - master to slave: FOLLOW UP msg
  - slave to master: DELAY REQ msg
  - master to slave: DELAY RSP msg
