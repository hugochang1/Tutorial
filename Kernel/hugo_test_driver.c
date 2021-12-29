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

//--------------------- DTS ---------------------
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>

/* DTS
my_module:my_module@10014000 {
	compatible = "hugo,my_module";
	reg = <0 0x10014000 0 0x1000>,
		<0 0x1022D000 0 0x1000>,
	interrupts = <GIC_SPI 209 IRQ_TYPE_LEVEL_HIGH 0>;
};
*/
static void dts_example(void)
{
	struct device_node *node = NULL;
	void __iomem *reg1;
	void __iomem *reg2;
	unsigned int irq_id;

	//struct device_node *of_find_compatible_node(struct device_node *from, const char *type, const char *compatible)
	node = of_find_compatible_node(NULL, NULL, "hugo,my_module");
	if (node == NULL) {
		pr_err("[hugo] node is NULL\n");
		return;
	}

	//void __iomem *of_iomap(struct device_node *np, int index)
	reg1 = of_iomap(node, 0);
	if (reg1 == NULL) {
		pr_err("[hugo] of_iomap(0) failed\n");
		return;
	}
	pr_err("[hugo] reg1=%px\n", reg1);
	
	reg2 = of_iomap(node, 1);
	if (reg2 == NULL) {
		pr_err("[hugo] of_iomap(1) failed\n");
		return;
	}
	pr_err("[hugo] reg2=%px\n", reg2);

	//unsigned int irq_of_parse_and_map(struct device_node *dev, int index)
	irq_id = irq_of_parse_and_map(node, 0);
	if (irq_id == 0) {
		pr_err("[hugo] irq_of_parse_and_map(0) failed\n");
		return;
	}
	pr_err("[hugo] irq_id=%d\n", irq_id);
}

//--------------------- suspend/resume ---------------------
#include <linux/syscore_ops.h>

static int sys_suspend(void)
{
	pr_err("[hugo] sys_suspend()\n");
	return 0;
}

static void sys_resume(void)
{
	pr_err("[hugo] sys_resume()\n");
}

static struct syscore_ops my_syscore_ops = {
  .suspend = sys_suspend,
  .resume = sys_resume,
};

static void suspend_example(void)
{
	register_syscore_ops(&my_syscore_ops);
}
