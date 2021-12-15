/**
  ******************************************************************************
  * @file    ledbutton.h
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    19-10-2021
  * @brief   .
  ******************************************************************************
  */
#ifndef _LEDBUTTON_H_
#define _LEDBUTTON_H_

/* #include */
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

/* #define */
#define EMERGENCY_PIN   41

#define LIGHT_PIN       39
#define START_PIN       26
#define STOP_PIN        27

#define LED_CONTROL_PIN 40
#define LED_NUMBER      18
#define ARG3            NEO_GRB + NEO_KHZ800
/* Variable */
/* Function */
//
class Led_control:Adafruit_NeoPixel
{
  public:
    Led_control(uint8_t led_number, uint8_t led_pin, uint8_t arg3);
    void Init(void);
    void Led_state_1(uint8_t state);
  private:
    uint8_t led_number_;
    uint8_t led_pin_;
    uint8_t arg3_;
};


class Light
{
  public:
    Light(uint8_t light_pin);
    void Init(void);
    void Set_light(bool light);

  private:
    uint8_t light_pin_;

};

class Button
{
  public:
    Button(uint8_t button_pin);
    void Init(void);
    uint8_t Get_Button(void);

  private:
    uint8_t button_pin_;
};

#endif
