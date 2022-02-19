#include <linux/module.h>
#include <linux/init.h>
#include <linux/ioport.h>

/*
$ sudo cat /proc/ioports
  4000-4fff : PCI Bus 0000:03
  5000-5fff : PCI Bus 0000:0b
  6000-6fff : PCI Bus 0000:13
  7000-7fff : PCI Bus 0000:1b
  8000-8fff : PCI Bus 0000:04
  9000-9fff : PCI Bus 0000:0c
  a000-afff : PCI Bus 0000:14
  b000-bfff : PCI Bus 0000:1c
  c000-cfff : PCI Bus 0000:05
  d000-dfff : PCI Bus 0000:0d
  e000-efff : PCI Bus 0000:15
  fce0-fcff : pnp 00:06
*/
#define IO_ADDR 0xfce0
#define IO_SIZE 0xf

static void reset_io(void)
{
	//clear
	outb(0, IO_ADDR);
	outw(0, IO_ADDR);
	outl(0, IO_ADDR);
}

static void demo_io_read_write(void)
{
	/*
	[ 5942.066929] ---------- ioport read ----------
	[ 5942.066939] inb()=0
	[ 5942.066948] inw()=0
	[ 5942.066957] inl()=0
	[ 5942.066957] ---------- ioport write ----------
	[ 5942.066974] inb()=12
	[ 5942.066992] inw()=3456
	[ 5942.067009] inl()=87654321
	[ 5942.067034] ---------- ioport read pause ----------
	[ 5942.067042] inb_p()=0
	[ 5942.067051] inw_p()=0
	[ 5942.067060] inl_p()=0
	[ 5942.067060] ---------- ioport read pause ----------
	[ 5942.067077] inb_p()=12
	[ 5942.067094] inw_p()=3456
	[ 5942.067111] inl_p()=87654321
	*/
	if (request_region(IO_ADDR, IO_SIZE, "hugo") == NULL) {
		pr_info("request_region() failed\n");
	}
	
	reset_io();
	
	pr_info("---------- ioport read ----------\n");
	pr_info("inb()=%u\n", inb(IO_ADDR));  //u8
	pr_info("inw()=%u\n", inw(IO_ADDR)); //u16
	pr_info("inl()=%u\n", inl(IO_ADDR));  //u32

	pr_info("---------- ioport write ----------\n");
	outb(12, IO_ADDR);
	pr_info("inb()=%u\n", inb(IO_ADDR));
	outw(3456, IO_ADDR);
	pr_info("inw()=%u\n", inw(IO_ADDR));
	outl(87654321, IO_ADDR);
	pr_info("inl()=%u\n", inl(IO_ADDR));
	
	reset_io();
	
	pr_info("---------- ioport read pause (wait the device) ----------\n");
	pr_info("inb_p()=%u\n", inb_p(IO_ADDR));  //u8
	pr_info("inw_p()=%u\n", inw_p(IO_ADDR)); //u16
	pr_info("inl_p()=%u\n", inl_p(IO_ADDR));  //u32
	
	pr_info("---------- ioport read pause (wait the device) ----------\n");
	outb_p(12, IO_ADDR);
	pr_info("inb_p()=%u\n", inb_p(IO_ADDR));
	outw_p(3456, IO_ADDR);
	pr_info("inw_p()=%u\n", inw_p(IO_ADDR));
	outl_p(87654321, IO_ADDR);
	pr_info("inl_p()=%u\n", inl_p(IO_ADDR));
	
	reset_io();
	
	release_region(IO_ADDR, IO_SIZE);
}

//----------------------------------------------------------------
static int hugo_init(void)
{
	pr_info("hugo_init ver=1.02\n");
	demo_io_read_write();

	return 0;
}

static void hugo_exit(void)
{
	pr_info("hugo_exit\n");
}

module_init(hugo_init);
module_exit(hugo_exit);

MODULE_LICENSE("GPL");
