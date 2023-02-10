# Source Code
````
#include <linux/module.h>
#include <linux/init.h>

//cat /sys/module/hugo/parameters/aaa
//echo 123 | sudo tee /sys/module/hugo/parameters/aaa
static int aaa = 0;
module_param(aaa, int, 0644);
MODULE_PARM_DESC(aaa, "this is aaa's description");

static int bbb = 0;
module_param(bbb, uint, 0644);

static char *ccc= "default";
module_param(ccc, charp, 0644);

static int hugo_init(void)
{
	pr_info("hugo_init\n");
	pr_info("hugo aaa=%d\n", aaa);
	pr_info("hugo bbb=%d\n", bbb);
	pr_info("hugo ccc=%s\n", ccc);
	return 0;
}
````

# modinfo
- `$ modinfo hugo.ko`
````
filename:       /home/hugo/work/driver/03_module_param/hugo.ko
license:        GPL
srcversion:     268B65F7441AC8CB4A5C92A
depends:        
retpoline:      Y
name:           hugo
vermagic:       5.4.174 SMP mod_unload modversions 
parm:           aaa:this is aaa's description (int)
parm:           bbb:uint
parm:           ccc:charp
````

# insmod with the assigned values
- `$ sudo insmod hugo.ko aaa=-123 bbb=345 ccc=hello`
- `$ dmesg | tail`
````
[ 5584.114469] hugo_init
[ 5584.114470] hugo aaa=-123
[ 5584.114470] hugo bbb=345
[ 5584.114470] hugo ccc=hello
````

# modify the module_param in runtime
- read `$ cat /sys/module/hugo/parameters/aaa`
- modify `$ echo 123 | sudo tee /sys/module/hugo/parameters/aaa`
