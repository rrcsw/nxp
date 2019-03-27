#ifndef __LQ_CONTROL_H
#define __LQ_CONTROL_H

#include "include.h"
#include "PID.h"

#define STRAIGHT_SPEED  80          //ֱ���ٶ�
#define BRAKE_SPEED     40          //����ǰ����
#define CURVE_SPEED     60          //������ٶ�

extern void TEST(void);
extern void LQ_Control_Motor(int16_t velocity);
extern void LQ_Control_Servo(void);    //PID�������
extern void seek_road(void);
extern void LQ_Line_Hunting(uint8_t Pixle [Use_ROWS][Use_Line]);
#endif