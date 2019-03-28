#ifndef _BASE_H
#define _BASE_H


#include "system.h"


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
