#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2

def camera_publisher():
    rospy.init_node('camera_publisher', anonymous=True)
    pub = rospy.Publisher('/camera/image_raw', Image, queue_size=10)
    cap = cv2.VideoCapture(0)  # Use 0 or the correct camera index
    bridge = CvBridge()
    rate = rospy.Rate(10)  # 10 Hz

    while not rospy.is_shutdown():
        ret, frame = cap.read()
        if not ret:
            continue
        ros_image = bridge.cv2_to_imgmsg(frame, "bgr8")
        pub.publish(ros_image)
        rate.sleep()

    cap.release()

if __name__ == '__main__':
    try:
        camera_publisher()
    except rospy.ROSInterruptException:
        pass
