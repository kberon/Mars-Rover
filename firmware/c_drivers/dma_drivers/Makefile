all:
	echo "This file needs sudo permissions and is auto-run by this makefile"
	#c++ -g main.cpp dma_drivers.cpp mailbox.c dma_mem.cpp -L/home/raspberry/Mars-Rover/firmware/c_drivers/gpio_drivers -lgpio_drivers -o dma_test2
	#sudo ./dma_test
	c++ -g main.cpp dma_drivers.cpp mailbox.c dma_mem.cpp -I/home/raspberry/Mars-Rover/firmware/c_drivers/gpio_drivers -L/home/raspberry/Mars-Rover/firmware/c_drivers/gpio_drivers -lgpio_drivers -o dma_test2

controller: controller.cpp
	echo "This file needs sudo permissions and is auto-run by this makefile"
	c++ -g controller.cpp dma_drivers.cpp mailbox.c dma_mem.cpp -I/home/raspberry/Mars-Rover/firmware/c_drivers/gpio_drivers -L/home/raspberry/Mars-Rover/firmware/c_drivers/gpio_drivers -lgpio_drivers -o controller
unit_test: unit_test.cpp
	c++ -g controller.cpp dma_drivers.cpp mailbox.c dma_mem.cpp -I/home/raspberry/Mars-Rover/firmware/c_drivers/gpio_drivers -L/home/raspberry/Mars-Rover/firmware/c_drivers/gpio_drivers -lgpio_drivers -o unit_test
