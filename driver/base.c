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
gpio_pin_config_t GPIO_Input_Config = {kGPIO_DigitalInput,      //���뷽��
                                     1,                         //�ߵ�ƽ
                                     kGPIO_NoIntmode,           //�������ж�
                                     };
//һ�������жϿڹܽŶ���
gpio_pin_config_t GPIO_ExInt_Config = {kGPIO_DigitalInput,//GPIOΪ���뷽��
                                      0,                    //�͵�ƽ
                                      kGPIO_IntRisingEdge,  //�����ش����ж�
                                      };


/* Function Definition -------------------------------------------------------*/

/*!
 * @brief ������ʼ��
 */
void LQ_KEY_Init(void)
{  
  CLOCK_EnableClock(kCLOCK_Iomuxc);          // IO��ʱ��ʹ��
  
  IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_GPIO3_IO04,0U);//�ܽ�P2
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_11_GPIO2_IO27,0U);   //�ܽ�C13
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_14_GPIO2_IO30,0U);   //�ܽ�C14
  
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_11_GPIO2_IO27,0xF080); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_14_GPIO2_IO30,0xF080);
  IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_04_GPIO3_IO04,0xF080);
 
  GPIO_PinInit(GPIO2, 27, &GPIO_Input_Config);        // GPIO����ڣ����ж�
  GPIO_PinInit(GPIO2, 30, &GPIO_Input_Config);        // GPIO����ڣ����ж�
  GPIO_PinInit(GPIO3,  4, &GPIO_Input_Config);        // GPIO����ڣ����ж�
     
}



/*!
 * @brief ��ȡ����
 *
 * @param ����ģʽ
 * @param pin GPIO port pin number.
 * @retval GPIO port input value.
 */
uint8_t LQ_KEY_Read(uint8_t mode)
{
    static uint8_t key_up=1;     //�����ɿ���־
    if(mode==1) 
    {
      key_up=1;    //֧������
    }
    if(key_up && (GPIO_PinRead(GPIO2, 27)==0 || GPIO_PinRead(GPIO2, 30)==0) || GPIO_PinRead(GPIO3, 4)==0)
    {
      delayms(10);   //����
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
    return 0;   //�ް�������
     
}



/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Whether the SW is turned on */
volatile bool g_InputSignal = false;
volatile int key_ok = true;
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵�����жϷ�����
������汾��V1.0
�������¡�2018��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void GPIO5_Combined_0_15_IRQHandler(void)
{ 
    delayms(10);      //����
    /* clear the interrupt status */
    if(GPIO_GetPinsInterruptFlags(GPIO5)&(1<<0))    //�ж��Ƿ�ΪGPIO5_0�ж�
    {
        g_InputSignal = true;                      //��־λ
        key_ok = 0;
    }
    GPIO_PortClearInterruptFlags(GPIO5, 1U << 0);   //�����־λ
    /* Change state of switch. */

    __DSB();				//����ͬ������ָ��
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵����������������GPIO���жϲ���   ���º��İ�WUP��������ʾ1s���
������汾��V1.0
�������¡�2018��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_GPIO_ExInt(void)
{
    LED_Init();
    
    /*GPIO �ⲿ�ж����ÿ�ʼ*/
    CLOCK_EnableClock(kCLOCK_Iomuxc);                         // IO��ʱ��ʹ��
    IOMUXC_SetPinMux(IOMUXC_SNVS_WAKEUP_GPIO5_IO00,0U);       // ���ùܽŸ��ù���                          
    IOMUXC_SetPinConfig(IOMUXC_SNVS_WAKEUP_GPIO5_IO00,0xF080);// ���ùܽ�
    
    gpio_pin_config_t GPIO_Input_Config =                     // GPIO��ʼ���ṹ��
    {
        kGPIO_DigitalInput,                                   // GPIOΪ���뷽��
        1,                                                    // �ߵ�ƽ
        kGPIO_IntFallingEdge,                                 // �½��ش����ж�
    };
    GPIO_PinInit(GPIO5, 0, &GPIO_Input_Config);               // GPIO����ڣ��ж�
    
    GPIO_PortEnableInterrupts(GPIO5,1<<0);			          // GPIO5_00�ж�ʹ��
    //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
    NVIC_SetPriority(GPIO5_Combined_0_15_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
	EnableIRQ(GPIO5_Combined_0_15_IRQn);			          //ʹ��GPIO5_0~15IO���ж�  
    /*GPIO �ⲿ�ж����ý���*/
    printf("GPIO���ܲ��ԣ�LED�������������룬�ⲿ�жϲ��Կ�ʼ...\r\n");
    
    while(1)
    {
        if(g_InputSignal)
        {        
            printf("\r\n Wake Up���������£�");      
            /* Reset state of switch. */
            g_InputSignal = false; 
            LED_Color(red);           //��� 
            delayms(1000);
        }   
        LED_Color(blue);    //����
    }
}








//GPIO2_IO23  -------->  �ܽ�B12   ----- >  ���İ�G��
//GPIO3_IO26  -------->  �ܽ�A7    ----- >  ���İ�R��
//GPIO3_IO27  -------->  �ܽ�C7    ----- >  ���İ�B��

//GPIO2_IO22  -------->  �ܽ�C12   ----- >  ĸ��D1
//GPIO2_IO25  -------->  �ܽ�A13   ----- >  ĸ��D0
//һ������ڹܽŶ���
gpio_pin_config_t GPIO_Output_Config = {kGPIO_DigitalOutput, //GPIOΪ�������
                                        0,                   //�͵�ƽ
                                        kGPIO_NoIntmode      //���ж�ģʽ
                                        };   
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵������ʼ��LED����IO��
������汾��V1.0
�������¡�2017��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LED_Init(void)
{    
  CLOCK_EnableClock(kCLOCK_Iomuxc);           // IO��ʱ��ʹ��
/*       ���İ��ϵ�LED       */
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
  
  /*             ĸ���ϵ�lED����             */
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_GPIO2_IO22, 0U);
  IOMUXC_SetPinMux(IOMUXC_GPIO_B1_09_GPIO2_IO25, 0U);
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_06_GPIO2_IO22,0x10B0u);
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_09_GPIO2_IO25,0x10B0u);
  GPIO_PinInit(GPIO2,22, &GPIO_Output_Config);      //C12  D1
  GPIO_PinInit(GPIO2,25, &GPIO_Output_Config);      //A13  D0
  
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����ָ������ɫ
������汾��V1.0
�������¡�2018��11��14�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LED_Color(LED_t color)
{
    switch(color)
    {
        case white:
            GPIO_PinWrite(GPIO2,23, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 0U);//LED��; 
            break;
        case black:
            GPIO_PinWrite(GPIO2,23, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 1U);//LED��; 
            break;
        case red:
            GPIO_PinWrite(GPIO2,23, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 1U);//LED��; 
            break;
        case green:
            GPIO_PinWrite(GPIO2,23, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 1U);//LED��; 
            break;
        case blue:
            GPIO_PinWrite(GPIO2,23, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 0U);//LED��; 
            break;
        case yellow:
            GPIO_PinWrite(GPIO2,23, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 1U);//LED��; 
            break;
        case violet:
            GPIO_PinWrite(GPIO2,23, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 0U);//LED��; 
            break;
        case cyan:
            GPIO_PinWrite(GPIO2,23, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 0U);//LED��; 
            break;
    }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����ָ����ɫ��˸
������汾��V1.0
�������¡�2018��11��14�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LED_Color_Reverse(LED_t color)
{
    static uint8_t count = 0;
    if(count++ % 2)
    {
        LED_Color(color);   //��ָ����ɫ�ĵ�
    }
    else
    {
        LED_Color(black);   //��
    }
    
}


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵��������IO����ߵ͵�ƽ
������汾��V1.0
�������¡�2017��11��24�� 
����������
������ֵ����
������ֵ��
LEDn_e ledno, ���
LEDs_e sta ״̬������
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LED_Ctrl(LEDn_e ledno, LEDs_e sta)
{
  switch(ledno) 
  {
  case LED_G:
    if(sta==ON)        GPIO_PinWrite(GPIO2,23, 0U);//LED��; 
    else if(sta==OFF) GPIO_PinWrite(GPIO2,23, 1U);//LED�� 
    else if(sta==RVS) GPIO_PinReverse (GPIO2, 23); //LED��ת
    break;  
  case LED_R:
    if(sta==ON)        GPIO_PinWrite(GPIO3,26, 0U);//LED��; 
    else if(sta==OFF) GPIO_PinWrite(GPIO3,26, 1U);//LED�� 
    else if(sta==RVS) GPIO_PinReverse (GPIO3, 26); //LED��ת
    break;    
  case LED_B:
    if(sta==ON)        GPIO_PinWrite(GPIO3, 27, 0U);//LED��; 
    else if(sta==OFF) GPIO_PinWrite(GPIO3, 27, 1U);//LED�� 
    else if(sta==RVS) GPIO_PinReverse (GPIO3, 27); //LED��ת
    break; 
  case LEDALL:
    if(sta==ON) 
    {        
      GPIO_PinWrite(GPIO2,23, 0U);//LED��; 
      GPIO_PinWrite(GPIO3,26, 0U);//LED��; 
      GPIO_PinWrite(GPIO3,27, 0U);//LED��; 
    }
    else if(sta==OFF)
    {  
      GPIO_PinWrite(GPIO2,23, 1U);//LED��; 
      GPIO_PinWrite(GPIO3,26, 1U);//LED��; 
      GPIO_PinWrite(GPIO3,27, 1U);//LED��; 
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
����  �ߡ�Z
������˵��������LED������ˮ��
������汾��V1.0
�������¡�2018��11��14�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_LED(void)
{
  LED_Init();
  LED_Ctrl(LEDALL, OFF);    
  while (1)
  {          
        LED_Color(red);     //���
        delayms(500);
        LED_Color(green);   //�̵�
        delayms(500);
        LED_Color(blue);    //����
        delayms(500);
        LED_Color(violet);  //�ϵ�
        delayms(500);
        LED_Color(yellow);  //�Ƶ�
        delayms(500);
        LED_Color(cyan);    //���
        delayms(500);
        LED_Color(white);   //�׵�
        delayms(500);
        LED_Color(black);   //�ص�
        delayms(500);
  }
}


