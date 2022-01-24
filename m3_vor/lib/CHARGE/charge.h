/**
  ******************************************************************************
  * @file    charge.h
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    27-12-2021
  * @brief   .
  ******************************************************************************
  */
#ifndef _CHARGE_H_
#define _CHARGE_H_

#include <Arduino.h>
#include "TeensyThreads.h"

// define charge pin
#define CHARGING_PIN    38
#define BATTERY_PIN     39
#define SSR_CHARGE      40

// state
#define FULL_BATTERY    1
#define LOW_BATTERY     2
#define CHARGING        3
#define NORMAL_BATTERY  4

// data
#define MAX_VOLTAGE     3.65*8
#define MIN_VOLTAGE     3*8

void main_charger(void);
void Init_charge(void);
float get_charging_voltage(void);
float get_battery_voltage(void);

#endif