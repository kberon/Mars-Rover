#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Image
from std_msgs.msg import String
from cv_bridge import CvBridge
import cv2
import Adafruit_CharLCD as LCD

# Set up the LCD
lcd = LCD.Adafruit_CharLCDPlate()

def detect_color(image):
    # Convert to HSV for color detection
    hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

    # Define color ranges and mask them (example for red color)
    lower_red = (0, 120, 70)
    upper_red = (10, 255, 255)
    mask = cv2.inRange(hsv_image, lower_red, upper_red)

    # Check if any red pixels are detected
    if cv2.countNonZero(mask) > 0:
        return "Red"
    
    # Similar checks for other colors (example for blue)
    lower_blue = (100, 150, 0)
    upper_blue = (140, 255, 255)
    mask = cv2.inRange(hsv_image, lower_blue, upper_blue)
    if cv2.countNonZero(mask) > 0:
        return "Blue"

    return "Unknown"

def image_callback(ros_image):
    bridge = CvBridge()
    try:
        # Convert the ROS image to OpenCV format
        cv_image = bridge.imgmsg_to_cv2(ros_image, "bgr8")
    except CvBridgeError as e:
        rospy.logerr(e)
        return

    # Detect the color in the image
    detected_color = detect_color(cv_image)
    rospy.loginfo(f"Detected Color: {detected_color}")

    # Display the detected color on the LCD screen
    lcd.clear()
    lcd.message(f"Color: {detected_color}")

def object_detection_color_node():
    rospy.init_node('object_detection_color_node', anonymous=True)
    rospy.Subscriber("/camera/image_raw", Image, image_callback)
    rospy.spin()

if __name__ == '__main__':
    try:
        object_detection_color_node()
    except rospy.ROSInterruptException:
        pass
