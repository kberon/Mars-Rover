#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
import cv2

def callback(ros_image):
    bridge = CvBridge()
    try:
        # Convert ROS Image message to OpenCV image
        cv_image = bridge.imgmsg_to_cv2(ros_image, "bgr8")
    except CvBridgeError as e:
        print(e)
        return

    # Your object detection code here
    # For example, convert to grayscale
    gray = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)
    
    # Display the image
    cv2.imshow("Camera Feed", cv_image)
    cv2.waitKey(1)

def object_detection_node():
    rospy.init_node('object_detection_node', anonymous=True)
    rospy.Subscriber("/camera/image_raw", Image, callback)
    rospy.spin()

    # Close all OpenCV windows
    cv2.destroyAllWindows()

if __name__ == '__main__':
    try:
        object_detection_node()
    except rospy.ROSInterruptException:
        pass
