#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

extern void fun1(void);

static int hugo_init(void)
{
	pr_info("hugo_init\n");
	fun1();
	return 0;
}

static void hugo_exit(void)
{
	pr_info("hugo_exit\n");
}

module_init(hugo_init);
module_exit(hugo_exit);
