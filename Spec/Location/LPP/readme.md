# 3GPP TS 37.355
* download: https://www.etsi.org/deliver/etsi_ts/137300_137399/137355/16.02.00_60/ts_137355v160200p.pdf
  * page 82
* Qualcomm OTDOA: https://www.qualcomm.com/content/dam/qcomm-martech/dm-assets/documents/otdoa_positioning_in_3gpp_lte_v1.pdf
  * page 49, 8.2

# LPP
* SMLC -> UE:  requestCapabilities
* SLMC <- UE:  provideCapabilities
* SLMC <- UE:  requestAssistanceData
* SMLC -> UE:  provideAssistanceData
* SMLC -> UE:  requestLocationInformation
* SMLC <- UE:  provideLocationInformation
* SMLC <-> UE: Error
* SMLC <-> UE: Abort

# Control Plane
* ![image](https://user-images.githubusercontent.com/6143237/221423237-0d37b969-00a9-44b1-a85f-4c4bdf979515.png)

# User Plane
* ![image](https://user-images.githubusercontent.com/6143237/221423430-b28afc53-43a2-4997-bc1b-80138b3f9027.png)

# Functionality
* a_gnss
* otdoa
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
    * OTDOA equations
      * RSTD(i,1) = sqrt((xt-xi)^2 + (yt-yi)^2)/c - sqrt((xt-x1)^2 + (yt-y1)^2)/c + (Ti -T1) + (ni - n1)
        * RSTD(i,1) is the time difference between an eNB i and the reference cell 1 measured at the UE
        * (Ti - T1) is the transmit time offset between the two eNB
        * ni n1 are the UE TOA measurement errors
        * c is the speed of light 3x10^8 m/s
* ecid
* epdu

# Capability Transfer procedure
### Server request UE capability
* Server -> UE: RequestCapability
* Server <- UE: ProvideCapability
### UE provides unsolicited capability 
* Server <- UE: ProvideCapability

# Assistance Data Transfer
### Assistance Data Transfer procedure
* Server <- UE: RequestAssistanceData
* Server -> UE: ProvideAssistanceData
* Server -> UE: ProvideAssistanceData  if needed
* ...  if needed

### Periodic Assistance Data Transfer procedure
* Server <- UE: RequestAssistanceData (TransactionID=T1, PeriodicSession=S, Control Parameter)
* Server -> UE: ProvideAssistanceData (TransactionID=T1, PeriodicSession=S, Control Parameter) **no assisData**
* Server -> UE: ProvideAssistanceData (TransactionID=T2, PeriodicSession=S, Periodic AssistanceData)
* Server -> UE: ProvideAssistanceData (TransactionID=T2, PeriodicSession=S, Periodic AssistanceData)
* Server -> UE: Abort (TransactionID=T2) if Server wants
* Server <- UE: Abort (TransactionID=T2) if UE wants
* ...
* Server -> UE: ProvideAssistanceData (TransactionID=T2, endTransaction, PeriodicSession=S, Periodic AssistanceData) normal end case

### Periodic Assistance Data Transfer with Update procedure
* If the target device changes its primary cell
* Server <-> UE: Periodic Session ongoing
* Server <- UE: RequestAssistanceData (TransactionID=T1, PeriodicSession=S, Control Parameter)
* Server -> UE: ProvideAssistanceData (TransactionID=T1, PeriodicSession=S, Control Parameter) **no assisData**
* Server <-> UE: Periodic Session ongoing

# Location Information Transfer 
### Location Information Transfer procedure
* Server -> UE: RequestLocationInformation
* Server <- UE: ProvideLocationInformation
* Server <- UE: ProvideLocationInformation if needed
* ... if needed

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
  * otdoa_Mode (MSA, MSA-NB, MSB for LPPe)
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
  * NeighbourCellInfo (up to 72 cells)
* epdu_Provide_Assistance_Data

### SMLC -> UE:  requestLocationInformation
* commonIEsRequestLocationInformation
  * locationInformationType (choice, MSA, MSB, MSA_Pref, MSB_Pref)
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
    * reference cell
      * time stamp
      * Identity of the reference cell (PCI, ARFCN, ECGI)
      * quality of TOA measurement from the reference cell
    * neighbor cells (up to 24)
      * Identity of the neighbor cells (PCI, ARFCN, ECGI)
      * RSTD measuremnts
      * quality of RSTD measurements
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
