#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>
//#include <linux/signal.h>

int thread_1(void *);
int thread_2(void *);
static struct task_struct *thread1, *thread2;

static int i;
int thread_1(void *a) {

	while(!kthread_should_stop()) {
		printk("thread_1 is running\n");
			i++;
		ssleep(2);
	}
	printk(KERN_INFO "thread 1 exited\n");
	do_exit(0);
	return 0;
}

int  thread_2(void *a) {
	/* TODO without allow_signal*/
	/*allow SIG_KILL signal to kill this thread. void allow_signal(int)*/
	allow_signal(SIGKILL);
	printk(KERN_INFO "Value of i is %d\n", i);
	
	/*int kthread_should_stop(void). returns an integer if kthread_stop invoked*/
	/* TODO without kthread_should_stop*/
	while(!kthread_should_stop()) {
		printk("thread_2 is running\n");
			i++;
		ssleep(2);
		/*int signal_pending(task_struct *). returns a non zero integer if pending for signal*/
		if(signal_pending(current)) {
			printk("received signal. terminating the thread\n");
			break;
		}
	}
	printk(KERN_INFO "thread 2 exited\n");
	do_exit(0);
	return 0;
}

static int __init kernel_thread_init(void)
{
    printk(KERN_INFO "Creating Thread\n");
    /*Create and wake up kernel threads*/
    thread1 = kthread_run(thread_1, NULL, "thread_1");

	/*TODO what will happen if the names of two threds are equal*/
    thread2 = kthread_run(thread_2, NULL, "thread_2");
    if (thread1)
        printk(KERN_INFO "Thread_1 Created successfully\n");
    else
        printk(KERN_ERR "Thread creation failed\n");

    if (thread2)
        printk(KERN_INFO "Thread_2 Created successfully\n");
    else
        printk(KERN_ERR "Thread creation failed\n");

    return 0;
}

static void __exit kernel_thread_cleanup(void)
{
	printk(KERN_INFO "Value of i is %d\n", i);
   if (thread1) {
	/* TODO without kthread_stop*/
       kthread_stop(thread1);
       printk(KERN_INFO "Thread 1 stopped\n");
   }
   if (thread2) {
       kthread_stop(thread1);
       printk(KERN_INFO "Thread 2 stopped\n");
   }
}
MODULE_LICENSE("GPL");
module_init(kernel_thread_init);
module_exit(kernel_thread_cleanup);
