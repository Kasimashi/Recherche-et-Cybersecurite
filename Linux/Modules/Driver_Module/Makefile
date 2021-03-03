obj-m += gpio_driver.o
default:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	rm -rf *.o *.ko *.mod.* *.mod modules.* Module.*

