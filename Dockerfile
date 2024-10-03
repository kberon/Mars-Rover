# Use an ARM64 base image compatible with Raspberry Pi
FROM ros:humble-ros-core

# Install necessary tools and dependencies
RUN apt-get update && apt-get install -y \
    python3-pip \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /root

# Install additional ROS dependencies as needed (e.g., ros-humble-desktop)
# RUN apt-get update && apt-get install -y ros-humble-desktop

# Source the ROS Humble setup
RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc