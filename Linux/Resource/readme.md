# top
- show CPU usage and memory usage in system view
- `$ top`
  - `P` sorted by current CPU usage (default)
  - `M` sorted by memory usage
  - `T` sorted by accumulated CPU usage
````
top - 07:00:13 up 2 min,  1 user,  load average: 0.33, 0.47, 0.21
Tasks: 454 total,   1 running, 294 sleeping,   0 stopped,   0 zombie
%Cpu(s):  0.1 us,  0.1 sy,  0.0 ni, 99.9 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
KiB Mem :  8121856 total,  5718232 free,  1573048 used,   830576 buff/cache
KiB Swap:  2097148 total,  2097148 free,        0 used.  6263524 avail Mem 

   PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND
  1777 hugo      20   0  612244 142392  59488 S   0.7  1.8   0:01.68 Xorg
   434 root       0 -20       0      0      0 I   0.3  0.0   0:00.02 kworker/9:1H-kb
  1907 hugo      20   0 4203832 188592  81412 S   0.3  2.3   0:03.85 gnome-shell
  2235 root      20   0       0      0      0 I   0.3  0.0   0:00.05 kworker/9:3-mm_
  ...
````
- `$ top -d1` update interval is 1s (default is 3s)
- `$ sudo renice <value> <pid>` to change the priority of a process
  - `<value>` -20~20, -20 highest priority, 20 lowest priority
  - `$ sudo renice -19 1723` 

# lsof
- show open file in system view
- `$ lsof`
  - TYPE could be file, directory or socket
  - `$ lsof /usr`
  - `$ lsof -p pid`
````
COMMAND    PID  TID             USER   FD      TYPE             DEVICE SIZE/OFF       NODE NAME
systemd      1                  root  cwd   unknown                                        /proc/1/cwd (readlink: Permission denied)
systemd      1                  root  rtd   unknown                                        /proc/1/root (readlink: Permission denied)
systemd      1                  root  txt   unknown                                        /proc/1/exe (readlink: Permission denied)
systemd      1                  root NOFD                                                  /proc/1/fd (opendir: Permission denied)
...
````

# strace
- trace system calls and signals
- `$ strace <command>`
  - `$ strace cat /dev/null`
  - `$ strace -ff cat /dev/null` follows all forks
  - `$ strace -o strace_file -ff cat /dev/null` the result will be outputed to strace_file.pid (ex: ex: `strace_file.4074`)
````
execve("/bin/cat", ["cat", "/dev/null"], 0x7ffc9ce10988 /* 52 vars */) = 0
...
close(2)                                = 0
exit_group(0)                           = ?
+++ exited with 0 +++
````

# ltrace
- A library call tracer
- `$ ltrace <command>`
  - `$ ltrace cat /dev/null`
````
getpagesize()                                                                                                                                                             = 4096
strrchr("cat", '/')                                                                                                                                                       = nil
setlocale(LC_ALL, "")                                                                                                                                                     = "en_US.UTF-8"
bindtextdomain("coreutils", "/usr/share/locale")                                                                                                                          = "/usr/share/l
...
fclose(0x7f5af296d680)                                                                                                                                                    = 0
+++ exited (status 0) +++
````

# ps
- report a snapshot of the current processes
- `$ ps -m -o pid,tid,command`
  - `$ ps -m -o pid,tid,command -A` to show all
````
   PID    TID COMMAND
  2187      - bash
     -   2187 -
  4144      - ps -m -o pid,tid,command
     -   4144 -
````

# time
- run programs and summarize system resource usage
- `$ time <command>`
  - `$ time ls`
````
real	0m0.001s
user	0m0.001s
sys	0m0.000s
````

- `$ /usr/bin/time <command>`
  - `$ /usr/bin/time ls`
  - minor: the memory page needed by the program is cache miss, need to access the memory
  - major: the memory page needed by the program is cache miss and memory miss, need to access the disk
````
Desktop  Documents  Downloads  Music  Pictures	Public	snap  Templates  tmp  Videos  work
0.00user 0.00system 0:00.00elapsed 0%CPU (0avgtext+0avgdata 2604maxresident)k
0inputs+0outputs (0major+109minor)pagefaults 0swaps
````

# vmstat
- Report virtual memory statistics
- `$ vmstat <interval>`
  - `$ vmstat 1` to update memory per 1 s
````
$ vmstat 1
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 0  0      0 5222172 176164 1104256    0    0    70     8   32   47  0  0 99  0  0
 0  0      0 5222172 176172 1104256    0    0     0   184  539  761  0  0 100  0  0
 0  0      0 5222172 176172 1104256    0    0     0     0  890 1223  0  0 100  0  0
 0  0      0 5222172 176172 1104256    0    0     0     0  268  385  0  0 100  0  0
````

# iostat
- `$ sudo apt install sysstat`
- `$ iostat` by disk
````
Linux 5.4.174 (ubuntu) 	02/06/2022 	_x86_64_	(12 CPU)

avg-cpu:  %user   %nice %system %iowait  %steal   %idle
           0.18    0.05    0.41    0.04    0.00   99.32

Device             tps    kB_read/s    kB_wrtn/s    kB_read    kB_wrtn
sdb               0.07         1.67         0.00       2117          4
sda              26.50       804.17       150.98    1018873     191284
````

- `$ iostat -p ALL` by partition
````
Linux 5.4.174 (ubuntu) 	02/06/2022 	_x86_64_	(12 CPU)

avg-cpu:  %user   %nice %system %iowait  %steal   %idle
           0.17    0.05    0.39    0.04    0.00   99.35

Device             tps    kB_read/s    kB_wrtn/s    kB_read    kB_wrtn
scd0              0.00         0.00         0.00          0          0
sdb               0.07         1.59         0.00       2117          4
sda              25.19       763.76       143.54    1018873     191480
sda1             25.13       762.21       143.54    1016813     191480
````

# iotop
- `$ sudo apt install iotop`
- `$ sudo iotop`
````
Total DISK READ :       0.00 B/s | Total DISK WRITE :       0.00 B/s
Actual DISK READ:       0.00 B/s | Actual DISK WRITE:       0.00 B/s
   TID  PRIO  USER     DISK READ  DISK WRITE  SWAPIN     IO>    COMMAND
   
   370 be/4 root        0.00 B/s    0.00 B/s  0.00 %  0.01 % [kworker/u256:28-events_freezable_power_]
     1 be/4 root        0.00 B/s    0.00 B/s  0.00 %  0.00 % init auto noprompt
     2 be/4 root        0.00 B/s    0.00 B/s  0.00 %  0.00 % [kthreadd]
     3 be/0 root        0.00 B/s    0.00 B/s  0.00 %  0.00 % [rcu_gp]
     4 be/0 root        0.00 B/s    0.00 B/s  0.00 %  0.00 % [rcu_par_gp]
     6 be/0 root        0.00 B/s    0.00 B/s  0.00 %  0.00 % [kworker/0:0H-kblockd]
...
````

# pidstat
- `$ pidstat -p <pid> <interval>`
  - `$ pidstat -p 1777 1`
````
Linux 5.4.174 (ubuntu) 	02/06/2022 	_x86_64_	(12 CPU)

07:25:15 AM   UID       PID    %usr %system  %guest   %wait    %CPU   CPU  Command
07:25:16 AM  1000      1777    1.00    1.00    0.00    0.00    2.00    10  Xorg
07:25:17 AM  1000      1777    0.99    0.99    0.00    0.00    1.98    11  Xorg
07:25:18 AM  1000      1777    2.00    3.00    0.00    1.00    5.00    11  Xorg
07:25:19 AM  1000      1777    1.00    1.00    0.00    0.00    2.00    11  Xorg
07:25:20 AM  1000      1777    1.00    2.00    0.00    0.00    3.00     9  Xorg
````

