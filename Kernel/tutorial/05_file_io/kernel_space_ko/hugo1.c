#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>

static char *DEVNAME = "hugo_dev";
static int major;
static struct class *my_class;

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
	char buf2[512];
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

static void hugo_devnode_create(void)
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

static void hugo_devnode_remove(void)
{
	device_destroy(my_class, MKDEV(major, 0));
	class_destroy(my_class);
	unregister_chrdev(major, DEVNAME);
}

static int hugo_init(void)
{
	pr_info("hugo_init ver=1.00\n");
	hugo_devnode_create();
	return 0;
}

static void hugo_exit(void)
{
	pr_info("hugo_exit\n");
	hugo_devnode_remove();
}

module_init(hugo_init);
module_exit(hugo_exit);

MODULE_LICENSE("GPL");
