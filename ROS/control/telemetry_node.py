#!/usr/bin/env python
import rospy
from std_msgs.msg import String

def telemetry_node():
    rospy.init_node('telemetry_node', anonymous=True)
    pub = rospy.Publisher('telemetry_data', String, queue_size=10)
    rate = rospy.Rate(1)  # 1 Hz

    while not rospy.is_shutdown():
        # Example telemetry data, replace with actual sensor data
        speed = "Speed: 0.5 m/s"
        direction = "Direction: Forward"
        
        telemetry_info = f"{speed}, {direction}"
        rospy.loginfo(telemetry_info)
        pub.publish(telemetry_info)
        
        rate.sleep()

if __name__ == '__main__':
    try:
        telemetry_node()
    except rospy.ROSInterruptException:
        pass
