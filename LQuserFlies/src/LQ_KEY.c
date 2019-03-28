/**
  *
  * @file    key.c
  * @author  
  * @version 
  * @date    2019/3/7
  * @brief   
  *
  */


/* Includes ------------------------------------------------------------------*/
#include "include.h"




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

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】CHIUSIR
【功能说明】测试按键及OLED显示
【软件版本】V1.0
【最后更新】2017年11月24日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_GPIO_KEY(void)
{ 
    LED_Init();
    LQ_KEY_Init(); 
    TFTSPI_Init();               //TFT1.8初始化  
    TFTSPI_CLS(u16BLUE);           //清屏
    while (1)
    {  
        //测试按键      

        switch(LQ_KEY_Read(0))  //
        {
            case 1:
                TFTSPI_CLS(u16WHITE);           //清屏
                TFTSPI_P8X8Str(4,3,(uint8_t*)"KEY0 Pressed!   ",u16RED,u16BLUE);
                LED_Ctrl(LED_B, RVS);
                break;           
            case 2:      
                TFTSPI_CLS(u16WHITE);           //清屏
                TFTSPI_P8X8Str(4,5,(uint8_t*)"KEY1 Pressed!   ",u16RED,u16BLUE);
                LED_Ctrl(LED_R, RVS);
                break;
            case 3:      
                TFTSPI_CLS(u16WHITE);           //清屏
                TFTSPI_P8X8Str(4,7,(uint8_t*)"KEY2 Pressed!   ",u16RED,u16BLUE);
                LED_Ctrl(LED_G, RVS);
                break;
            default:
                TFTSPI_P8X8Str(4,0,(uint8_t*)"LQ Test KEY",u16RED,u16BLUE);
                break;
        }
        //延时
        delayms(50);
//        LED_Color_Reverse(red);  //灯闪烁
    }
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
