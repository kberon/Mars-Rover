import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy
from std_msgs.msg import Float32MultiArray

class MotorControlNode(Node):
    def __init__(self):
        super().__init__('motor_control_node')
        self.pub = self.create_publisher(Twist, 'cmd_vel', 10)

        # Subscribe to joystick input
        self.joy_sub = self.create_subscription(Joy, 'joy', self.joy_callback, 10)

        # Subscribe to sensor readings for autonomous navigation
        self.gyro_sub = self.create_subscription(Float32MultiArray, 'gyro', self.gyro_callback, 10)
        
        self.autonomous = False

    def joy_callback(self, msg):
        # Toggle autonomous mode using button press
        if msg.buttons[0] == 1:
            self.autonomous = not self.autonomous
            self.get_logger().info(f"Autonomous Mode: {'On' if self.autonomous else 'Off'}")

        # Publish joystick movement if not in autonomous mode
        if not self.autonomous:
            twist = Twist()
            twist.linear.x = msg.axes[1]  # Forward/backward
            twist.angular.z = msg.axes[0]  # Rotation
            self.pub.publish(twist)

    def gyro_callback(self, msg):
        if self.autonomous:
            # Implement autonomous control based on gyro data
            twist = Twist()
            # Example: simple proportional control based on sensor readings
            twist.angular.z = -0.1 * msg.data[2]  # Adjust yaw based on z-axis rotation
            twist.linear.x = 0.5  # Move forward
            self.pub.publish(twist)

def main(args=None):
    rclpy.init(args=args)
    motor_control_node = MotorControlNode()
    rclpy.spin(motor_control_node)
    motor_control_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
