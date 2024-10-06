import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
import numpy as np

class ColorDetector(Node):
    def __init__(self):
        super().__init__('color_detector')
        self.subscription = self.create_subscription(
            Image,
            '/image_raw',  # Adjust this topic as needed
            self.listener_callback,
            10)
        self.bridge = CvBridge()

    def listener_callback(self, msg):
        cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        self.detect_color(cv_image)

    def detect_color(self, image):
        # Convert the image to HSV color space
        hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

        # Define color ranges in HSV
        colors = {
            "Red": ([0, 100, 100], [10, 255, 255]),
            "Green": ([40, 100, 100], [80, 255, 255]),
            "Blue": ([100, 100, 100], [140, 255, 255]),
            "Yellow": ([20, 100, 100], [40, 255, 255]),
            "Orange": ([10, 100, 100], [20, 255, 255])
        }

        for color_name, (lower, upper) in colors.items():
            lower_bound = np.array(lower)
            upper_bound = np.array(upper)

            # Create a mask for the current color
            mask = cv2.inRange(hsv_image, lower_bound, upper_bound)
            color_pixels = cv2.countNonZero(mask)

            if color_pixels > 0:
                self.get_logger().info(f'Detected {color_name} color!')

def main(args=None):
    rclpy.init(args=args)
    color_detector = ColorDetector()
    rclpy.spin(color_detector)
    color_detector.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
