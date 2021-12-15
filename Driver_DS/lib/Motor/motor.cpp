/**
  ******************************************************************************
  * @file    motor.cpp
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    19-10-2021
  * @brief   .
  ******************************************************************************
  */

/* #include */
#include "motor.h"
#include <Arduino.h>


/* #define */
/* Variable */
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;
CAN_message_t msg;

uint8_t CAN1Sedbuf[8];
uint8_t CAN2Sedbuf[8];
uint32_t PV_spd;
uint32_t PP_spd;
uint32_t PT_spd;
/* Function */

void CAN_Init(void)
{
  can1.begin();
  can1.setBaudRate(1000000);
  CANopen_PV_Init();
  Motor_enable();
}

void SDO_Write_OD(uint8_t CANopen_ID, uint8_t CMD, uint16_t Index, uint8_t SubIndex, uint32_t DATA)
{
  msg.buf[0] = CMD;
  msg.buf[1] = (uint8_t)(Index >> 8 & 0xFF);
  msg.buf[2] = (uint8_t)(Index >> 8 & 0xFF);
  msg.buf[3] = SubIndex;
  msg.buf[4] = (uint8_t)(DATA & 0xFF);
  msg.buf[5] = (uint8_t)(DATA >>  8 & 0xFF);
  msg.buf[6] = (uint8_t)(DATA >> 16 & 0xFF);
  msg.buf[7] = (uint8_t)(DATA >> 24 & 0xFF);
  //msg.id = CANopen_ID;
  msg.id = 0x600 + CANopen_ID;
  msg.len = 8;
  can1.write(msg);
  delay(5);
  //return (1);
}

void Control_Mode_SET(uint8_t CANopen_ID, uint8_t CANopen_mode)
{
  CAN1Sedbuf[0] = SDO_W1;
  CAN1Sedbuf[1] = 0x60;
  CAN1Sedbuf[2] = 0x60;
  CAN1Sedbuf[3] = 0x00;
  CAN1Sedbuf[4] = CANopen_mode;
  CAN1Sedbuf[5] = 0x00;
  CAN1Sedbuf[6] = 0x00;
  CAN1Sedbuf[7] = 0x00;
  //msg.id = CANopen_ID;
  msg.id = 0x600 + CANopen_ID;
  msg.len = 8;
  can1.write(msg);
  delay(5);
  //return (1);
}

void CANopen_Activate(uint8_t CANopen_ID)
{
  CAN1Sedbuf[0] = 0x01;
  CAN1Sedbuf[1] = CANopen_ID;
  msg.id = 0x000;
  msg.len = 2;
  can1.write(msg);
  delay(5);
  //return (1);
}

void CANopen_PV_Init(void)
{

  // Step 1: Dam bao driver dang o mode CANopen
  // He tham so 1: Fn00=20; he tham so 2: F0/1.1.002=20
  // Step 2: Node duoc set thanh controllabe status
  // send: 000 01 02 set node 2 thanh controllabe status
  // CANopen_Activate(01);     // 000 01 01
  // CANopen_Activate(02);     // 000 01 02
  msg.buf[0] = 01;
  msg.buf[1] = 01;
  msg.id = 0x000;
  msg.len = 2;
  can1.write(msg);
  delay(5);
  msg.buf[0] = 01;
  msg.buf[1] = 02;
  msg.id = 0x000;
  msg.len = 2;
  can1.write(msg);
  delay(5);
  // Step 3: Config
  // 1. Set mode lam viec (6060H) lam mode van toc
  // vd: send: 602 2F 60 60 00 03 00 00 00
  msg.buf[0] = 0x2F;
  msg.buf[1] = 0x60;
  msg.buf[2] = 0x60;
  msg.buf[3] = 0x00;
  msg.buf[4] = 0x03;
  msg.buf[5] = 0x00;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;
  msg.id = 0x601;
  msg.len = 8;
  can1.write(msg);
  delay(5);
  msg.buf[0] = 0x2F;
  msg.buf[1] = 0x60;
  msg.buf[2] = 0x60;
  msg.buf[3] = 0x00;
  msg.buf[4] = 0x03;
  msg.buf[5] = 0x00;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;
  msg.id = 0x602;
  msg.len = 8;
  can1.write(msg);
  delay(5);
  // 2. set thoi gian thay doi toc do tu 0rpm den 3000rpm (tang toc 6083h, giam toc 6084h), don vi ms,
  // set 6083h = 1s - send: 602 23 83 60 00 E8 03 00 00
  // set 6084h = 1s - send: 602 23 84 60 00 E8 03 00 00
  msg.buf[0] = 0x23;
  msg.buf[1] = 0x83;
  msg.buf[2] = 0x60;
  msg.buf[3] = 0x00;
  msg.buf[4] = 0xE8;
  msg.buf[5] = 0x03;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;
  msg.id = 0x601;
  msg.len = 8;
  can1.write(msg);
  delay(5);
  msg.buf[0] = 0x23;
  msg.buf[1] = 0x83;
  msg.buf[2] = 0x60;
  msg.buf[3] = 0x00;
  msg.buf[4] = 0xE8;
  msg.buf[5] = 0x03;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;
  msg.id = 0x602;
  msg.len = 8;
  can1.write(msg);
  delay(5);
  msg.buf[0] = 0x23;
  msg.buf[1] = 0x84;
  msg.buf[2] = 0x60;
  msg.buf[3] = 0x00;
  msg.buf[4] = 0xE8;
  msg.buf[5] = 0x03;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;
  msg.id = 0x601;
  msg.len = 8;
  can1.write(msg);
  delay(5);
  msg.buf[0] = 0x23;
  msg.buf[1] = 0x84;
  msg.buf[2] = 0x60;
  msg.buf[3] = 0x00;
  msg.buf[4] = 0xE8;
  msg.buf[5] = 0x03;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;
  msg.id = 0x601;
  msg.len = 8;
  can1.write(msg);
  delay(5);
  // 3. Set toc do muc tieu: 60FFh,don vi 0,1rpm
  // set 60FFh = 10rpm - send: 602 23 FF 60 00 64 00 00 00
  msg.buf[0] = 0x23;
  msg.buf[1] = 0xFF;
  msg.buf[2] = 0x60;
  msg.buf[3] = 0x00;
  msg.buf[4] = 0x00;
  msg.buf[5] = 0x00;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;
  msg.id = 0x601;
  msg.len = 8;
  can1.write(msg);
  delay(5);
  msg.buf[0] = 0x23;
  msg.buf[1] = 0xFF;
  msg.buf[2] = 0x60;
  msg.buf[3] = 0x00;
  msg.buf[4] = 0x00;
  msg.buf[5] = 0x00;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;
  msg.id = 0x602;
  msg.len = 8;
  can1.write(msg);
  delay(5);
  
}

void CANopen_PV_SET(uint32_t Acc, uint32_t Dec, int32_t TargetVelocity)
{

  SDO_Write_OD(Left_Wheel_ID, SDO_W4, 0x6083, 0x00, Acc);
  SDO_Write_OD(Left_Wheel_ID, SDO_W4, 0x6084, 0x00, Dec);

  SDO_Write_OD(Right_Wheel_ID, SDO_W4, 0x6083, 0x00, Acc);
  SDO_Write_OD(Right_Wheel_ID, SDO_W4, 0x6084, 0x00, Dec);

  SDO_Write_OD(Left_Wheel_ID, SDO_W4, 0x60FF, 0x00, TargetVelocity);
  SDO_Write_OD(Right_Wheel_ID, SDO_W4, 0x60FF, 0x00, TargetVelocity);
}

void Motor_PV_Zero(void)
{
  SDO_Write_OD(Left_Wheel_ID, SDO_W4, 0x60FF, 0x00, 0);
  SDO_Write_OD(Right_Wheel_ID, SDO_W4, 0x60FF, 0x00, 0);
}

void Motor_PV_Go(uint32_t _PV_spd)
{
  SDO_Write_OD(Left_Wheel_ID, SDO_W4, 0x60FF, 0x00, _PV_spd);
  SDO_Write_OD(Right_Wheel_ID, SDO_W4, 0x60FF, 0x00, _PV_spd);
}

void Motor_PV_Left(uint32_t _PV_spd)
{
  SDO_Write_OD(Left_Wheel_ID, SDO_W4, 0x60FF, 0x00, ~_PV_spd + 1);
  SDO_Write_OD(Right_Wheel_ID, SDO_W4, 0x60FF, 0x00, _PV_spd);
}

void Motor_PV_Right(uint32_t _PV_spd)
{
  SDO_Write_OD(Left_Wheel_ID, SDO_W4, 0x60FF, 0x00, _PV_spd);
  SDO_Write_OD(Right_Wheel_ID, SDO_W4, 0x60FF, 0x00, ~_PV_spd + 1);
}

void Motor_PV_Back(uint32_t _PV_spd)
{
  SDO_Write_OD(Left_Wheel_ID, SDO_W4, 0x60FF, 0x00, ~_PV_spd + 1);
  SDO_Write_OD(Right_Wheel_ID, SDO_W4, 0x60FF, 0x00, ~_PV_spd + 1);
}

void Motor_enable(void)
{
  // 4. set controlword 6040h de enable driver:
  // Lan dau enable phai ghi lan luot 0x06, 0x07, 0x0F.
  // set 6040h = 6 - chuan bi - send: 602 2B 40 60 00 06 00 00 00
  msg.buf[0] = 0x2B;
  msg.buf[1] = 0x40;
  msg.buf[2] = 0x60;
  msg.buf[3] = 0x00;
  msg.buf[4] = 0x06;
  msg.buf[5] = 0x00;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;
  msg.id = 0x601;
  msg.len = 8;
  can1.write(msg);
  delay(5);
  msg.buf[0] = 0x2B;
  msg.buf[1] = 0x40;
  msg.buf[2] = 0x60;
  msg.buf[3] = 0x00;
  msg.buf[4] = 0x06;
  msg.buf[5] = 0x00;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;
  msg.id = 0x602;
  msg.len = 8;
  can1.write(msg);
  delay(5);
  
  // set 6040h = 7 - Disable - send: 602 2B 40 60 00 07 00 00 00
  msg.buf[0] = 0x2B;
  msg.buf[1] = 0x40;
  msg.buf[2] = 0x60;
  msg.buf[3] = 0x00;
  msg.buf[4] = 0x07;
  msg.buf[5] = 0x00;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;
  msg.id = 0x601;
  msg.len = 8;
  can1.write(msg);
  delay(5);
  msg.buf[0] = 0x2B;
  msg.buf[1] = 0x40;
  msg.buf[2] = 0x60;
  msg.buf[3] = 0x00;
  msg.buf[4] = 0x07;
  msg.buf[5] = 0x00;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;
  msg.id = 0x602;
  msg.len = 8;
  can1.write(msg);
  delay(5);
 
  // set 6040h = F - Enable - send: 602 2B 40 60 00 0F 00 00 00
  msg.buf[0] = 0x2B;
  msg.buf[1] = 0x40;
  msg.buf[2] = 0x60;
  msg.buf[3] = 0x00;
  msg.buf[4] = 0x0F;
  msg.buf[5] = 0x00;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;
  msg.id = 0x601;
  msg.len = 8;
  can1.write(msg);
  delay(5);
  msg.buf[0] = 0x2B;
  msg.buf[1] = 0x40;
  msg.buf[2] = 0x60;
  msg.buf[3] = 0x00;
  msg.buf[4] = 0x0F;
  msg.buf[5] = 0x00;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;
  msg.id = 0x602;
  msg.len = 8;
  can1.write(msg);
  delay(5);

  // Dong co chay voi toc do 60FFh sau khi enable
}

void Motor_Disable(void)
{
  SDO_Write_OD(Left_Wheel_ID, SDO_W4, 0x6040, 0x00, 0x07);
  SDO_Write_OD(Right_Wheel_ID, SDO_W4, 0x6040, 0x00, 0x07);
}

uint32_t rpm_to_hex(uint32_t rpm)
{
  return  10*rpm;
}


void dao_chieu(void)
{
  msg.buf[0] = 0x23;
  msg.buf[1] = 0xFF;
  msg.buf[2] = 0x60;
  msg.buf[3] = 0x00;
  msg.buf[4] = 0x88;
  msg.buf[5] = 0x13;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;
  msg.id = 0x601;
  msg.len = 8;
  can1.write(msg);
  msg.id = 0x602;
  can1.write(msg);

  delay(6000);

  msg.buf[4] = 0x00;
  msg.id = 0x601;
  can1.write(msg);
  msg.id = 0x602;
  can1.write(msg);
  delay(1000);

  msg.buf[4] = ~0x88 + 1;
  msg.buf[5] = ~0x13;
  msg.buf[6] = 0xFF;
  msg.buf[7] = 0xFF;
  msg.id = 0x601;
  can1.write(msg);
  msg.id = 0x602;
  can1.write(msg);
  delay(6000);

  msg.buf[4] = 0x00;
  msg.buf[5] = 0x00;
  msg.buf[6] = 0x00;
  msg.buf[7] = 0x00;
  msg.id = 0x601;
  can1.write(msg);
  msg.id = 0x602;
  can1.write(msg);
  delay(1000);
}
