#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

//----------------------------------------------------------------
static irqreturn_t hugo_isr(int irq, void *dev)
{
	//this is in the interrupt context, don't use API which may cause the sleep
	pr_info("hugo_isr() irq=%d\n", irq);
	return IRQ_NONE;
	//@IRQ_NONE		interrupt was not from this device or was not handled
	//@IRQ_HANDLED		interrupt was handled by this device
	//@IRQ_WAKE_THREAD	handler requests to wake the handler thread
}

static void demo_interrupt_start(void)
{
	int ret;
	
	//static int request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags, const char *name, void *dev)
	ret = request_irq(19, hugo_isr, IRQF_SHARED, "hugo_isr", (void *)hugo_isr);
#if 0
/*
 * These flags used only by the kernel as part of the
 * irq handling routines.
 *
 * IRQF_SHARED - allow sharing the irq among several devices
 * IRQF_PROBE_SHARED - set by callers when they expect sharing mismatches to occur
 * IRQF_TIMER - Flag to mark this interrupt as timer interrupt
 * IRQF_PERCPU - Interrupt is per cpu
 * IRQF_NOBALANCING - Flag to exclude this interrupt from irq balancing
 * IRQF_IRQPOLL - Interrupt is used for polling (only the interrupt that is
 *                registered first in a shared interrupt is considered for
 *                performance reasons)
 * IRQF_ONESHOT - Interrupt is not reenabled after the hardirq handler finished.
 *                Used by threaded interrupts which need to keep the
 *                irq line disabled until the threaded handler has been run.
 * IRQF_NO_SUSPEND - Do not disable this IRQ during suspend.  Does not guarantee
 *                   that this interrupt will wake the system from a suspended
 *                   state.  See Documentation/power/suspend-and-interrupts.rst
 * IRQF_FORCE_RESUME - Force enable it on resume even if IRQF_NO_SUSPEND is set
 * IRQF_NO_THREAD - Interrupt cannot be threaded
 * IRQF_EARLY_RESUME - Resume IRQ early during syscore instead of at device
 *                resume time.
 * IRQF_COND_SUSPEND - If the IRQ is shared with a NO_SUSPEND user, execute this
 *                interrupt handler after suspending interrupts. For system
 *                wakeup devices users need to implement wakeup detection in
 *                their interrupt handlers.
 */
#endif
	pr_info("request_irq() ret=%d\n", ret);
}

static void demo_interrupt_stop(void)
{
	//void *free_irq(unsigned int, void *);
	free_irq(19, (void *)hugo_isr);
}

//----------------------------------------------------------------
static struct tasklet_struct tasklet;

static void hugo_tasklet(unsigned  long data)
{
	//this is in the interrupt context, don't use API which may cause the sleep
	pr_info("hugo_tasklet() data=%lu\n", data); //12345678
}

static void demo_tasklet_start(void)
{
	tasklet_init(&tasklet, hugo_tasklet, 12345678);
	
	tasklet_schedule(&tasklet);
}

static void demo_tasklet_stop(void)
{
	tasklet_kill(&tasklet);
}

//----------------------------------------------------------------

typedef struct my_struct {
	int data1;
	int data2;
	struct work_struct work;
} my_struct;

struct my_struct data;

static void hugo_workqueue(struct work_struct *w)
{
	struct my_struct *data = container_of(w, struct my_struct, work);
	//this is in the process context, can use API which may cause the sleep
	pr_info("hugo_workqueue() data1=%d data2=%d\n", data->data1, data->data2);
}

static void demo_workqueue_start(void)
{
	INIT_WORK(&data.work, hugo_workqueue);
	data.data1 = 1;
	data.data2 = 2;
	
	schedule_work(&data.work);
}

static void demo_workqueue_stop(void)
{
	flush_scheduled_work();
}
//----------------------------------------------------------------
static int hugo_init(void)
{
	pr_info("hugo_init ver=1.00");
	demo_interrupt_start();
	demo_tasklet_start();
	demo_workqueue_start();
	return 0;
}

static void hugo_exit(void)
{
	pr_info("hugo_exit\n");
	demo_interrupt_stop();
	demo_tasklet_stop();
	demo_workqueue_stop();
}

module_init(hugo_init);
module_exit(hugo_exit);

MODULE_LICENSE("GPL");
