## SPI
- Serial Peripheral Interface is a synchronous serial communication interface specification used for short-distance communication
  - SCLK: Serial Clock (output from master)
  - MOSI: Master Out Slave In (data output from master)
  - MISO: Master In Slave Out (data output from slave)
  - CS /SS: Chip/Slave Select (often active low, output from master to indicate that data is being sent)

## UART
- Universal Asynchronous Receiver-Transmitter is an asynchronous serial communication in which the data format and transmission speeds are configurable
  - TX/RX
    - speed: ex: 921600
    - data: 8bit or 7bit
    - parity: none, odd, even, ...etc.
    - stop bit: 1bit, 1.5bit, 2bit
    - flow control: none, Xon/Xoff, ...etc.

## I2C
- Inter-Integrated Circuit is a synchronous, multi-master and multi-slave serial communication bus in short-distance, intra-board communication
  - SDA (Serial Clock): it is a clock signal that is driven by the master (idle is in high voltage)
  - SCL (Serial Data): it is a bi-directional data signal that can be driven by either the master or the slave (idle is in high voltage)
    - Standard mode (Sm) 100 kbps
    - Fast mode (Fm) 400 kbps
    - Fast mode plus (Fm+) 1 Mbps
    - High-speed mode (Hs) 3.4 Mbps
  - Master
    - could be AP, MD, ...etc.
    - Only master can do START condition and STOP condition
    - clock on SCL is generated by master
    - 7-bit slave address
    - Arbitration for Multiple Master
  - Slave
    - could be touch, sensors, LED, EEPROM, NFC, camera control path, ...etc.
  - I2C operation
    - master writes the data to slave
    - master read the data from slave
  - I3C: Improved Inter Integrated Circuit
    - Two wire serial interface up to 12.5 MHz 
    - Legacy I2C Device co-existence on the same Bus
    - Dynamic Addressing
    - Multi-Master capability (a slave can ask to become a master)
    - In-Band Interrupt (IBI, a slave can notify mater to read the data)
- My job
  - familiar with I2C HW register design
  - maintain I2C driver in bootloader, kernel
    - kernel migration
    - modify I2C driver for new I2C HW design in new chip
  - design and maintain the I2C test code
    - for chip Manufacturing

## USB
### USB History
  - USB 1.0 (1996)
    - Low speed: 1.5 Mbit/s
    - Full speed: 12 Mbit/s
  - USB 2.0 (2000)
    - High speed: 400 Mbit/s
    - 2000: mini-A and mini-B
    - 2006: USB On-The-Go
    - 2007: Micro USB
  - USB 3.0 (2008)
    - Super speed: 5 Gbit/s
    - reduce power consumption
    - increase power output for charging
    - compatible with USB 2.0
  - USB 3.1 (2013)
    - Super speed plus: 10 Gbit/s
    - compatible with USB 2.0 and USB 3.0
### Electrical
  - USB 2.0
    - VBUS
    - D+
    - D-
    - GND
  - USB 3.0
    - StdA_SSRX−
    - StdA_SSRX+
    - GND_DRAIN
    - StdA_SSTX−
    - StdA_SSTX+
### Data Flow Types
  - Control Transfers
    - to configure a device at attach time
    - can be used for other device-specific purposes
  - Bulk Data Transfers
    - Non-periodic, large-packet burst communication
    - ex: file transfer, data packet transfer
  - Interrupt Data Transfers
    - low-frequency, bounded-latency communication
    - ex: mouse, keyboard
  - Isochronous Data Transfers
    - peiodic, continuous communication
    - real time video/voice
### USB functions
  - RNDIS
    - INTERFACE DESCRIPTOR
      - bInterfaceClass: Wireless Controller (0xe0)
      - bInterfaceSubClass: 0x01
      - bInterfaceProtocol: 0x03
  - ECM
    - INTERFACE DESCRIPTOR
      - bInterfaceClass: Communications and CDC Control (0x02)
      - bInterfaceSubClass: Ethernet Networking Control Model (0x06)
      - bInterfaceProtocol: No class specific protocol required (0x00)
  - NCM
    - INTERFACE DESCRIPTOR
      - bInterfaceClass: Communications and CDC Control (0x02)
      - bInterfaceSubClass: Network Control Model (0x0D)
      - bInterfaceProtocol: No encapsulated commands / responses (0x00)