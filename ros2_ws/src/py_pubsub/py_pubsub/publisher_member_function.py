# Copyright 2016 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import rclpy
from rclpy.node import Node
# Sets up the inbuilt string message type that the node uses in order to format the messages
from std_msgs.msg import String

# Subclass of Node
class MinimalPublisher(Node):
    
    def __init__(self):
        super().__init__('minimal_publisher') #Passes the name of the function
        self.publisher_ = self.create_publisher(String, 'topic', 10) # This node publishes strings, top ic name of topic, queue size of 10 (this limits the amount of messages in the queue to ensure performance)
        # Create a timer that callbacks and executes 0.5 seconds
        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback) 
        self.i = 0
    # Creates a message and appends the counter value to it
    def timer_callback(self):
        msg = String()
        msg.data = 'Hello World: %d' % self.i
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.data)
        self.i += 1


# Main function definition
# rclpy initialized, 'spin' node so callbacks are called
def main(args=None):
    rclpy.init(args=args)

    minimal_publisher = MinimalPublisher()

    rclpy.spin(minimal_publisher)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
