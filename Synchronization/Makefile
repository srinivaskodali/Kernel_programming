obj-m = atomicmodule.o spinlockmodule.o kthread.o spinlock_problem.o Helloworld.o kthread2.o
atomicmodule-objs := ./atomic.o
spinlockmodule-objs := spinlock.o
kthread2-objs := kthread1.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
