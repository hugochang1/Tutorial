----------------------------------------------------
        printk
----------------------------------------------------
// get current kernel log level
$ cat /proc/sys/kernel/printk
4 4 1 7

// disable all kernel logs
$ echo "0" > /proc/sys/kernel/printk
$ echo "0" | sudo tee /proc/sys/kernel/printk

// enable all kernel logs
$ echo "7" > /proc/sys/kernel/printk
$ echo "7" | sudo tee /proc/sys/kernel/printk

reference: https://linuxconfig.org/introduction-to-the-linux-kernel-log-levels

----------------------------------------------------
        others
----------------------------------------------------

