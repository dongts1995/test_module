/**
  ******************************************************************************
  * @file    ledbutton.cpp
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    19-10-2021
  * @brief   .
  ******************************************************************************
  */

/* #include */
#include "ledbutton.h"
#include <Arduino.h>

/* #define */
/* Variable */
/* Function */
Led_control::Led_control(uint8_t led_number, uint8_t led_pin, uint8_t arg3):
Adafruit_NeoPixel(led_number,led_pin,arg3)
{
  led_number_= led_number;
  led_pin_ = led_pin;
  arg3_ = arg3;
}

void Led_control::Init(void)
{
  pinMode(led_pin_, INPUT_PULLUP);
  begin();
  show();
}

// Ham nay viet tam thoi
void Led_control::Led_state_1(uint8_t state)
{
  switch (state)
  {
  case 1:
    setPixelColor(0,50,0,0);
    show();
    break;
  case 2:
    setPixelColor(0,0,50,0);
    show();
    break;
  case 3:
    setPixelColor(0,0,0,50);
    show();
    break;
  default:
    break;
  }
}

Light::Light(uint8_t light_pin):
light_pin_(light_pin)
{
}

void Light::Init(void)
{
  pinMode(light_pin_, OUTPUT);
}

void Light::Set_light(bool light)
{
  if(light) digitalWrite(light_pin_, HIGH);
  else digitalWrite(light_pin_, LOW);
}

Button::Button(uint8_t button_pin):
button_pin_(button_pin)
{
}

void Button::Init(void)
{
  pinMode(button_pin_, INPUT);
}

uint8_t Button::Get_Button(void)
{
  return digitalRead(button_pin_);
}
