#include <ros/ros.h>
#include <iostream>
#include <fstream>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
using namespace std;
void odom_callback(const nav_msgs::Odometry &odom_msg)
{
     static tf::TransformBroadcaster odom_broadcaster;
    double th = 2 * atan2(odom_msg.pose.pose.orientation.z, odom_msg.pose.pose.orientation.w);
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);
    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = ros::Time::now();
    // odom_trans.header.stamp = odom_msg.header.stamp;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "/base_link";
    odom_trans.transform.translation.x = odom_msg.pose.pose.position.x;
    odom_trans.transform.translation.y = odom_msg.pose.pose.position.y;
    odom_trans.transform.translation.z = odom_msg.pose.pose.position.z;
    //odom_trans.transform.rotation = odom_msg.pose.pose.orientation;
    odom_trans.transform.rotation = odom_quat;
    //send the transform
    odom_broadcaster.sendTransform(odom_trans);
}
int main(int argc, char **argv)
{
   ros::init(argc, argv, "odom_base_link_tf");
    ros::NodeHandle n;
    ros::Subscriber odom_sub = n.subscribe("odom", 40, odom_callback);
    
    ros::Rate rate(3); // 30 Hz

    while (ros::ok())
    {
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}