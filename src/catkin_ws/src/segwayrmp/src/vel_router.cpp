#include "ros/ros.h"
#include "segwayrmp/robot.h"


segway_msgs::ros_set_chassis_enable_cmd ros_set_chassis_enable_srv;

geometry_msgs::Twist this_vel;

void sub_set_vel(const geometry_msgs::Twist::ConstPtr &set_vel)
{
    this_vel.angular.z = set_vel->angular.z; 
    this_vel.linear.x = set_vel->linear.x;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "vel_router");
    ros::NodeHandle n;
    ros::Rate loop_rate(1000);

    ros::Subscriber sub = n.subscribe("set_vel", 1, sub_set_vel);
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    ros::ServiceClient ros_set_chassis_enable_cmd_client = n.serviceClient<segway_msgs::ros_set_chassis_enable_cmd>("ros_set_chassis_enable_cmd_srv");

    ros_set_chassis_enable_srv.request.ros_set_chassis_enable_cmd = true;
    ros_set_chassis_enable_cmd_client.call(ros_set_chassis_enable_srv);

    while(ros::ok())
    {
        ros::spinOnce();
        pub.publish(this_vel);
        loop_rate.sleep();
    }

    ros_set_chassis_enable_srv.request.ros_set_chassis_enable_cmd = false;
    ros_set_chassis_enable_cmd_client.call(ros_set_chassis_enable_srv);

    return 0;
}