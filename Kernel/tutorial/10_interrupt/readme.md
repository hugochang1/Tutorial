# source code
````
#include <linux/interrupt.h>

static irqreturn_t hugo_isr(int irq, void *dev)
{
	pr_info("hugo_isr() irq=%d\n", irq);
	return IRQ_NONE;
}


static int hugo_init(void)
{
	ret = request_irq(19, hugo_isr, IRQF_SHARED, "hugo_isr", (void *)hugo_isr);
	return 0;
}

static void hugo_exit(void)
{
	free_irq(19, (void *)hugo_isr);
}

module_init(hugo_init);
module_exit(hugo_exit);
````

- `$ cat /proc/interrupts`
````
            CPU0       CPU1       CPU2       CPU3       CPU4       CPU5       CPU6       CPU7       CPU8       CPU9       CPU10      CPU11      
  19:          0          0          0          0          0          0          0          0          0         71          0       2130   IO-APIC   19-fasteoi   ens33
````

- `$ sudo insmod hugo.ko`
- `$ cat /proc/interrupts`
````
            CPU0       CPU1       CPU2       CPU3       CPU4       CPU5       CPU6       CPU7       CPU8       CPU9       CPU10      CPU11      
  19:          0          0          0          0          0          0          0          0          0         71          0       2165   IO-APIC   19-fasteoi   ens33, hugo_isr
````


- `$ sudo rmmod hugo.ko`
- `$ cat /proc/interrupts`
````
            CPU0       CPU1       CPU2       CPU3       CPU4       CPU5       CPU6       CPU7       CPU8       CPU9       CPU10      CPU11      
  19:          0          0          0          0          0          0          0          0          0         71          0       2130   IO-APIC   19-fasteoi   ens33
````
