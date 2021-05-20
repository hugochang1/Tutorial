int test_ktime(void) {
	ktime_t t1, t2;
	
	t1 = ktime_get();
	mdelay(1000);
	t2 = ktime_get();
	//ktime_add(t1, t2);
	t1 = ktime_sub(t2, t1);
	pr_err("hugo ktime_to_ms()=%lld\n", ktime_to_ms(t1));
	pr_err("hugo ktime_to_us()=%lld\n", ktime_to_us(t1));
	pr_err("hugo ktime_to_ns()=%lld\n", ktime_to_ns(t1));
	//[ 2103.567391] <3>.(3)[13967:insmod]hugo ktime_to_ms()=1023
	//[ 2103.568076] <3>.(3)[13967:insmod]hugo ktime_to_us()=1023285
	//[ 2103.568782] <3>.(3)[13967:insmod]hugo ktime_to_ns()=1023285231
	return 0;
}
