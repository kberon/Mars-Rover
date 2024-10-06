# ROS Configuration Guide

This guide provides steps for configuring ROS on Windows using WSL 2 and Ubuntu 22.04.3 LTS. This includes instructions for setting up ROS 2 using the Iron Irwini release.

## Prerequisites

- Windows 10 or later
- Enabled WSL 2 (with Ubuntu 22.04.3 LTS installed)

## Steps for Configuration

1. **Set up WSL 2:** Ensure you have WSL 2 installed and configured. You can check the WSL version using the following command in Windows PowerShell:
   wsl -l -v
2. **Follow intruction guide** Follow this guide: https://docs.ros.org/en/iron/Installation/Alternatives/Ubuntu-Development-Setup.html up until Next Steps (if the install development tools section does not work, try sudo apt update && sudo apt install ros-dev-tools instead)


## Docker
To make the process of building our ROS2 container simpler I have created a dockerfile and accompanying docker-compose.yml file. These two files help us build and then run the ROS2 docker container.

If you are not using the build script, you can use these commands to build and create the docker container.

1. cd into the docker directory
2. Enter in this command to build the docerfile "docker build -t ros2 ." *Does not necessarily need to be rebuilt unless dockerfile or docker-compose.yml is altered.*
3. Use this command to run the container: "docker-compose up -d"
4. To connect to the container enter this into the terminal: "docker exec -it docker_ros2_1 bash"

## More Helpful Commands

- List all running containers: "docker ps"
- Stop the specific container: "docker stop CONTAINER_ID"
- Get node list: "ros2 node list"
- Get package list: "ros2 pkg list"