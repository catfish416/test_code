obj-m := char_driver.o
CURRENT_PATH := $(shell pwd)
LINUX_KERNEL := $(shell uname -r)
#LINUX_KERNEL_PATH := /usr/src/linux-headers-$(LINUX_KERNEL)
LINUX_KERNEL_PATH := /home/wsj/share/code/nxp_git_code/kernel/linux

#ARCH:=arm

all:
	$(MAKE) -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
	mkdir out
	mv char_driver.ko $(CURRENT_PATH)/out/
	mkdir obj
	mv *.o *.mod.c *.order *.symvers .*.cmd obj

clean:
	rm -rf obj
	rm -rf .tmp_versions
	rm -rf out
