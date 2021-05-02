TARGET_CFLAGS ==-Wno-error
obj-m += testing_module.o
all:
		CFLAGS=-Wno-error
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
		CFLAGS=-Wno-error
clean:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
