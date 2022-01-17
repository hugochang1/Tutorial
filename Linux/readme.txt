----------------------------------------------------
        iso
----------------------------------------------------
https://free.nchc.org.tw/ubuntu-cd/16.04/

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

