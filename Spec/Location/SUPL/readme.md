# NI, proxy mode (non-roaming and roaming are the same from UE's view)
* SLP ->  SET: SUPL INIT (session-id, posmethod, SLP mode)
* SLP <-  SET: SUPL POS INIT (session-id, lid, SET capabilities, ver)
* SLP <-> SET: SUPL POS (session-id, RRLP/TIA801/LPP/LPPe)
* SLP ->  SET: SUPL END (session-id)

# Emergency Services Location Request
* SLP ->  SET: SUPL INIT (session-id, posmethod, SLP mode, **E-SLP** address)
* SLP <-  SET: SUPL POS INIT (session-id, lid, SET capabilities, ver)
* SLP <-> SET: SUPL POS (session-id, RRLP/RRC/TIA-801/LPP/LPPe)
* SLP ->  SET: SUPL END (session-id)

# NI, user rejects SUPL_INIT
* SLP ->  SET: SUPL INIT (session-id, posmethod, SLP mode)
* SLP <-  SET: SUPL END (session-id, status code=**consentDeniedByUser**, ver)

# NI, Periodic Triggers
* SLP ->  SET: SUPL INIT (session-id, trigger_type=**periodic**, posmethod, SLP mode)
* SLP <-  SET: SUPL TRIGGERED START(session-id, lid, SET capabilities, **rep_capabilities**, ver)
* SLP ->  SET: SUPL TRIGGERED RESPONSE(session-id, posmethod, **trigger_params**, **rep_mode**)
* SLP <-  SET: SUPL POS INIT(session-id, lid, SET Capabilities)
* SLP <-> SET: SUPL POS (session-id, RRLP/TIA801/LPP/LPPe)
* SLP ->  SET: SUPL REPORT(session-id, position)
* SLP <-  SET: SUPL REPORT(session-id, positions)
* ... (SET sends SUPL REPORT periodic)
* SLP ->  SET: SUPL END (session-id)

# NI, Event Trigger
* SLP ->  SET: SUPL INIT (session-id, trigger_type=**area_event**, posmethod, SLP mode)
* SLP <-  SET: SUPL TRIGGERED START(session-id, lid, SET capabilities, ver)
* SLP ->  SET: SUPL TRIGGERED RESPONSE(session-id, posmethod, **trigger_params**)
* SLP <-  SET: SUPL POS INIT(session-id, lid, SET Capabilities)
* SLP <-> SET: SUPL POS (session-id, RRLP/TIA801/LPP/LPPe)
*         SET: (SET check for area event)
* SLP ->  SET: SUPL REPORT(session-id)
* ... (SET checks for area event and sends SUPL REPORT if condition met)
* SLP ->  SET: SUPL END (session-id)

# NI, Event Trigger, Network/SET capabilities change
* SLP <-> SET: ongoing Area event
*         SET: network change
* SLP <-  SET: SUPL TRIGGERED START (session-id, lid, SET capabilities, **cause**)
* SLP ->  SET: SUPL TRIGGERED RESPONSE (session-id, posmethods, trigger_parameters)
* SLP <-> SET: continued Area event

# NI, notification/verification on current location
* SLP ->  SET: SUPL INIT (session-id, posmethod, SLP mode, ...)
* SLP <-  SET: SUPL POS INIT (session-id, SET capabilities,ver)
* SLP <-> SET: SUPL POS (session-id, RRLP/RRC/TIA-801/LPP/LPPe)
* SLP ->  SET: **SUPL NOTIFY (session-id, notification)**
* SLP <-  SET: **SUPL NOTIFY RESPONSE (session-id, notification-response)**
* SLP ->  SET: SUPL END (session-id)

# NI, notification/verification on current location, SET denies permission
* SLP ->  SET: SUPL INIT (session-id, posmethod, SLP mode, ...)
* SLP <-  SET: SUPL POS INIT (session-id, SET capabilities,ver)
* SLP <-> SET: SUPL POS (session-id, RRLP/RRC/TIA-801/LPP/LPPe)
* SLP ->  SET: SUPL NOTIFY (session-id, notification)
* SLP <-  SET: SUPL NOTIFY RESPONSE (session-id, notification-response=**not_allow**)
* SLP ->  SET: SUPL END (session-id)

# NI, Retrieval of Historical Positions and/or Enhanced Cell Sector Measurements
* SLP ->  SET: SUPL INIT(session-id, posmethod=**historical data retrieval**, SLP mode, **historic reporting**)
* SLP <-  SET: SUPL REPORT(session-id, positions/enhanced cell/sector measurements, ver)

# NI, Session Info Query
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

# Misc
* a hash of the received SUPL INIT message (ver)
