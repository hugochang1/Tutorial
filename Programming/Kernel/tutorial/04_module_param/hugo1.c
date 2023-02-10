#include <linux/module.h>
#include <linux/init.h>

//cat /sys/module/hugo/parameters/aaa
//echo 123 | sudo tee /sys/module/hugo/parameters/aaa
static int aaa = 0;
module_param(aaa, int, 0644);
MODULE_PARM_DESC(aaa, "this is aaa's description");

static int bbb = 0;
module_param(bbb, uint, 0644);

static char *ccc= "default";
module_param(ccc, charp, 0644);

static int hugo_init(void)
{
	pr_info("hugo_init\n");
	pr_info("hugo aaa=%d\n", aaa);
	pr_info("hugo bbb=%d\n", bbb);
	pr_info("hugo ccc=%s\n", ccc);
	return 0;
}

static void hugo_exit(void)
{
	pr_info("hugo_exit\n");
}

module_init(hugo_init);
module_exit(hugo_exit);

MODULE_LICENSE("GPL");
