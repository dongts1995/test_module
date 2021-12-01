#include <Arduino.h>
#include <sensor.h>

Ultrasonic ultra_1(TRIGGER_PIN_1, PWM_PIN_1);
uint32_t duration_ultral = 0;

void setup() {
  // put your setup code here, to run once:
  ultra_1.Init_Ultra();
  Serial.begin(115200);
  Serial.println("test print");
}

void loop() {
  // put your main code here, to run repeatedly:
  duration_ultral = ultra_1.Get_Duration_cm();
  Serial.println(duration_ultral);
  delay(100);
}