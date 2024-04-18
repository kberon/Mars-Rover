Repo for parts for the MIL Rover

<img width="394" alt="Old Rover CAD Screenshot" src="https://github.com/amcaleer271/Mars-Rover/assets/93012410/63f4e23b-9c5b-4e58-aedf-c8c5b46f9684">

contact: adammcaleer@ufl.edu

## Project Architecture
<img width="700" alt="Iamge overview" src="https://github.com/kberon/Mars-Rover/assets/115107058/b77744f1-999a-49fe-8464-b7bfb6649720">

### Finished tasks
Firmware has a build system using wiringPI as a HAL for c++ finished, along with a build system for assembly. <br>
The basics of the drivers for PWM are done under the motors directory, and drivers for an IMU and BME280 are available under a secondary branch.<br>
<br>
Our high level software team has finished configuring ROS for our external computer nodes, and have dived into the details of ROS through toturials.<br>
<br>
Additionally, the team has dived into the battery monitor board design, and details of the future voltage dividing procedure.<br>
<br>
The team has also spent a great deal of time researching and buying parts. Included in the documentation directory are details on that procedure, especailly for the motor selection<br>
<br>
We encourage you to explore the repo and read the subdirectory README's and the different available documentation

## Bugs
Firmware bugs are as follows: as of right now software PWM is extremely buggy, however a warning is presented when they need to be utilized by our motor drivers.<br>
We additonally have some minor bugs in our IMU and BME280 drivers, with functionality being questionable due to a lack of dev boards currently being on hand, and not having the IMU and DME280 <br>
to interact with directly yet.

## Raspberry Pi Control
On UF wifi, use 
```
ssh raspberry@10.138.203.107
```
to log into the raspberry pi. The password is pi.pi
