#include <math.h>
#include <iostream>
#include <termios.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include "segwayrmp/robot.h"

#define ENABLECMD 'e'

int rate = 10;
ros::Publisher cmd_pub;
segway_msgs::ros_set_chassis_enable_cmd enable_request;
ros::ServiceClient ros_set_chassis_enable_cmd_client;
enable_request.request.ros_set_chassis_enable_cmd = 1;
enable_switch = 1;
enable_request.request.ros_set_chassis_enable_cmd = set_enable_cmd;
++set_enable_cmd;
set_enable_cmd %= 2;
ROS_INFO_NAMED("drive_sample", "enable chassis switch[%d]", enable_request.request.ros_set_chassis_enable_cmd);
printf("current set_line_speed[%lf], set_angular_speed[%lf]\n", set_line_speed, set_angular_speed);

if (enable_switch)
{
    ros_set_chassis_enable_cmd_client.call(enable_request);
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "drive_segway_sample");
    ros::NodeHandle n_;
    ros_set_chassis_enable_cmd_client = n_.serviceClient<segway_msgs::ros_set_chassis_enable_cmd>("ros_set_chassis_enable_cmd_srv");
    chassis_send_event_srv_server = n_.advertiseService("chassis_send_event_srv", &ros_get_chassis_send_event_callback);
    ROS_INFO("Waiting for action server to start.");
    ac.waitForServer();
    ROS_INFO("Action server started.");
    ros::Rate loop_rate(rate);
    printf("%s\n", print_help());
    while (ros::ok())
    {
        drive_chassis_test(ac);

        loop_rate.sleep();
        ros::spinOnce();
    }
    return 0;
}