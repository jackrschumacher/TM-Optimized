# Two Month Optimized

> [!WARNING]
>
> **This code is currently untested on hardware but parts of the code have been used on hardware in the past**

## Table of Contents

[TOC]

## Resources

Here are some important resources for Rover 2 month

### Pico

#### [Writing to the SD Card](https://medium.com/@cemmreis/logging-data-with-an-sd-card-module-and-raspberry-pi-pico-in-arduino-ide-5b280382527e)

### ROS2

#### [ROS2 Publisher and Subscriber Tutorial](https://github.com/ros2/ros2_documentation/blob/humble/source/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Py-Publisher-And-Subscriber.rst)

## Pin Assignments

Pin assignments can be easily updated to suit different hardware configurations.

| **Pin** | Function |
| ------- | -------- |
|         |          |
|         |          |
|         |          |
|         |          |
|         |          |
|         |          |
|         |          |
|         |          |
|         |          |

## ROS 2

Make sure to source your ROS2 setup script

### Building and Running a ROS2 Package

####  Run rosdep

> [!IMPORTANT]
>
> It is a good idea to run rosdep in the root of your workspace before building to ensure that no packages are missing

```bash
rosdep install -i --from-path src --rosdistro humble -y
```

#### Build your package

Run this from the root of your workspace (like ros2_ws)

```bash
colcon build --packages-select [packageName]
```

#### Source the Setup Files

```bash
source install/setup.bash
```

#### Start the talker node

```bash
ros2 run [package_name] talker
```

Like this:

```bash
ros2 run py_pubsub talker
```

The output may look like this:

```bash
[info] [minimal_publisher]: publishing: "hello world: 0"
[info] [minimal_publisher]: publishing: "hello world: 1"
[info] [minimal_publisher]: publishing: "hello world: 2"
[info] [minimal_publisher]: publishing: "hello world: 3"
[info] [minimal_publisher]: publishing: "hello world: 4"
```

#### Start the listener node

```bash
ros2 run [package_name] listener
```

Like:

```bash
ros2 run py_pubsub listener
```

The output may look like this:

```bash
[INFO] [minimal_subscriber]: I heard: "Hello World: 10"
[INFO] [minimal_subscriber]: I heard: "Hello World: 11"
[INFO] [minimal_subscriber]: I heard: "Hello World: 12"
[INFO] [minimal_subscriber]: I heard: "Hello World: 13"
[INFO] [minimal_subscriber]: I heard: "Hello World: 14"
```

