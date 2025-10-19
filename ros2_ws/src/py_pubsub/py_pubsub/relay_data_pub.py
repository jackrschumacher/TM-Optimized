# Relay telemetry data from the Pico

import rclpy
import serial
import threading
import sys
from rclpy.node import Node

from std_msgs.msg import String


class relay_Telemetry(Node):
    def __init__(self):
        super.__init__("telemetry_Publisher")

        # Set serial up with baud rate of 9600 on /dev/ttyACM0
        self.ser = serial.Serial("/dev/ttyACM0", 9600)
        self.publisher = self.create_publisher(String, "/pico/output", 10)
        # Update every 0.1 seconds -can change this value to increase or decrease the update frequency
        self.create_timer(0.1, self.read_data)

        def run(self):
            # Threading to optimize performance
            thread = threading.Thread(target=rclpy.spin, args={self}, daemon=True)
            thread.start()

            # Try-catch to improve error handling
            try:
                while rclpy.ok():
                    self.read_data()
            
            # Upon keyboard interrupt exit
            except KeyboardInterrupt:
                sys.exit(0)

                

        def read_data(self):
            # Read Serial
            data_output = str(self.ser.readline(), "utf8")

            if data_output:
                message = String()
                self.posXYZ, self.acceleration, self.atmospheric = data_output.split(
                    "$"
                )
            self.get_logger().info(
                f"{self.posXYZ} {self.acceleration} {self.atmospheric}"
            )

def main(args=None):
    rclpy.init(args=args)
    telemetry_Publisher = relay_Telemetry()
    rclpy.spin(telemetry_Publisher)
    telemetry_Publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()