/**
  ******************************************************************************
  * @file    buttons.cpp
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    27-12-2021
  * @brief   .Dua vao trang thai nut nhan de quyet dinh cap nguon bang chan SSR
  *           Ghi trang thai _button_state de dieu khien LED
  ******************************************************************************
  */

/* #include */
#include "buttons.h"
#include <Arduino.h>

extern uint8_t _button_state;

void main_button (void)
{
  setup_button();
  while(1)
  {
    if(digitalRead(STOP_PIN) == LOW)
    {
      _button_state = STOP;
      digitalWrite(SSR_POWER_PIN, LOW);
    }
    else if (digitalRead(ESTOP_PIN) == LOW)
    {   
      _button_state = ESTOP;
      digitalWrite(SSR_POWER_PIN, LOW);
    }
    else if (digitalRead(START_PIN) == LOW)
    {
      _button_state = START;
      digitalWrite(SSR_POWER_PIN, HIGH);
    }

    threads.yield();
  }
}

void setup_button (void)
{
  pinMode(START_PIN, INPUT_PULLUP);
  pinMode(STOP_PIN, INPUT_PULLUP);
  pinMode(ESTOP_PIN, INPUT_PULLUP);
  pinMode(SSR_POWER_PIN, OUTPUT);
  digitalWrite(SSR_POWER_PIN, LOW);
}