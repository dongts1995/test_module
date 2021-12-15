/**
  ******************************************************************************
  * @file    status.h
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    19-10-2021
  * @brief   .
  ******************************************************************************
  */
#ifndef _ROBOT_MSGS_STATUS_H_
#define _ROBOT_MSGS_STATUS_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

class Status : public ros::Msg
{
public:

    Status()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
    }

    const char *getType() { return "Status"; }
    const char *getMD5() { return "0ee8ad4cb7809be2d5a0a76352fea86b"; }
};


#endif
