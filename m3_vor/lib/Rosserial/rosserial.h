/**
  ******************************************************************************
  * @file    rosserial.h
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    27-12-2021
  * @brief   .
  ******************************************************************************
  */
#ifndef _ROSSERIAL_H_
#define _ROSSERIAL_H_

#include <Arduino.h>
#include "TeensyThreads.h"
#include "ros.h"
#include "geometry_msgs/Twist.h"


void commandCallback(const geometry_msgs::Twist& cmd_msg);
void setup_rosserial(void);


#endif