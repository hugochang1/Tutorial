struct delayed_work hugo_delay_w1;
 
static void process_hugo_delay_work1(struct work_struct *work)
{
    pr_err("process_hugo_delay_work1()\n");
}
 
 
static int hugo_init(void)
{
    INIT_DELAYED_WORK(&hugo_delay_w1, process_hugo_delay_work1);
 
    // bool schedule_delayed_work_on(int cpu, struct delayed_work *dwork, unsigned long delay)
    // @cpu: cpu to use (0~NR_CPUS)
    // @dwork: job to be done
    // @delay: number of jiffies to wait
    schedule_delayed_work_on(1, &hugo_delay_w1, 0); //cpu_id , delayed_work, delay_time_in_jiff
}
 
static void hugo_exit(void)
{
    cancel_delayed_work_sync(&hugo_delay_w1);
}
