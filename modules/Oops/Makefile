obj-m   := oops.o 
KDIR    := /lib/modules/$(shell uname -r)/build
PWD     := $(shell pwd) 
SYM=$(PWD) 
 
all: 
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	for n in $(SUBDIRS); do $(MAKE) -C $$n clean; done
