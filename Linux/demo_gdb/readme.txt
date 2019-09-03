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
