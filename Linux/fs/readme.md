# list
- $ sudo blkid
````
/dev/sda1: UUID="9972783d-88b5-4cb2-9125-e9e80601e5c0" TYPE="ext4" PARTUUID="a82de0be-01"
````

- $ mount
````
sysfs on /sys type sysfs (rw,nosuid,nodev,noexec,relatime)
proc on /proc type proc (rw,nosuid,nodev,noexec,relatime)
udev on /dev type devtmpfs (rw,nosuid,relatime,size=1973712k,nr_inodes=493428,mode=755)
devpts on /dev/pts type devpts (rw,nosuid,noexec,relatime,gid=5,mode=620,ptmxmode=000)
...
````

# create
- $ sudo mkfs -t ext4 /dev/sdf2 2048
````
mke2fs 1.44.1 (24-Mar-2018)
Creating regular file /dev/sdf2
Creating filesystem with 2048 1k blocks and 256 inodes

Allocating group tables: done                            
Writing inode tables: done                            
Creating journal (1024 blocks): done
Writing superblocks and filesystem accounting information: done
````

- $ ls -al /dev/sdf2
````
-rw-r--r-- 1 root root 2097152 Jan 19 05:53 sdf2
````

# mount
- $ sudo mkdir /extra
- $ sudo mount -t ext4 /dev/sdf2 /extra
- $ sudo blkid
````
/dev/sda1: UUID="9972783d-88b5-4cb2-9125-e9e80601e5c0" TYPE="ext4" PARTUUID="a82de0be-01"
/dev/loop19: UUID="9b8ca4c4-031e-417d-88f1-9426e0e09b91" TYPE="ext4"
````

# umount
- $ sudo umount /extra
- $ sudo blkid
````
/dev/sda1: UUID="9972783d-88b5-4cb2-9125-e9e80601e5c0" TYPE="ext4" PARTUUID="a82de0be-01"
````
