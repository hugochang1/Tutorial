# use char driver as example

### prepare your module files
- `$ mkdir drivers/char/hugo`
- copy the source code and Makefile into the hugo folder
- `$ vi drivers/char/hugo/Makefile`
- before `obj-m := hugo.o`
- after `obj-$(CONFIG_HUGO) := hugo.o`

### add Kconfig
- `$ vi drivers/char/Kconfig`
````
config HUGO
        tristate "hugo driver"
        ---help---
          this is hugo driver.
````

- `$ vi drivers/char/Makefile` to include the hugo folder
- add
````
obj-$(CONFIG_HUGO)              += hugo/
````

### enable my Kconfig
- `$ make menuconfig`
  - Device Drivers -> Character devices -> hugo driver (NEW) -> enable as built-in
  - exit and save

- `$ vi .config` to check whether CONFIG_HUGO is enabled
````
...
CONFIG_HUGO=y
...
````

### re-build kernel and apply it
- `$ make -j12` to rebuild the kernel
````
...
  CC      drivers/char/hugo/hugo1.o
  CC      drivers/char/hugo/hugo2.o
...
````

- `$ sudo make install` to apply the kernel to the system
- `$ reboot`
- after reboot
- `$ dmesg | grep hugo` to check kernel log whether hugo module is run successfully
````
[    4.430053] hugo_init
````
