obj-m := D4p1.o

KERNELDIR = /lib/modules/$(shell uname -r)/build

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o D4p1_app D4p1_app.c
	
install: 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm D4p1_app


