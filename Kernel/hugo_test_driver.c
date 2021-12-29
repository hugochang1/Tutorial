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
