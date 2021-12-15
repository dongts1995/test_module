/**
  ******************************************************************************
  * @file    power.h
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    19-10-2021
  * @brief   .
  ******************************************************************************
  */
#ifndef _POWER_H_
#define _POWER_H_

/* #include */
#include <Arduino.h>

/* #define */
#define POWER_PIN     4
#define CHARGING_PIN  5
/* Variable */
/* Function */
class Power
{
  public:
    Power(uint8_t power_pin, uint8_t charging_pin);
    void Init_power(void);
    void Set_power(uint8_t status_power);
    uint8_t Get_charging_status(void);

  private:
    uint8_t power_pin_;
    uint8_t charging_pin_;

};

#endif
