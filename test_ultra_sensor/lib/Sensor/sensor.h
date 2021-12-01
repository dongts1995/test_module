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

/* #define */
#define TRIGGER_PIN_1   14
#define PWM_PIN_1       15
#define TRIGGER_PIN_2   16
#define PWM_PIN_2       17
#define TRIGGER_PIN_3   24
#define PWM_PIN_3       25
#define TRIGGER_PIN_4   28
#define PWM_PIN_4       29
#define TRIGGER_PIN_5   36
#define PWM_PIN_5       37
#define PROXIMITY_PIN   10
#define PHOTOELEC_PIN_1 6
#define PHOTOELEC_PIN_2 9
/* Variable */
/* Function */

class Ultrasonic
{
  public:
    Ultrasonic(uint8_t trigger_pin, uint8_t pwm_pin);
    void Init_Ultra(void);
    uint32_t Get_Duration_cm(void);

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
