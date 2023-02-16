obj-m := hello.o
KERNELDIR := /lib/modules/$(shell uname -r)/build    
PWD := $(shell pwd)  
  
modules:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules  
  
clean:
		rm -rf *.o *.mod.c *.ko *.symvers *.order *.makers
		#rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions Module* modules*
	
.PHONY: modules modules_install clean  
