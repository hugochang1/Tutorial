----------------------------------------------------
        iso
----------------------------------------------------
https://free.nchc.org.tw/ubuntu-cd/16.04/

----------------------------------------------------
        sudo with echo >
----------------------------------------------------
# echo <your_msg> | sudo tee -a <your_file> > /dev/null
# echo 'deb blah ... blah' | sudo tee -a /etc/apt/sources.list > /dev/null

----------------------------------------------------
        find
https://blog.gtwang.org/linux/unix-linux-find-command-examples/
----------------------------------------------------
# case sensitive
find ./ -name file_name
find ./ -name file*

# case insensitive
find ./ -iname file_name

find ./ -type f -name file_name
find ./ -type d -name folder_name
find ./ -type d -name "folder_*"

----------------------------------------------------
        grep
----------------------------------------------------
grep keyword ./ -r
grep keyword ./ -r --include=file_name
grep keyword ./ -r --include=*.cpp
grep -E -i -w 'keyword1|keyword2'

----------------------------------------------------
        objdump
to check which libraries your module needed
----------------------------------------------------
objdump -x your_module | grep NEEDED


----------------------------------------------------
        tree dump
to show folder structure
-C color
-L 2: specific to show 2 layers
----------------------------------------------------
$tree -C -L 2 .
.
+-- 1_make_run.sh
+-- certs
¦   +-- test.pem
¦   +-- UbuntuOne-Go_Daddy_CA.pem
+-- demo_epoll.c
+-- demo_pthread.c
+-- demo_semaphore.c
+-- fifo
+-- main.c
+-- Makefile
+-- readme.txt
+-- test_data2.txt
+-- test_data.txt
+-- utils
    +-- utils.c
    +-- utils.h

----------------------------------------------------
        netstat
to show network status
-a   display all sockets (default: connected)
-t   TCP sockets
-p   display PID/Program name for sockets
----------------------------------------------------
$ netstat -atp
Active Internet connections (servers and established)
Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name
tcp        0      0 0.0.0.0:domain          0.0.0.0:*               LISTEN      1813/dnsmasq
tcp        0      0 0.0.0.0:ssh             0.0.0.0:*               LISTEN      2326/dropbear
tcp        0      0 0.0.0.0:https           0.0.0.0:*               LISTEN      2010/uhttpd
tcp        0      0 localhost:14140         0.0.0.0:*               LISTEN      2716/my_daemon

----------------------------------------------------
        ps
----------------------------------------------------
$ps axu
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root         1  0.0  0.0  30472  5064 ?        Ss   07:12   0:01 /sbin/init
root         2  0.0  0.0      0     0 ?        S    07:12   0:00 [kthreadd]
user1     4734  0.0  0.0  11336  2196 pts/51   R+   08:57   0:00 ps axu

STAT:
R: running state
S: sleeping state
D: sleeping state for storage I/O
Z: zombie state, wait for Kernel to recycle this process

----------------------------------------------------
        ps -eo pid,comm,etime,time
----------------------------------------------------
$ps -eo pid,comm,etime,time
  PID COMMAND             ELAPSED     TIME
    1 init               03:10:00 00:00:01
    2 kthreadd           03:10:00 00:00:00
    3 ksoftirqd/0        03:10:00 00:00:07

----------------------------------------------------
        time
----------------------------------------------------
$time /bin/sleep 3

real    0m3.005s
user    0m0.004s
sys     0m0.001s

----------------------------------------------------
        free & swapon
----------------------------------------------------
$time /bin/sleep 3
free
              total        used        free      shared  buff/cache   available
Mem:        1698604      104472     1552220       22540       41912     1505296
Swap:             0           0           0

the unit is KB
total: 1.69 GB
used: 104 MB
free: 1.55 GB

$/sbin/swapon -s
Filename                                Type            Size    Used    Priority
/dev/mapper/rootvg-swaplv               partition       7811068 100300  -1


----------------------------------------------------
        diff
----------------------------------------------------
$diff file1 file2 -u
--- aaa.txt     2022-01-19 08:59:40.596677000 +0800
+++ aaa2.txt    2022-01-19 08:59:53.942717000 +0800
@@ -1 +1 @@
-hello
\ No newline at end of file
+Hello world
\ No newline at end of file

----------------------------------------------------
        ln
----------------------------------------------------
create a symbolic link (like shortcut)
$ln -s target linkname
$ls -al
lrwxrwxrwx  1 user1 group1      7 Jan 19 09:35 linkname -> target

----------------------------------------------------
        dd
----------------------------------------------------
copy the data from "if" to "of" with specific data size
$dd if=/dev/zero of=new_file bs=1024 count=1
1+0 records in
1+0 records out
1024 bytes (1.0 kB) copied, 0.000553609 s, 1.8 MB/s

bs=block size
count=number of bs to be copied

$ls -al new_file
-rw-r--r-- 1 mtk04140 srv_wear 1024 Jan 19 11:12 new_file



----------------------------------------------------
        udevadm
----------------------------------------------------
get the detail info of specific device node
$udevadm info --query=all --name=/dev/sdb
P: /devices/pci0000:00/0000:00:11.0/0000:02:01.0/host3/target3:0:0/3:0:0:0/block/sdb
N: sdb
S: disk/by-path/pci-0000:02:01.0-scsi-0:0:0:0
E: DEVLINKS=/dev/disk/by-path/pci-0000:02:01.0-scsi-0:0:0:0
E: DEVNAME=/dev/sdb
E: DEVPATH=/devices/pci0000:00/0000:00:11.0/0000:02:01.0/host3/target3:0:0/3:0:0:0/block/sdb
E: DEVTYPE=disk
E: ID_BUS=scsi
E: ID_FS_TYPE=LVM2_member
E: ID_FS_USAGE=raid
E: ID_FS_UUID=IdZPt8-2Pcl-h0XM-srbm-fzN8-q7qU-oZA2c7
E: ID_FS_UUID_ENC=IdZPt8-2Pcl-h0XM-srbm-fzN8-q7qU-oZA2c7
E: ID_FS_VERSION=LVM2 001
E: ID_MODEL=Virtual_disk
E: ID_MODEL_ENC=Virtual\x20disk\x20\x20\x20\x20
E: ID_PATH=pci-0000:02:01.0-scsi-0:0:0:0
E: ID_PATH_TAG=pci-0000_02_01_0-scsi-0_0_0_0
E: ID_REVISION=1.0
E: ID_SCSI=1
E: ID_TYPE=disk
E: ID_VENDOR=VMware
E: ID_VENDOR_ENC=VMware\x20\x20
E: MAJOR=8
E: MINOR=16
E: SUBSYSTEM=block
E: UDISKS_LVM2_PV_NUM_MDA=1
E: UDISKS_LVM2_PV_UUID=IdZPt8-2Pcl-h0XM-srbm-fzN8-q7qU-oZA2c7
E: UDISKS_LVM2_PV_VG_EXTENT_COUNT=127999
E: UDISKS_LVM2_PV_VG_EXTENT_SIZE=4194304
E: UDISKS_LVM2_PV_VG_FREE_SIZE=0
E: UDISKS_LVM2_PV_VG_LV_LIST=name=tmplv;uuid=w9a1K3-rFsf-9yek-TD4R-DriN-z585-waiShG;size=536866717696;;active=1
E: UDISKS_LVM2_PV_VG_NAME=localvg
E: UDISKS_LVM2_PV_VG_PV_LIST=uuid=IdZPt8-2Pcl-h0XM-srbm-fzN8-q7qU-oZA2c7;size=536866717696;allocated_size=536866717696
E: UDISKS_LVM2_PV_VG_SEQNUM=2
E: UDISKS_LVM2_PV_VG_SIZE=536866717696
E: UDISKS_LVM2_PV_VG_UUID=7bFRGA-d1iv-IEDr-d6tK-9Nfx-oKae-66v4bQ
E: UDISKS_PRESENTATION_NOPOLICY=0
E: USEC_INITIALIZED=46957
