#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dov & Daniel");
MODULE_DESCRIPTION("A simple example kernel module with parameter.");
MODULE_VERSION("1.1");

static char* msg = "World";
module_param(msg, charp, S_IRUSR | S_IWUSR);

static int __init lkm_example_init(void) {
	printk(KERN_INFO "%s\n", msg);
	return 0;
}

static void __exit lkm_example_exit(void) {
	printk(KERN_INFO "Goodbye world!\n");
}

module_init(lkm_example_init);
module_exit(lkm_example_exit);
