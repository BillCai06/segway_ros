#include <iostream>
#include "segwayrmp/robot.h"
#include <boost/thread/thread.hpp>
#include <ros/ros.h>
#include <signal.h>
#include <math.h>
#include <termios.h>
#include <geometry_msgs/Twist.h>

using namespace std;

int rate = 50;
ros::Publisher cmd_pub;
ros::ServiceServer chassis_send_event_srv_server;
ros::ServiceClient ros_get_charge_mos_ctrl_status_cmd_client;
ros::ServiceClient ros_set_chassis_enable_cmd_client;
ros::ServiceClient ros_clear_chassis_error_code_cmd_client;
ros::ServiceClient ros_enable_chassis_rotate_cmd_client;
ros::ServiceClient ros_start_chassis_left_rotate_cmd_client;
ros::ServiceClient ros_stop_chassis_rotate_cmd_client;

segway_msgs::ros_get_charge_mos_ctrl_status_cmd ros_get_charge_mos_ctrl_status_srv;
segway_msgs::ros_set_chassis_enable_cmd ros_set_chassis_enable_srv;
segway_msgs::ros_set_iap_cmdGoal ros_set_iap_cmd_goal;

bool ros_get_chassis_send_event_callback(segway_msgs::chassis_send_event::Request &req, segway_msgs::chassis_send_event::Response &res)
{
    ROS_INFO("Initializing failed! The node receives the event ID:%d", req.chassis_send_event_id);
    res.ros_is_received = true;
    return true;
}

bool setChassisEnable(bool enable)
{
    ros_set_chassis_enable_srv.request.ros_set_chassis_enable_cmd = enable;
    return ros_set_chassis_enable_cmd_client.call(ros_set_chassis_enable_srv);
}

void MySigintHandler(int sig)
{
    ROS_INFO("shut down!");
    setChassisEnable(false);
    ros::shutdown();
    exit(0);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "enable_chassis");
    ros::NodeHandle n_;

    chassis_send_event_srv_server = n_.advertiseService("chassis_send_event_srv", &ros_get_chassis_send_event_callback);

    ros_get_charge_mos_ctrl_status_cmd_client = n_.serviceClient<segway_msgs::ros_get_charge_mos_ctrl_status_cmd>("ros_get_charge_mos_ctrl_status_cmd_srv");
    ros_set_charge_mos_ctrl_cmd_client = n_.serviceClient<segway_msgs::ros_set_charge_mos_ctrl_cmd>("ros_set_charge_mos_ctrl_cmd_srv");
    ros_set_chassis_enable_cmd_client = n_.serviceClient<segway_msgs::ros_set_chassis_enable_cmd>("ros_set_chassis_enable_cmd_srv");
    // ros_set_vel_max_cmd_client = n_.serviceClient<segway_msgs::ros_set_vel_max_cmd>("ros_set_vel_max_cmd_srv"); //It needs to be consistent with the server-side name

    iapActionClient ac("ros_set_iap_cmd_action", true);
    ROS_INFO("Waiting for action server to start.");
    ac.waitForServer();
    ROS_INFO("Action server started. Sending enable signal...");

    ros::AsyncSpinner spinner(4);
    ros::Rate loop_rate(rate);
    spinner.start();

    signal(SIGINT, MySigintHandler);

    while (ros::ok())
    {
        setChassisEnable(true);
        loop_rate.sleep();
        ros::spinOnce();
    }
    /*ROS_INFO("Node exit");
	printf("Process exit\n");*/

    return 0;
}

