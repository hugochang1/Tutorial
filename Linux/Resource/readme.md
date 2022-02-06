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
