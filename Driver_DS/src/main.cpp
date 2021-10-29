#include <Arduino.h>
#include <FlexCAN_T4.h>


FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can0;
CAN_message_t msg;

// tham so cua driver
#define SDO_W1 0x2F //ask write 1 byte
#define SDO_W2 0x2B //ask write 2 byte
#define SDO_W4 0x23 //ask write 4 byte
#define SDO_RD 0x40 //ask read data
//#define PP_Mode 1
#define PV_Mode 3
//#define PT_Mode 4
//CAN ID
#define Left_Wheel_ID 0x0001
#define Right_Wheel_ID 0x0002
/* Variable */
uint8_t CAN1Sedbuf[8];
uint32_t PV_spd;
//uint32_t PP_spd;
//uint32_t PT_spd;

uint8_t SDO_Write_OD(uint8_t CANopen_ID, uint8_t CMD, uint16_t Index, uint8_t SubIndex, uint32_t DATA);
uint8_t Contol_Mode_SET(uint8_t CANopen_ID, uint8_t CANopen_mode);
uint8_t CANopen_Activate(uint8_t CANopen_ID);
void CANopen_PV_Init(void);
void CANopen_PV_SET(uint32_t Acc, uint32_t Dec, int32_t TargetVelocity);
void Motor_PV_Zero(void);
void Motor_PV_Go(uint32_t _PV_spd);
void Motor_PV_Left(uint32_t _PV_spd);
void Motor_PV_Right(uint32_t _PV_spd);
void Motor_PV_Back(uint32_t _PV_spd);
void Motor_enable(void);
void Motor_Disable(void);

void setup(void)
{
  can0.begin();
  can0.setBaudRate(250000);
  CANopen_PV_Init();
  Motor_enable();
}

void loop()
{
  Motor_PV_Go(rpm_to_hex(10));
  delay(3000);
  Motor_PV_Left(rpm_to_hex(10));
  delay(3000);
  Motor_PV_Back(rpm_to_hex(10));
  delay(3000);
  Motor_PV_Right(rpm_to_hex(10));
  delay(3000);
  Motor_PV_Zero();
  delay(3000);
}

uint8_t SDO_Write_OD(uint8_t CANopen_ID, uint8_t CMD, uint16_t Index, uint8_t SubIndex, uint32_t DATA)
{
  msg.buf[0] = CMD;
  msg.buf[1] = (uint8_t)(Index & 0xFF);
  msg.buf[2] = (uint8_t)(Index >> 8 & 0xFF);
  msg.buf[3] = SubIndex;
  msg.buf[4] = (uint8_t)(DATA & 0xFF);
  msg.buf[5] = (uint8_t)(DATA >> 8 & 0xFF);
  msg.buf[6] = (uint8_t)(DATA >> 16 & 0xFF);
  msg.buf[7] = (uint8_t)(DATA >> 24 & 0xFF);
  //msg.id = CANopen_ID;
  msg.id = 0x600 + CANopen_ID;
  msg.len = 8;
  can0.write(msg);
  delay(5);
  return (1);
}

uint8_t Contol_Mode_SET(uint8_t CANopen_ID, uint8_t CANopen_mode)
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
  can0.write(msg);
  delay(5);
  return (1);
}

uint8_t CANopen_Activate(uint8_t CANopen_ID)
{
  CAN1Sedbuf[0] = 0x01;
  CAN1Sedbuf[1] = CANopen_ID;
  msg.id = 0x000;
  msg.len = 2;
  can0.write(msg);
  delay(5);
  return (1);
}

void CANopen_PV_Init(void)
{

  // Step 1: Dam bao driver dang o mode CANopen
  // He tham so 1: Fn00=20; he tham so 2: F0/1.1.002=20
  // Step 2: Node duoc set thanh controllabe status
  // send: 000 01 02 set node 2 thanh controllabe status
  CANopen_Activate(Left_Wheel_ID);
  CANopen_Activate(Right_Wheel_ID);
  // Step 3: Config
  // 1. Set mode lam viec (6060H) lam mode van toc
  // vd: send: 602 2F 60 60 00 03 00 00 00
  Contol_Mode_SET(Left_Wheel_ID, PV_Mode);
  Contol_Mode_SET(Right_Wheel_ID, PV_Mode);
  // 2. set thoi gian thay doi toc do tu 0rpm den 3000rpm (tang toc 6083h, giam toc 6084h), don vi ms,
  // set 6083h = 1s - send: 602 23 83 60 00 E8 03 00 00
  // set 6084h = 1s - send: 602 23 84 60 00 E8 03 00 00
  SDO_Write_OD(Left_Wheel_ID, SDO_W4, 0x6083, 0x00, 0x000003e8);
  SDO_Write_OD(Left_Wheel_ID, SDO_W4, 0x6084, 0x00, 0x000003e8);
  SDO_Write_OD(Right_Wheel_ID, SDO_W4, 0x6083, 0x00, 0x000003e8);
  SDO_Write_OD(Right_Wheel_ID, SDO_W4, 0x6084, 0x00, 0x000003e8);
  // 3. Set toc do muc tieu: 60FFh,don vi 0,1rpm
  // set 60FFh = 10rpm - send: 602 23 FF 60 00 64 00 00 00
  SDO_Write_OD(Left_Wheel_ID, SDO_W4, 0x60FF, 0x00, 0x00000000);
  SDO_Write_OD(Right_Wheel_ID, SDO_W4, 0x60FF, 0x00, 0x00000000);
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
  SDO_Write_OD(Left_Wheel_ID, SDO_W4, 0x6040, 0x00, 0x06);
  SDO_Write_OD(Right_Wheel_ID, SDO_W4, 0x6040, 0x00, 0x06);
  // set 6040h = 7 - Disable - send: 602 2B 40 60 00 06 00 00 00
  SDO_Write_OD(Left_Wheel_ID, SDO_W4, 0x6040, 0x00, 0x07);
  SDO_Write_OD(Right_Wheel_ID, SDO_W4, 0x6040, 0x00, 0x07);
  // set 6040h = F - Enable - send: 602 2B 40 60 00 06 00 00 00
  SDO_Write_OD(Left_Wheel_ID, SDO_W4, 0x6040, 0x00, 0x0F);
  SDO_Write_OD(Right_Wheel_ID, SDO_W4, 0x6040, 0x00, 0x0F);
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
