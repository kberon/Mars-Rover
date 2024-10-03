import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist

class JoystickController(Node):
    def __init__(self):
        super().__init__('joystick_controller')
        self.sub = self.create_subscription(Joy, 'joy', self.joy_callback, 10)
        self.pub = self.create_publisher(Twist, 'cmd_vel', 10)
        self.autonomous = False

    def joy_callback(self, msg):
        # Example to toggle between autonomous and manual modes using button 0 (e.g., 'A' button)
        if msg.buttons[0] == 1:
            self.autonomous = not self.autonomous
            self.get_logger().info(f"Autonomous Mode: {'On' if self.autonomous else 'Off'}")

        # Publish joystick movement if not in autonomous mode
        if not self.autonomous:
            twist = Twist()
            twist.linear.x = msg.axes[1]  # Example mapping to forward/backward
            twist.angular.z = msg.axes[0]  # Example mapping to rotation
            self.pub.publish(twist)

def main(args=None):
    rclpy.init(args=args)
    joystick_controller = JoystickController()
    rclpy.spin(joystick_controller)
    joystick_controller.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
