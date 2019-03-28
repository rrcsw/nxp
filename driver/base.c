/**
  *
  * @file    base.c
  * @author  
  * @version 
  * @date    2019/3/7
  * @brief   
  *
  */


/* Includes ------------------------------------------------------------------*/
#include "base.h"




/* Global Variable Definition ------------------------------------------------*/
gpio_pin_config_t GPIO_Input_Config = {kGPIO_DigitalInput,      //输入方向
                                     1,                         //高电平
                                     kGPIO_NoIntmode,           //不触发中断
                                     };
//一般输入中断口管脚定义
gpio_pin_config_t GPIO_ExInt_Config = {kGPIO_DigitalInput,//GPIO为输入方向
                                      0,                    //低电平
                                      kGPIO_IntRisingEdge,  //上升沿触发中断
                                      };


/* Function Definition -------------------------------------------------------*/

/*!
 * @brief 按键初始化
 */
void LQ_KEY_Init(void)
{  
  CLOCK_EnableClock(kCLOCK_Iomuxc);          // IO口时钟使能
  
  IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_GPIO3_IO04,0U);//管脚P2
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_11_GPIO2_IO27,0U);   //管脚C13
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_14_GPIO2_IO30,0U);   //管脚C14
  
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_11_GPIO2_IO27,0xF080); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_14_GPIO2_IO30,0xF080);
  IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_04_GPIO3_IO04,0xF080);
 
  GPIO_PinInit(GPIO2, 27, &GPIO_Input_Config);        // GPIO输入口，非中断
  GPIO_PinInit(GPIO2, 30, &GPIO_Input_Config);        // GPIO输入口，非中断
  GPIO_PinInit(GPIO3,  4, &GPIO_Input_Config);        // GPIO输入口，非中断
     
}



/*!
 * @brief 读取按键
 *
 * @param 按键模式
 * @param pin GPIO port pin number.
 * @retval GPIO port input value.
 */
uint8_t LQ_KEY_Read(uint8_t mode)
{
    static uint8_t key_up=1;     //按键松开标志
    if(mode==1) 
    {
      key_up=1;    //支持连按
    }
    if(key_up && (GPIO_PinRead(GPIO2, 27)==0 || GPIO_PinRead(GPIO2, 30)==0) || GPIO_PinRead(GPIO3, 4)==0)
    {
      delayms(10);   //消抖
      key_up=0;
      if(GPIO_PinRead(GPIO2, 27)==0)      
      {
          return 1;
      }
      
      else if(GPIO_PinRead(GPIO2, 30)==0) 
      {
          return 2;    
      }
      
      else if(GPIO_PinRead(GPIO3,  4)==0) 
      {
          return 3;    
      }
      
    }
    if(GPIO_PinRead(GPIO2, 27)==1 && GPIO_PinRead(GPIO2, 30)==1 && GPIO_PinRead(GPIO3,  4)==1) 
    {
     key_up=1;   
    }
    return 0;   //无按键按下
     
}



/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Whether the SW is turned on */
volatile bool g_InputSignal = false;
volatile int key_ok = true;
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】CHIUSIR
【功能说明】中断服务函数
【软件版本】V1.0
【最后更新】2018年11月24日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void GPIO5_Combined_0_15_IRQHandler(void)
{ 
    delayms(10);      //消抖
    /* clear the interrupt status */
    if(GPIO_GetPinsInterruptFlags(GPIO5)&(1<<0))    //判断是否为GPIO5_0中断
    {
        g_InputSignal = true;                      //标志位
        key_ok = 0;
    }
    GPIO_PortClearInterruptFlags(GPIO5, 1U << 0);   //清除标志位
    /* Change state of switch. */

    __DSB();				//数据同步屏蔽指令
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】CHIUSIR
【功能说明】按键或者输入GPIO口中断测试   按下核心板WUP按键，显示1s红灯
【软件版本】V1.0
【最后更新】2018年11月24日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_GPIO_ExInt(void)
{
    LED_Init();
    
    /*GPIO 外部中断配置开始*/
    CLOCK_EnableClock(kCLOCK_Iomuxc);                         // IO口时钟使能
    IOMUXC_SetPinMux(IOMUXC_SNVS_WAKEUP_GPIO5_IO00,0U);       // 设置管脚复用功能                          
    IOMUXC_SetPinConfig(IOMUXC_SNVS_WAKEUP_GPIO5_IO00,0xF080);// 配置管脚
    
    gpio_pin_config_t GPIO_Input_Config =                     // GPIO初始化结构体
    {
        kGPIO_DigitalInput,                                   // GPIO为输入方向
        1,                                                    // 高电平
        kGPIO_IntFallingEdge,                                 // 下降沿触发中断
    };
    GPIO_PinInit(GPIO5, 0, &GPIO_Input_Config);               // GPIO输入口，中断
    
    GPIO_PortEnableInterrupts(GPIO5,1<<0);			          // GPIO5_00中断使能
    //优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断
    NVIC_SetPriority(GPIO5_Combined_0_15_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
	EnableIRQ(GPIO5_Combined_0_15_IRQn);			          //使能GPIO5_0~15IO的中断  
    /*GPIO 外部中断配置结束*/
    printf("GPIO功能测试：LED驱动，按键输入，外部中断测试开始...\r\n");
    
    while(1)
    {
        if(g_InputSignal)
        {        
            printf("\r\n Wake Up按键被按下！");      
            /* Reset state of switch. */
            g_InputSignal = false; 
            LED_Color(red);           //红灯 
            delayms(1000);
        }   
        LED_Color(blue);    //蓝灯
    }
}








//GPIO2_IO23  -------->  管脚B12   ----- >  核心板G灯
//GPIO3_IO26  -------->  管脚A7    ----- >  核心板R灯
//GPIO3_IO27  -------->  管脚C7    ----- >  核心板B灯

//GPIO2_IO22  -------->  管脚C12   ----- >  母板D1
//GPIO2_IO25  -------->  管脚A13   ----- >  母板D0
//一般输出口管脚定义
gpio_pin_config_t GPIO_Output_Config = {kGPIO_DigitalOutput, //GPIO为输出方向
                                        0,                   //低电平
                                        kGPIO_NoIntmode      //非中断模式
                                        };   
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】CHIUSIR
【功能说明】初始化LED所用IO口
【软件版本】V1.0
【最后更新】2017年11月24日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LED_Init(void)
{    
  CLOCK_EnableClock(kCLOCK_Iomuxc);           // IO口时钟使能
/*       核心板上的LED       */
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_07_GPIO2_IO23, 0U);
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_40_GPIO3_IO26, 0U);
  IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_41_GPIO3_IO27, 0U);

  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_07_GPIO2_IO23,0x10B0u);
  IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_40_GPIO3_IO26,0x10B0u);
  IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_41_GPIO3_IO27,0x10B0u);
  
  // Init output LED GPIO.

  GPIO_PinInit(GPIO2,23, &GPIO_Output_Config);      //  
  GPIO_PinInit(GPIO3,26, &GPIO_Output_Config);      //  
  GPIO_PinInit(GPIO3,27, &GPIO_Output_Config);      //   
  
  /*             母板上的lED引脚             */
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_GPIO2_IO22, 0U);
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_09_GPIO2_IO25, 0U);
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_06_GPIO2_IO22,0x10B0u);
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_09_GPIO2_IO25,0x10B0u);
  GPIO_PinInit(GPIO2,22, &GPIO_Output_Config);      //C12  D1
  GPIO_PinInit(GPIO2,25, &GPIO_Output_Config);      //A13  D0
  
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】Z
【功能说明】指定灯颜色
【软件版本】V1.0
【最后更新】2018年11月14日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LED_Color(LED_t color)
{
    switch(color)
    {
        case white:
            GPIO_PinWrite(GPIO2,23, 0U);//LED亮; 
            GPIO_PinWrite(GPIO3,26, 0U);//LED亮; 
            GPIO_PinWrite(GPIO3,27, 0U);//LED亮; 
            break;
        case black:
            GPIO_PinWrite(GPIO2,23, 1U);//LED灭; 
            GPIO_PinWrite(GPIO3,26, 1U);//LED灭; 
            GPIO_PinWrite(GPIO3,27, 1U);//LED灭; 
            break;
        case red:
            GPIO_PinWrite(GPIO2,23, 1U);//LED灭; 
            GPIO_PinWrite(GPIO3,26, 0U);//LED亮; 
            GPIO_PinWrite(GPIO3,27, 1U);//LED灭; 
            break;
        case green:
            GPIO_PinWrite(GPIO2,23, 0U);//LED灭; 
            GPIO_PinWrite(GPIO3,26, 1U);//LED亮; 
            GPIO_PinWrite(GPIO3,27, 1U);//LED灭; 
            break;
        case blue:
            GPIO_PinWrite(GPIO2,23, 1U);//LED灭; 
            GPIO_PinWrite(GPIO3,26, 1U);//LED亮; 
            GPIO_PinWrite(GPIO3,27, 0U);//LED灭; 
            break;
        case yellow:
            GPIO_PinWrite(GPIO2,23, 0U);//LED灭; 
            GPIO_PinWrite(GPIO3,26, 0U);//LED亮; 
            GPIO_PinWrite(GPIO3,27, 1U);//LED灭; 
            break;
        case violet:
            GPIO_PinWrite(GPIO2,23, 1U);//LED灭; 
            GPIO_PinWrite(GPIO3,26, 0U);//LED亮; 
            GPIO_PinWrite(GPIO3,27, 0U);//LED灭; 
            break;
        case cyan:
            GPIO_PinWrite(GPIO2,23, 0U);//LED灭; 
            GPIO_PinWrite(GPIO3,26, 1U);//LED亮; 
            GPIO_PinWrite(GPIO3,27, 0U);//LED灭; 
            break;
    }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】Z
【功能说明】指定颜色闪烁
【软件版本】V1.0
【最后更新】2018年11月14日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LED_Color_Reverse(LED_t color)
{
    static uint8_t count = 0;
    if(count++ % 2)
    {
        LED_Color(color);   //亮指定颜色的灯
    }
    else
    {
        LED_Color(black);   //灭
    }
    
}


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】CHIUSIR
【功能说明】控制IO输出高低电平
【软件版本】V1.0
【最后更新】2017年11月24日 
【函数名】
【返回值】无
【参数值】
LEDn_e ledno, 编号
LEDs_e sta 状态，亮灭
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LED_Ctrl(LEDn_e ledno, LEDs_e sta)
{
  switch(ledno) 
  {
  case LED_G:
    if(sta==ON)        GPIO_PinWrite(GPIO2,23, 0U);//LED亮; 
    else if(sta==OFF) GPIO_PinWrite(GPIO2,23, 1U);//LED灭 
    else if(sta==RVS) GPIO_PinReverse (GPIO2, 23); //LED反转
    break;  
  case LED_R:
    if(sta==ON)        GPIO_PinWrite(GPIO3,26, 0U);//LED亮; 
    else if(sta==OFF) GPIO_PinWrite(GPIO3,26, 1U);//LED灭 
    else if(sta==RVS) GPIO_PinReverse (GPIO3, 26); //LED反转
    break;    
  case LED_B:
    if(sta==ON)        GPIO_PinWrite(GPIO3, 27, 0U);//LED亮; 
    else if(sta==OFF) GPIO_PinWrite(GPIO3, 27, 1U);//LED灭 
    else if(sta==RVS) GPIO_PinReverse (GPIO3, 27); //LED反转
    break; 
  case LEDALL:
    if(sta==ON) 
    {        
      GPIO_PinWrite(GPIO2,23, 0U);//LED亮; 
      GPIO_PinWrite(GPIO3,26, 0U);//LED亮; 
      GPIO_PinWrite(GPIO3,27, 0U);//LED亮; 
    }
    else if(sta==OFF)
    {  
      GPIO_PinWrite(GPIO2,23, 1U);//LED亮; 
      GPIO_PinWrite(GPIO3,26, 1U);//LED亮; 
      GPIO_PinWrite(GPIO3,27, 1U);//LED亮; 
    }
    else if(sta==RVS)
    {       
      GPIO_PinReverse (GPIO3, 27); //Toggle on target LED
      GPIO_PinReverse (GPIO3, 26); 
      GPIO_PinReverse (GPIO2, 23);
    }
    break;
  default:
    break;    
  }   
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】Z
【功能说明】测试LED亮灭，流水灯
【软件版本】V1.0
【最后更新】2018年11月14日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_LED(void)
{
  LED_Init();
  LED_Ctrl(LEDALL, OFF);    
  while (1)
  {          
        LED_Color(red);     //红灯
        delayms(500);
        LED_Color(green);   //绿灯
        delayms(500);
        LED_Color(blue);    //蓝灯
        delayms(500);
        LED_Color(violet);  //紫灯
        delayms(500);
        LED_Color(yellow);  //黄灯
        delayms(500);
        LED_Color(cyan);    //青灯
        delayms(500);
        LED_Color(white);   //白灯
        delayms(500);
        LED_Color(black);   //关灯
        delayms(500);
  }
}


