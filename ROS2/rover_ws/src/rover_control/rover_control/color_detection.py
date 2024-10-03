import rclpy
from rclpy.node import Node
import cv2
from sensor_msgs.msg import Image
from cv_bridge import CvBridge

class ColorDetectionNode(Node):
    def __init__(self):
        super().__init__('color_detection_node')
        self.sub = self.create_subscription(Image, 'camera/image_raw', self.image_callback, 10)
        self.bridge = CvBridge()

    def image_callback(self, msg):
        # Convert the image from ROS to OpenCV
        cv_image = self.bridge.imgmsg_to_cv2(msg, 'bgr8')

        # Example color detection logic (detects if something red is in the image)
        hsv_image = cv2.cvtColor(cv_image, cv2.COLOR_BGR2HSV)
        lower_red = (0, 120, 70)
        upper_red = (10, 255, 255)
        mask = cv2.inRange(hsv_image, lower_red, upper_red)
        if cv2.countNonZero(mask) > 0:
            self.get_logger().info("Red object detected")

def main(args=None):
    rclpy.init(args=args)
    color_detection_node = ColorDetectionNode()
    rclpy.spin(color_detection_node)
    color_detection_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
