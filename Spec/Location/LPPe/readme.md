# LPPe
* spec download link: https://www.openmobilealliance.org/release/LPPe/V2_0-20200804-C/OMA-TS-LPPe-V2_0-20200804-C.pdf

# Poisitioning method
* highAccuracy3DPosition
  * latitude        INTEGER(-2147483648..2147483647)
  * longitude        INTEGER(-2147483648..2147483647)
* IP (ipv4, ipv6, NAT)
* BT/BLE (report a list of MAC and RSSI)
* WLAN (report a list of MAC and RSSI)
* Sensor (Barometer for altitude)

# Message
* requestCapability
  * Common
    * iP-Address
    * highAccuracy3DPosition
    * highAccuracy3Dvelocity
  * wlan-ap
  * sensor
  * srn (bt, ble, nfc, ...etc.)
* provideCapability
  * Common
    * iP-Address (ipv4, ipv6, NAT)
    * highAccuracy3DPosition
    * highAccuracy3Dvelocity
  * wlan-ap 
    * MeasSupport (SSID, SN, RSSI, RTD, ...etc)
    * MAC
  * sensor (atmosphericPressureSupport)
  * srn
    * type (bt, ble, nfc, ...etc.)
    * MAC
* requestAssistanceData (most of them are for MSB)
* provideAssistanceData (most of them are for MSB)
* requestLocationInformation
  * Common
    * iP-Address
  * wlan-ap (SSID, RSSI, ChanFreq, ...etc)
  * sensor (atmosphericPressure)
  * snr (bt, ble, nfc, ...etc)
* provideLocationInformation
  * Common
    * highAccuracy3Dposition
    * highAccuracy3Dvelocity
    * iP-Address-List (ipv4, ipv6, nat)
    * locationSource (agnss, wlanAP, srn, sensors, ...etc.)
  * wlan-ap
    * wlan-AP-Error
    * wlan-AP-CombinedLocationInformation (1~64)
      * relativeTimeStamp
      * servingFlag
      * MAC, SSID, SignalNoise, SignalStrength, ChannelFrequency, RoundTripDelay ReportedLocation, ...etc.
  * sensor
    * sensorError
    * atmosphericPressure
      * sensorMeasurement
      * uncertainty
  * srn
    * srnError
    * srnMeasurementList (1~64)
      * MAC
      * type (bt, ble, nfc, ...etc.)
      * measurementList (1~64)
        * relativeTimeStamp
        * rssi
        * rtd
