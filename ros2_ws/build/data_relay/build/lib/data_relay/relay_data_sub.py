# Relay telemetry data from the Pico

import rclpy
import serial
import sys
import threading
from rclpy.node import Node

from std_msgs.msg import String


class telemetery_Relay(Node):
    def __init__(self):
        super().__init__("telemetry_subscriber")
        self.ser = serial.Serial('/dev/ttyACM0', 9600)

        self.subscription = self.create_subscription(String, 'pico/command', self.send, 10)

        def send_data(self,message):
            self.get_logger().info('received input: '+message.data)
            command = message.data + '\n'
            self.ser.write(bytes(command,"utf8"))
            self.ser.flush() # Send out data as soon as received to avoid piling up


def main(args=None):
    rclpy.init(args=args)
    telemetry_Subscriber = telemetery_Relay()
    rclpy.spin(telemetry_Subscriber)
    telemetry_Subscriber.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()

