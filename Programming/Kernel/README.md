# Good Article
* Kernel code reference
  * https://elixir.bootlin.com/linux/v5.4.174/source
* kernel qemu
  * https://hackmd.io/@sysprog/linux-virtme
* How to compile and install Linux Kernel 5.6.9 from source code
  * https://www.cyberciti.biz/tips/compiling-linux-kernel-26.html
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

# get page size
- `$ getconf PAGESIZE`
````
4096
````

# memory barrier
* https://zhuanlan.zhihu.com/p/96001570

````
void __dynamic_pr_info(struct _ddebug *descriptor, const char *fmt, ...)
{
	va_list args;
	struct va_format vaf;
	char buf[PREFIX_SIZE];

	BUG_ON(!descriptor);
	BUG_ON(!fmt);

	va_start(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	printk(KERN_INFO "%s%pV", dynamic_emit_prefix(descriptor, buf), &vaf);

	va_end(args);
}
````

# dump raw data
````
static void dump_buff(char* prefix, char* buff, int len) {
    int i = 0;
    int offset = 0;
    char str[64] = {0};
    pr_info("%s dump_buff() len=[%d]\n", prefix, len);
     
    for(i = 0; i < len; i++) {
        if(i != 0 && i % 16 == 0) {
            pr_info("%s  %s\n", prefix, str);
            offset = 0;
            memset(str, 0, sizeof(str));
        }
        sprintf(str + offset, "%02x ", buff[i] & 0xff);
        offset += 3;
    }
    if(i != 0) {
        pr_info("%s  %s\n", prefix, str);
    }
}
````
