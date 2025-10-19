# Relay telemetry data from the Pico

import rclpy
import serial
import sys
import threading
from rclpy.node import Node

from std_msgs.msg import String
