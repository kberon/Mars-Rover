#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from pynput.keyboard import Key, Listener

def on_press(key):
    command = None
    try:
        if key.char == 'w':  # Move forward
            command = "forward"
        elif key.char == 's':  # Move backward
            command = "backward"
        elif key.char == 'a':  # Turn left
            command = "left"
        elif key.char == 'd':  # Turn right
            command = "right"
    except AttributeError:
        pass

    if command:
        rospy.loginfo("Sending command: %s", command)
        pub.publish(command)

def on_release(key):
    if key == Key.esc:
        # Stop listener by returning False
        return False

if __name__ == '__main__':
    rospy.init_node('keyboard_servo_control', anonymous=True)
    pub = rospy.Publisher('servo_command', String, queue_size=10)
    rate = rospy.Rate(10)  # 10hz

    # Start the listener
    with Listener(on_press=on_press, on_release=on_release) as listener:
        rospy.spin()  # Keeps Python from exiting until this node is stopped

        listener.join()
