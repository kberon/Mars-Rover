Repo for parts for the MIL Rover

<img width="394" alt="Old Rover CAD Screenshot" src="https://github.com/amcaleer271/Mars-Rover/assets/93012410/63f4e23b-9c5b-4e58-aedf-c8c5b46f9684">

contact: adammcaleer@ufl.edu

## Project Architecture
<img width="700" alt="Iamge overview" src="https://github.com/kberon/Mars-Rover/assets/115107058/b77744f1-999a-49fe-8464-b7bfb6649720">

### Finished tasks
Firmware has somewhat shifted away from a build system using wiringPI as a HAL for c++ - have moved towards a build system for assembly and C for performance. <br>
The basics of the drivers for PWM are done under the c_drivers directory, and drivers for an IMU and BME280 are available under the main branch now.<br>
We have now also added configurations for sonar in the form of a kernel interrupt - this being done once again in hopes of better performance<br>
<br>
Our high level software team has finished configuring ROS for our external computer nodes, and have dived into the details of ROS through toturials.<br>
<br>
Additionally, the team has dived into the battery monitor board design, and details of the future voltage dividing procedure.<br>
<br>
The team has also spent a great deal of time researching and buying parts. Included in the documentation directory are details on that procedure, especailly for the motor selection<br>
<br>
We encourage you to explore the repo and read the subdirectory README's and the different available documentation

## Bugs
Firmware bugs are as follows: PWM through DMA drivers needs to become a persistant object to capture memory leaks - otherwise causes issues when run multiple times<br>
Our sonar modules work independently, but need some kind of daisychaning or internal delays to prevent interference with one another.

## Set up to run:
1. Load the gpio_interface module for PWM
```
cd /Mars-Rover/firmware/kernel_modules/
sudo insmod gpio_interface.ko
```