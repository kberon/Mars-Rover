#!/usr/bin/env python
import rospy
from std_msgs.msg import String

# Example: Assuming you have a motor driver class (MotorDriver)
class MotorDriver:
    def __init__(self):
        # Initialize motor pins and setup
        pass

    def move_forward(self):
        rospy.loginfo("Moving forward")
        # Code to move the motor forward

    def move_backward(self):
        rospy.loginfo("Moving backward")
        # Code to move the motor backward

    def turn_left(self):
        rospy.loginfo("Turning left")
        # Code to turn the rover left

    def turn_right(self):
        rospy.loginfo("Turning right")
        # Code to turn the rover right

    def stop(self):
        rospy.loginfo("Stopping")
        # Code to stop the motors

def motor_callback(msg):
    command = msg.data
    motor_driver = MotorDriver()

    if command == "forward":
        motor_driver.move_forward()
    elif command == "backward":
        motor_driver.move_backward()
    elif command == "left":
        motor_driver.turn_left()
    elif command == "right":
        motor_driver.turn_right()
    elif command == "stop":
        motor_driver.stop()

def motor_control_node():
    rospy.init_node('motor_control_node', anonymous=True)
    rospy.Subscriber("motor_commands", String, motor_callback)
    rospy.spin()

if __name__ == '__main__':
    try:
        motor_control_node()
    except rospy.ROSInterruptException:
        pass
