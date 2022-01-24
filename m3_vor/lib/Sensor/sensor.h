/**
  ******************************************************************************
  * @file    sensor.h
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    19-10-2021
  * @brief   .
  ******************************************************************************
  */
#ifndef _SENSOR_H_
#define _SENSOR_H_

/* #include */
#include <Arduino.h>
#include "TeensyThreads.h"

/* #define */
// define _sensor_state
#define ULTRA_LONG_DISTAN   1
#define ULTRA_SHORT_DISTAN  2

#define TRIGGER_PIN_1   8  
#define PWM_PIN_1       7
#define TRIGGER_PIN_2   24
#define PWM_PIN_2       25
#define TRIGGER_PIN_3   29
#define PWM_PIN_3       28
#define TRIGGER_PIN_4   14
#define PWM_PIN_4       15
#define TRIGGER_PIN_5   17
#define PWM_PIN_5       16

#define PROXIMITY_PIN_1 34
#define PROXIMITY_PIN_2 35

void main_sensor(void);
void trigger_5_ultra(void);

class Ultrasonic
{
  public:
    Ultrasonic(uint8_t trigger_pin, uint8_t pwm_pin);
    void Init_Ultra(void);
    uint32_t Get_Distance_cm(void);

  private:
    //uint8_t time_us;
    uint8_t trigger_pin_;
    uint8_t pwm_pin_;
    void Trigger_DYP(void);
};

class Proximity
{
  public:
    Proximity(uint8_t proximity_pin);
    void Init_Prox(void);
    uint8_t Get_Prox(void);

  private:
    uint8_t proximity_pin_;
};



#endif