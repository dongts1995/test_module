/**
  ******************************************************************************
  * @file    rosserial.cpp
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    27-12-2021
  * @brief   .
  ******************************************************************************
  */

/* #include */
#include "rosserial.h"
#include <Arduino.h>
#include "sensor.h"

extern float g_req_linear_vel_x;
extern float g_req_linear_vel_y;
extern float g_req_linear_vel_z;

// ros::NodeHandle nh;

// ros::Subscriber<geometry_msgs::Twist> cmd_sub("cmd_vel", commandCallback);


void commandCallback(const geometry_msgs::Twist& cmd_msg)
{
    g_req_linear_vel_x = cmd_msg.linear.x;
    g_req_linear_vel_y = cmd_msg.linear.y;
    g_req_linear_vel_z = cmd_msg.angular.z;
}
void setup_rosserial(void)
{
    // nh.initNode();
    // nh.getHardware()->setBaud(57600);
    // nh.subscribe(cmd_sub);

    // //while (!nh.connected())
    // while (1)
    // {
    //     nh.spinOnce();
    // }
    // // spin();
    // threads.delay(1);
    
}

