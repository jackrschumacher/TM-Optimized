import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/jack/Documents/TM-Optimized/ros2_ws/install/data_relay'
