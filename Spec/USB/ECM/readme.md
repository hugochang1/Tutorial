# ECM (Ethernet Control Model)
- Class Code
  - 02h: Communications Device Class
- Subclass Code
  - 06h: Ethernet Networking Control Model
- Protocol Code 
  - 00h: No class specific protocol required 

# Data Class interface
- shall have a minimum of two interface settings
  - The first setting (the default interface setting) includes no endpoints
  - the second setting includes a pair of endpoints (one IN, and one OUT) to exchange network traffic
- to recover the device to known states
  - the host will first select the default interface setting (with no endpoints) and then select the appropriate alternate interface setting

# Ethernet Networking Functional Descriptor
![ecm_functional_descriptor.png not found.](./img/ecm_functional_descriptor.png)

# Ethernet Statistics Capabilities
![ecm_stat_cap.png not found.](./img/ecm_stat_cap.png)

# Messages
![ecm_request_code.png not found.](./img/ecm_request_code.png)

# SetEthernetMulticastFilters
![ecm_SetEthernetMulticastFilters.png not found.](./img/ecm_SetEthernetMulticastFilters.png)

# SetEthernetPowerManagementPatternFilter
![ecm_SetEthernetPowerManagementPatternFilter.png not found.](./img/ecm_SetEthernetPowerManagementPatternFilter.png)

# PowerManagementPatternFilterStructure
![ecm_PowerManagementPatternFilterStructure.png not found.](./img/ecm_PowerManagementPatternFilterStructure.png)

# GetEthernetPowerManagementPatternFilter
![ecm_GetEthernetPowerManagementPatternFilter.png not found.](./img/ecm_GetEthernetPowerManagementPatternFilter.png)

# SetEthernetPacketFilter
![ecm_SetEthernetPacketFilter.png not found.](./img/ecm_SetEthernetPacketFilter.png)

# GetEthernetStatistic
![ecm_GetEthernetStatistic.png not found.](./img/ecm_GetEthernetStatistic.png)

# EthernetStatisticsFeatureSelectorCodes
![ecm_EthernetStatisticsFeatureSelectorCodes.png not found.](./img/ecm_EthernetStatisticsFeatureSelectorCodes.png)

# Notifications
![ecm_Notifications.png not found.](./img/ecm_Notifications.png)

# NotificationCodes
![ecm_NotificationCodes.png not found.](./img/ecm_NotificationCodes.png)

