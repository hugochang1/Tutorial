### check 32-bit or 64-bit architecture
- `uname -m`
  - output example `aarch64`

### check kernel config
- Ubuntu
  - `cat /boot/config-$(uname -r)`
  - `cat /boot/config-$(uname -r) | grep XFRM`
- OpenWrt
  - `zcat /proc/config.gz | grep <your interesting keyword>`
  - `zcat /proc/config.gz | grep XFRM`
```
CONFIG_XFRM=y
CONFIG_XFRM_ALGO=y
CONFIG_XFRM_USER=y
```

### check Kernel module
- `cd /lib/modules/$(uname -r)`
- `cd /lib64/modules/$(uname -r)`
- `lsmod`
- `lsmod | grep <your interesting module name>`
  - `lsmod | grep gre`

