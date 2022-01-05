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
	.probe = hugo_probe,
	.remove = hugo_remove,
 
static int hugo_remove(struct platform_device *pdev)
{
	pr_err("[hugo] hugo_remove()\n");
	file_remove_example(&pdev->dev);
	return 0;
}

static int hugo_probe(struct platform_device *pdev)
{
	pr_err("[hugo] hugo_probe()\n");
	dma_mapping_example(&pdev->dev);
	file_create_example(&pdev->dev);
	test_examples();
	return 0;
}

//--------------------- file ---------------------
// cat /sys/devices/platform/10014000.hugo/hugo_file
// [output] hugo said hello 123 abc
static ssize_t file_show_config(struct device *dev, struct device_attribute *attr, char *buff)
{
	pr_err("[hugo] file_show_config()\n");
	sprintf(buff, "hugo said hello %d %s\n", 123, "abc");
	return strlen(buff);
}

// echo hello world > /sys/devices/platform/10014000.hugo/hugo_file
// [log] 308 [  230.533129]  (1)[6680:sh][hugo] file_set_config() count=12 buff=[hello world
static ssize_t file_set_config(struct device *dev, struct device_attribute *attr, const char *buff, size_t count)
{
	pr_err("[hugo] file_set_config() count=%zu buff=[%s]\n", count, buff);
	return count;
}

//DEVICE_ATTR(_name, _mode, _show, _store)
static DEVICE_ATTR(hugo_file, 0660, file_show_config, file_set_config);

static void file_create_example(struct device *dev)
{
	int ret = 0;
	
	//int device_create_file(struct device *dev, const struct device_attribute *attr)
	ret = device_create_file(dev, &dev_attr_hugo_file);
	if (ret != 0) {
		pr_err("[hugo] file_create_example() device_create_file() failed, ret=%d\n", ret);
		return;
	}
	pr_err("[hugo] file_create_example() device_create_file() success\n");
}

static void file_remove_example(struct device *dev)
{
	pr_err("[hugo] file_remove_example()\n");
	//void device_remove_file(struct device *dev, const struct device_attribute *attr)
	device_remove_file(dev, &dev_attr_hugo_file);
}

//--------------------- skb ---------------------
#include <linux/skbuff.h>
#include <linux/netdevice.h>

static void skb_example(void)
{
	struct sk_buff *skb;

	skb = __dev_alloc_skb(1200, GFP_KERNEL);
	if(unlikely(!skb)) {
		pr_err("[hugo] __dev_alloc_skb return NULL\n");
		return;
	}

	pr_err("[hugo] skb_headroom=%u\n", skb_headroom(skb)); // 64

	dev_kfree_skb_any(skb);
}
````
