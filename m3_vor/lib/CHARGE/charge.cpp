/**
  ******************************************************************************
  * @file    charge.cpp
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    27-12-2021
  * @brief   .
  ******************************************************************************
  */

/* #include */
#include "charge.h"
#include <Arduino.h>

extern uint8_t _charging_state;
extern uint8_t battery_percent;

unsigned long g_prev_charging_time = 0;

void main_charger(void)
{
    Init_charge();
    digitalWrite(SSR_CHARGE, HIGH);
    while (1)
    {
        // get battery percent
        if (_charging_state == CHARGING)
        {
            if (millis() - g_prev_charging_time >= 60000)
            {
                g_prev_charging_time = millis();
                digitalWrite(SSR_CHARGE, LOW);
                threads.delay(10);
                battery_percent = map(get_battery_voltage(), MIN_VOLTAGE, MAX_VOLTAGE, 0, 100);
                threads.delay(10);
                digitalWrite(SSR_CHARGE, HIGH);
            }
        }
        else
        {
            battery_percent = map(get_battery_voltage(), MIN_VOLTAGE, MAX_VOLTAGE, 0, 100);
        }

        // status charging, low_bat
        if (get_charging_voltage() >= 2.5)
        {
            if (battery_percent >= 95)
            {
                _charging_state = FULL_BATTERY;
            }
            else
            {
                _charging_state = CHARGING;
            }
        }
        else if (battery_percent <= 20)
        {
            _charging_state = LOW_BATTERY;
        }
        else
        {
            _charging_state = NORMAL_BATTERY;
        }

        // status full bat
        threads.yield();
    }
}

void Init_charge(void)
{
    pinMode(CHARGING_PIN, INPUT);
    pinMode(BATTERY_PIN, INPUT);
    pinMode(SSR_CHARGE, OUTPUT);
}

float get_charging_voltage(void)
{
    float charging_voltage;
    charging_voltage = map(analogRead(CHARGING_PIN), 0, 1023, 0, 3.3);
    return charging_voltage;
}

float get_battery_voltage(void)
{
    float battery_voltage;
    battery_voltage = map(analogRead(BATTERY_PIN), 0, 1023, 0, 3.3);
    return battery_voltage;
}
