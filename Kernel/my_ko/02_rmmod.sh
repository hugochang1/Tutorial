sudo rmmod hello.ko
case $? in
	0) dmesg;
		echo -e "\e[1;32m---------- rmmod hello.ko success -----------\e[m";
		;;
	*) echo -e "\e[1;31m---------- rmmod hello.ko failed-----------\e[m";
		;;
esac
