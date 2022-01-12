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

//--------------------- devnode ---------------------
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>

/*
# cat /dev/hugo_dev0
abc 123
[console log]
6396 [  393.279835]  (0)[6991:cat]hugo_open()
6397 [  393.280323]  (0)[6991:cat]hugo_read() size=4096 strlen=8 flag=1
6398 [  393.281102]  (0)[6991:cat]hugo_read() size=4096 strlen=8 flag=0
6399 [  393.281875]  (0)[6991:cat]hugo_release()

# echo "aaa" > /dev/hugo_dev0 
[console log]
6497 [  464.827913]  (2)[6202:sh]hugo_open()
6498 [  464.828434]  (2)[6202:sh]hugo_write() size=4 buf=[aaa
6500 [  464.829554]  (2)[6202:sh]hugo_release()
*/

static int hugo_open(struct inode *inode, struct file *filp)
{
	pr_err("hugo_open()\n");
	return 0;
}

static int hugo_release(struct inode *inode, struct file *filp)
{
	pr_err("hugo_release()\n");
	return 0;
}

static int flag = 0;

static ssize_t hugo_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	char *buf2 = "abc 123\n";
	size_t len = strlen(buf2);
	
	if (copy_to_user(buf, buf2, len)) {
		pr_err("hugo_read() copy_to_user() failed");
		return -EFAULT;
	}
	
	flag = !flag;
	pr_err("hugo_read() size=%ld strlen=%ld flag=%d\n", count, len, flag);
	
	if (flag)
		return len;
	else
		return 0;
}

static ssize_t hugo_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	char buf2[1024];
	if (copy_from_user(buf2, buf, count)) {
		pr_err("hugo_read() copy_from_user() failed");
		return -EFAULT;
	}
	pr_err("hugo_write() size=%ld buf=[%s]\n", count, buf2);
	return count;
}

static unsigned int hugo_poll(struct file *filp, struct poll_table_struct *wait)
{
	pr_err("hugo_poll()\n");
	return 0;
}

static long hugo_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	pr_err("hugo_ioctl()\n");
	return 0;
}

static const struct file_operations hugo_fops = {
  	.owner          = THIS_MODULE,
  	.open           = hugo_open,
  	.release        = hugo_release,
  	.read           = hugo_read,
  	.write          = hugo_write,
  	.poll           = hugo_poll,
  	.unlocked_ioctl = hugo_ioctl,
  	.compat_ioctl   = hugo_ioctl,
};

static char *DEVNAME = "hugo_dev";
static int major;
static struct class *my_class;

static void devnode_create_example(void)
{
	struct device *dev;
	
	major = register_chrdev(0, DEVNAME, &hugo_fops);
	if (major < 0) {
		pr_err("hugo register_chrdev() failed\n");
		return;
	}
	
	my_class = class_create(THIS_MODULE, DEVNAME);
	if (IS_ERR(my_class)) {
		pr_err("hugo class_create() failed\n");
		return;
	}
	
	dev = device_create(my_class, NULL, MKDEV(major, 0), NULL, "%s%d", DEVNAME, 0);
	if (IS_ERR(dev)) {
		pr_err("hugo device_create() failed\n");
		return;
	}
}

static void devnode_remove_example(void)
{
	device_destroy(my_class, MKDEV(major, 0));
	class_destroy(my_class);
	unregister_chrdev(major, DEVNAME);
}



	devnode_create_example();
	devnode_remove_example();
````
