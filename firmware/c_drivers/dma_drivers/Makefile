all:
	echo "This file needs sudo permissions and is auto-run by this makefile"
	c++ -g dma_drivers.cpp mailbox.c dma_mem.cpp -o dma_test
	sudo ./dma_test
