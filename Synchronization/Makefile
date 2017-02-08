obj-m += atomicmodule.o spinlockmodule.o kthread.o spinlock_problem.o
atomicmodule-objs := ./atomic.o
spinlockmodule-objs := spinlock.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
