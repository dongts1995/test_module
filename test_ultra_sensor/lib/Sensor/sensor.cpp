/**
  ******************************************************************************
  * @file    sensor.cpp
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    19-10-2021
  * @brief   .
  ******************************************************************************
  */

/* #include */
#include "sensor.h"
#include <Arduino.h>

/* #define */
/* Variable */
/* Function */

Ultrasonic::Ultrasonic(uint8_t trigger_pin, uint8_t pwm_pin):
trigger_pin_(trigger_pin),
pwm_pin_(pwm_pin)
{ 
}

void Ultrasonic::Init_Ultra(void)
{
  pinMode(trigger_pin_, OUTPUT);
  pinMode(pwm_pin_, INPUT);
}

void Ultrasonic::Trigger_DYP(void)
{
  digitalWrite(trigger_pin_, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger_pin_, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigger_pin_, LOW);
}

uint32_t Ultrasonic::Get_Duration_cm(void)
{
  Ultrasonic::Trigger_DYP();
  uint32_t duration;
  pinMode(pwm_pin_, INPUT);
  duration = pulseIn(pwm_pin_, HIGH);
  return duration/58;
}

Proximity::Proximity(uint8_t proximity_pin):
proximity_pin_(proximity_pin)
{
}

void Proximity::Init_Prox(void)
{
  pinMode(proximity_pin_,INPUT);
}

uint8_t Proximity::Get_Prox(void)
{
  return digitalRead(proximity_pin_);
}



