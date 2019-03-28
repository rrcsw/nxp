/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱i.MX RT1052核心板-智能车板
【编    写】CHIUSIR
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2018年2月1日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR8.20.1及以上版本
【Target 】 i.MX RT1052
【Crystal】 24.000Mhz
【ARM PLL】 1200MHz
【SYS PLL】 528MHz
【USB PLL】 480MHz

GPIO2_IO23  -------->  管脚B12   ----- >  核心板G灯
GPIO3_IO26  -------->  管脚A7    ----- >  核心板R灯
GPIO3_IO27  -------->  管脚C7    ----- >  核心板B灯

GPIO2_IO22  -------->  管脚C12   ----- >  母板D0
GPIO2_IO25  -------->  管脚A13   ----- >  母板D1
字段解释： 
2.0、SRE 数据位：0 
SRE(Slew Rate Field)：转换速度字段？？？这是一个可以调整高低电平切换上升和下降时间速度的设置项，在一般的应用中使用芯片默认的设置就可以了。在需要微调SI或EMI性能时可以尝试修改配置 
可选的值： 
0 SRE_0_Slow_Slew_Rate — Slow Slew Rate：转换速度慢 
1 SRE_1_Fast_Slew_Rate — Fast Slew Rate： 转换速度快

2.1、DSE 数据位5-3 
DSE(Drive Strength Field)：驱动能力字段，作为输出时有效 
可选的值： 
000 DSE_0_output_driver_disabled_ — output driver disabled; 禁止输出 
001 DSE_1_R0_260_Ohm___3_3V__150_Ohm_1_8V__240_Ohm_for_DDR_ — R0(260 Ohm @ 
3.3V, 150 Ohm@1.8V, 240 Ohm for DDR) -R0：260欧姆@3.3v；150欧姆@1.8v 
010 DSE_2_R0_2 — R0/2 -R0的二分之一，一下类同 
011 DSE_3_R0_3 — R0/3 
100 DSE_4_R0_4 — R0/4 
101 DSE_5_R0_5 — R0/5 
110 DSE_6_R0_6 — R0/6 
111 DSE_7_R0_7 — R0/7

2.2、SPEED 数据位7-6 
Speed Field：速度字段 
可选的值 
00 SPEED_0_low_50MHz_ — low(50MHz) 最低50MHz 
01 SPEED_1_medium_100MHz_ — medium(100MHz)中间值100MHz 
10 SPEED_2_medium_100MHz_ — medium(100MHz)中间值100MHz 
11 SPEED_3_max_200MHz_ — max(200MHz) 最大200MHz

2.3、ODE 数据位11 
ODE(Open Drain Enable Field)：漏极开路？？？作为输出时有效，依靠外部电压，提高输出能力 
可选的值： 
0 ODE_0_Open_Drain_Disabled — Open Drain Disabled ：禁止漏极开路 
1 ODE_1_Open_Drain_Enabled — Open Drain Enabled： 使能漏极开路

2.4、PKE 数据位12 
PKE(Pull / Keep Enable Field)：拉/保持使能字段 
可选的值： 
0 PKE_0_Pull_Keeper_Disabled — Pull/Keeper Disabled： 禁止拉/保持 
1 PKE_1_Pull_Keeper_Enabled — Pull/Keeper Enabled： 使能拉/保持

2.5、PUE 数据位13 
PUE(Pull / Keep Select Field)：拉/保持选择字段？？？两者不能同时设置， 
保持：使能输入状态保存器可以在IO供电NVCC_xxx关掉之后，使输入缓冲器的输出自动维持在关电之前的逻辑状态。其价值可以在低功耗的应用中得到体现。 
使能输出状态保存器可以在内核供电关掉之后，使IO的输出自动维持在关电之前的逻辑状态(需要注意的是输出状态保存器不能与上下拉同时工作)。其价值同样可以体现在低功耗的应用中 
可选的值： 
0 PUE_0_Keeper — Keeper ：保持 
1 PUE_1_Pull — Pull ：拉

2.6、PUS 数据位15-14 
PUS(Pull Up / Down Config. Field)：上拉/下拉配置？？？主要作用是提高输出信号的驱动能力、确定输入信号的电平（防止干扰） 
可选的值： 
00 PUS_0_100K_Ohm_Pull_Down — 100K Ohm Pull Down ：100K欧姆的拉低 
01 PUS_1_47K_Ohm_Pull_Up — 47K Ohm Pull Up ：47K欧姆的拉高 
10 PUS_2_100K_Ohm_Pull_Up — 100K Ohm Pull Up ：100K欧姆的拉高 
11 PUS_3_22K_Ohm_Pull_Up — 22K Ohm Pull Up ：22K欧姆的拉高

2.77、HYS 数据位16 
HYS(Hyst. Enable Field)：磁滞使能字段？？？作为输入时有效 
0 HYS_0_Hysteresis_Disabled — Hysteresis Disabled：禁止磁滞 
1 HYS_1_Hysteresis_Enabled — Hysteresis Enabled： 使能磁滞
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"

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

