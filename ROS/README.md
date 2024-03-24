# ROS Configuration Guide

This guide provides steps for configuring ROS on Windows using WSL 2 and Ubuntu 20.04.6 LTS. This includes instructions for setting up ROS 2 using the Iron Irwini release.

## Prerequisites

- Windows 10 or later
- Enabled WSL 2 (with Ubuntu 20.04.6 LTS installed)

## Steps for Configuration

1. **Set up WSL 2:** Ensure you have WSL 2 installed and configured. You can check the WSL version using the following command in Windows PowerShell:
   wsl -l -v
2. **Follow intruction guide** Follow this guide: https://docs.ros.org/en/iron/Installation/Alternatives/Ubuntu-Development-Setup.html up until Next Steps (if the install development tools section does not work, try sudo apt update && sudo apt install ros-dev-tools instead)

