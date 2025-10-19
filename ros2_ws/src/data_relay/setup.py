from setuptools import find_packages, setup

package_name = 'data_relay'
maintainer ='Jack Schumacher',
maintainer_email='jackrschumacher@gmail.com',
description='Example ROS2 publisher subscriber for 2 Month using rclpy'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='jack',
    maintainer_email='jackrschumacher@gmail.com',
    description='TODO: Package description',
    license='Apache-2.0',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        # Make sure that these are named correctly otherwise fails
        'console_scripts': [
                'relay_pub =  data_relay.relay_data_pub:main',
                'relay_sub = data_relay.relay_data_sub:main'

        ],
},
)

