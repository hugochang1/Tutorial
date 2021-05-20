static int hugo_param = 123;
module_param(hugo_param, int, 0644);
MODULE_PARM_DESC(tx_wakeup_threshold, "hugo test param");

/sys/module/hugo_drv/parameters/hugo_param
