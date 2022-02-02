# user space initial flow
- init
- infrastructure init (ex: udevd, syslogd)
- network setting
- service init (ex: cron and printer)
- login, GUI and other services


# Systemd Introduction
- systemd is one of user space initial program
- goal
  - to make more user space initial in parallel as more as possible
- Systemd flow
  - sysemd loads setting info
  - systemd determines start target (ex: default.target)
  - systemd check the dependency of target
  - asystemd start response (ex: uevent) and start all component
- other user space initial programs
  - System V (old Linux used it)
  - Upstart (old Ubuntu used it)

# Systemd setting
- /usr/lib/systemd (global setting)
````
$ tree /usr/lib/systemd
.
├── boot
│   └── efi
│       ├── linuxx64.efi.stub
│       └── systemd-bootx64.efi
├── catalog
│   ├── systemd.be.catalog
│   ├── systemd.be@latin.catalog
│   ├── systemd.bg.catalog
│   ├── systemd.catalog
│   ├── systemd.de.catalog
│   ├── systemd.fr.catalog
│   ├── systemd.it.catalog
│   ├── systemd.pl.catalog
│   ├── systemd.pt_BR.catalog
│   ├── systemd.ru.catalog
│   ├── systemd.zh_CN.catalog
│   └── systemd.zh_TW.catalog
├── logind.conf.d
│   └── unattended-upgrades-logind-maxdelay.conf
├── system-environment-generators
│   └── snapd-env-generator
├── tests
│   └── testdata
├── user
│   ├── at-spi-dbus-bus.service
│   ├── basic.target
│   ├── bluetooth.target
│   ├── colord-session.service
│   ├── dbus-org.bluez.obex.service -> obex.service
│   ├── dbus.service
│   ├── dbus.socket
│   ├── default.target
│   ├── dirmngr.service
│   ├── dirmngr.socket
│   ├── evince.service
│   ├── evolution-addressbook-factory.service
│   ├── evolution-calendar-factory.service
│   ├── evolution-source-registry.service
│   ├── evolution-user-prompter.service
│   ├── exit.target
│   ├── glib-pacrunner.service
│   ├── gnome-keyring.service
│   ├── gnome-keyring-ssh.service
│   ├── gnome-session.service
│   ├── gnome-terminal-server.service
│   ├── gpg-agent-browser.socket
│   ├── gpg-agent-extra.socket
│   ├── gpg-agent.service
│   ├── gpg-agent.socket
│   ├── gpg-agent-ssh.socket
│   ├── graphical-session-pre.target
│   ├── graphical-session-pre.target.wants
│   │   ├── gnome-keyring.service -> ../gnome-keyring.service
│   │   ├── gnome-keyring-ssh.service -> ../gnome-keyring-ssh.service
│   │   ├── im-config.service -> ../im-config.service
│   │   ├── session-migration.service -> ../session-migration.service
│   │   └── ssh-agent.service -> ../ssh-agent.service
│   ├── graphical-session.target
│   ├── graphical-session.target.wants
│   │   ├── unicast-local-avahi.path -> ../unicast-local-avahi.path
│   │   ├── update-notifier-crash.path -> ../update-notifier-crash.path
│   │   └── update-notifier-release.path -> ../update-notifier-release.path
│   ├── gvfs-afc-volume-monitor.service
│   ├── gvfs-daemon.service
│   ├── gvfs-goa-volume-monitor.service
│   ├── gvfs-gphoto2-volume-monitor.service
│   ├── gvfs-metadata.service
│   ├── gvfs-mtp-volume-monitor.service
│   ├── gvfs-udisks2-volume-monitor.service
│   ├── im-config.service
│   ├── obex.service
│   ├── paths.target
│   ├── printer.target
│   ├── pulseaudio.service
│   ├── pulseaudio.socket
│   ├── session-migration.service
│   ├── shutdown.target
│   ├── smartcard.target
│   ├── snapd.session-agent.service
│   ├── snapd.session-agent.socket
│   ├── sockets.target
│   ├── sockets.target.wants
│   │   ├── dbus.socket -> ../dbus.socket
│   │   ├── dirmngr.socket -> ../dirmngr.socket
│   │   ├── gpg-agent-browser.socket -> ../gpg-agent-browser.socket
│   │   ├── gpg-agent-extra.socket -> ../gpg-agent-extra.socket
│   │   ├── gpg-agent.socket -> ../gpg-agent.socket
│   │   ├── gpg-agent-ssh.socket -> ../gpg-agent-ssh.socket
│   │   └── snapd.session-agent.socket -> ../snapd.session-agent.socket
│   ├── sound.target
│   ├── ssh-agent.service
│   ├── systemd-exit.service
│   ├── systemd-tmpfiles-clean.service
│   ├── systemd-tmpfiles-clean.timer
│   ├── systemd-tmpfiles-setup.service
│   ├── timers.target
│   ├── ubuntu-report.path
│   ├── ubuntu-report.service
│   ├── unicast-local-avahi.path
│   ├── unicast-local-avahi.service
│   ├── update-notifier-crash.path
│   ├── update-notifier-crash.service
│   ├── update-notifier-livepatch.path
│   ├── update-notifier-livepatch.service
│   ├── update-notifier-release.path
│   ├── update-notifier-release.service
│   ├── xdg-desktop-portal-gtk.service
│   ├── xdg-desktop-portal.service
│   ├── xdg-document-portal.service
│   └── xdg-permission-store.service
├── user-environment-generators
│   ├── 30-systemd-environment-d-generator
│   └── 90gpg-agent
├── user-generators
└── user-preset
    └── 90-systemd.preset

14 directories, 102 files
````
- /etc/systemd/system (local setting)
````
tree /etc/systemd/system/
/etc/systemd/system/
├── bluetooth.target.wants
│   └── bluetooth.service -> /lib/systemd/system/bluetooth.service
├── cloud-final.service.wants
│   └── snapd.seeded.service -> /lib/systemd/system/snapd.seeded.service
├── dbus-fi.w1.wpa_supplicant1.service -> /lib/systemd/system/wpa_supplicant.service
├── dbus-org.bluez.service -> /lib/systemd/system/bluetooth.service
├── dbus-org.freedesktop.Avahi.service -> /lib/systemd/system/avahi-daemon.service
├── dbus-org.freedesktop.ModemManager1.service -> /lib/systemd/system/ModemManager.service
├── dbus-org.freedesktop.nm-dispatcher.service -> /lib/systemd/system/NetworkManager-dispatcher.service
├── dbus-org.freedesktop.resolve1.service -> /lib/systemd/system/systemd-resolved.service
├── dbus-org.freedesktop.thermald.service -> /lib/systemd/system/thermald.service
├── default.target.wants
│   └── ureadahead.service -> /lib/systemd/system/ureadahead.service
├── display-manager.service -> /lib/systemd/system/gdm3.service
├── display-manager.service.wants
│   └── gpu-manager.service -> /lib/systemd/system/gpu-manager.service
├── final.target.wants
│   └── snapd.system-shutdown.service -> /lib/systemd/system/snapd.system-shutdown.service
├── getty.target.wants
│   └── getty@tty1.service -> /lib/systemd/system/getty@.service
├── graphical.target.wants
│   ├── accounts-daemon.service -> /lib/systemd/system/accounts-daemon.service
│   └── udisks2.service -> /lib/systemd/system/udisks2.service
├── multi-user.target.wants
│   ├── anacron.service -> /lib/systemd/system/anacron.service
│   ├── avahi-daemon.service -> /lib/systemd/system/avahi-daemon.service
│   ├── console-setup.service -> /lib/systemd/system/console-setup.service
│   ├── cron.service -> /lib/systemd/system/cron.service
│   ├── cups-browsed.service -> /lib/systemd/system/cups-browsed.service
│   ├── cups.path -> /lib/systemd/system/cups.path
│   ├── dns-clean.service -> /lib/systemd/system/dns-clean.service
│   ├── irqbalance.service -> /lib/systemd/system/irqbalance.service
│   ├── kerneloops.service -> /lib/systemd/system/kerneloops.service
│   ├── ModemManager.service -> /lib/systemd/system/ModemManager.service
│   ├── networkd-dispatcher.service -> /lib/systemd/system/networkd-dispatcher.service
│   ├── networking.service -> /lib/systemd/system/networking.service
│   ├── NetworkManager.service -> /lib/systemd/system/NetworkManager.service
│   ├── ondemand.service -> /lib/systemd/system/ondemand.service
│   ├── open-vm-tools.service -> /lib/systemd/system/open-vm-tools.service
│   ├── pppd-dns.service -> /lib/systemd/system/pppd-dns.service
│   ├── qemu-kvm.service -> /lib/systemd/system/qemu-kvm.service
│   ├── remote-fs.target -> /lib/systemd/system/remote-fs.target
│   ├── rsync.service -> /lib/systemd/system/rsync.service
│   ├── rsyslog.service -> /lib/systemd/system/rsyslog.service
│   ├── run-vmblock\x2dfuse.mount -> /lib/systemd/system/run-vmblock\x2dfuse.mount
│   ├── snap-bare-5.mount -> /etc/systemd/system/snap-bare-5.mount
│   ├── snap-core18-2128.mount -> /etc/systemd/system/snap-core18-2128.mount
│   ├── snap-core18-2284.mount -> /etc/systemd/system/snap-core18-2284.mount
│   ├── snap-core20-1081.mount -> /etc/systemd/system/snap-core20-1081.mount
│   ├── snap-core20-1328.mount -> /etc/systemd/system/snap-core20-1328.mount
│   ├── snapd.apparmor.service -> /lib/systemd/system/snapd.apparmor.service
│   ├── snapd.autoimport.service -> /lib/systemd/system/snapd.autoimport.service
│   ├── snapd.core-fixup.service -> /lib/systemd/system/snapd.core-fixup.service
│   ├── snapd.recovery-chooser-trigger.service -> /lib/systemd/system/snapd.recovery-chooser-trigger.service
│   ├── snapd.seeded.service -> /lib/systemd/system/snapd.seeded.service
│   ├── snapd.service -> /lib/systemd/system/snapd.service
│   ├── snap-gnome\x2d3\x2d28\x2d1804-161.mount -> /etc/systemd/system/snap-gnome\x2d3\x2d28\x2d1804-161.mount
│   ├── snap-gnome\x2d3\x2d34\x2d1804-72.mount -> /etc/systemd/system/snap-gnome\x2d3\x2d34\x2d1804-72.mount
│   ├── snap-gnome\x2d3\x2d34\x2d1804-77.mount -> /etc/systemd/system/snap-gnome\x2d3\x2d34\x2d1804-77.mount
│   ├── snap-gnome\x2d3\x2d38\x2d2004-70.mount -> /etc/systemd/system/snap-gnome\x2d3\x2d38\x2d2004-70.mount
│   ├── snap-gnome\x2d3\x2d38\x2d2004-87.mount -> /etc/systemd/system/snap-gnome\x2d3\x2d38\x2d2004-87.mount
│   ├── snap-gnome\x2dcalculator-884.mount -> /etc/systemd/system/snap-gnome\x2dcalculator-884.mount
│   ├── snap-gnome\x2dcalculator-920.mount -> /etc/systemd/system/snap-gnome\x2dcalculator-920.mount
│   ├── snap-gnome\x2dcharacters-726.mount -> /etc/systemd/system/snap-gnome\x2dcharacters-726.mount
│   ├── snap-gnome\x2dcharacters-741.mount -> /etc/systemd/system/snap-gnome\x2dcharacters-741.mount
│   ├── snap-gnome\x2dlogs-106.mount -> /etc/systemd/system/snap-gnome\x2dlogs-106.mount
│   ├── snap-gnome\x2dsystem\x2dmonitor-163.mount -> /etc/systemd/system/snap-gnome\x2dsystem\x2dmonitor-163.mount
│   ├── snap-gnome\x2dsystem\x2dmonitor-174.mount -> /etc/systemd/system/snap-gnome\x2dsystem\x2dmonitor-174.mount
│   ├── snap-gtk\x2dcommon\x2dthemes-1515.mount -> /etc/systemd/system/snap-gtk\x2dcommon\x2dthemes-1515.mount
│   ├── snap-gtk\x2dcommon\x2dthemes-1519.mount -> /etc/systemd/system/snap-gtk\x2dcommon\x2dthemes-1519.mount
│   ├── snap-notepad\x2dplus\x2dplus-340.mount -> /etc/systemd/system/snap-notepad\x2dplus\x2dplus-340.mount
│   ├── snap-snapd-12883.mount -> /etc/systemd/system/snap-snapd-12883.mount
│   ├── snap-snapd-14549.mount -> /etc/systemd/system/snap-snapd-14549.mount
│   ├── snap-wine\x2dplatform\x2d6\x2dstable-14.mount -> /etc/systemd/system/snap-wine\x2dplatform\x2d6\x2dstable-14.mount
│   ├── snap-wine\x2dplatform\x2druntime-282.mount -> /etc/systemd/system/snap-wine\x2dplatform\x2druntime-282.mount
│   ├── snap-wine\x2dplatform\x2druntime-283.mount -> /etc/systemd/system/snap-wine\x2dplatform\x2druntime-283.mount
│   ├── systemd-resolved.service -> /lib/systemd/system/systemd-resolved.service
│   ├── thermald.service -> /lib/systemd/system/thermald.service
│   ├── ua-reboot-cmds.service -> /lib/systemd/system/ua-reboot-cmds.service
│   ├── ufw.service -> /lib/systemd/system/ufw.service
│   ├── unattended-upgrades.service -> /lib/systemd/system/unattended-upgrades.service
│   ├── whoopsie.service -> /lib/systemd/system/whoopsie.service
│   └── wpa_supplicant.service -> /lib/systemd/system/wpa_supplicant.service
├── network-online.target.wants
│   ├── networking.service -> /lib/systemd/system/networking.service
│   └── NetworkManager-wait-online.service -> /lib/systemd/system/NetworkManager-wait-online.service
├── oem-config.service.wants
│   └── gpu-manager.service -> /lib/systemd/system/gpu-manager.service
├── open-vm-tools.service.requires
│   └── vgauth.service -> /lib/systemd/system/vgauth.service
├── paths.target.wants
│   ├── acpid.path -> /lib/systemd/system/acpid.path
│   └── apport-autoreport.path -> /lib/systemd/system/apport-autoreport.path
├── printer.target.wants
│   └── cups.service -> /lib/systemd/system/cups.service
├── snap-bare-5.mount
├── snap-core18-2128.mount
├── snap-core18-2284.mount
├── snap-core20-1081.mount
├── snap-core20-1328.mount
├── snap-gnome\x2d3\x2d28\x2d1804-161.mount
├── snap-gnome\x2d3\x2d34\x2d1804-72.mount
├── snap-gnome\x2d3\x2d34\x2d1804-77.mount
├── snap-gnome\x2d3\x2d38\x2d2004-70.mount
├── snap-gnome\x2d3\x2d38\x2d2004-87.mount
├── snap-gnome\x2dcalculator-884.mount
├── snap-gnome\x2dcalculator-920.mount
├── snap-gnome\x2dcharacters-726.mount
├── snap-gnome\x2dcharacters-741.mount
├── snap-gnome\x2dlogs-106.mount
├── snap-gnome\x2dsystem\x2dmonitor-163.mount
├── snap-gnome\x2dsystem\x2dmonitor-174.mount
├── snap-gtk\x2dcommon\x2dthemes-1515.mount
├── snap-gtk\x2dcommon\x2dthemes-1519.mount
├── snap-notepad\x2dplus\x2dplus-340.mount
├── snap-snapd-12883.mount
├── snap-snapd-14549.mount
├── snap-wine\x2dplatform\x2d6\x2dstable-14.mount
├── snap-wine\x2dplatform\x2druntime-282.mount
├── snap-wine\x2dplatform\x2druntime-283.mount
├── sockets.target.wants
│   ├── acpid.socket -> /lib/systemd/system/acpid.socket
│   ├── apport-forward.socket -> /lib/systemd/system/apport-forward.socket
│   ├── avahi-daemon.socket -> /lib/systemd/system/avahi-daemon.socket
│   ├── cups.socket -> /lib/systemd/system/cups.socket
│   ├── snapd.socket -> /lib/systemd/system/snapd.socket
│   └── uuidd.socket -> /lib/systemd/system/uuidd.socket
├── spice-vdagentd.target.wants
│   └── spice-vdagentd.service -> /lib/systemd/system/spice-vdagentd.service
├── sysinit.target.wants
│   ├── apparmor.service -> /lib/systemd/system/apparmor.service
│   ├── keyboard-setup.service -> /lib/systemd/system/keyboard-setup.service
│   ├── setvtrgb.service -> /lib/systemd/system/setvtrgb.service
│   └── systemd-timesyncd.service -> /lib/systemd/system/systemd-timesyncd.service
├── syslog.service -> /lib/systemd/system/rsyslog.service
├── timers.target.wants
│   ├── anacron.timer -> /lib/systemd/system/anacron.timer
│   ├── apt-daily.timer -> /lib/systemd/system/apt-daily.timer
│   ├── apt-daily-upgrade.timer -> /lib/systemd/system/apt-daily-upgrade.timer
│   ├── fstrim.timer -> /lib/systemd/system/fstrim.timer
│   ├── motd-news.timer -> /lib/systemd/system/motd-news.timer
│   ├── snapd.snap-repair.timer -> /lib/systemd/system/snapd.snap-repair.timer
│   └── ua-messaging.timer -> /lib/systemd/system/ua-messaging.timer
└── vmtoolsd.service -> /lib/systemd/system/open-vm-tools.service

17 directories, 127 files
````

# Dependency
- Type
  - Requisite
    - need + order
  - Requires
    - need
  - Wants
    - nice to have
  - Conflicts
    - cannot have

# Service Example
````
$ cat /usr/lib/systemd/user/gpg-agent.socket
[Unit]
Description=GnuPG cryptographic agent and passphrase cache
Documentation=man:gpg-agent(1)

[Socket]
ListenStream=%t/gnupg/S.gpg-agent
FileDescriptorName=std
SocketMode=0600
DirectoryMode=0700

[Install]
WantedBy=sockets.target
````

# systemctl
- list all units
````
$ systemctl list-units
UNIT                                                                                                     LOAD   ACTIVE SUB       DESCRIPTION                                                                                                      
proc-sys-fs-binfmt_misc.automount                                                                        loaded active waiting   Arbitrary Executable File Formats File System Automount Point                                                    
sys-devices-pci0000:00-0000:00:10.0-host32-target32:0:0-32:0:0:0-block-sda-sda1.device                   loaded active plugged   VMware_Virtual_S 1                                                                                               
sys-devices-pci0000:00-0000:00:10.0-host32-target32:0:0-32:0:0:0-block-sda.device                        loaded active plugged   VMware_Virtual_S                                                                                                 
sys-devices-pci0000:00-0000:00:10.0-host32-target32:0:1-32:0:1:0-block-sdb.device                        loaded active plugged   VMware_Virtual_S                                                                                                 
sys-devices-pci0000:00-0000:00:11.0-0000:02:00.0-usb2-2\x2d2-2\x2d2.1-2\x2d2.1:1.0-bluetooth-hci0.device loaded active plugged   /sys/devices/pci0000:00/0000:00:11.0/0000:02:00.0/usb2/2-2/2-2.1/2-2.1:1.0/bluetooth/hci0      
...
````

- check status by service
````
$ systemctl status proc-sys-fs-binfmt_misc.automount
● proc-sys-fs-binfmt_misc.automount - Arbitrary Executable File Formats File System Automount Point
   Loaded: loaded (/lib/systemd/system/proc-sys-fs-binfmt_misc.automount; static; vendor preset: enabled)
   Active: active (waiting) since Tue 2022-02-01 04:29:59 PST; 3h 19min ago
    Where: /proc/sys/fs/binfmt_misc
     Docs: https://www.kernel.org/doc/html/latest/admin-guide/binfmt-misc.html
           https://www.freedesktop.org/wiki/Software/systemd/APIFileSystems
````

- check log by service
````
$ journalctl _SYSTEMD_UNIT=proc-sys-fs-binfmt_misc.automount
-- Logs begin at Fri 2022-01-28 03:18:21 PST, end at Tue 2022-02-01 07:47:10 PST. --
-- No entries --
````

- check running jobs
````
$ systemctl list-jobs
No jobs running.
````

# add a new target
- `$ sudo vi /etc/systemd/system/test1.target`
````
[Unit]
Description=test 1
````

- `$ sudo vi /etc/systemd/system/test2.target`
````
[Unit]
Description=test 2
Wants=test1.target
````

- `$ systemctl start test2.target` to start a target
- `$ systemctl status test1.target test2.target` to check status
````
● test1.target - test 1
   Loaded: loaded (/etc/systemd/system/test1.target; static; vendor preset: enabled)
   Active: active since Wed 2022-02-02 04:29:57 PST; 5min ago

Feb 02 04:29:57 ubuntu systemd[1]: Reached target test 1.

● test2.target - test 2
   Loaded: loaded (/etc/systemd/system/test2.target; static; vendor preset: enabled)
   Active: active since Wed 2022-02-02 04:35:43 PST; 7s ago

Feb 02 04:35:43 ubuntu systemd[1]: Reached target test 2.
````

- `$ systemctl stop test2.target` to stop a target
- `$ systemctl disable test2.target` to disable a target
- `$ systemctl status test1.target test2.target`
````
● test1.target - test 1
   Loaded: loaded (/etc/systemd/system/test1.target; static; vendor preset: enabled)
   Active: active since Wed 2022-02-02 04:29:57 PST; 6min ago

Feb 02 04:29:57 ubuntu systemd[1]: Reached target test 1.

● test2.target - test 2
   Loaded: loaded (/etc/systemd/system/test2.target; static; vendor preset: enabled)
   Active: inactive (dead)

Feb 02 04:29:57 ubuntu systemd[1]: Reached target test 2.
Feb 02 04:31:12 ubuntu systemd[1]: Stopped target test 2.
Feb 02 04:35:43 ubuntu systemd[1]: Reached target test 2.
Feb 02 04:36:21 ubuntu systemd[1]: Stopped target test 2.
````

