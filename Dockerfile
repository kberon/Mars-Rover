# Use an ARM64 base image compatible with Raspberry Pi
FROM ros:humble-ros-core

# Install necessary tools and dependencies
RUN apt-get update && apt-get install -y \
    python3-pip \
    build-essential \
    ros-humble-joy \
    v4l-utils \  
    ros-humble-usb-cam \
    ros-humble-camera-info-manager \
    ros-humble-image-transport \
    ros-humble-image-transport-plugins \
    libopencv-dev \
    python3-opencv \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /root

# Install additional ROS dependencies as needed (e.g., ros-humble-desktop)
# RUN apt-get update && apt-get install -y ros-humble-desktop

# Source the ROS Humble setup
RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc

# Install USB camera support (assuming you need v4l-utils)
RUN apt-get update && apt-get install -y \
    v4l-utils \
    && rm -rf /var/lib/apt/lists/*

# Optionally, install OpenCV Python bindings
RUN pip3 install opencv-python
