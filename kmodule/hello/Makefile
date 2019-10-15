ifneq ($(KERNELRELEASE),)
	obj-m := k_module.o
else
CURRENT_PATH := $(shell pwd)
#LINUX_KERNEL_PATH := /usr/src/linux-headers-$(shell uname -r)
LINUX_KERNEL_PATH := /home/hp/code/nxp_git_code/kernel/linux-4.1.26_bsp14.0
#LINUX_KERNEL_PATH := /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
	mkdir out
	mv k_module.ko $(CURRENT_PATH)/out/
	mkdir obj
	mv *.o *.mod.c *.order *.symvers .*.cmd obj

endif
clean:
	rm -rf obj
	rm -rf .tmp_versions
	rm -rf out
