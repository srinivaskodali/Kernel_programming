#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


#include <linux/kthread.h>
#include <linux/delay.h>

struct task_struct *thread;
int thread_1 (void *);

int thread_1 (void *a) {
	allow_signal(SIGKILL);
	while(!kthread_should_stop()) {
		printk("I'm in thread1\n");
		ssleep(5);
		if(signal_pending(current)) {
				printk("thread1 received signal\n");
				thread = NULL;
				break;
		}	
	}
		printk("thread1 exited\n");
	return 0;
}

static int kinit(void) {
	thread = kthread_create (thread_1, NULL, "thread_1");
	if (thread) {
		printk("thread created\n");
//		wake_up_process(thread);
	}
	else
		printk("thread creation failed\n");

	return 0;
}

static void  kunint(void) {
		if(thread) {
//			kthread_stop (thread);
		}
		printk("unregisterd kthread1\n");
}

module_init(kinit);
module_exit(kunint);

MODULE_LICENSE("GPL");
