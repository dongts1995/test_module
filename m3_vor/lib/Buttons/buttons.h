/**
  ******************************************************************************
  * @file    buttons.h
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    27-12-2021
  * @brief   .
  ******************************************************************************
  */
#ifndef _BUTTONS_H_
#define _BUTTONS_H_

#include <Arduino.h>
#include "TeensyThreads.h"

// _button_state
#define NOPE    0
#define START   1
#define STOP    2
#define ESTOP   3

// define PIN
#define START_PIN 4
#define STOP_PIN  5
#define ESTOP_PIN 6
#define SSR_POWER_PIN 3

void main_button (void);
void setup_button (void);

#endif