Nodes Overview
1. Camera Publisher Node
File: camera_publisher.py

Purpose: Captures the camera feed using OpenCV and publishes it as a ROS topic (/camera/image_raw).

Usage: Automatically launched via the launch file.

2. Object Detection Node
File: object_detection_node.py

Purpose: Subscribes to the camera feed topic, processes the images to detect objects (colors and shapes), and displays the processed images.

Usage: Automatically launched via the launch file.

3. Motor Control Node
File: motor_control.py

Purpose: Receives commands from other nodes (e.g., keyboard control or object detection) and controls the rover's motors accordingly.

Usage: Automatically launched via the launch file.

4. Keyboard Control Node
File: keyboard_control.py

Purpose: Allows manual control of the rover using the keyboard. Publishes commands like "forward", "backward", "left", "right", and "stop" to the motor control node.

Usage: Automatically launched via the launch file.

5. Telemetry Node
File: telemetry_node.py

Purpose: Publishes telemetry data, such as speed and direction, to the telemetry_data topic. This data can be used for monitoring and debugging.

Usage: Automatically launched via the launch file.
