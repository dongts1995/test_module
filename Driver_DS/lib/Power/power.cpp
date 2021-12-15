/**
  ******************************************************************************
  * @file    power.cpp
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    19-10-2021
  * @brief   .Bao gom cac ham lien quan den nguon dien va sac pin
  ******************************************************************************
  */

/* #include */
#include "power.h"
#include <Arduino.h>

/* #define */
/* Variable */
/* Function */
Power::Power(uint8_t power_pin, uint8_t charging_pin):
power_pin_(power_pin),
charging_pin_(charging_pin)
{
}

void Power::Init_power(void)
{
  pinMode(power_pin_, OUTPUT);
  pinMode(charging_pin_, INPUT);
}

void Power::Set_power(uint8_t status_power)
{
  if(status_power)
    digitalWrite(POWER_PIN, HIGH);
  else
    digitalWrite(POWER_PIN, LOW);
}

uint8_t Power::Get_charging_status(void)
{
  return digitalRead(CHARGING_PIN);
}



