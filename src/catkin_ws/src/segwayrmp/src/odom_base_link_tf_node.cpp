#include <ros/ros.h>
#include <iostream>
#include <fstream>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
using namespace std;

void odom_callback(const nav_msgs::Odometry &odom_msg)
{
    static tf2_ros::TransformBroadcaster odom_broadcaster;
    double th = 2 * atan2(odom_msg.pose.pose.orientation.z, odom_msg.pose.pose.orientation.w);
    tf2::Quaternion odom_quat;
    odom_quat.setRPY(0, 0, th);

    // First, we'll publish the transform over tf2
    geometry_msgs::TransformStamped odom_trans;
    // odom_trans.header.stamp = odom_msg.header.stamp;
    odom_trans.header.stamp = odom_msg.header.stamp + ros::Duration(1e-9);

    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";
    odom_trans.header.frame_id = "odom";
    odom_trans.transform.translation.x = odom_msg.pose.pose.position.x;
    odom_trans.transform.translation.y = odom_msg.pose.pose.position.y;
    odom_trans.transform.translation.z = odom_msg.pose.pose.position.z;
    odom_trans.transform.rotation.x = odom_quat.x();
    odom_trans.transform.rotation.y = odom_quat.y();
    odom_trans.transform.rotation.z = odom_quat.z();
    odom_trans.transform.rotation.w = odom_quat.w();

    // Send the transform
    odom_broadcaster.sendTransform(odom_trans);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "odom_base_link_tf");
    ros::NodeHandle n;
    ros::Subscriber odom_sub = n.subscribe("odom", 40, odom_callback);

    ros::Rate rate(10); // 10 Hz

    while (ros::ok())
    {
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
