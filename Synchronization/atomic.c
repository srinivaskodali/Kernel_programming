/*
Copyright (C) 2017  Srinivas Kodali
See Copying in root directory for licensing information
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <asm/atomic.h>


static int init_atomic(void);
static void exit_module(void);

module_init(init_atomic);
module_exit(exit_module);

static int init_atomic(void)
{
		atomic_t atomic_variable = ATOMIC_INIT(0);
	//	atomic_t *ptrble = ATOMIC_INIT(0);
		int result = 0;
		
		printk("\natomic module successfully registered\n");

		printk("first value of atomic_variable is = %d\n",atomic_read(&atomic_variable));

		atomic_set(&atomic_variable, 5);
		printk("after setting, value of atomic_variable is = %d\n",atomic_read(&atomic_variable));

		atomic_add(2,&atomic_variable);
		printk("after adding 2 to atomic_variable = %d \n",atomic_read(&atomic_variable));

		atomic_sub(2,&atomic_variable);
		printk("after subtracting 2 from atomic_variable = %d \n",atomic_read(&atomic_variable));

		atomic_inc(&atomic_variable);
		printk("after incrementing the atomic_variable = %d\n",atomic_read(&atomic_variable));

		atomic_dec(&atomic_variable);
		printk("after decrementing the atomic_variable = %d\n",atomic_read(&atomic_variable));

		result = atomic_sub_and_test(2, &atomic_variable);
		printk("return value after decrementing is = %d, and atomic_variable is = %d\n", result, atomic_read(&atomic_variable));

		result = atomic_add_negative( -9, &atomic_variable);
		printk("return value after adding -9 is = %d, and atomic_variable is = %d\n", result, atomic_read(&atomic_variable));


		result = atomic_add_return( 17, &atomic_variable);
		printk("return value after adding 17 is = %d, and atomic_variable is = %d\n", result, atomic_read(&atomic_variable));

		result = atomic_sub_return( 7, &atomic_variable);
		printk("return value after subtracting 7 is = %d, and atomic_variable is = %d\n", result, atomic_read(&atomic_variable));

		result = atomic_dec_and_test( &atomic_variable);
		printk("return value after decrementing is = %d, and atomic_variable is = %d\n", result, atomic_read(&atomic_variable));


		atomic_set(&atomic_variable, 33554431);
		printk("after decrementing the atomic_variable = %d\n",atomic_read(&atomic_variable));
		printk("size of atomic_variable is = %d\n", sizeof(&atomic_variable));
		return 0;
}
static void exit_module(void)
{
		printk("\natomic module successfully unregistered\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Srinivas Kodali");
MODULE_DESCRIPTION("A Sample program on atomic variables");


