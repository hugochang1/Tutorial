# RRLP
* download link: https://www.etsi.org/deliver/etsi_ts/144000_144099/144031/14.03.00_60/ts_144031v140300p.pdf

# Terms
* SMLP: Serving Mobile Location Centre
* MS: Mobile Station
* LCS: Location Services
* RRLP: Radio Resource LCS Protocol

# Functionality of Protocol
* Measure Position Request
* Measure Position Response
* Assistance Data
* Assistance Data Acknowledgement
* Protocol Error
* Positioning Capability Request
* Positioning Capability Response
* Multilateration Timing Advance Request

### Position Measurement Procedure
* Capability Transfer Procedure
  * SMLC ->  MS: RRLP(Positioning Capability Request)
  * SMLC <-  MS: RRLP(Protocol Error) if something wrong happen
  * SMLC <-  MS: RRLP(Positioning Capability Response)
* Assistance Data Transfer
  * SMLC ->  MS: RRLP(Assistance Data)
  * SMLC <-  MS: RRLP(Protocol Error) if something wrong happen
  * SMLC <-  MS: RRLP(Assistnace Data Ack)
* Measure Position
  * SMLC ->  MS: RRLP (Measure Position Request)
    * QoP
    * assistance data for MSA
  * SMLC <-  MS: RRLP (Protocol Error) if something wrong happen
    * SMLC may resend Measure Position Request or start a new positioning measurement procedure
  * SMLC <-  MS: RRLP (Measure Position Response)

### Error Handling
* SMLC <-  MS: RRLP(Protocol Error - Message Too Short)
  * when MS receives a RRLP msg, that is too short to contain all mandatory IEs.
* SMLC ->  MS: RRLP(Protocol Error - Unknown Reference Number)
  * A SMLC detects that it has received a RRLP message with an unknown Reference Number
* SMLC <-  MS: RRLP(Protocol Error - Missing Information Element or Component Element)
  * When MS receives a RRLP message, that does not contain IEs or component elements expected to be present
* SMLC <-  MS: RRLP(Protocol Error - Incorrect Data)
  * When MS receives a RRLP message, that is contains IEs or elements of components that are syntactically incorrect
* Repeated Component
  * if the old and new Measure Position Request components have the **same Reference** Number
    * the MS ignores the later component
  * if the old and new Measure Position Request components have **different Reference** Numbers
    * the MS aborts activity for the former component
* Missing Component (Time out)
  * When the SMLC sends a Measure Position Request component to the MS, it starts a timer.
* Unforeseen Component
  * When the MS receives a complete Assistance Data pseudo-segmentation sequence or an Assistance Data component that was sent without pseudo-segmentation

# Message Structure
### Abbreviation
* msr = measure
* req = request
* rsp = response
* nbr = number
* ack = acknowledgement
```
PDU ::= SEQUENCE {
	referenceNumber			INTEGER (0..7),
	component				RRLP-Component 
}

RRLP-Component ::= CHOICE {
	msrPositionReq  MsrPosition-Req,
	msrPositionRsp  MsrPosition-Rsp,
	assistanceData  AssistanceData,
	assistanceDataAck  NULL,
	protocolError  ProtocolError,
	...,
	posCapabilityReq  PosCapability-Req,
	posCapabilityRsp  PosCapability-Rsp,
	multilaterationOTDReq  MultilaterationOTD-Req,
	multilaterationOTDRsp  MultilaterationOTD-Rsp,
	posMTAReq  PosMTA-Req
}
```

# Components
### Measure Position Request
* PositionInstruct
  * methodType (MSA, MSB, MSAPref, MSBPref)
  * positionMethod (eotd, gps, gpsOrEOTD)
  * measureResponseTime (0..7) // 1,2,4,8,16,32,64,128
  * useMultipleSets (multipleSets, oneSet)
  * environmentCharacter (badArea, notBadArea, mixedArea)
* ReferenceAssistData
  * bcchCarrier (0..1024) // RF channel number of BCCH (Broadcast Control Channel)
  * bsic (0..63) //Base station identity code
  * timeSlotScheme (equalLength, variousLength)
  * btsPosition
* MsrAssistData
  * msrAssistList (list 1..15)
    * bcchCarrier
    * bsic
    * multiFrameOffset (0..51)
    * timeSlotScheme
    * roughRTD (0..1250)
* SystemInfoAssistData
  * systemInfoAssistList (list 1..32) // E-OTD Measurement assistance data
* GPS-AssistData
  * referenceTime (gpsTime)
  * refLocation (threeDLocation)
  * ionosphericModel
  * dgpsCorrections (gpsTOW, status, satList)
  * navigationModel //list, by satellite
    * satelliteID
    * satStatus (ephemeris data)
  * utcModel
  * almanac //by satellite
  * acquisAssist //by satellite
  * realTimeIntegrity // number of bad satellites
* rel98-MsrPosition-Req-extension
  * gpsTimeAssistanceMeasurementRequest
  * GPSReferenceTimeUncertainty
* rel5-MsrPosition-Req-extension (empty)
* rel7-MsrPosition-Req-extension
  * velocityRequested (NULL)
  * ganssPositionMethod (ganssID, mas, msb, standalone, signals)
  * ganss-AssistData (commonAssistData, GenericAssistDataList)
  * ganssCarrierPhaseMeasurementRequest (NULL)
  * ganssTODGSMTimeAssociationMeasurementRequest (NULL)
  * requiredResponseTime (1..128)
  * add-GPS-AssistData (gpsEphemerisExt, gpsEphemerisExtCheck, ...)
  * ganssMultiFreqMeasurementRequest (NULL)

### Measure Position Response
* MultipleSets (choice)
  * MultipleSets
  * oneSet
* ReferenceIdentity (list, 1..3)
* OTD-MeasureInfo (1..3)
* LocationInfo
  * refFrame (0..65535)
  * gpsTOW (0..14399999)
  * fixType (2DFix, 3DFix)
  * posEstimate
* GPS-MeasureInfo // by satellites (1..16)
* LocationError
  * unDefined
  * notEnoughBTSs
  * notEnoughSats
  * eotdLocCalAssDataMissing 
  * eotdAssDataMissing 
  * gpsLocCalAssDataMissing 
  * gpsAssDataMissing 
  * methodNotSupported 
  * notProcessed 
  * refBTSForGPSNotServingBTS 
  * refBTSForEOTDNotServingBTS
* rel-98-MsrPosition-Rsp-Extension
* rel-5-MsrPosition-Rsp-Extension
* rel-7-MsrPosition-Rsp-Extension 
  * VelocityEstimate
  * GANSSLocationInfo
  * GANSSMeasureInfo

### Assistance Data
* ReferenceAssistData
  * bcchCarrier (0..1024) // RF channel number of BCCH (Broadcast Control Channel)
  * bsic (0..63) //Base station identity code
  * timeSlotScheme (equalLength, variousLength)
  * btsPosition
* MsrAssistData (list 1..15)
* SystemInfoAssistData (list 1..32)
* GPS-AssistData
  * referenceTime (gpsTime)
  * refLocation (threeDLocation)
  * dgpsCorrections (gpsTOW, status, satList)
  * navigationModel //list, by satellite
    * satelliteID
    * satStatus (ephemeris data)
  * ionosphericModel
  * utcModel
  * almanac //by satellite
  * acquisAssist //by satellite
  * realTimeIntegrity // number of bad satellites
* MoreAssDataToBeSent (noMoreMessages, moreMessagesOnTheWay)
* rel98-AssistanceData-Extension
  * gpsTimeAssistanceMeasurementRequest (null)
  * gpsReferenceTimeUncertainty (0..127)
* rel5-AssistanceData-Extension
* rel7-AssistanceData-Extension
  * ganss-AssistData
  * ganssCarrierPhaseMeasurementRequest
  * ganssTODGSMTimeAssociationMeasurementRequest
  * add-GPS-AssistData

### Protocol Error
* ErrorCodes (choice)
  * unDefined
  * missingComponet
  * incorrectData
  * missingIEorComponentElement
  * messageTooShort
  * unknowReferenceNumber
* rel-5-ProtocolError-Extension

### Positioning Capability Request
* Extended-reference
  * smlc-code (0..63)
  * transaction-ID (0..262143)
* GANSSPositionMethods (MSA-EOTD, MSB-EOTD, MSA-GPS, MSB-GPS, StandaloneGPS)

### Positioning Capability Response
* Extended-reference
  * smlc-code (0..63)
  * transaction-ID (0..262143)
* PosCapabilities
  * NonGANSSPositionMethods (MSA-EOTD, MSB-EOTD, MSA-GPS, MSB-GPS, Standalone)
  * GANSSPositionMethods (ganssID, MSA/MSB/Standalone, signals)
  * MultipleMeasurementSets (eotd, gps, ganss)
* AssistanceSupported
  * GPSAssistance
  * GANSSAssistanceSet
  * GANSSAdditionalAssistanceChoices (list 1..16)
* AssistanceNeeded
  * GPSAssistanceData
  * GANSSAssistanceData

### Positioning Multilateration Timing Advance Request
* target-Number-of-Cells (0..7)
* requested-MS-Synchronization-Accuracy (0..15)
* mta-Method
* random-ID-Set
* mpm-Timer (0..7)
* serving-cell
* co-sited-cells
* cell-Set1~8

### Multilateration OTD Response
* servingCellDLAccuracy (1..16)
* OTDMeasurementResults (list 1..7)
  * reportedCell
  * msSyncAccuracy (0..15)
  * observedTimeDiff (0..999)
* RXLEVMeasurementResults (list 1..6)
  * reportedCell
  * rxLEV (0..63)
