/**
  ******************************************************************************
  * @file    kinematic.h
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    19-10-2021
  * @brief   .
  ******************************************************************************
  */
#ifndef _KINEMATIC_H_
#define _KINEMATIC_H_

/* #include */
#include <Arduino.h>

#define RPM_TO_RPS 1/60

#define MAX_RPM 330
#define WHEEL_DIAMETER 0.10
#define WHELLS_DISTANCE 0.235

class Kinematics
{
    public:
        
        struct rpm
        {
            int motor1;
            int motor2;
        };
        
        struct velocities
        {
            float linear_x;
            float linear_y;
            float angular_z;
        };

        struct pwm
        {
            int motor1;
            int motor2;
            int motor3;
            int motor4;
        };

        Kinematics(int motor_max_rpm, float wheel_diameter, float wheels_distance);
        velocities getVelocities(float steering_angle, int rpm1, int rpm2);
        velocities getVelocities(int rpm1, int rpm2);
        rpm getRPM(float linear_x, float linear_y, float angular_z);

    private:
        rpm calculateRPM(float linear_x, float linear_y, float angular_z);

        int max_rpm_;
        float wheels_distance_;
        float pwm_res_;
        float wheel_circumference_;
};

#endif
