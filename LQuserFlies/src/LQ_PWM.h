/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�LPC546XX���İ�
����    д��CHIUSIR
����    ע��
������汾��V1.0
�������¡�2017��11��19��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
���������䡿chiusir@163.com
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"
#ifndef __LQPWM_H__
#define __LQPWM_H__


extern void LQ_SetMotorDty(uint8_t num, short duty);
extern void LQ_SetServoDty(uint16_t duty);

extern void Test_Servo(void);//�������
extern void Test_Motor(void);//�������
void Test_Servo_K(void);
extern void LQPWM_Init(void);
void Test_PWM_nCH(void);

extern void LQ_PWM_Init(PWM_Type *base, pwm_submodule_t subModule, pwm_channels_t pwm_channels, uint16_t Frequency);
extern void LQ_PWM_SetDuty(PWM_Type *base, pwm_submodule_t subModule, pwm_channels_t pwm_channels, uint16_t duty);
extern void LQ_PWMA_B_SetDuty(PWM_Type *base, pwm_submodule_t subModule, uint16_t duty1, uint16_t duty2);
#endif 



