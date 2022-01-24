#include <Arduino.h>
#include "TeensyThreads.h"
#include "buttons.h"
#include "rosserial.h"
#include "motor.h"
#include "sensor.h"
#include "charge.h"
#include "led.h"

uint8_t _button_state = 0;       // trang thai nut nhan gan nhat
uint8_t _motion_state = 0;       // trang thai chuyen dong
uint8_t _sensor_state = 0;       // trang thai nhan biet co vat can hay k
uint8_t _charging_state = 0;     // trang thai pin hoac dang sac
uint8_t _running_state = 0;      // trang thai Robot dang dung hoac dang chay
uint32_t ultra_distance[5] = {}; // gia tri cam bien
uint8_t proxi_sensor[2] = {};    // gia tri cam bien
uint8_t battery_percent = 0;     // % pin
float g_req_linear_vel_x = 0;    // vx nhan duoc tu Jetson
float g_req_linear_vel_y = 0;    // vy nhan duoc tu Jetson
float g_req_linear_vel_z = 0;    // w nhan duoc tu Jetson
int32_t velocity_L, velocity_R;  // Khai bao de in ra, ti nua k dung thi xoa

Ultrasonic ultra_1_(TRIGGER_PIN_1, PWM_PIN_1);
Ultrasonic ultra_2_(TRIGGER_PIN_2, PWM_PIN_2);
Ultrasonic ultra_3_(TRIGGER_PIN_3, PWM_PIN_3);
Ultrasonic ultra_4_(TRIGGER_PIN_4, PWM_PIN_4);
Ultrasonic ultra_5_(TRIGGER_PIN_5, PWM_PIN_5);

void setup()
{
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  delay(3000);
  // threads.addThread(main_button);  // Set trang thai bien _button_state khi nut nhan duoc nhan.
  _button_state = START;

  threads.addThread(setup_rosserial);

  threads.addThread(main_motor);

  threads.addThread(main_sensor); // _sensor_state = ULTRA_SHORT_DISTAN;
                                  _sensor_state = ULTRA_LONG_DISTAN;
                                  // ultra_1_.Init_Ultra();

  // threads.addThread(main_charger);
  _charging_state = NORMAL_BATTERY;

  threads.addThread(main_led);
}

void loop()
{

  // Serial.print("banh trai: ");
  // Serial.print(velocity_L);
  // Serial.print(" - banh phai: ");
  // Serial.print(velocity_R);
  // Serial.println();
  // Serial.print("x: ");
  // Serial.println(g_req_linear_vel_x);
  // Serial.print("y: ");
  // Serial.println(g_req_linear_vel_y);
  // ultra_1_.Get_Distance_cm();
  // Serial.print("z: ");
  // Serial.println(ultra_1_.Get_Distance_cm());
  // delay(300);

  // threads.delay(150);
  // threads.yield();
  // ultra_distance[0] = ultra_1_.Get_Distance_cm();
  // ultra_distance[1] = ultra_2_.Get_Distance_cm();
  // ultra_distance[2] = ultra_3_.Get_Distance_cm();
  // ultra_distance[3] = ultra_4_.Get_Distance_cm();
  // ultra_distance[4] = ultra_5_.Get_Distance_cm();
  // trigger_5_ultra();
  // ultra_distance[0] = pulseIn(PWM_PIN_1, HIGH);
  // Serial.println(ultra_distance[0]);
}