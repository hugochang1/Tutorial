# echo
### simple
- `echo hello world` or `echo "hello world"` or `echo 'hello world'`
  - output: `hello world`
- `echo hello world $a` or `echo "hello world $a"`
  - `a=1`
  - ouptput: `hello world 1`
- `echo 'hello world $a'`
  - output: `hello world $a`
- `echo I don\'t` or `echo "I don't"` or `echo 'I don'\''t'`
  - output: `I don't`
### specific parameters
- script command: `./xxx.sh 1 abc`
  - `echo $0` script name
    - output: `./xxx.sh`
  - `echo $1` first parameter
    - output: `1`
  - `echo $2` second parameter
    - output: `abc`
  - `echo $#` the number of parameter
    - output: `2`
  - `echo $@` all parameters
    - output: `1 abc`
- others
  - `echo $$` pid
    - output: `2468`
  - `echo $?` the result of last command
    - 0: success
    - others: could be failed
### color
- `echo -e "\e[1;31mRed\e[m"`
  - output: `Red`
- `echo -e "\e[1;32mGreen\e[m"`
  - output: `Green`
- `echo -e "\e[1;33mYellow\e[m"`
  - output: `Yellow`

# if
### if, elif, else, fi
````
a=1
if [ $a = 1 ]; then
  echo "come here"
elif [ $b = 2 ]; then
  echo "not come here"
else
  echo "not come here"
fi
````

### string comparison
````
a=abc
if [ $a = abc ]; then
  echo "come here 0"
fi
````

### number comparison
````
a=1
if [ $a -eq 1 ]; then
  echo "equal"
fi

if [ $a -ne 2 ]; then
  echo "not equal"
fi

if [ $a -lt 2 ]; then
  echo "less than"
fi

if [ $a -gt 0 ]; then
  echo "great than"
fi

if [ $a -le 1 ]; then
  echo "less or equal"
fi

if [ $a -ge 1 ]; then
  echo "great or equal"
fi
````

### and or
````
a=1
b=2
if [ $a = 1 ] && [ $b = 2 ]; then
  echo "come here 1"
fi

if [ $a = 1 ] || [ $b = 1 ]; then
  echo "come here 2"
fi
````

### empty check
````
a=
if [ -z $a ]; then
  echo "variable is empty"
fi

a=1
if [ -n $a ]; then
  echo "variable is not empty"
fi
````

### file type
````
if [ -f "test.txt" ]; then
  echo "it's a file"
fi

if [ -d "folder" ]; then
  echo "it's a folder"
fi

if [ -h "test_sym.txt" ]; then
  echo "it's a symbolic link"
fi

if [ -b "/dev/sda" ]; then
  echo "it's a block dev"
fi

if [ -c "/dev/tty0" ]; then
  echo "it's a char dev"
fi

if [ -p "pipe" ]; then
  echo "it's a pipe channel"
fi

if [ -S "socket" ]; then
  echo "it's socket channel"
fi
````

### permission check
````
if [ -r "test.txt" ]; then
  echo "it's readable"
fi

if [ -w "test.txt" ]; then
  echo "it's writable"
fi

if [ -x "test.txt" ]; then
  echo "it's executable"
fi
````

# case
````
a=1
case $a in
  1)
    echo "come here"
    ;;
  2|3|a|abc)
    ;;
  *)
    echo "other case"
    ;;
esac
````

# for
````
for a in a b hello; do
  echo $a
done
````
- output
````
a
b
hello
````

# number operation
- a--
````
a=2
a=$[$a - 1]
echo $a
````
- output is `1`

# read from user
````
read -p "Enter something:" var
echo $var
````
````
read -p "Press enter to continue"
````

# function
````
run_fail_exit()
{
        echo -e "\e[1;33m$1\e[m"
        d1=$(date +"%s")
        eval $1
        if [ $? -ne 0 ]; then
                d2=$(date +"%s")
                echo -e "\e[1;31m$1, failed, time used: $((d2-d1))s\e[m"
                exit 1
        fi
        d2=$(date +"%s")
        echo -e "\e[1;32m$1, success, time used: $((d2-d1))s\e[m"
}

run_fail_exit "ls -al"
````
- output
````
ls -al
total 36
drwxrwxr-x 3 hugo hugo  4096 Jan 30 07:40 .
drwxrwxr-x 5 hugo hugo  4096 Jan 29 07:02 ..
-rwxrwxrwx 1 hugo hugo   315 Jan 28 08:32 01_script_demo.sh
-rwxrwxrwx 1 hugo hugo  2576 Jan 30 07:40 02_test.sh
-rw-r--r-- 1 hugo hugo 12288 Jan 30 07:40 .02_test.sh.swp
drwxrwxr-x 2 hugo hugo  4096 Jan 30 06:46 folder
lrwxrwxrwx 1 hugo hugo     8 Jan 30 06:48 test_sym.txt -> test.txt
-rw-rw-r-- 1 hugo hugo    51 Jan 28 19:57 test.txt
ls -al, success, time used: 0s
````
