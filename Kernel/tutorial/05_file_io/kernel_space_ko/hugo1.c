#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/poll.h>

//-------------------- ioctl --------------------
#include <linux/ioctl.h>

struct hugo_ioctl_cmd {
	int d1;
};

#define HUGO_IOCTL_GET _IOR('d', 1, struct hugo_ioctl_cmd)
#define HUGO_IOCTL_SET _IOW('d', 2, struct hugo_ioctl_cmd)
#define HUGO_IOCTL_SU _IOW('d', 3, struct hugo_ioctl_cmd)

//-------------------- ctx --------------------
struct data_ctx {
	int pid;
	struct hugo_ioctl_cmd ioctl;
	struct  timer_list timer;
	wait_queue_head_t wq;
	bool has_data;
	spinlock_t lock;
	struct mutex mutex;
};

//-------------------- timer for generating the data --------------------
static void timer_func(struct timer_list *t)
{
	struct data_ctx *ctx = from_timer(ctx, t, timer);
	unsigned long flags;

	pr_err("timer_func() pid=%d\n", ctx->pid);
	spin_lock_irqsave(&ctx->lock, flags);
	ctx->has_data = true;
	wmb(); //ensure ctx->has_data = true before wakeup
	wake_up_interruptible(&ctx->wq);
	spin_unlock_irqrestore(&ctx->lock, flags);
}

//-------------------- file functions --------------------
static ssize_t hugo_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	struct data_ctx *ctx = filp->private_data;
	unsigned long flags;
	char data[] = {0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7};
	int ret, len;

	pr_err("hugo_read() pid=%d ctx=%p count=%ld buf=%p  \n", ctx->pid, ctx, count, buf);
	mod_timer(&ctx->timer, jiffies + (HZ/2)); //start 0.5s timer
	
	spin_lock_irqsave(&ctx->lock, flags);
	if (filp->f_flags & O_NONBLOCK) {
		//non-block
		if (!ctx->has_data) {
			spin_unlock_irqrestore(&ctx->lock, flags);
			return -EAGAIN; //errno=11 Resource temporarily unavailable
		}
	} else {
		spin_unlock_irqrestore(&ctx->lock, flags);
		//block
		ret = wait_event_interruptible(ctx->wq, ctx->has_data);
		pr_err("after wait_event_interruptible() ret=%d\n", ret);
		if (ret == -ERESTARTSYS) {
			pr_err("ERESTARTSYS\n");
			return -ERESTARTSYS; //errno=512 Unknown error 512
		}
	}
	ctx->has_data = false;
	spin_unlock_irqrestore(&ctx->lock, flags);
	
	//check length
	if (count < sizeof(data))
		len = count;
	else
		len = sizeof(data);
	
	if (copy_to_user(buf, data, len)) {
		pr_err("copy_to_user() failed\n");
		ret = -EFAULT;
	} else {
		ret = len;
	}
	
	return ret;
}

static ssize_t hugo_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	struct data_ctx *ctx = filp->private_data;
	char buf2[512];
	int len;

	//check length
	if (count < sizeof(buf2))
		len = count;
	else
		len = sizeof(buf2);

	if (copy_from_user(buf2, buf, count)) {
		pr_err("hugo_read() copy_from_user() failed");
		return -EFAULT; //errno=14 Bad address
	}
	pr_err("hugo_write() pid=%d ctx=%p count=%ld buf=[%s]\n", ctx->pid, ctx, count, buf2);
	return count;
}


static long hugo_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct data_ctx *ctx = filp->private_data;
	long ret = 0;
	struct hugo_ioctl_cmd *data = &ctx->ioctl;
	
	pr_err("hugo_ioctl() cmd=0x%x arg=0x%lx\n", cmd, arg);
	if (!access_ok((void __user *)arg, _IOC_SIZE(arg))) {
		pr_err("access_ok() failed\n");
		ret = -EFAULT; //errno=14 Bad address
	}
	switch (cmd) {
		case HUGO_IOCTL_GET:
			pr_err("HUGO_IOCTL_GET\n");
			mutex_lock(&ctx->mutex);
			if (copy_to_user((int __user *)arg, data, sizeof(*data))) {
				pr_err("copy_to_user() failed\n");
				ret = -EFAULT; //errno=14 Bad address
			}
			mutex_unlock(&ctx->mutex);
			break;
		case HUGO_IOCTL_SET:
			pr_err("HUGO_IOCTL_SET\n");
			mutex_lock(&ctx->mutex);
			if (copy_from_user(data, (int __user *)arg, sizeof(*data))) {
				pr_err("copy_from_user() failed\n");
				ret = -EFAULT; //errno=14 Bad address
			}
			mutex_unlock(&ctx->mutex);
			pr_err("d1=%d\n", data->d1);
			break;
		case HUGO_IOCTL_SU:
			if (!capable(CAP_SYS_ADMIN)) {
				pr_err("no permission\n");
				ret = -EPERM; //errno=1 Operation not permitted
			} else {
				pr_err("permission is ok\n");
			}
			break;
		default:
			pr_err("default\n");
			ret = -ENOTTY; //errno=25 Inappropriate ioctl for device
			break;
	}
	return ret;
}

static unsigned int hugo_poll(struct file *filp, struct poll_table_struct *wait)
{
	struct data_ctx *ctx = filp->private_data;
	unsigned int mask = 0;

	mod_timer(&ctx->timer, jiffies + (HZ/2)); //start 0.5s timer
	
	poll_wait(filp, &ctx->wq, wait);
	pr_err("after poll_wait() has_data=%d\n", ctx->has_data);
	if (ctx->has_data) {
		mask = POLLIN | POLLRDNORM;
	}
	
	return mask;
}

#include <linux/slab.h> //kmalloc

static int hugo_open(struct inode *inode, struct file *filp)
{
	struct data_ctx *ctx;
	
	ctx = kmalloc(sizeof(struct data_ctx), GFP_KERNEL);
	if (ctx == NULL) {
		pr_err("hugo_open() kmalloc() failed\n");
		return -1;
	}
	pr_err("hugo_open() major=%d minor=%d pid=%d ctx=%p flags=0x%x\n",
		imajor(inode), iminor(inode), current->pid, ctx, filp->f_flags);
	filp->private_data = ctx;

	ctx->pid = current->pid;
	spin_lock_init(&ctx->lock);
	mutex_init(&ctx->mutex);
	init_waitqueue_head(&ctx->wq);
	ctx->has_data = false;
	timer_setup(&ctx->timer, timer_func, 0);
	
	return 0;
}

static int hugo_release(struct inode *inode, struct file *filp)
{
	struct data_ctx *ctx = filp->private_data;

	pr_err("hugo_release() major=%d minor=%d pid=%d ctx=%p\n",
		imajor(inode), iminor(inode), current->pid, ctx);

	if (ctx) {
		del_timer(&ctx->timer);
		kfree(ctx);
	}

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

static int hugo_devnode_create(void)
{
	struct device *dev;
	
	major = register_chrdev(0, DEVNAME, &hugo_fops);
	if (major < 0) {
		pr_err("hugo register_chrdev() failed\n");
		return -1;
	}
	
	my_class = class_create(THIS_MODULE, DEVNAME);
	if (IS_ERR(my_class)) {
		pr_err("hugo class_create() failed\n");
		return -1;
	}
	
	dev = device_create(my_class, NULL, MKDEV(major, 0), NULL, "%s%d", DEVNAME, 0);
	if (IS_ERR(dev)) {
		pr_err("hugo device_create() failed\n");
		return -1;
	}
	
	return 0;
}

static void hugo_devnode_remove(void)
{
	device_destroy(my_class, MKDEV(major, 0));
	class_destroy(my_class);
	unregister_chrdev(major, DEVNAME);
}

#include <linux/module.h>
#include <linux/init.h>

static int hugo_init(void)
{
	pr_info("hugo_init ver=1.01\n");
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
