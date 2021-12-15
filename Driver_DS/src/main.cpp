#include <Arduino.h>
#include <motor.h>

// Set hệ tham số 2: F0/1.1.002=20
// Set baud 1000000


void setup()
{
  CAN_Init();
}

void loop()
{
  dao_chieu();


  // Motor_PV_Go(60);
  
  //  delay(3000);

   //Motor_PV_Go(0);
  //  delay(1000);

  //  Motor_PV_Back(60);
  
  //  delay(3000);

  //  Motor_PV_Go(0);
  //  delay(1000);
  // Motor_PV_Back(60);
  // delay(1000);
} // End switch state
