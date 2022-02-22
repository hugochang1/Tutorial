#include <linux/module.h>
#include <linux/init.h>

//-------------------------------------------------------------------------------------------
static void demo_atomic(void)
{
	atomic_t a = ATOMIC_INIT(0);
	int b;
	
	//atomic operation
	pr_info("a=%d\n", atomic_read(&a)); // 0
	atomic_set(&a, 0); //a=0
	atomic_inc(&a); //a=1
	atomic_dec(&a); //a=0
	b = atomic_dec_and_test(&a); //a=-1 and return (a==0)
	pr_info("b=%d\n", b); //0
	
	atomic_add(3, &a); //a=2
	atomic_sub(1, &a); //a=1
	pr_info("a=%d\n", atomic_read(&a)); 
	b = atomic_sub_and_test(1, &a); //a=0 and return (a==0)
	pr_info("b=%d\n", b); //1
	b = atomic_inc_and_test(&a); //a=1 and return (a==0)
	pr_info("b=%d\n", b); //0
}

//-------------------------------------------------------------------------------------------
static void demo_atomic_bitops(void)
{
	volatile unsigned long reg = 0x0;
	int ret;
	
	set_bit(3, &reg); //0x8
	clear_bit(3, &reg); //0x0
	change_bit (2, &reg); //0x4
	change_bit (2, &reg); //0x0
	ret = test_and_set_bit(1, &reg);  //return the original bit value=0 of reg and reg=0x2
	ret = test_and_clear_bit(1, &reg); //return the original bit value of reg=1 and reg=0x0
	ret = test_and_change_bit(0, &reg); //return theoriginal bit value of reg=0 and reg=0x1
	pr_info("reg=0x%lx\n", reg); 
	pr_info("ret=%d\n", ret);
	
}

//-------------------------------------------------------------------------------------------
#include <linux/completion.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static struct completion comp;
static wait_queue_head_t wait;
static struct task_struct *task;

static int hugo_thread(void *arg)
{
	pr_info("hugo_thread() arg=%px\n", arg); //NULL
	mdelay(500);
	pr_info("complete_and_exit()\n");
	complete_and_exit(&comp, 0);
	
	return 0;
}

static void demo_completion(void)
{
	init_completion(&comp);
	init_waitqueue_head(&wait);
	task = kthread_run(hugo_thread, NULL, "hugo_thread");

	pr_info("wait_for_completion() before\n");
	wait_for_completion(&comp);
	pr_info("wait_for_completion() after\n");
	/*
	[   74.618656] wait_for_completion() before
	[   74.618666] hugo_thread() arg=0000000000001234
	[   75.114893] complete_and_exit()
	[   75.114938] wait_for_completion() after
	*/
	//wait_for_completion() must be called before complete_and_exit(), or wait_for_completion() will be blocked forever
	//we can use  wait_for_completion_timeout to avoid blocking forever
	//unsigned long wait_for_completion_timeout(struct completion *x, unsigned long timeout);
}

//-------------------------------------------------------------------------------------------
static void demo_mutex(void)
{
	struct mutex mutex;
	
	mutex_init(&mutex);
	
	mutex_lock(&mutex);
	mutex_unlock(&mutex);
}

//-------------------------------------------------------------------------------------------
static int hugo_kthread(void *arg)
{
	pr_info("hugo_kthread() arg=%px\n", arg); // NULL
	
	while (!kthread_should_stop()) {
		pr_info("hugo_kthread()\n");
		mdelay(500);
	}
	pr_info("hugo_kthread() exit\n");
	return 0;
}

static struct task_struct *ktask = NULL;

static void demo_kthread(void)
{
# if 0
	ktask = kthread_create(hugo_kthread, NULL, "hugo_kthread");
	if (IS_ERR(ktask)) {
		pr_err("kthread_create() failed\n");
		//return PTR_ERR(ktask);
		return;
	}
	wake_up_process(ktask); //to start the thread
#else
	ktask = kthread_run(hugo_kthread, NULL, "hugo_kthread");
	if (IS_ERR(ktask)) {
		pr_err("kthread_run() failed\n");
		//return PTR_ERR(ktask);
		return;
	}
#endif
	mdelay(2000);
	kthread_stop(ktask);
}

//-------------------------------------------------------------------------------------------

static void demo_spinlock(void)
{
	unsigned long flags;
	spinlock_t lock;
	
	spin_lock_init(&lock);
	
	spin_lock(&lock); //get lock
	spin_unlock(&lock);
	
	pr_info("spin_trylock()=%d\n", spin_trylock(&lock)); //1
	pr_info("spin_trylock()=%d\n", spin_trylock(&lock)); //0
	spin_unlock(&lock);
	
	spin_lock_irqsave(&lock, flags); //get lock + disable local processor interrupt 
	spin_unlock_irqrestore(&lock, flags);
	
	//do not suggest to use this, because we didn't know whether interrupt is disabled or not
	spin_lock_irq(&lock); //get lock + disable local processor interrupt
	spin_unlock_irq(&lock);
}
//-------------------------------------------------------------------------------------------
static int hugo_init(void)
{
	pr_info("hugo_init ver=1.01\n");
	demo_atomic();
	demo_atomic_bitops();
	demo_completion();
	demo_mutex();
	demo_kthread();
	demo_spinlock();
	
	return 0;
}

static void hugo_exit(void)
{
	pr_info("hugo_exit\n");
}

module_init(hugo_init);
module_exit(hugo_exit);

MODULE_LICENSE("GPL");
