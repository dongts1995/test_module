#include <Arduino.h>



// digital pin 6 has a sensor pin attached to it. Give it a name:
#define SENSOR_PIN  6
#define LED_PIN     13

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Hahaha");
  // make the SENSOR's pin an input:
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int sensorState = digitalRead(SENSOR_PIN);
  if(sensorState) digitalWrite(LED_PIN, HIGH);
  else digitalWrite(LED_PIN, LOW);
  // print out the state of the sensor:
  //Serial.println(sensorState);
  //delay(100);        // delay in between reads for stability
}