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
* commonIEsProvideCapabilities
* a_gnss_ProvideCapabilities
  * gnss_SupportList (list)
    * gnss_ID
    * agnss_Modes
    * gnss_Signals
    * fta_MeasSupport
    * adr_Support
    * velocityMeasurementSupport
  * assistanceDataSupportList
    * gnss_CommonAssistanceDataSupport
      * ReferenceTimeSupport
      * ReferenceLocationSupport
      * IonosphericModelSupport
      * EarthOrientationParametersSupport
    * gnss_GenericAssistanceDataSupport
      * gnss_ID
      * TimeModelsSupport
      * DifferentialCorrectionsSupport
      * NavigationModelSupport
      * RealTimeIntegritySupport
      * DataBitAssistanceSupport
      * AcquisitionAssistanceSupport
      * AlmanacSupport
      * UTC_ModelSupport
      * AuxiliaryInformationSupport
  * locationCoordinateTypes
    * Bool ellipsoidPoint
    * Bool ellipsoidPointWithUncertaintyCircle
    * Bool ellipsoidPointWithUncertaintyEllipse
    * Bool polygon
    * Bool ellipsoidPointWithAltitude
    * Bool ellipsoidPointWithAltitudeAndUncertaintyEllipsoid
    * Bool ellipsoidArc
  * velocityTypes
    * Bool horizontalVelocity
    * Bool horizontalWithVerticalVelocity
    * Bool horizontalVelocityWithUncertainty
    * Bool horizontalWithVerticalVelocityAndUncertainty
* otdoa_ProvideCapabilities
  * otdoa_Mode
  * supportedBandListEUTRA
  * interFreqRSTDmeasurement_r10
  * additionalNeighbourCellInfoList_r10
  * prs_id_r14
* ecid_ProvideCapabilities
  * ecid_MeasSupported
* epdu_ProvideCapabilities

### SLMC <- UE:  requestAssistanceData
* 

### SMLC -> UE:  provideAssistanceData

### SMLC -> UE:  requestLocationInformation

### SMLC <- UE:  provideLocationInformation
