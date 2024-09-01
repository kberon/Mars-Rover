#!/usr/bin/env python
import rospy
from std_msgs.msg import String
import sys, select, termios, tty

def getKey():
    tty.setraw(sys.stdin.fileno())
    select.select([sys.stdin], [], [], 0)
    key = sys.stdin.read(1)
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, termios.tcgetattr(sys.stdin))
    return key

def keyboard_control_node():
    rospy.init_node('keyboard_control_node')
    pub = rospy.Publisher('motor_commands', String, queue_size=10)
    
    try:
        while not rospy.is_shutdown():
            key = getKey()
            if key == 'w':
                pub.publish("forward")
            elif key == 's':
                pub.publish("backward")
            elif key == 'a':
                pub.publish("left")
            elif key == 'd':
                pub.publish("right")
            elif key == 'q':
                pub.publish("stop")
            elif key == '\x03':  # Ctrl-C to quit
                break
    except Exception as e:
        rospy.logerr(e)

if __name__ == '__main__':
    try:
        keyboard_control_node()
    except rospy.ROSInterruptException:
        pass
