#!/usr/bin/env python
import rospy
from sensor_msgs.msg import LaserScan
from std_msgs.msg import String

# Threshold for how close an object can be to the rover
CLOSE_THRESHOLD = 1.0  # Meters

def lidar_callback(data):
    # Check the minimum distance in the lidar scan data
    min_distance = min(data.ranges)

    # Create a publisher for motor commands
    pub = rospy.Publisher('motor_commands', String, queue_size=10)

    # Move backward if object is too close, stop if within a safe distance
    if min_distance < CLOSE_THRESHOLD:
        rospy.loginfo("Object detected close, stopping rover.")
        pub.publish("stop")
    else:
        rospy.loginfo("No close object, moving forward.")
        pub.publish("forward")

def lidar_proximity_node():
    rospy.init_node('lidar_proximity_node', anonymous=True)
    rospy.Subscriber("/scan", LaserScan, lidar_callback)
    rospy.spin()

if __name__ == '__main__':
    try:
        lidar_proximity_node()
    except rospy.ROSInterruptException:
        pass
