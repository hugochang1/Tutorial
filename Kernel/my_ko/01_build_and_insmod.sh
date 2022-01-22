insmod_fun()
{
	sudo insmod hello.ko
	case $? in
		0) dmesg;
			echo -e "\e[1;32m--------- insmod hello.ko success ----------\e[m";
			;;
		*) echo -e "\e[1;31m----------- insmod hello.ko failed ----------\e[m";
			;;
	esac
}


make
case $? in
	0) echo -e "\e[1;32m------------ make success -----------\e[m";
		insmod_fun;
		;;
	*) echo -e "\e[1;31m------------ make failed  -----------\e[m"
		;;
esac

