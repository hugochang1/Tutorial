# Device Tree
- Device Tree Source file (.dts or .dtsi)
- Device Tree Compiler (dtc) 
  - .dts → dtb (efficient representation)
  - only .dts files are accepted as input to dtc
- Device Tree Blob (.dtb)
  - can be linked directly inside a bootload binary (U-Boot)
  - can be passed to the operating system by the bootloader (Linux)
  - U-Boot: `bootz <kernel-addr> - <dtb-addr>`

# Where are Device Tree Sources located?
- `arch/<ARCH>/boot/dts`

# Exploring the DT on the target
- `$ adb shell dtc -I fs /sys/firmware/devicetree/base/ > dts.txt`

# Reference
- Youtube
  - https://www.youtube.com/watch?v=Nz6aBffv-Ek
