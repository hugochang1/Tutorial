# Good Article
* printk
  * https://www.kernel.org/doc/Documentation/printk-formats.txt- 
  * https://linuxconfig.org/introduction-to-the-linux-kernel-log-levels
  * get current kernel log level
    * $ cat /proc/sys/kernel/printk
  * disable all kernel logs
    * $ echo "0" > /proc/sys/kernel/printk
    * $ echo "0" | sudo tee /proc/sys/kernel/printk
  * enable all kernel logs
    * $ echo "7" > /proc/sys/kernel/printk
    * $ echo "7" | sudo tee /proc/sys/kernel/printk


| type | printk format |
| ------ | ----- |
| int | %d or %x |
| unsigned int | %u or %x |
| long | %ld or %lx |
| long long | %lld or %llx |
| unsigned long long | %llu or %llx |
| size_t | %zu or %zx |
| ssize_t | %zd or %zx |
| pointer | %pf or %px (real address) |

```
#define MY_LOG(fmt, args...) pr_emerg("%s MY_TAG,%s, "fmt"\n", "1.00", __func__, ## args)
```

# memory barrier
* https://zhuanlan.zhihu.com/p/96001570

````

````
