/**
  ******************************************************************************
  * @file    motor.h
  * @author  dongts1 - M3 Team
  * @version V1.0.0
  * @date    19-10-2021
  * @brief   .
  ******************************************************************************
  */
#ifndef _MOTOR_H_
#define _MOTOR_H_

/* #include */
#include <Arduino.h>
#include <FlexCAN_T4.h>

/* #define */
// tham so cua driver
#define SDO_W1  0x2F   //ask write 1 byte
#define SDO_W2  0x2B    //ask write 2 byte
#define SDO_W4  0x23    //ask write 4 byte
#define SDO_RD  0x40    //ask read data
//#define PP_Mode  1
#define PV_Mode  3 
//#define PT_Mode  4 
//CAN ID
#define  Left_Wheel_ID                 01
#define  Right_Wheel_ID                02

/* Variable */

void CAN_Init(void);
void SDO_Write_OD(uint8_t CANopen_ID, uint8_t CMD, uint16_t Index, uint8_t SubIndex, uint32_t DATA);
void Control_Mode_SET(uint8_t CANopen_ID, uint8_t CANopen_mode);
void CANopen_Activate(uint8_t CANopen_ID);
void CANopen_PV_Init(void);
void CANopen_PV_SET(uint32_t Acc, uint32_t Dec, int32_t TargetVelocity);
void Motor_PV_Zero(void);
void Motor_PV_Go(uint32_t _PV_spd);
void Motor_PV_Left(uint32_t _PV_spd);
void Motor_PV_Right(uint32_t _PV_spd);
void Motor_PV_Back(uint32_t _PV_spd);
void Motor_enable(void);
void Motor_Disable(void);
uint32_t rpm_to_hex(uint32_t rpm);
void dao_chieu(void);

#endif
