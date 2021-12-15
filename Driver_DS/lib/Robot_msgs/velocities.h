/**
  ******************************************************************************
  * @file    velocities.h
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    19-10-2021
  * @brief   .
  ******************************************************************************
  */
#ifndef _ROBOT_MSGS_VELOCITIES_H_
#define _ROBOT_MSGS_VELOCITIES_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

class Velocities : public ros::Msg
{
public:
    typedef float _liner_x_type;
    _liner_x_type liner_x;
    typedef float _liner_y_type;
    _liner_y_type liner_y;
    typedef float _angular_z_type;
    _angular_z_type angular_z;

    Velocities() : liner_x(0),
                   liner_y(0),
                   angular_z(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
    }

    const char *getType() { return "Velocities"; }
    const char *getMD5() { return "0ee8ad4cb7809be2d5a0a76352fea86a"; }
};

#endif
