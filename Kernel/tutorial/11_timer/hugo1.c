#include <linux/module.h>
#include <linux/init.h>

//-------------------------------------------------------------------------------------------
#include <linux/delay.h>

static void demo_jiffies(void)
{
	//jiffies will overflow after 497 days
	pr_info("HZ=%d\n", HZ);
	pr_info("jiffies=%ld\n", jiffies);
	pr_info("jiffies_64=%lld\n", jiffies_64);
	mdelay(1000);
	pr_info("after 1s\n");
	pr_info("jiffies=%ld\n", jiffies);
	pr_info("jiffies_64=%lld\n", jiffies_64);
	/*
	[ 3960.075741] HZ=250
	[ 3960.075741] jiffies=4295882230
	[ 3960.075741] jiffies_64=4295882230
	[ 3961.068269] after 1s
	[ 3961.068270] jiffies=4295882479
	[ 3961.068271] jiffies_64=4295882479
	*/
}

//-------------------------------------------------------------------------------------------
static void demo_delay(void)
{
	//not yield CPU to others
	pr_info("demo_delay()\n");
	mdelay(100);
	pr_info("after mdelay()\n");
	udelay(19999); // cannot over 19999 or build error happens
	pr_info("after udelay()\n");
	ndelay(19999); // cannot over 19999 or build error happens
	pr_info("after ndelay()\n");
	/*
	[ 4562.542058] demo_delay()
	[ 4562.641290] after mdelay()
	[ 4562.661131] after udelay()
	[ 4562.661155] after ndelay()
	*/
}

//-------------------------------------------------------------------------------------------
static void demo_sleep(void)
{
	//yield CPU to others
	pr_info("demo_sleep()\n");
	ssleep(1);
	pr_info("ssleep()\n");
	msleep(100);
	pr_info("msleep()\n");
	/*
	[ 4771.782395] demo_sleep()
	[ 4772.799389] ssleep()
	[ 4772.907845] msleep()
	*/
}

//-------------------------------------------------------------------------------------------
static void demo_sleep_interruptible(void)
{
	unsigned long ret;
	
	pr_info("demo_sleep_interruptible()\n");
	ret = msleep_interruptible(2000);
	if (ret == 0) {
		pr_info("msleep_interruptible() timeout\n");
	} else {
		pr_info("msleep_interruptible() interrupted ret=%lu\n", ret);
		//msleep_interruptible() interrupted ret=1212
		//ret=1~2000
	}
}

//-------------------------------------------------------------------------------------------
#include <linux/timer.h>

struct time_ctx {
	int data;
	struct timer_list timer;
};

struct time_ctx g_time_ctx;

static void timer_func(struct timer_list *t)
{
	//interrupt context, cannot sleep	
	struct time_ctx *ctx = from_timer(ctx, t, timer);

	pr_err("timer_func() data=%d\n", ctx->data);
}

static void demo_timer(void)
{	
	g_time_ctx.data = 123;
	timer_setup(&g_time_ctx.timer, timer_func, 0);

	/*
	2*HZ   //2 seconds in jiffies
	HZ       // 1 second in jiffies
	foo * HZ // foo seconds in jiffies
	HZ/10    // 100 milliseconds in jiffies
	HZ/100   // 10 milliseconds in jiffies
	bar*HZ/1000 // bar milliseconds in jiffies
	*/
	pr_err("mod_timer() for 1s");
	mod_timer(&g_time_ctx.timer, jiffies + 1 * HZ); // 1s
	msleep(1200);
	/*
	[ 5967.600340] mod_timer() for 1s
	[ 5968.615230] timer_func() data=123
	*/
	
	pr_err("mod_timer() for 500ms");
	mod_timer(&g_time_ctx.timer, jiffies + (500 * HZ)/1000); //500ms
	msleep(600);
	/*
	[ 5968.807160] mod_timer() for 500ms
	[ 5969.318992] timer_func() data=123
	*/
	
	mod_timer(&g_time_ctx.timer, jiffies + 2 * HZ); // 2s
	del_timer(&g_time_ctx.timer);
	del_timer_sync(&g_time_ctx.timer);
}

//-------------------------------------------------------------------------------------------
static int hugo_init(void)
{
	pr_info("hugo_init ver=1.00\n");
	demo_jiffies();
	demo_delay();
	demo_sleep();
	demo_sleep_interruptible();
	demo_timer();

	return 0;
}

static void hugo_exit(void)
{
	pr_info("hugo_exit\n");

}

module_init(hugo_init);
module_exit(hugo_exit);

MODULE_LICENSE("GPL");
