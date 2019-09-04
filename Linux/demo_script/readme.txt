----------------------------------------------------
        find
https://blog.gtwang.org/linux/unix-linux-find-command-examples/
----------------------------------------------------
# case sensitive
find ./ -name file_name
find ./ -name file*

# case insensitive
find ./ -iname file_name

find ./ -type f file_name
find ./ -type d folder_name

----------------------------------------------------
        grep
----------------------------------------------------
grep keyword ./ -r
grep keyword ./ -r --include=file_name
grep keyword ./ -r --include=*.cpp

