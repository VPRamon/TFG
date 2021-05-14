obj-m := poc_lkm.o

KVERSION = 5.4.117 #$(shell uname -r)
KDIR := /lib/modules/5.4.117/build
#KDIR := /home/jinbum/github/linux

ccflags-y += -DKCOV

default:
	$(MAKE) -C $(KDIR) M=$(shell pwd) modules

clean:
	rm -rf *.o *.ko *.mod *.symvers *.order *.mod.c .*cmd .tmp*
