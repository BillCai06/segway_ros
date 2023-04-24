#include "ros/ros.h"
#include "nav_msgs/Odometry.h" // Include the nav_msgs/Odometry header
#include "segwayrmp/robot.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "SmartCar");
    ros::NodeHandle n;
    // ros::Publisher Odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50); // Create a publisher object named "Odom_pub" with the topic "odom"
    ros::NodeHandle pn("~");
    std::string serial;
    pn.param<std::string>("segwaySmartCarSerial", serial, "segway");

    if (pn.hasParam("segwaySmartCarSerial")){
        std::string nn;
        pn.getParam("segwaySmartCarSerial", nn);
        printf("segwaySmartCarSerial: %s\n",nn.c_str());
        set_smart_car_serial(nn.c_str());
    }

    // Before calling init_control_ctrl, need to call this function to set whether the communication port is a serial port or a CAN port, "comu_serial":serial; "comu_can":CAN.;Others: Illegal
    set_comu_interface(comu_serial); 
    if(init_control_ctrl() == -1){
        printf("init_control faild\n");
    }else{
        printf("init success!\n");
    }

    robot::Chassis sbv(n);

    ros::spin();
    return 0;
}
