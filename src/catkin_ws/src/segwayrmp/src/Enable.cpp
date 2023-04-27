#include <ros/ros.h>
#include <math.h>
#include <iostream>
#include <termios.h>
#include <geometry_msgs/Twist.h>
#include "segwayrmp/robot.h"
#include <segway_msgs/ros_set_chassis_enable_cmd.h>

int rate = 10;
ros::Publisher cmd_pub;
ros::ServiceClient ros_set_chassis_enable_cmd_client;

bool enableRobot()
{
    segway_msgs::ros_set_chassis_enable_cmd enable_request;
    enable_request.request.ros_set_chassis_enable_cmd = 1;

    if (!ros_set_chassis_enable_cmd_client.waitForExistence(ros::Duration(5)))
    {
        ROS_ERROR("Failed to connect to the service within the specified timeout.");
        return false;
    }
     else
    {
        if (ros_set_chassis_enable_cmd_client.call(enable_request))
        {
            ROS_INFO("Service call was successful.");
            return true;
        }
    
        else
        {
            ROS_ERROR("Failed to call the service.");
            return false;
        }
    }
}

   


int main(int argc, char **argv)
{
    ros::init(argc, argv, "enable_robot");
    ros::NodeHandle nh;
    ros_set_chassis_enable_cmd_client.waitForExistence(ros::Duration(500));
    ros_set_chassis_enable_cmd_client = nh.serviceClient<segway_msgs::ros_set_chassis_enable_cmd>("ros_set_chassis_enable_cmd");

    bool enabled = enableRobot();
    if (!enabled)
    {
        ROS_ERROR("Unable to enable the robot. Exiting.");
        return 1;
    }

    ros::Rate loop_rate(rate);
    while (ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
