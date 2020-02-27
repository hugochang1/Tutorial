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
