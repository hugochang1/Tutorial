# LocationManager
* Location and Context API
  * https://developers.google.com/location-context
* provide to access to the system location services
  * provider
    * GPS
    * Network Location Provider (ex: provided by GMS=Google Mobile Services)
    * Fused Location Provider (GPS + NLP)
    * Passive
  * requestLocationUpdates/removeUpdates
  * register/unregister to listen GnssStatus, NmeaMessage, GnssMeasurements, GnssNavigation
  * getLastKnownLocation

# Location
* represent a geographic location such as UTC time, latitude, longitude, accuracy, altitude, ...etc.

# GnssStatus
* the current state of the GNSS engine such as constellation type, carrier frequency, satellite ID, elevation, azimuth, baseband/antenna carrier-to-noise, used in fix, ...etc.)

# Geocoder
* A class to transform location coordinate (latitude and longitude) info an address

# GnssAntennaInfo
* GNSS antenna info are measured for each specific device model by device manufactures
  * GPS antenna characteristics can be changed such as a device is folded open or closed

# GnssCapabilities
* provide GNSS capabilities such as constellation type (ex: GPS, Galileo, Glonass, Beidou) and their carry frequency
  * whether GNSS chip can support low power mode. when low power mode is active, GNSS HW must take limit the power usage
  * whether to support MSA (mobile station assisted)
  * whether to support MSB (mobile station based)
  * whether GNSS chip can support Accumulated Delta Range (ADR)
    * ADR measures the change in phase of the carrier wave, ADR is theoretically ~1000x more precise than the pseudorange


