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

//--------------------- tasklet ---------------------
#include <linux/interrupt.h>

static void my_tasklet(unsigned long data)
{
	struct tasklet_struct *tasklet;
	
	tasklet = (struct tasklet_struct *)data;
	pr_err("[hugo] my_tasklet() tasklet=%px\n", tasklet);
}


struct tasklet_struct g_tasklet;
static void tasklet_example(void)
{
	//void tasklet_init(struct tasklet_struct *t, void (*func)(unsigned long), unsigned long data)
	tasklet_init(&g_tasklet, my_tasklet, (unsigned long)&g_tasklet);

	//void tasklet_schedule(struct tasklet_struct *t)
	tasklet_schedule(&g_tasklet);
	
	//void tasklet_hi_schedule(struct tasklet_struct *t), high priority tasklet
	tasklet_hi_schedule(&g_tasklet);
}

//--------------------- workqueue ---------------------
#include <linux/workqueue.h>

struct work_struct g_work;
struct delayed_work g_delay_work;
struct workqueue_struct *g_wq;

static void my_work_func(struct work_struct *work)
{
	pr_err("[hugo] my_work_func()\n");
}

static void workqueue_example(void)
{
	unsigned long timeout_in_s = 1;

	//struct workqueue_struct *alloc_workqueue(const char *fmt, unsigned int flags, int max_active, ...)
	g_wq = alloc_workqueue("my_workqueue", WQ_UNBOUND | WQ_MEM_RECLAIM, 1);

	// ----------- demo work ----------- 
	INIT_WORK(&g_work, my_work_func);

	//bool queue_work(struct workqueue_struct *wq, struct work_struct *work)
	queue_work(g_wq, &g_work);

	//bool flush_work(struct work_struct *work)
	//wait for a work to finish executing the last queueing instance
	flush_work(&g_work);
	
	// ----------- demo delay_work -----------
	INIT_DELAYED_WORK(&g_delay_work, my_work_func);

	//bool queue_delayed_work(struct workqueue_struct *wq, struct delayed_work *dwork, unsigned long delay)
	queue_delayed_work(g_wq, &g_delay_work, timeout_in_s * HZ);
	
	//bool cancel_delayed_work(struct delayed_work *dwork)
	cancel_delayed_work(&g_delay_work);

	//bool flush_delayed_work(struct work_struct *work)
	//wait for a dwork to finish executing the last queueing
	flush_delayed_work(&g_delay_work);
}

//--------------------- kthread ---------------------
#include <linux/wait.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sched.h>

wait_queue_head_t g_wait_q;
int g_flag = 0;

static int my_kthread(void *arg)
{
	int ret;
	
	pr_err("[hugo] my_kthread()\n");
	ret = wait_event_interruptible(g_wait_q, ((g_flag == 1) || kthread_should_stop()));
	pr_err("[hugo] my_kthread() wait_event_interruptible() ret=%d\n", ret);
	if (ret == -ERESTARTSYS) {
		pr_err("[hugo] my_kthread() wait_event_interruptible() return -ERESTARTSYS\n");
		return 0;
	}
	return 0;
}

static void set_kthread_to_cpux(struct task_struct *task)
{
	struct cpumask mask;

	cpumask_clear(&mask);
	//cpumask_set_cpu(0, &mask); //enable on CPU0
	//cpumask_set_cpu(1, &mask); //enable on CPU1
	cpumask_set_cpu(2, &mask); //enable on CPU2
	//cpumask_set_cpu(3, &mask); //enable on CPU3
	//int set_cpus_allowed_ptr(struct task_struct *p, const struct cpumask *new_mask)
	set_cpus_allowed_ptr(task, &mask);
}

static void kthread_example(void)
{
	struct task_struct *task;

	init_waitqueue_head(&g_wait_q);
	// "my_kthread" will appear in top
	task = kthread_run(my_kthread, NULL, "my_kthread");
	set_kthread_to_cpux(task);

	pr_err("[hugo] mdelay(1000) before 1\n");
	//use ndelay() that will cause build error
	mdelay(1000);
	pr_err("[hugo] mdelay(1000) after\n");
	g_flag = 1;
	wake_up_all(&g_wait_q);
}

//--------------------- sk_buff_head ---------------------
#include <linux/skbuff.h>
#include <linux/netdevice.h>

static void sk_buff_head_example(void)
{
	struct sk_buff_head skb_list;
	struct sk_buff *skb;

	//void skb_queue_head_init(struct sk_buff_head *list)
	skb_queue_head_init(&skb_list);

	//sk_buff *__dev_alloc_skb(unsigned int length, gfp_t gfp_mask)
	skb = __dev_alloc_skb(1662, GFP_KERNEL);
	if (skb == NULL) {
		pr_err("[hugo] __dev_alloc_skb() return NULL 1");
		return;
	}
	skb_queue_tail(&skb_list, skb);
	
	skb = __dev_alloc_skb(2048, GFP_ATOMIC);
	if (skb == NULL) {
		pr_err("[hugo] __dev_alloc_skb() return NULL 2");
		return;
	}
	skb_queue_tail(&skb_list, skb);

	pr_err("[hugo] skb_list.qlen=%d\n", skb_list.qlen); // 2

	skb = skb_dequeue(&skb_list);
	pr_err("[hugo] 1 skb->end=%d\n", skb->end); // 1728
	dev_kfree_skb_any(skb);
	
	skb = skb_dequeue(&skb_list);
	pr_err("[hugo] 2 skb->end=%d\n", skb->end); // 2112
	dev_kfree_skb_any(skb);

	pr_err("[hugo] skb_list.qlen=%d\n", skb_list.qlen); // 0
}

//--------------------- dma_mapping ---------------------
#include <linux/dma-mapping.h>

static void dma_mapping_example(struct device *dev)
{
	struct sk_buff *skb;
	dma_addr_t phy_addr;
	
	void *data = NULL;
	struct page *page = NULL;
	unsigned long offset;
	
	// ----------- dma_map_single -----------
	skb = __dev_alloc_skb(1662, GFP_KERNEL);
	if (skb == NULL) {
		pr_err("[hugo] __dev_alloc_skb() return NULL 1");
		return;
	}

	//dma_addr_t dma_map_single(struct device *dev, void *ptr, size_t size, enum dma_data_direction dir)
	phy_addr = dma_map_single(dev, skb->data, 1662, DMA_FROM_DEVICE);
	if (dma_mapping_error(dev, phy_addr)) {
		pr_err("[hugo] dma_map_single() dma_mapping_error() is true\n");
		goto exit;
	}
	pr_err("[hugo] dma_map_single() phy_addr=%llx\n", phy_addr);

	//void dma_unmap_single(struct device *dev, dma_addr_t addr, size_t size, enum dma_data_direction dir)
	dma_unmap_single(dev, phy_addr, 1662, DMA_FROM_DEVICE);

	// ----------- dma_map_page -----------
	//void *netdev_alloc_frag(unsigned int fragsz)
	//Allocates a frag from a page for receive buffer. Uses GFP_ATOMIC allocations.
	data = netdev_alloc_frag(1992);
	
	//struct page *virt_to_head_page(const void *x)
	page = virt_to_head_page(data);

	//void *page_address(const struct page *page)
	offset = data - page_address(page);
	pr_err("[hugo] page offset=%lu\n", offset);

	//dma_addr_t dma_map_page_attrs(struct device *dev, struct page *page, size_t offset, size_t size, enum dma_data_direction dir)
	phy_addr = dma_map_page(dev, page, offset, 1992, DMA_FROM_DEVICE);
	if (dma_mapping_error(dev, phy_addr)) {
		pr_err("[hugo] dma_map_page() dma_mapping_error() is true\n");
		goto exit;
	}
	pr_err("[hugo] dma_map_page() phy_addr=%llx\n", phy_addr);

	//void dma_unmap_page(struct device *dev, dma_addr_t addr, size_t size, enum dma_data_direction dir)
	dma_unmap_page(dev, phy_addr, 1992, DMA_FROM_DEVICE);
	
exit:
	dev_kfree_skb_any(skb);
	skb_free_frag(data);
}

//--------------------- atomic ---------------------
#include <asm/atomic.h>

void static atomic_example(void)
{
	atomic_t atomic;
	int ret;

	//int atomic_read(const atomic_t *v)
	atomic_set(&atomic, 0);
	pr_err("[hugo] atomic a=%d\n", atomic_read(&atomic));
	atomic_set(&atomic, -123);
	pr_err("[hugo] atomic a=%d\n", atomic_read(&atomic));
	atomic_set(&atomic, 456);
	pr_err("[hugo] atomic a=%d\n", atomic_read(&atomic));
	
	atomic_inc(&atomic); //457
	pr_err("[hugo] atomic a=%d\n", atomic_read(&atomic));

	//int atomic_dec_and_test(atomic_t *v)
	//returns true if the result is 0, or false for all other
	ret = atomic_dec_and_test(&atomic);
	pr_err("[hugo] atomic_dec_and_test()=%d a=%d\n", ret, atomic_read(&atomic)); //0, 456

	//int atomic_cmpxchg(atomic_t *v, int old, int new)
	//old: to compare with v
	//new: if v == old then v = new
	//return original v
	ret = atomic_cmpxchg(&atomic, 456, 200);
	pr_err("[hugo] atomic atomic_cmpxchg()=%d a=%d\n", ret, atomic_read(&atomic)); //456, 200
}

//--------------------- list_head ---------------------
typedef struct my_struct {
	int data1;
	struct list_head list;
	int data2;
} my_struct;

static void list_head_example(void)
{
	struct list_head my_list;
	struct my_struct my1;
	struct my_struct my2;

	// for traversal
	struct my_struct *my;
	struct list_head *act, *tmp;
	
	// ----------- inital -----------
	my1.data1 = 1;
	my1.data2 = 2;
	my2.data1 = 111;
	my2.data2 = 222;
	
	INIT_LIST_HEAD(&my_list);
	pr_err("[hugo] list_empty()=%d\n", list_empty(&my_list)); // 1

	// ----------- add -----------
	list_add(&my1.list, &my_list);
	list_add_tail(&my2.list, &my_list);
	pr_err("[hugo] list_empty()=%d\n", list_empty(&my_list)); // 0
	
	// ----------- traversal -----------
	list_for_each_safe(act, tmp, &my_list) {
		my = list_entry(act, struct my_struct, list);
		pr_err("[hugo] data1=%d data2=%d\n", my->data1, my->data2);
	}
	
	// ----------- delete all -----------
	list_for_each_safe(act, tmp, &my_list) {
		if (!act)
			continue;

		my = list_entry(act, struct my_struct, list);
		list_del(&my->list);
	}
	pr_err("[hugo] list_empty()=%d\n", list_empty(&my_list)); // 1
}

//--------------------- spin_lock ---------------------
#include <linux/spinlock.h>

static void spin_lock_example(void)
{
	spinlock_t lock;
	unsigned long flags;
	int ret;

	spin_lock_init(&lock);

	spin_lock(&lock);
	spin_unlock(&lock);

	spin_lock_irq(&lock);
	spin_unlock_irq(&lock);

	// recommend to use this one
	spin_lock_irqsave(&lock, flags);
	spin_unlock_irqrestore(&lock, flags);

	spin_lock_bh(&lock);
	spin_unlock_bh(&lock);

	//int spin_trylock(spinlock_t *lock)
	//return 1 means requiring the lock, 0 means not requiring the lock
	ret = spin_trylock(&lock);
	pr_err("[hugo] spin_trylock() ret=%d\n", ret); // 1
	ret = spin_trylock(&lock);
	pr_err("[hugo] spin_trylock() ret=%d\n", ret); // 0
	spin_unlock(&lock);
}
