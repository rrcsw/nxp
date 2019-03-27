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
#ifndef __LQ_LED_H__
#define __LQ_LED_H__

#include "include.h"

extern gpio_pin_config_t GPIO_Output_Config;  
/*******************************************************************************
* Definitions
******************************************************************************/
extern gpio_pin_config_t GPIO_Output_Config;

//����ģ���
typedef enum
{
  LED_G=1,
  LED_R=2,   
  LED_B=3,
  LEDALL=5,//ȫ��   
} LEDn_e;
typedef enum
{
  white = 0,  //��ɫ
  black = 1,  //��ɫ
  red   = 2,  //��
  green = 3,  //��
  blue  = 4,  //��ɫ 
  yellow= 5,  //��ɫ
  violet= 6,  //��ɫ
  cyan  = 7,  //��ɫ
}LED_t;

typedef enum
{
  ON=0,  //��
  OFF=1, //��
  RVS=2, //��ת  
}LEDs_e;
extern void LED_Color(LED_t color);
extern void LED_Color_Reverse(LED_t color);
extern void LED_Init(void);
extern void LED_Ctrl(LEDn_e ledno, LEDs_e sta);
extern void Test_LED(void);

#endif 
