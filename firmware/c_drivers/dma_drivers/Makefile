all:
	echo "This file needs sudo permissions and is auto-run by this makefile"
	#c++ -g main.cpp dma_drivers.cpp mailbox.c dma_mem.cpp -L/home/raspberry/Mars-Rover/firmware/c_drivers/gpio_drivers -lgpio_drivers -o dma_test2
	#sudo ./dma_test
	c++ -g main.cpp dma_drivers.cpp mailbox.c dma_mem.cpp -I/home/raspberry/Mars-Rover/firmware/c_drivers/gpio_drivers -L/home/raspberry/Mars-Rover/firmware/c_drivers/gpio_drivers -lgpio_drivers -o dma_test2

controller: 
	echo "This file needs sudo permissions and is auto-run by this makefile"
	#c++ -g controler.cpp dma_drivers.cpp mailbox.c dma_mem.cpp -L/home/raspberry/Mars-Rover/firmware/c_drivers/gpio_drivers -lgpio_drivers -o dma_test2
	#sudo ./dma_test
	c++ -g controller.cpp dma_drivers.cpp mailbox.c dma_mem.cpp -I/home/raspberry/Mars-Rover/firmware/c_drivers/gpio_drivers -L/home/raspberry/Mars-Rover/firmware/c_drivers/gpio_drivers -lgpio_drivers -o dma_test2