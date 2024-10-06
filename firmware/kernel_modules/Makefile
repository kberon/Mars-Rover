obj-m += gpio_interface.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	# sudo insmod gpio_interface.ko

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	sudo rmmod gpio_interface.ko
