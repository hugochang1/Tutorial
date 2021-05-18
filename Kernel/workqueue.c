struct work_struct  hugo_work1;
 
//workqueue function is called when queue_work() is called
static void process_hugo_work1(struct work_struct *work)
{
    pr_err("process_hugo_work1()");
}
 
static int hugo_init(void)
{  
    hugo_wq1  = create_singlethread_workqueue("hugo_wq1");
    if(!hugo_wq1) {
        pr_err("hugo create_singlethread_workqueue(hugo_wq1) failed");
        ret = -ENOMEM;
    }
 
    INIT_WORK(&hugo_work1, process_hugo_work1);
 
    //start run work queue once
    queue_work(hugo_wq1, &hugo_work1);
}
 
static void hugo_exit(void)
{
    destroy_workqueue(hugo_wq1);
}
 
module_init(hugo_init);
module_exit(hugo_exit);
