/*
Copyright (C) 2017  Srinivas Kodali
See Copying in root directory for licensing information
*/

#include <linux/init.h>
#include <linux/module.h>
#include <asm/spinlock.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Srinivas Kodali");
MODULE_DESCRIPTION("A Sample program on spin locks");

//aproach 1
//static spinlock_t my_lock1 = SPIN_LOCK_UNLOCKED;

//aproach 2
DEFINE_SPINLOCK(my_lock);

int thread_1(void *);
int thread_2(void *);
static struct task_struct *thread1, *thread2;

static int i;
int thread_1(void *a) {

		int j = 0;
		for(j=0; j< 100000 ; j++) {
				spin_lock(&my_lock);
				i++;
				spin_unlock(&my_lock);
				printk(KERN_INFO "Value of i is %d\n", i);
				ssleep(1);
				if(kthread_should_stop()) 
						break;
		}
		printk(KERN_INFO "thread 1 stopeed\n");
		do_exit(0);
		return 0;
}

int  thread_2(void *a) {
		int j = 0;
		int ret=0;

		for(j=0; j< 100000 ; j++) {

				ret=spin_trylock(&my_lock);
				if(!ret) {
						printk(KERN_INFO "Unable to hold lock");
				} else {
						i++;
						printk(KERN_INFO "Lock acquired");
						spin_unlock(&my_lock);
				}
				printk(KERN_INFO "Value of i is %d\n", i);
				ssleep(1);
				if(kthread_should_stop()) 
						break;
		}
#if 0
#endif
		printk(KERN_INFO "thread 2 stopeed\n");
		do_exit(0);
		return 0;
}
static int spinlock_init(void) {

	printk(KERN_INFO "spinlock module registerd\n");
	thread1 = kthread_create(thread_1, NULL, "thread1");
	thread2 = kthread_create(thread_2, NULL, "thread2");
	if((thread1))
	{
			wake_up_process(thread1);
	}

	if((thread2))
	{
			wake_up_process(thread2);
	}

	return 0;
}

static void spinlock_uninit(void) {

	printk(KERN_INFO "Value of i is %d\n", i);

	kthread_stop (thread1);
	kthread_stop (thread2);
	printk(KERN_INFO "spinlock module unregisterd\n");

}

module_init(spinlock_init);
module_exit(spinlock_uninit);
