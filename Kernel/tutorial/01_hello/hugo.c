#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

static int hugo_init(void)
{
	pr_info("hugo_init\n");
	return 0;
}

static void hugo_exit(void)
{
	pr_info("hugo_exit\n");
}

module_init(hugo_init);
module_exit(hugo_exit);
