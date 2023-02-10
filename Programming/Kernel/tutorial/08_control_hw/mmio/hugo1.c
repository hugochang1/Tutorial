#include <linux/module.h>
#include <linux/init.h>
//#include <linux/io.h>

/*
$ sudo cat /proc/iomem 
  ...
  fed00000-fed003ff : pnp 00:04
  ...
*/

//void __iomem *ioremap(phys_addr_t paddr, unsigned long size);
//void __iomem *ioremap_nocache(resource_size_t offset, unsigned long size);
//void iounmap(volatile void __iomem *addr);

#define MEM_ADDR 0xfed00000
#define MEM_OFFSET 0x3ff

static void mmio_demo(void)
{
	char  __iomem *mem;

	mem = ioremap_nocache(MEM_ADDR, MEM_OFFSET);
	if (mem == NULL) {
		pr_info("ioremap_nocache() failed\n");
	} else {
		pr_info("ioremap_nocache() success %px\n", mem);
		mem[0] = 0x12;
		mem[1] = 0x24;
		mem[MEM_OFFSET - 1] = 0xff;
		pr_info("%x %x %x\n", mem[0] & 0xff, mem[1] & 0xff, mem[MEM_OFFSET - 1] & 0xff);
		
		iounmap(mem);
	}
}

//----------------------------------------------------------------
static int hugo_init(void)
{
	pr_info("hugo_init\n");
	mmio_demo();
	return 0;
}

static void hugo_exit(void)
{
	pr_info("hugo_exit\n");
}

module_init(hugo_init);
module_exit(hugo_exit);

MODULE_LICENSE("GPL");
