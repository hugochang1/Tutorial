[issue]
hugo@hugo-VirtualBox:~/app/demo_utils$ ./1_make_run.sh 
gcc -g -c -g -Wall -D __COMPILE_OPTION__ -m32  -I./ -I./utils/  -o utils/utils.o utils/utils.c
In file included from /usr/include/errno.h:28:0,
                 from utils/utils.c:1:
/usr/include/features.h:367:25: fatal error: sys/cdefs.h: No such file or directory
compilation terminated.
Makefile:41: recipe for target 'utils/utils.o' failed
make: *** [utils/utils.o] Error 1

[solution]
sudo apt install libc6-dev-i386

-----------------------------------------------------------------------------------------------------

sudo apt install
[issue]
E: Could not get lock /var/lib/dpkg/lock – open (11: Resource temporarily unavailable)
E: Unable to lock the administration directory (/var/lib/dpkg/), is another process using it?

[Solution]
ps aux | grep -i apt
sudo killall apt apt-get

https://itsfoss.com/could-not-get-lock-error/

-----------------------------------------------------------------------------------------------------

make
[issue]
/usr/bin/ld: skipping incompatible /usr/lib/gcc/x86_64-linux-gnu/5/libstdc++.so when searching for -lstdc++
/usr/bin/ld: skipping incompatible /usr/lib/gcc/x86_64-linux-gnu/5/libstdc++.a when searching for -lstdc++
/usr/bin/ld: cannot find -lstdc++


[Solution]
$ gcc --version
gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609

sudo apt-get install libstdc++-<你的gcc版本号>-dev
sudo apt-get install libstdc++-5.4-dev

apt-get source
