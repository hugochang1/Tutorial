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
- enusre the path of Wireshark has been added to PATH
  - path
- help
  - dumpcap -h
- list all interface
  - dumpcap -D
- start capture in specific interface
  - dumpcap -i 5 -w C:\Users\88692\Desktop\simple.pcapng -b filesize:1000 -b files:3
    - -i 5: which interface you want to capture
    - -w C:\Users\88692\Desktop\simple.pcapng: which place and file name you want to save to
    - -b filesize: use the ring buffer in kilobyte for each file size
    - -b files: use the ring buffer with maximum file number

