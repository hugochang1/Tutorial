# Wireshark

## Customize GUI
#### Show Delta Time
###### Edit -> Preferences -> Appearance -> Columns -> Add -> Delta Time Displayed
#### Coloring Rule
###### View -> Coloring Rule -> Add -> Filter: tcp.flags.syn==1
#### Apply as Column
###### In packet field -> Mouse right clock -> Apply as Column
#### Show Field Values
###### Edit -> Preferences 
![wireshark_preferences2.png not found.](./img/wireshark_preferences2.png)
![wireshark_show_field_values.png not found.](./img/wireshark_show_field_values.png)

## Ring buffer for Output File
#### GUI
###### Capture -> Options -> Output tab
- select file path by clicking Browse button
- check "Create a new file automatically"
- check "after XXX kilobytes"
- check "Use a ring buffer with XXX files"
#### Command Line
###### TBD
