- $ dmesg
  - to show kernel log
- $ cat /proc/cmdline
````
BOOT_IMAGE=/boot/vmlinuz-4.4.0-148-generic root=/dev/mapper/rootvg-rootlv ro quiet splash
````

![149607261-8ad1b958-e048-4d3f-bc50-c613d5f46b07](https://user-images.githubusercontent.com/6143237/151820206-3b7d4468-3881-471b-8837-f17427628f46.png)

https://cloudchef.medium.com/linux-boot-process-part-2-bd7514913495

![image](https://user-images.githubusercontent.com/6143237/150150057-d12f8c86-add1-4239-ab7d-b96aa69154a8.png)

# How GRUB working
- BIOS or UEFI initialize the HW and use MBR or GPT to search boot loader (ex: GRUB)
- BIOS or UEFI finds GRUB and start it
- load the GRUB
- initialize GRUB, it can read the disk and file system
- GRUB identify boot area and read the config setting
- GRUB provide user to change boot option if user interrupt it
- according to the final config setting, GRUB load kernel and pass the control to it
