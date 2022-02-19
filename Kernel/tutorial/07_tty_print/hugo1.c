#include <linux/module.h>
#include <linux/init.h>
#include <linux/tty.h>

static void __tty_print(char *msg)
{
	struct tty_struct *tty;
	
	tty = get_current_tty();
	if (tty != NULL) {
		tty->ops->write(tty, msg, strlen(msg));
	}
}

static void tty_printf(const char *fmt, ...)
{
	va_list args;
	struct va_format vaf;
	char output[800] = {0};

	BUG_ON(!fmt);

	va_start(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	sprintf(output, "%pV", &vaf);
	__tty_print(output);

	va_end(args);
}

static int hugo_init(void)
{
	pr_info("hugo_init ver=1.01\n");
	
	__tty_print("hello world\r\n");
	tty_printf("hugo %d %s\r\n", 123, "ggggg kkkk");
	tty_printf("test 1\r\n");
	tty_printf("test 2\n");
	tty_printf("test 3\n");
	tty_printf("test 4\n");

	/*
	hello world
	hugo 123 ggggg kkkk
	test 1
	test 2
		  test 3
				test 4
	*/
	return 0;
}

static void hugo_exit(void)
{
	pr_info("hugo_exit\n");
}

module_init(hugo_init);
module_exit(hugo_exit);

MODULE_LICENSE("GPL");
