#ifndef _BASE_H
#define _BASE_H


#include "system.h"


/*******************************************************************************
* Definitions
******************************************************************************/
extern gpio_pin_config_t GPIO_Input_Config;
extern gpio_pin_config_t GPIO_ExInt_Config;
//定义模块号
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

//定义模块号
typedef enum
{
  LED_G=1,
  LED_R=2,   
  LED_B=3,
  LEDALL=5,//全部   
} LEDn_e;
typedef enum
{
  white = 0,  //白色
  black = 1,  //黑色
  red   = 2,  //红
  green = 3,  //绿
  blue  = 4,  //蓝色 
  yellow= 5,  //黄色
  violet= 6,  //紫色
  cyan  = 7,  //青色
}LED_t;

typedef enum
{
  ON=0,  //亮
  OFF=1, //灭
  RVS=2, //反转  
}LEDs_e;
extern void LED_Color(LED_t color);
extern void LED_Color_Reverse(LED_t color);
extern void LED_Init(void);
extern void LED_Ctrl(LEDn_e ledno, LEDs_e sta);
extern void Test_LED(void);


#endif
