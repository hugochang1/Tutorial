# SUPL spec
* download link: https://www.openmobilealliance.org/release/SUPL/V2_0_4-20181213-A/OMA-TS-ULP-V2_0_4-20181213-A.pdf

# NI
### NI, Proxy Mode (non-roaming and roaming are the same from UE's view)
* SLP ->  SET: SUPL INIT (session-id, posmethod, SLP mode)
* SLP <-  SET: SUPL POS INIT (session-id, lid, SET capabilities, ver)
* SLP <-> SET: SUPL POS (session-id, RRLP/RRC/TIA-801/LPP/LPPe)
* SLP ->  SET: SUPL END (session-id)

### Emergency Services Location Request
* SLP ->  SET: SUPL INIT (session-id, posmethod, SLP mode, **E-SLP** address)
* SLP <-  SET: SUPL POS INIT (session-id, lid, SET capabilities, ver)
* SLP <-> SET: SUPL POS (session-id, RRLP/RRC/TIA-801/LPP/LPPe)
* SLP ->  SET: SUPL END (session-id)

### NI, User Rejects SUPL_INIT
* SLP ->  SET: SUPL INIT (session-id, posmethod, SLP mode)
* SLP <-  SET: SUPL END (session-id, status code=**consentDeniedByUser**, ver)

### NI, Periodic Triggers
* SLP ->  SET: SUPL INIT (session-id, trigger_type=**periodic**, posmethod, SLP mode)
* SLP <-  SET: SUPL TRIGGERED START(session-id, lid, SET capabilities, **rep_capabilities**, ver)
* SLP ->  SET: SUPL TRIGGERED RESPONSE(session-id, posmethod, **trigger_params**, **rep_mode**)
* (wait until start time)
* SLP <-  SET: SUPL POS INIT(session-id, lid, SET Capabilities)
* SLP <-> SET: SUPL POS (session-id, RRLP/TIA801/LPP/LPPe) 1st position for MSB
* SLP ->  SET: SUPL REPORT(session-id, **position** for MSA) 1st position for MSA
* (wait for next periodic report)
* SLP <-  SET: SUPL REPORT(session-id, **positions**) 2nd psoition for MSB
* (repeat and SET sends SUPL REPORT periodic)
* (reach to number of fixes)
* SLP ->  SET: SUPL END (session-id)

### NI, Event Trigger
* SLP ->  SET: SUPL INIT (session-id, trigger_type=**area_event**, posmethod, SLP mode)
* SLP <-  SET: SUPL TRIGGERED START(session-id, lid, SET capabilities, ver)
* SLP ->  SET: SUPL TRIGGERED RESPONSE(session-id, posmethod, **trigger_params**)
  * **geographicTargetAreaList** provided
* (wait until start time)
* (compare current cell with geographicTargetAreaList, if condition met then start below procedure)
* SLP <-  SET: SUPL POS INIT(session-id, lid, SET Capabilities)
* SLP <-> SET: SUPL POS (session-id, RRLP/RRC/TIA-801/LPP/LPPe)
* SLP ->  SET: SUPL REPORT(session-id)
* (SET checks whether current location has been met the area event condition)
* SLP <-  SET: SUPL REPORT (seesion-id)
* (SET repated to check area event and send SUPL REPORT if condition met)
* (reach to end time)
* SLP ->  SET: SUPL END (session-id)

### NI, Event Trigger, Network/SET capabilities change
* SLP <-> SET: ongoing Area event
* (SET network change)
* SLP <-  SET: SUPL TRIGGERED START (session-id, lid, SET capabilities, **cause**)
* SLP ->  SET: SUPL TRIGGERED RESPONSE (session-id, posmethods, trigger_parameters)
* SLP <-> SET: continued Area event

### NI, notification/verification on current location
* SLP ->  SET: SUPL INIT (session-id, posmethod, SLP mode, ...)
* SLP <-  SET: SUPL POS INIT (session-id, SET capabilities,ver)
* SLP <-> SET: SUPL POS (session-id, RRLP/RRC/TIA-801/LPP/LPPe)
* SLP ->  SET: **SUPL NOTIFY (session-id, notification)**
* SLP <-  SET: **SUPL NOTIFY RESPONSE (session-id, notification-response)**
* SLP ->  SET: SUPL END (session-id)

### NI, notification/verification on current location, SET denies permission
* SLP ->  SET: SUPL INIT (session-id, posmethod, SLP mode, ...)
* SLP <-  SET: SUPL POS INIT (session-id, SET capabilities,ver)
* SLP <-> SET: SUPL POS (session-id, RRLP/RRC/TIA-801/LPP/LPPe)
* SLP ->  SET: SUPL NOTIFY (session-id, notification)
* SLP <-  SET: SUPL NOTIFY RESPONSE (session-id, notification-response=**not_allow**)
* SLP ->  SET: SUPL END (session-id)

### NI, Retrieval of Historical Positions and/or Enhanced Cell Sector Measurements
* SLP ->  SET: SUPL INIT(session-id, posmethod=**historical data retrieval**, SLP mode, **historic reporting**)
* SLP <-  SET: SUPL REPORT(session-id, positions/enhanced cell/sector measurements, ver)

### NI, Session Info Query
* Purpose
  * Query the SET for active SUPL session information.
  * Perform re-notification or re-notification and verification for active Network Initiated sessions
  * Terminate any ongoing Triggered sessions without waiting for the next report interval
* SLP ->  SET: SUPL INIT(session-id, posmethod=**sessioninfoquery**, SLP mode)
* SLP <-  SET: SUPL REPORT(SessionInfoQuery session-id, **sessionlist**, ver)
* (Perform re-notification)
* SLP ->  SET: SUPL NOTIFY (Triggered session-id, notification) 
* SLP <-  SET: SUPL NOTIFY RESPONSE (Triggered session-id, notification-resp, ...)
* (Terminate any ongoing Triggered sessions)
* SLP ->  SET: SUPL TRIGGERED STOP (Triggered session-id)
* SLP <-  SET: SUPL END (Triggered session-id)
* SLP ->  SET: SUPL END (SessionInfoQuery session-id)

# SI
### SI, Proxy mode
* SLP <-  SET: SUPL START(session-id, lid, SET capabilities)
* SLP ->  SET: SUPL RESPONSE(session-id, posmethod)
* SLP <-  SET: SUPL POS INIT(session-id, lid, SET capabilities)
* SLP <-> SET: SUPL POS (session-id, RRLP/RRC/TIA-801/LPP/LPPe)
* SLP ->  SET: SUPL END (session-id)

### SI, Triggered Services
* SLP <-  SET: SUPL TRIGGERED START(session-id, trigger_type=**periodic**, lid, SET capabilities, **trigger_params**)
* SLP ->  SET: SUPL TRIGGERED RESPONSE(session-id, posmethod)
* (wait for start time)
* SLP <-  SET: SUPL POS INIT(session-id, lid, SET capabilities)
* SLP <-> SET: SUPL POS (session-id, RRLP/RRC/TIA-801/LPP/LPPe) 1s position for MSB case
* SLP ->  SET: SUPL REPORT(session-id, **position**) 1s position for MSA case
* (repated until reach the number of fixes)
* SLP <-  SET: SUPL END (session-id)

### SI, Triggered Services
* SLP <-  SET: SUPL TRIGGERED START(session-id, **trigger_type=area event**, lid, SET capabilities, **trigger_params**)
  * SET can indicate **geographicTargetAreaList** to SLP
* SLP ->  SET: SUPL TRIGGERED RESPONSE(session-id, posmethod)
  * SLP can provide cell info in **areaIdLists**
* (wait until start time)
* (SET checks **areaIdLists** first. if condition met, start GNSS for location calculation)
* SLP <-  SET: SUPL POS INIT(session-id, lid, SET capabilities)
* SLP <-> SET: SUPL POS (session-id, RRLP/RRC/TIA-801/LPP/LPPe)
* SLP ->  SET: SUPL REPORT(session-id, **position**) for MSA
* (SET checks for area event and repeated)
* (reach to end time)
* SLP <-  SET: SUPL END (session-id)

# Misc
### verification field (**ver**)
* a hash of the received SUPL INIT message (ver)
  * VER=H(SLP XOR opad, H(SLP XOR ipad, SUPL INIT))
    * where SLP is the FQDN of the SLP address
    * SHA-256 MUST be used as the hash (H) function, with opad and ipad as specified in [HMAC]
    * The output of the SHA-256 HASH function MUST be truncated to 64 bits
### NMR (Network Measurement Reports)
* use for GSM cell
### RepMode (Report Mode for periodic report)
* realtime
* quasirealtime
* batch
### SUPL INIT interface
* TCP/UDP
  * port 7275
* SIP push
  * Application Resource Identifier +g.oma.pusheventapp= “ulp.ua”
  * Content-Type header application/vnd.omaloc-supl-init.
  * SIP MESSAGE body contain PER encoded SUPL INIT message
* MT SMS
  * For GSM/WCDMA/TD-SCDMA
  * port 7275
