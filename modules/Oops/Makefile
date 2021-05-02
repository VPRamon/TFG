obj-m   := oops.o 
KDIR    := /lib/modules/$(shell uname -r)/build
PWD     := $(shell pwd) 
SYM=$(PWD) 
 
all: 
	$(MAKE) -C $(KDIR) M=$(PWD) modules
