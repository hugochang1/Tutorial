#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>
#include <linux/version.h>


//--------------------------------------------------------------
/*
$ cat /proc/hugo/file1 
start
hello world 123 !!!!

$ dmesg
[ 4136.283121] seq_start() pos=0
[ 4136.283122] seq_show()
[ 4136.283123] seq_next() pos=0
[ 4136.283123] seq_stop()
[ 4136.283140] seq_start() pos=1
[ 4136.283141] seq_stop()
*/
static void *seq_start(struct seq_file *m, loff_t *pos)
{
	loff_t n = *pos;

	pr_info("seq_start() pos=%lld\n", n);
	if (n == 0)
		return (void *)1;
	else
		return 0;
}

static void *seq_next(struct seq_file *m, void *p, loff_t *pos)
{
	loff_t n = *pos;

	pr_info("seq_next() pos=%lld\n", n);
	return 0;
}

static void seq_stop(struct seq_file *m, void *p)
{
	pr_info("seq_stop()\n");
}

static int seq_show(struct seq_file *m, void *p)
{
	pr_info("seq_show()\n");
	seq_printf(m, "start\n");
	seq_printf(m, "hello world %d %s\n", 123, "!!!!");
	return 0;
}

static struct seq_operations seq_op = {
	.start	= seq_start,
 	.next	= seq_next,
	.stop	= seq_stop,
	.show	= seq_show,
};

static int hugo_proc_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &seq_op);
}

static struct file_operations hugo_proc_ops = {
	.open = hugo_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = seq_release,
};

//--------------------------------------------------------------

#define PROC_FOLDER "hugo"
#define PROC_FILE1 "file1"

struct proc_dir_entry *dir;
struct proc_dir_entry *file1;
static int hugo_init(void)
{
	pr_info("hugo_init ver=1.02\n");
	dir = proc_mkdir(PROC_FOLDER, NULL);
	if (dir == NULL) {
		pr_info("proc_mkdir() failed\n");
	}

	file1 = proc_create(PROC_FILE1, 0444, dir, &hugo_proc_ops);
	if (file1 == NULL) {
		pr_info("proc_create() 1 failed\n");
	}
	return 0;
}

static void hugo_exit(void)
{
	pr_info("hugo_exit\n");
	
	 proc_remove(file1);
	 proc_remove(dir);
}

module_init(hugo_init);
module_exit(hugo_exit);

MODULE_LICENSE("GPL");
