obj-m += test_module.o

KBUILD_CFLAGS += -z execstack

PWD       := $(shell pwd)


#all:
#	make -C /lib/modules/$(shell uname -r)/build SUBDIRS=$(shell pwd) modules
all:
	make -C /lib/modules/5.4.117/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	# We put a — in front of the rmmod command to tell make to ignore
	# an error in case the module isn’t loaded.
	-sudo rmmod lkm_example
	# Clear the kernel log without echo
	sudo dmesg -C
	# Insert the module
	sudo insmod lkm_example.ko
	# Display the kernel log
	dmesg

depend .depend dep:
	$(CC) $(KBUILD_CFLAGS) -M *.c > .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif
