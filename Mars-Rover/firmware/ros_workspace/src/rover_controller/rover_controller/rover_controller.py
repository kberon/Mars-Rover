import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist

class RoverController(Node):
    def __init__(self):
        # Initialize the Node with the name 'rover_controller'
        super().__init__('rover_controller')
        
        # Create a subscription to the 'joy' topic to listen to joystick messages
        self.subscription = self.create_subscription(Joy, 'joy', self.joy_callback, 10)
        
        # Create a publisher to send commands to the 'cmd_vel' topic for controlling the rover
        self.publisher = self.create_publisher(Twist, 'cmd_vel', 10)
        
        # Boolean flag to track if the rover is in autonomous mode
        self.autonomous_mode = False

    def joy_callback(self, msg):
        # Callback function for joystick input
        
        twist = Twist()  # Create a Twist message to control linear and angular velocity
        
        # Check if the rover is in autonomous mode
        if self.autonomous_mode:
            # Ignore user input if in autonomous mode
            return

        # Set linear velocity from the joystick input (Forward/Backward)
        twist.linear.x = msg.axes[1]
        # Set angular velocity from the joystick input (Left/Right)
        twist.angular.z = msg.axes[0]
        
        # Publish the Twist message to the 'cmd_vel' topic
        self.publisher.publish(twist)
        
        # Print the current joystick inputs for monitoring
        self.get_logger().info(f'Joystick Input - Linear X: {twist.linear.x}, Angular Z: {twist.angular.z}')

    def toggle_autonomous_mode(self):
        # Toggle the autonomous mode state
        self.autonomous_mode = not self.autonomous_mode
        # Print the new autonomous mode state
        self.get_logger().info(f'Autonomous Mode: {"Enabled" if self.autonomous_mode else "Disabled"}')

def main(args=None):
    # Initialize the ROS client library
    rclpy.init(args=args)
    
    # Create an instance of the RoverController class
    controller = RoverController()

    try:
        # Keep the node running until interrupted
        rclpy.spin(controller)
    except KeyboardInterrupt:
        # Handle the shutdown gracefully on a keyboard interrupt
        pass

    # Destroy the node to free up resources
    controller.destroy_node()
    
    # Shutdown the ROS client library
    rclpy.shutdown()

# Entry point of the script
if __name__ == '__main__':
    main()
