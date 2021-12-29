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

```
//--------------------- main ---------------------
#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

static void test_examples(void)
{
	kmalloc_example();
	wakeup_example();
	timer_example();
	dts_example();
	suspend_example();
	tasklet_example();
	workqueue_example();
	kthread_example();
	sk_buff_head_example();
	atomic_example();
	list_head_example();
	spin_lock_example();
}

static int hugo_probe(struct platform_device *pdev)
{
	pr_err("[hugo] hugo_probe()\n");
	dma_mapping_example(&pdev->dev);
	test_examples();
	return 0;
}

static const struct of_device_id hugo_of_dev_ids[] = {
	{.compatible = "hugo,my_module"}, //need to ensure xxx.dts has this compatible
	{}
};

static struct platform_driver hugo_driver = {
	.driver = {
		.name = "hugo_test",
		.of_match_table = hugo_of_dev_ids,
	},
	.probe = hugo_probe,
};

static int hugo_test_init(void)
{
    int ret = 0;
	
    pr_err("[hugo] hugo_test_init() v2\n");
	ret = platform_driver_register(&hugo_driver);
	if (ret) {
		pr_err("[hugo] hugo_test_init() platform_driver_register() failed ret=%d\n", ret);
		return -1;
	}
    return ret;
}

static void hugo_test_exit(void)
{
    pr_err("[hugo] hugo_test_exit()\n");
	platform_driver_unregister(&hugo_driver);
}

module_init(hugo_test_init);
module_exit(hugo_test_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hugo Chang");
```
