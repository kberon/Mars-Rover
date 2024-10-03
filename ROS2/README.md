# Rover Project with ROS2

## Overview
This project implements a rover robot controlled using ROS2 nodes, with two modes: manual and autonomous. The rover can be controlled via a game controller in manual mode, or operate autonomously based on sensor readings in autonomous mode. The project integrates various sensors and actuators to achieve this, including a camera for color detection and IMU (Inertial Measurement Unit) for movement sensing.

### Nodes and Their Functions

1. **Sensor Reader Node (`sensor_reader_node`)**:
    - **Package**: `sensor_reader`
    - **Language**: C++
    - **Function**: Reads data from the BME280 (temperature, humidity, pressure) and ISM330DHCX (gyro, accelerometer) sensors and publishes these readings to ROS topics.
    - **Published Topics**:
        - `/temperature` - Temperature data from BME280.
        - `/humidity` - Humidity data from BME280.
        - `/pressure` - Pressure data from BME280.
        - `/gyro` - Gyroscope data from ISM330DHCX.
        - `/accel` - Accelerometer data from ISM330DHCX.

2. **Game Controller Node (`joystick_controller_node`)**:
    - **Package**: `rover_control`
    - **Language**: Python
    - **Function**: Reads input from a game controller and publishes movement commands to the `/cmd_vel` topic when in manual mode. The node also toggles between manual and autonomous modes.
    - **Subscribed Topics**:
        - `/joy` - Joystick input (provided by the `joy` package).
    - **Published Topics**:
        - `/cmd_vel` - Command velocities for rover movement.

3. **Motor Control Node (`motor_control_node`)**:
    - **Package**: `rover_control`
    - **Language**: Python
    - **Function**: Controls the motors of the rover based on joystick input in manual mode or based on sensor data in autonomous mode. It subscribes to both joystick and sensor data to decide how to move the rover.
    - **Subscribed Topics**:
        - `/joy` - Joystick input for manual mode.
        - `/gyro` - Gyroscope data for determining movement in autonomous mode.
    - **Published Topics**:
        - `/cmd_vel` - Command velocities for rover movement.

4. **Camera Color Detection Node (`color_detection_node`)**:
    - **Package**: `rover_control`
    - **Language**: Python
    - **Function**: Detects colors in the environment using the rover's camera feed. The node processes images and detects the presence of specific colors (e.g., red).
    - **Subscribed Topics**:
        - `/camera/image_raw` - The raw image feed from the camera.

### ROS Topics

- **`/cmd_vel`**: Used to control the rover's motors.
- **`/temperature`**, **`/humidity`**, **`/pressure`**, **`/gyro`**, **`/accel`**: These topics provide sensor data published by the sensor reader node.
- **`/joy`**: Input from the game controller for manual operation.

### Launching the Nodes

To make running the project easier, a launch file (`rover_launch.py`) has been provided. This launch file will start all the nodes needed for the rover to operate in both manual and autonomous modes.

#### Launch Instructions

1. **Build the ROS Workspace**:
   Before running the nodes, make sure your workspace is built and sourced:
   ```bash
   cd ~/rover_ws
   colcon build
   source install/setup.bash

2. **Run the Launch File**:
	Run the Launch File:
   ros2 launch rover_control rover_launch.py

###Testing the Nodes
Manual Mode Testing:

Connect your game controller via Bluetooth.
Use the joystick to move the rover. Ensure the rover moves according to joystick inputs.
Toggle between manual and autonomous mode using the designated button (A button in the joystick setup).
Autonomous Mode Testing:

In autonomous mode, the rover should move based on sensor readings.
Make sure the IMU data is being read correctly, and the rover moves as expected.
Test the camera color detection to see if the rover correctly identifies objects of a specified color.

#### File Structure
rover_ws/
 ├── src/
 │    ├── sensor_reader/
 │    │    └── src/
 │    │         └── sensor_reader.cpp  # Sensor reader node
 │    ├── rover_control/
 │    │    ├── rover_control/
 │    │    │    ├── joystick_controller.py  # Game controller node
 │    │    │    ├── motor_control.py  # Motor control and autonomous switching node
 │    │    │    └── color_detection.py  # Camera color detection node
 │    │    └── launch/
 │    │         └── rover_launch.py  # Launch file to start all nodes
 └── install/
