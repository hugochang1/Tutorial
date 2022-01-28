#!/bin/bash

# ===========================================
# 			print
# ===========================================
echo hello world
printf "good morning\n"

# ===========================================
# 			variable
# ===========================================
a1=10		#assign variable
echo $a1	#print variable
echo "$a1"	#print variable
echo '$a1'	#print a1
unset a1	#remove a1 variable
echo $a1

# ===========================================
# 			check variable exist
# ===========================================
if [ -z $1 ]
then
        echo "parameter not exist"
else
        echo "parameter=[$1]"
fi

# ===========================================
# 			get substring of variable
# ===========================================
string=0123456789abcde

echo ${string:0:3}
#012

echo ${string:5:2}
#56

echo ${string:10:5}
#abcd

# ===========================================
# 			date
# ===========================================
now=`date`
echo $now
# Tue Aug 25 14:24:16 CST 2020

now="$(date +'%Y%m%d_%H%M%S')"
echo $now
# 20200825_142447

# ===========================================
# 			read input from user
# ===========================================
#read -p "input:" a1
#echo "your input is: $a1"

# ===========================================
# 			shell script status
# ===========================================
echo "last command result: $?"
echo "shell script name: $0"
echo "first parameter: $1"
echo "second paramter: $2"
echo "all parameters: $@"
echo "all parameters: $*"

# ===========================================
# 			+ - * /
# ===========================================
expr 6 + 2  # 8
expr 3 - 2  # 1
expr 2 \* 3 # 6
expr 8 / 3  # 2
expr 8 % 3  # 2

a1=`expr 10 + 20`
echo $a1	# 30

echo $((1+1)) # 2
echo $((2-1)) # 1
echo $((2*2)) # 4
echo $((5/2)) # 2
echo $((3%2)) # 1

a1=$((2+2))
echo $a1

# ===========================================
# 			condition and test
# ===========================================
ls && echo YES1 || echo "NO1"
ls /dev/aaa && echo YES2 || echo "NO2"

test aaa = aaa && echo YES3		#string comparsion: equal
test aaa != bbb && echo YES4	#string comparsion: not equal
test 5 -eq 5 && echo YES5		#integer comparsion: equal
test 1 -ne 2 && echo YES6		#integer comparsion: not equal
test 2 -gt 1 && echo YES7		#integer comparsion: greater than
test 1 -lt 2 && echo YES8		#integer comparsion: less than
test 2 -ge 2 && echo YES9		#integer comparsion: greater or equal
test 2 -le 2 && echo YES10		#integer comparsion: less or equal

a1="aaa"
a2="aaa"
test $a1 = $a2 && echo YES11

# ===========================================
# 			if else
# ===========================================
if [ aaa = aaa ]
then
	echo "come here 1"
else
	echo "never reach"
fi


if [ aaa = bbb ]
then
	echo "never reach"
elif [ bbb = bbb ]
then
	echo "come here 2"
else
	echo "never reach"
fi


if [ $0 = $0 ]
then
	echo "come here 3"
else
	echo "never reach"
fi


if [ aaa = aaa ]; then
	echo "come here 4"
elif [ bbb = bbb ]; then
	echo "never reach"
fi

# ===========================================
# 			while
# ===========================================
i=0
while [ $i -le 5 ]
	do
		echo $i
		i=$(($i+1))
		#i=`expr $i + 1`
	done


# ===========================================
# 			for
# ===========================================
for i in aaa bbb ccc 
	do
		echo $i
	done


for i in $@
	do
		echo $i
	done

# ===========================================
# 			case
# ===========================================
case 1 in
	1)		echo "1";;
	2|3|4)	echo "2~4";;
	*)		echo "others";;
esac


# ===========================================
# 			function
# ===========================================
f1()
{
	echo "f1() called"
	echo "f1() 1st parameter $1"
	echo "f1() 2nd parameter $2"
}

f1 aa bb

# ===========================================
# 			exit
# ===========================================

#exit 0

# ===========================================
# 			make
# ===========================================
make clean
make
status=$?
case $status in
	0) echo "-----------make success-----------";;
	*) echo "-----------make failed-----------";;
esac

./test
status=$?
echo "test result: $status"

make clean


# ===========================================
# 			time diff
# ===========================================
d1=$(date +"%s")
read -p "Press enter to continue"
d2=$(date +"%s")

echo $((d2-d1))

