#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

void fun1(void)
{
	pr_info("fun1\n");
}
