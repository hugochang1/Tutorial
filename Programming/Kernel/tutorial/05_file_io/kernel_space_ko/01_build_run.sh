run_fail_exit()
{
        echo -e "\e[1;33m$@\e[m"
        d1=$(date +"%s")
        eval "$@"
        if [ $? -ne 0 ]; then
                d2=$(date +"%s")
                echo -e "\e[1;31m$1, failed, time used: $((d2-d1))s\e[m"
                exit 1
        fi
        d2=$(date +"%s")
        echo -e "\e[1;32m$1, success, time used: $((d2-d1))s\e[m"
}


run_fail_exit "make"
run_fail_exit "sudo insmod hugo.ko $@"
run_fail_exit "lsmod | grep hugo"
run_fail_exit "sudo chmod 777 /dev/hugo_dev0"
run_fail_exit "dmesg | tail"

read -p "Press enter to rmmod hugo.ko"
run_fail_exit "sudo rmmod hugo"
run_fail_exit "dmesg | tail"

