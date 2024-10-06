Nodes Overview
1. Lidar Proximity Node
File: lidar_proximity.py

Purpose: This node subscribes to the lidar data published on the /scan topic, checks the distance to nearby objects, and publishes motor commands based on the proximity of objects.

Communication:

Subscribes to: /scan (Lidar data)
Publishes to: motor_commands (String)
Logic:

If an object is within the CLOSE_THRESHOLD, the node publishes a "stop" command to the motor control node.
If no object is within the threshold, it publishes a "forward" command.
2. Object Detection and Color Analysis Node
File: object_detection_color.py

Purpose: This node subscribes to the camera feed published on the /camera/image_raw topic, processes the image to detect the object's color, and displays the detected color on an LCD screen connected to the Raspberry Pi.

Communication:

Subscribes to: /camera/image_raw (Camera image data)
Displays: Detected color on an LCD screen
Logic:

The node converts the camera image to the HSV color space.
It then checks for specific color ranges (e.g., red, blue).
The detected color is printed to the LCD screen.
3. Motor Control Node
File: motor_control.py

Purpose: This node receives motor commands from the lidar proximity node (or other sources) and controls the motors of the rover accordingly.

Communication:

Subscribes to: motor_commands (String)
Logic:

The node interprets commands like "forward" and "stop" to control the rover's movement.
4. Launch File
File: rover_launch.launch

Purpose: This launch file starts all the nodes needed for the rover's operation, including the camera, lidar proximity detection, color detection, and motor control.

Node Communication Flow
Lidar Proximity Detection:

The lidar_proximity.py node processes lidar data to determine if an object is close to the rover.
Depending on the distance, it sends a "stop" or "forward" command to the motor_control.py node via the motor_commands topic.
Motor Control:

The motor_control.py node listens to the motor_commands topic and moves the rover accordingly.
Object Detection and Color Analysis:

The object_detection_color.py node listens to the camera feed on the /camera/image_raw topic.
It processes the image to detect the object's color and displays the result on the LCD screen.