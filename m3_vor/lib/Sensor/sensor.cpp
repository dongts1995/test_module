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



extern uint8_t _sensor_state;
extern uint32_t ultra_distance[5];
extern uint8_t proxi_sensor[2];

Ultrasonic ultra_1(TRIGGER_PIN_1, PWM_PIN_1);
Ultrasonic ultra_2(TRIGGER_PIN_2, PWM_PIN_2);
Ultrasonic ultra_3(TRIGGER_PIN_3, PWM_PIN_3);
Ultrasonic ultra_4(TRIGGER_PIN_4, PWM_PIN_4);
Ultrasonic ultra_5(TRIGGER_PIN_5, PWM_PIN_5);
Proximity proxi_1(PROXIMITY_PIN_1);
Proximity proxi_2(PROXIMITY_PIN_2);

void main_sensor(void)
{
    ultra_1.Init_Ultra();
    ultra_2.Init_Ultra();
    ultra_3.Init_Ultra();
    ultra_4.Init_Ultra();
    ultra_5.Init_Ultra();
    proxi_1.Init_Prox();
    proxi_2.Init_Prox();
    while(1)
    {
      // uint32_t temp;
      // temp = ultra_4.Get_Distance_cm();
      // Serial.println(temp);
      // delay(300);
        proxi_sensor[0] = proxi_1.Get_Prox();
        proxi_sensor[1] = proxi_2.Get_Prox();
        _sensor_state = ULTRA_LONG_DISTAN;
        for (uint8_t i = 0; i < 5; i++)
        {
            if (ultra_distance[i] < 10)
            {
                _sensor_state = ULTRA_SHORT_DISTAN;
            }
        }
        threads.delay(100);

        threads.yield();
    }
}

void trigger_5_ultra(void)
{
  digitalWrite(TRIGGER_PIN_1, LOW);
  digitalWrite(TRIGGER_PIN_2, LOW);
  digitalWrite(TRIGGER_PIN_3, LOW);
  digitalWrite(TRIGGER_PIN_4, LOW);
  digitalWrite(TRIGGER_PIN_5, LOW);
  threads.delay_us(5);
  digitalWrite(TRIGGER_PIN_1, HIGH);
  digitalWrite(TRIGGER_PIN_2, HIGH);
  digitalWrite(TRIGGER_PIN_3, HIGH);
  digitalWrite(TRIGGER_PIN_4, HIGH);
  digitalWrite(TRIGGER_PIN_5, HIGH);
  threads.delay_us(100);
  digitalWrite(TRIGGER_PIN_1, LOW);
  digitalWrite(TRIGGER_PIN_2, LOW);
  digitalWrite(TRIGGER_PIN_3, LOW);
  digitalWrite(TRIGGER_PIN_4, LOW);
  digitalWrite(TRIGGER_PIN_5, LOW);
}

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
  threads.delay_us(5);
  digitalWrite(trigger_pin_, HIGH);
  threads.delay_us(100);
  digitalWrite(trigger_pin_, LOW);
}

uint32_t Ultrasonic::Get_Distance_cm(void)
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