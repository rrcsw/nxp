/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1052���İ�-���ܳ���
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2018��2��1��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR8.20.1�����ϰ汾
��Target �� i.MX RT1052
��Crystal�� 24.000Mhz
��ARM PLL�� 1200MHz
��SYS PLL�� 528MHz
��USB PLL�� 480MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef __LQ_KEY_H__
#define __LQ_KEY_H__

#include "include.h"

/*******************************************************************************
* Definitions
******************************************************************************/
extern gpio_pin_config_t GPIO_Input_Config;
extern gpio_pin_config_t GPIO_ExInt_Config;
//����ģ���
typedef enum
{
    KEY0=0,
    KEY1=1,
    KEY2=2,   
} KEYn_e;
typedef enum
{
    LOW=0,  //DOWN
    HIGH=1, //UP  
    FAIL=0xff,
}KEYs_e;

extern void LQ_KEY_Init(void);
extern uint8_t LQ_KEY_Read(uint8_t mode);
extern void Test_GPIO_KEY(void);
extern void Test_GPIO_ExInt(void);
#endif 
