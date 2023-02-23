# 3GPP TS 37.355
* download: https://www.etsi.org/deliver/etsi_ts/137300_137399/137355/16.02.00_60/ts_137355v160200p.pdf

# LPP
### SMLC -> UE:  requestCapabilities
### SLMC <- UE:  provideCapabilities
### SLMC <- UE:  requestAssistanceData
### SMLC -> UE:  provideAssistanceData
### SMLC -> UE:  requestLocationInformation
### SMLC <- UE:  provideLocationInformation

# Functionality
* a_gnss
* otdoa
* ecid
* epdu

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
    * gnss_GenericAssistanceDataSupport (list)
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
* commonIEsRequestAssistanceData
  * mcc, mnc, cellid
* a_gnss_RequestAssistanceData
  * gnss_CommonAssistDataReq
    * ReferenceTime
    * ReferenceLocation
    * IonosphericModel
    * EarthOrientationParameters
  * gnss_GenericAssistDataReq (list)
    * gnss_ID
    * TimeModels
    * DifferentialCorrections
    * NavigationModel
    * RealTimeIntegrity
    * DataBitAssistance
    * AcquisitionAssistance
    * Almanac
    * UTCModel
    * AuxiliaryInformation
* otdoa_RequestAssistanceData
  * physCellId
* epdu_RequestAssistanceData

### SMLC -> UE:  provideAssistanceData
* commonIEsProvideAssistanceData
* a_gnss_ProvideAssistanceData
  * gnss_CommonAssistData
    * ReferenceLocation
    * IonosphericModel
    * EarthOrientationPrameters
  * gnss_GenericAssistData (list)
    * gnss_ID
    * TimeModels
    * DifferentialCorrections
    * NavigationModel
    * RealTimeIntegrity
    * DataBitAssistance
    * AcquisitionAssistance
    * Almanac
    * UTC_Model
    * AuxiliaryInformation
* otdoa_ProvideAssistanceData
  * ReferenceCellInfo
  * NeighbourCellInfo
* epdu_Provide_Assistance_Data

### SMLC -> UE:  requestLocationInformation
* commonIEsRequestLocationInformation
  * locationInformationType (choice)
    * locationEstimateRequired
    * locationMeasurementsRequired
    * locationEstimatePreferred
    * locationMeasurementsPreferred
  * triggeredReporting
    * cellChange
    * reportingDuration
  * periodicalReporting
    * reportingAmount (choice, 1,2,4,8,16,32,64)
    * reportingInterval (choice, 0_25, 0_5, 1,2,4,8,16,32,64)
  * additionalInformation (choice)
    * onlyReturnInformationRequested
    * mayReturnAditionalInformation
  * qos
    * horizontalAccuracy
    * verticalCoordinateRequest
    * verticalAccuracy
    * responseTime
    * velocityRequest
  * environment (choice, badArea, notBadArea, mixedArea)
  * locationCoordinateTypes
    * bool ellipsoidPoint
    * bool ellipsoidPointWithUncertaintyCircle
    * bool ellipsoidPointWithUncertaintyEllipse
    * bool polygon
    * bool ellipsoidPointWithAltitude
    * bool ellipsoidPointWithAltitudeAndUncertaintyEllipsoid
    * bool ellipsoidArc
  * velocityTypes
    * Bool horizontalVelocity
    * Bool horizontalWithVerticalVelocity
    * Bool horizontalVelocityWithUncertainty
    * Bool horizontalWithVerticalVelocityAndUncertainty
* a_gnss_RequestLocationInformation
  * Bool fineTimeAssistanceMeasReq
  * Bool adrMeasReq
  * Bool multiFreqMeasReq
  * Bool assistanceAvailability
* otdoa_RequestLocationInformatio
  * Bool assistanceAvailability
  * multipathRSTD
  * maxNoOfRSTDmeas
* ecid_RequestLocationInformation
* epdu_RequestLocationInformation

### SMLC <- UE:  provideLocationInformation
* commonIEsProvideLocationInformation
  * locationEstimate
  * velocityEstimate
  * locationError (choice)
    * undefined
    * requestMethodNotSupport
    * positionMethodFailure
    * periodicLocationMeasurementNotAvailable
* a_gnss_ProvideLocationInformation
  * gnss_SignalMeasurementInformation
  * gnss_LocationInformation
  * gnss_Error (choice)
    * undefined
    * thereWereNotEnoughSatellitesReceived
    * assistanceDataMissing
    * notAllRequestedMeasurementsPossible
* otdoa_ProvideLocationInformation
  * otdoaSignalMeasurementInformation
  * otdoa_Error (choice)
    * undefined
    * assistance_data_missing
    * unableToMeasureReferenceCell
    * unableToMeasureAnyNeighbourCell
    * attemptedButUnableToMeasureSomeNeighbourCells
* ecid_ProvideLocationInformation
  * primaryCellMeasuredResults
    * physCellId
    * cellGlobalId
    * arfcnEUTRA
    * systemFrameNumber
    * rsrp_Result
    * rsrq_Result
    * ue_RxTxTimeDiff
  * measuredResultsList (list)
  * ecid_Error (choice)
    * undefined
    * requestedMeasurementNotAvailable
    * notAllrequestedMeasurementsPossible
* epdu_ProvideLocationInformation
