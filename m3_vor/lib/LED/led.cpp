/**
  ******************************************************************************
  * @file    led.cpp
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    27-12-2021
  * @brief   .
  ******************************************************************************
  */

/* #include */
#include "led.h"
#include <Arduino.h>
#include "buttons.h"
#include "charge.h"
#include "sensor.h"
#include "motor.h"

#define LIGHT_PIN 33
#define LED_RGB_PIN 21

#define NUMPIXELS 18
#define BRIGHTNESS 20

Adafruit_NeoPixel pixels(NUMPIXELS, LED_RGB_PIN, NEO_GRB + NEO_KHZ800);

uint8_t j_in_state = 0;

extern uint8_t _button_state;
extern uint8_t _charging_state;
extern uint8_t _sensor_state;
extern uint8_t _running_state;

#define RGB_RED pixels.Color(255, 0, 0)
#define RGB_GREEN pixels.Color(0, 255, 0)
#define RGB_BLUE pixels.Color(0, 0, 255)
#define RGB_WHITE pixels.Color(127, 127, 127)
#define RGB_YELLOW pixels.Color(255, 255, 0)

void main_led(void)
{
    Init_led();
    Normal_state();
    while(1)
    {
        if( (_button_state == ESTOP) | (_sensor_state == ULTRA_SHORT_DISTAN) )
        {
            Warning_state();
        } 
        else if (_charging_state == CHARGING)
        {
            Charging_state();
        }
        else if (_charging_state == LOW_BATTERY)
        {
            Low_battery_state();
        }
        else if (_charging_state == FULL_BATTERY)
        {
            Full_battery_state();
        }
        else if (_running_state == STOP)
        {
            Waiting_state();
        }
        else 
        {
            Normal_state();
        }

        threads.yield();
    }
}

void Init_led(void)
{
    pixels.begin();
    pixels.setBrightness(BRIGHTNESS);
}

void Warning_state() // Nhay do
{
    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, RGB_RED);
    }
    threads.delay(300);
    pixels.show();

    pixels.clear();
    threads.delay(300);
    pixels.show();
}

void Low_battery_state() // Nhay vang
{
    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, RGB_YELLOW);
    }
    threads.delay(600);
    pixels.show();

    pixels.clear();
    threads.delay(600);
    pixels.show();
}

void Full_battery_state() // Sang xanh
{
    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, RGB_GREEN);
    }
    pixels.show();
}

void Blink_random()
{
    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, pixels.Color(random(0, 255), random(0, 255), random(0, 255)));
        pixels.show();
    }
}

void Charging_state()
{

    pixels.setPixelColor(j_in_state, RGB_RED);
    pixels.show();
    j_in_state++;
    if (j_in_state > NUMPIXELS)
    {
        j_in_state = 0;
    }

    pixels.setPixelColor(j_in_state, RGB_GREEN);
    pixels.show();
    j_in_state++;
    if (j_in_state > NUMPIXELS)
    {
        j_in_state = 0;
    }

    pixels.setPixelColor(j_in_state, RGB_BLUE);
    pixels.show();
    j_in_state++;
    if (j_in_state > NUMPIXELS)
    {
        j_in_state = 0;
    }
}

void Waiting_state()
{
    uint16_t i;
    for (i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, Wheel((i + j_in_state) & 255));
    }
    pixels.show();
    j_in_state = (j_in_state + 1) % 256;
}

void Normal_state()
{
    uint16_t i;
    for (i = 0; i < pixels.numPixels(); i++)
    {
        pixels.setPixelColor(i, Wheel(((i * 256 / NUMPIXELS) + j_in_state) & 255));
    }
    pixels.show();
    j_in_state = (j_in_state + 1) % (256 * 5);
}

uint32_t Wheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170)
    {
        WheelPos -= 85;
        return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
