//--------------------- kmalloc ---------------------
#include <linux/slab.h>

static void kmalloc_example(void)
{
	void *data1;

	data1 = kmalloc(1024, GFP_KERNEL);
	if (data1 == NULL) {
		pr_err("[hugo] kmalloc() failed 1\n");
		return;
	}
	kfree(data1);

	data1 = kzalloc(1024, GFP_ATOMIC);
	if (data1 == NULL) {
		pr_err("[hugo] kmalloc() failed 2\n");
		return;
	}
	kfree(data1);
}

//--------------------- wakeup_source ---------------------
#include <linux/device.h>
#include <linux/pm_wakeup.h>

static void wakeup_example(void)
{
	struct wakeup_source *wakeup_src;

	wakeup_src = wakeup_source_register(NULL, "my_wakeup_name");

	//void __pm_stay_awake(struct wakeup_source *ws)
	__pm_stay_awake(wakeup_src);

	//void __pm_relax(struct wakeup_source *ws)
	__pm_relax(wakeup_src);
}

//--------------------- timer_list ---------------------
#include <linux/timer.h>

struct time_ctx {
	int data;
	struct timer_list timer;
};

struct time_ctx g_time_ctx;
static void timer_func(struct timer_list *t)
{
	struct time_ctx *ctx = from_timer(ctx, t, timer);

	pr_err("[hugo] timer_func() data=%d\n", ctx->data);
}

static void timer_example(void)
{
	unsigned long timeout_in_s = 1;
	
	g_time_ctx.data = 123;
	//timer_setup(timer, callback, flags)
	timer_setup(&g_time_ctx.timer, timer_func, 0);

	//int mod_timer(struct timer_list *timer, unsigned long expires)
	//The function returns whether it has modified a pending timer or not
	//(ie. mod_timer() of an inactive timer returns 0, mod_timer() of an active timer returns 1.)
	// jiffies: accumulated by timer interrupt
	// HZ: timer interrupt count per second
	mod_timer(&g_time_ctx.timer, jiffies + timeout_in_s * HZ);

	//int del_timer(struct timer_list *timer)
	//The function returns whether it has deactivated a pending timer or not
	//(ie. del_timer() of an inactive timer returns 0, del_timer() of an active timer returns 1.)
	//del_timer(&g_time_ctx.timer);
}
