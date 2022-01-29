# list
- ``sudo blkid``
````
/dev/sda1: UUID="9972783d-88b5-4cb2-9125-e9e80601e5c0" TYPE="ext4" PARTUUID="a82de0be-01"
````

- ``mount``
````
sysfs on /sys type sysfs (rw,nosuid,nodev,noexec,relatime)
proc on /proc type proc (rw,nosuid,nodev,noexec,relatime)
udev on /dev type devtmpfs (rw,nosuid,relatime,size=1973712k,nr_inodes=493428,mode=755)
devpts on /dev/pts type devpts (rw,nosuid,noexec,relatime,gid=5,mode=620,ptmxmode=000)
````

- ``df -h``
````
Filesystem      Size  Used Avail Use% Mounted on
udev            3.7G     0  3.7G   0% /dev
tmpfs           794M  2.1M  792M   1% /run
/dev/sda1        98G   37G   57G  40% /
tmpfs           3.9G     0  3.9G   0% /dev/shm
tmpfs           5.0M  4.0K  5.0M   1% /run/lock
tmpfs           3.9G     0  3.9G   0% /sys/fs/cgroup
/dev/loop0       44M   44M     0 100% /snap/snapd/14549
````

- check all disks by ``ls /dev/[sh]d``
````
/dev/sda  /dev/sda1
````

# status
- ``sudo fdisk -l /dev/sda``
````
Disk /dev/sda: 100 GiB, 107374182400 bytes, 209715200 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0xa53817f2

Device     Boot Start       End   Sectors  Size Id Type
/dev/sda1  *     2048 209713151 209711104  100G 83 Linux
````

# create
- ``ls -al /dev/sdf2``
````
-rw-r--r-- 1 root root 2097152 Jan 19 05:53 sdf2
````

# mount
- ``sudo mkdir /extra``
- ``sudo mount -t ext4 /dev/sdf2 /extra``
- ``sudo blkid``
````
/dev/sda1: UUID="9972783d-88b5-4cb2-9125-e9e80601e5c0" TYPE="ext4" PARTUUID="a82de0be-01"
/dev/loop19: UUID="9b8ca4c4-031e-417d-88f1-9426e0e09b91" TYPE="ext4"
````

# umount
- ``sudo umount /extra`` or ``sudo umount /dev/sdf2``
- ``sudo blkid``
````
/dev/sda1: UUID="9972783d-88b5-4cb2-9125-e9e80601e5c0" TYPE="ext4" PARTUUID="a82de0be-01"
````

# add a new disk flow
- main steps
  - check new disk dev by ``ls /dev/[sh]d*``
  - start partition by ``sudo fdisk /dev/sdb``
  - format partition by ``sudo mkfs -t ext4 /dev/sdb``
  - mount by ``sudo mount /dev/sdb ~/data1``
  - boot mount by modifying ``sudo vi /etc/fstab``
- ``ls /dev/[sh]d*``
  - /dev/sdb is a new one
````
/dev/sda  /dev/sda1  /dev/sdb
````
- ``sudo fdisk /dev/sdb``
````
Welcome to fdisk (util-linux 2.31.1).
Changes will remain in memory only, until you decide to write them.
Be careful before using the write command.

Device does not contain a recognized partition table.
Created a new DOS disklabel with disk identifier 0x6c2e020c.

Command (m for help): m
````
- input ``m`` for help
````
Help:

  DOS (MBR)
   a   toggle a bootable flag
   b   edit nested BSD disklabel
   c   toggle the dos compatibility flag

  Generic
   d   delete a partition
   F   list free unpartitioned space
   l   list known partition types
   n   add a new partition
   p   print the partition table
   t   change a partition type
   v   verify the partition table
   i   print information about a partition

  Misc
   m   print this menu
   u   change display/entry units
   x   extra functionality (experts only)

  Script
   I   load disk layout from sfdisk script file
   O   dump disk layout to sfdisk script file

  Save & Exit
   w   write table to disk and exit
   q   quit without saving changes

  Create a new label
   g   create a new empty GPT partition table
   G   create a new empty SGI (IRIX) partition table
   o   create a new empty DOS partition table
   s   create a new empty Sun partition table
````
- input ``n`` for add a new partition
  - input ``Enter`` for others
````
Partition type
   p   primary (0 primary, 0 extended, 4 free)
   e   extended (container for logical partitions)
Select (default p): p
Partition number (1-4, default 1): 1
First sector (2048-41943039, default 2048): 
Last sector, +sectors or +size{K,M,G,T,P} (2048-41943039, default 41943039): 

Created a new partition 1 of type 'Linux' and of size 20 GiB.
````
- input ``w`` to write table to disk and exit
````
The partition table has been altered.
Calling ioctl() to re-read partition table.
Syncing disks.
````
- format a new partition by ``sudo mkfs -t ext4 /dev/sdb``
````
mke2fs 1.44.1 (24-Mar-2018)
Found a dos partition table in /dev/sdb
Proceed anyway? (y,N) y
Creating filesystem with 5242880 4k blocks and 1310720 inodes
Filesystem UUID: eee9a205-eec6-4f49-9c35-aa894965f35f
Superblock backups stored on blocks: 
	32768, 98304, 163840, 229376, 294912, 819200, 884736, 1605632, 2654208, 
	4096000

Allocating group tables: done                            
Writing inode tables: done                            
Creating journal (32768 blocks): done
Writing superblocks and filesystem accounting information: done
````
- check the GUID for the new parition ``sudo blkid``
````
/dev/sda1: UUID="eac71733-82a8-4832-8fc6-4e7b649a559a" TYPE="ext4" PARTUUID="a53817f2-01"
/dev/sdb: UUID="eee9a205-eec6-4f49-9c35-aa894965f35f" TYPE="ext4"
````
- create a new folder by ``mkdir ~/data1`` and mount it ``sudo mount /dev/sdb ~/data1``
  - after mounting it, please give the permission ``chmod 777 ~/data1`` for access
  - to unmount it, please use ``umount ~/data1`` or ``umount /dev/sdb``
- you can also configure fstab to auto configuration in boot time ``sudo vi /etc/fstab``
  - add ``UUID=eee9a205-eec6-4f49-9c35-aa894965f35f /data1          ext4    defaults 0 0``
  - save and exit /etc/fstab
  - reboot PC
  - you can find ``/data1``
  - please give the permission ``chmod 777 /data1`` for access
