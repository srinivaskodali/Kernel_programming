#include <linux/kernel.h>
#include <linux/module.h>

static int Hello_init(void) {
	printk ("WelCome to Mirafra world....\n");
	return 0;
}

static void Hello_unint(void) {
	printk ("Bye Mirafra world...!\n");
}

module_init(Hello_init);
module_exit(Hello_unint);

MODULE_LICENSE("GPL");
