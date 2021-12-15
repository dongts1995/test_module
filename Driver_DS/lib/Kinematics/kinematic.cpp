/**
  ******************************************************************************
  * @file    kinematic.cpp
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    19-10-2021
  * @brief   .
  ******************************************************************************
  */

/* #include */
#include "kinematic.h"
#include <Arduino.h>


Kinematics::Kinematics(int motor_max_rpm, float wheel_diameter, float wheels_distance):
    max_rpm_(motor_max_rpm),
    wheels_distance_(wheels_distance),
    wheel_circumference_(PI * wheel_diameter)
{    
}

Kinematics::rpm Kinematics::calculateRPM(float linear_x, float linear_y, float angular_z)
{
    float linear_vel_x_mins;
    float linear_vel_y_mins;
    float angular_vel_z_mins;
    float tangential_vel;
    float x_rpm;
    float y_rpm;
    float tan_rpm;

    //convert m/s to m/min
    linear_vel_x_mins = linear_x * 60;
    linear_vel_y_mins = linear_y * 60;

    //convert rad/s to rad/min
    angular_vel_z_mins = angular_z * 60;

    tangential_vel = angular_vel_z_mins * (wheels_distance_ / 2);

    x_rpm = linear_vel_x_mins / wheel_circumference_;
    y_rpm = linear_vel_y_mins / wheel_circumference_;
    tan_rpm = tangential_vel / wheel_circumference_;

    Kinematics::rpm rpm;

    //calculate for the target motor RPM and direction
    //front-left motor
    rpm.motor1 = x_rpm - y_rpm - tan_rpm;
    // rpm.motor1 = x_rpm + y_rpm - tan_rpm;
    rpm.motor1 = constrain(rpm.motor1, -max_rpm_, max_rpm_);

    //front-right motor
    rpm.motor2 = x_rpm + y_rpm + tan_rpm;
    // rpm.motor2 = x_rpm - y_rpm + tan_rpm;
    rpm.motor2 = constrain(rpm.motor2, -max_rpm_, max_rpm_);

    return rpm;
}

Kinematics::rpm Kinematics::getRPM(float linear_x, float linear_y, float angular_z)
{
    Kinematics::rpm rpm;
    
    rpm = calculateRPM(linear_x, linear_y , angular_z);

    return rpm;
}

Kinematics::velocities Kinematics::getVelocities(float steering_angle, int rpm1, int rpm2)
{
    Kinematics::velocities vel;
    float average_rps_x;

    //convert average revolutions per minute to revolutions per second
    average_rps_x = ((float)(rpm1 + rpm2) / 2) / 60; // RPM
    vel.linear_x = average_rps_x * wheel_circumference_; // m/s

    vel.linear_y = 0.0;

    //http://wiki.ros.org/teb_local_planner/Tutorials/Planning%20for%20car-like%20robots
    vel.angular_z =  (vel.linear_x * tan(steering_angle)) / wheels_distance_;

    return vel;
}

Kinematics::velocities Kinematics::getVelocities(int rpm1, int rpm2)
{
    Kinematics::velocities vel;
    float average_rps_x;
    float average_rps_y;
    float average_rps_a;

    //convert average revolutions per minute to revolutions per second
    average_rps_x = ((float)(rpm1 + rpm2) / 2) / 60; // RPM
    vel.linear_x = average_rps_x * wheel_circumference_; // m/s

    //convert average revolutions per minute in y axis to revolutions per second
    vel.linear_y = 0;

    //convert average revolutions per minute to revolutions per second
    average_rps_a = ((float)(-rpm1 + rpm2) / 2) / 60;
    vel.angular_z =  (average_rps_a * wheel_circumference_) / (wheels_distance_ / 2); //  rad/s

    return vel;
}
/* #define */
/* Variable */
/* Function */


