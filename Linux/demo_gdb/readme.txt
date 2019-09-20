# gdb test
# gdb test core_dump

-------------------------------------------------------------------------------
GNU gdb (Ubuntu 7.7.1-0ubuntu5~14.04.3) 7.7.1
Copyright (C) 2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./test...done.


(gdb) run
Starting program: /proj/mtk04140/app2/demo_gdb/test
gdb demo program started
Program received signal SIGSEGV, Segmentation fault.
0x000000000040053d in crash_here () at main.c:26
26        *crash = 1;


(gdb) list
21      static my_enum en = ENUM_B;
22      static my_struct2 s;
23
24      void crash_here() {
25        char* crash = NULL;
26        *crash = 1;
27      }
28
29      int main() {
30        printf("gdb demo program started\n");


(gdb) bt
#0  0x000000000040053d in crash_here () at main.c:26
#1  0x000000000040055a in main () at main.c:31


(gdb) print en
$1 = ENUM_B


(gdb) print s
$2 = {a = 0, b = 0, c = '\000' <repeats 31 times>, d = {a1 = 0 '\000', a2 = 0}}


(gdb) print s.a
$3 = 0


(gdb) print s.c
$4 = '\000' <repeats 31 times>


(gdb) print s.d
$5 = {a1 = 0 '\000', a2 = 0}


(gdb) print s.d.a2
$6 = 0

(gdb) info variables
(gdb) info args
(gdb) info locals
d = 123
en = ENUM_C
b = 2

(gdb) select-frame 1
(gdb) info locals
en = ENUM_C
b = 2


(gdb) info sharedlibrary
From                To                  Syms Read   Shared Object Library
0x00007ffff7ddab00  0x00007ffff7df55b0  Yes         /lib64/ld-linux-x86-64.so.2
0x00007ffff7a30520  0x00007ffff7b78e03  Yes         /lib/x86_64-linux-gnu/libc.so.6

(gdb) set solib-search-path /lib64/ld-linux-x86-64.so.2 /lib/x86_64-linux-gnu/libc.so.6


(gdb) info thread
  Id   Target Id         Frame 
  1    Thread 0x7ffff7fde700 (LWP 3381) "test" 0x00007ffff78bc30d in nanosleep () at ../sysdeps/unix/syscall-template.S:84
* 2    Thread 0x7ffff77ef700 (LWP 3382) "test" 0x0000000000400796 in crash_here () at main.c:27
  3    Thread 0x7ffff6fee700 (LWP 3383) "test" 0x00007ffff78bc30d in nanosleep () at ../sysdeps/unix/syscall-template.S:84

(gdb) thread 1
[Switching to thread 1 (Thread 0x7ffff7fde700 (LWP 3418))]
#0  0x00007ffff78bc30d in nanosleep () at ../sysdeps/unix/syscall-template.S:84
84	in ../sysdeps/unix/syscall-template.S

(gdb) bt
#0  0x00007ffff78bc30d in nanosleep () at ../sysdeps/unix/syscall-template.S:84
#1  0x00007ffff78bc25a in __sleep (seconds=0) at ../sysdeps/posix/sleep.c:55
#2  0x00000000004008e7 in main () at main.c:71
