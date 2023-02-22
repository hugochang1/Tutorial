# RRLP
* download link: https://www.3gpp.org/ftp/Specs/archive/04_series/04.31/
# Terms
* SMLP: Serving Mobile Location Centre
* MS: Mobile Station
* LCS: Location Services
* RRLP: Radio Resource LCS Protocol

### Position Measurement Procedure
* SMLC <-> MS: Assistance Data Delivery Procedure
* SMLC ->  MS: RRLP (Measure Position Request)
  * QoP
  * assistance data for MSA
* SMLC <-  MS: RRLP (Protocol Error) if something wrong happen
  * SMLC may resend Measure Position Request or start a new positioning measurement procedure
* SMLC <-  MS: RRLP (Measure Position Response)

### Assistance Data Delivery Procedure
* SMLC ->  MS: RRLP(Assistance Data)
* SMLC <-  MS: RRLP(Protocol Error) if something wrong happen
* SMLC <-  MS: RRLP(Assistnace Data Ack)

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
