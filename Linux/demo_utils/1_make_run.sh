#!/bin/bash


make_success()
{
	echo -e "\E[1;32;40m-----------------------------make success-----------------------------\E[0m"
	./test
	ret=$?
	case $ret in
		0) echo -e "\E[1;32;40m-----------------------------end of program success-----------------------------\E[0m";;
		*) echo -e "\E[1;31;40m-----------------------------end of program failed ret=${ret}-----------------------------\E[0m";;
	esac
}

make_failed()
{
	echo -e "\E[1;31;40m-----------------------------make failed, ret=${ret}-----------------------------\E[0m"
}

#----------------------------------------------------

make
ret=$?
case $ret in
	0) make_success;;
	*) make_failed ret;;
esac
make clean


