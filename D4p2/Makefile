
obj-m := D4p2.o

KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)

default :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o D4p2_app D4p2_app.c

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm D4p2_app
