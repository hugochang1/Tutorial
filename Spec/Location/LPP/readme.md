# 3GPP TS 37.355
* download: https://www.etsi.org/deliver/etsi_ts/137300_137399/137355/16.02.00_60/ts_137355v160200p.pdf

# LPP
### SMLC -> UE:  requestCapabilities
### SLMC <- UE:  provideCapabilities
### SLMC <- UE:  requestAssistanceData
### SMLC -> UE:  provideAssistanceData
### SMLC -> UE:  requestLocationInformation
### SMLC <- UE:  provideLocationInformation

# LPP_LPP_MessageBody lpp_MessageBody

### SMLC -> UE:  requestCapabilities
* commonIEsRequestCapabilities
* a_gnss_RequestCapabilities
  * Bool gnss_SupportListReq
  * Bool assistanceDataSupportListReq
  * Bool locationVelocityTypesReq
* otdoa_RequestCapabilities
* ecid_RequestCapabilities
* epdu_RequestCapabilities

### SLMC <- UE:  provideCapabilities
### SLMC <- UE:  requestAssistanceData
### SMLC -> UE:  provideAssistanceData
### SMLC -> UE:  requestLocationInformation
### SMLC <- UE:  provideLocationInformation
