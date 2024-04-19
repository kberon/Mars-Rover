#!/bin/bash

# Define the image and container names
IMAGE_NAME="ros-noetic-pi"
CONTAINER_NAME="my_ros_container_pi"

# Build the Docker image
echo "Building the Docker image..."
docker build -t $IMAGE_NAME .

# Check if the container already exists and remove it if it does
if [ $(docker ps -a -f name=$CONTAINER_NAME | grep -w $CONTAINER_NAME | wc -l) -eq 1 ]; then
    echo "Removing existing container..."
    docker rm -f $CONTAINER_NAME
fi

# Run the Docker container
echo "Running the Docker container..."
docker run -it --name $CONTAINER_NAME $IMAGE_NAME

echo "You are now in the bash shell of your Docker container."
