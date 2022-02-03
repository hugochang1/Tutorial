# top
- `$ top`
  - `P` sorted by current CPU usage (default)
  - `M` sorted by memory usage
  - `T` sorted by accumulated CPU usage
- `$ sudo renice <value> <pid>`
  - `<value>` -20~20, -20 highest priority, 20 lowest priority
  - `$ sudo renice -19 1723` 

# lsof
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
- system trace
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
- library trace
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
- `$ time ls`
````
real	0m0.001s
user	0m0.001s
sys	0m0.000s
````

