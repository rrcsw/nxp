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

GPIO3_IO04 ------ �ܽ�P2   ----- >  ĸ�尴��K2
GPIO2_IO27 ------ �ܽ�C13  ----- >  ĸ�尴��K0
GPIO2_IO30 ------ �ܽ�C14  ----- >  ĸ�尴��k1
GPIO5_I000 ------ �ܽ�L6   ----- >  ���İ尴��WUP

�ֶν��ͣ� 
2.0��SRE ����λ��0 
SRE(Slew Rate Field)��ת���ٶ��ֶ� ����һ�����Ե����ߵ͵�ƽ�л��������½�ʱ���ٶȵ������
��һ���Ӧ����ʹ��оƬĬ�ϵ����þͿ����ˡ�����Ҫ΢��SI��EMI����ʱ���Գ����޸����� 
��ѡ��ֵ�� 
0 SRE_0_Slow_Slew_Rate �� Slow Slew Rate��ת���ٶ��� 
1 SRE_1_Fast_Slew_Rate �� Fast Slew Rate�� ת���ٶȿ�

2.1��DSE ����λ5-3 
DSE(Drive Strength Field)�����������ֶΣ���Ϊ���ʱ��Ч 
��ѡ��ֵ�� 
000 DSE_0_output_driver_disabled_ �� output driver disabled; ��ֹ��� 
001 DSE_1_R0_260_Ohm___3_3V__150_Ohm_1_8V__240_Ohm_for_DDR_ �� R0(260 Ohm 
@ 3.3V, 150 Ohm@1.8V, 240 Ohm for DDR) -R0��260ŷķ@3.3v��150ŷķ@1.8v 
010 DSE_2_R0_2 �� R0/2 -R0�Ķ���֮һ��һ����ͬ 
011 DSE_3_R0_3 �� R0/3 
100 DSE_4_R0_4 �� R0/4 
101 DSE_5_R0_5 �� R0/5 
110 DSE_6_R0_6 �� R0/6 
111 DSE_7_R0_7 �� R0/7

2.2��SPEED ����λ7-6 
Speed Field���ٶ��ֶ� 
��ѡ��ֵ 
00 SPEED_0_low_50MHz_ �� low(50MHz) ���50MHz 
01 SPEED_1_medium_100MHz_ �� medium(100MHz)�м�ֵ100MHz 
10 SPEED_2_medium_100MHz_ �� medium(100MHz)�м�ֵ100MHz 
11 SPEED_3_max_200MHz_ �� max(200MHz) ���200MHz

2.3��ODE ����λ11 
ODE(Open Drain Enable Field)��©����·��������Ϊ���ʱ��Ч�������ⲿ��ѹ������������ 
��ѡ��ֵ�� 
0 ODE_0_Open_Drain_Disabled �� Open Drain Disabled ����ֹ©����· 
1 ODE_1_Open_Drain_Enabled �� Open Drain Enabled�� ʹ��©����·

2.4��PKE ����λ12 
PKE(Pull / Keep Enable Field)����/����ʹ���ֶ� 
��ѡ��ֵ�� 
0 PKE_0_Pull_Keeper_Disabled �� Pull/Keeper Disabled�� ��ֹ��/���� 
1 PKE_1_Pull_Keeper_Enabled �� Pull/Keeper Enabled�� ʹ����/����

2.5��PUE ����λ13 
PUE(Pull / Keep Select Field)����/����ѡ���ֶΣ��������߲���ͬʱ���ã� 
���֣�ʹ������״̬������������IO����NVCC_xxx�ص�֮��ʹ���뻺����������Զ�ά���ڹص�֮ǰ���߼�״̬�����ֵ�����ڵ͹��ĵ�Ӧ���еõ����֡� 
ʹ�����״̬�������������ں˹���ص�֮��ʹIO������Զ�ά���ڹص�֮ǰ���߼�״̬(��Ҫע��������״̬������������������ͬʱ����)�����ֵͬ�����������ڵ͹��ĵ�Ӧ���� 
��ѡ��ֵ�� 
0 PUE_0_Keeper �� Keeper ������ 
1 PUE_1_Pull �� Pull ����

2.6��PUS ����λ15-14 
PUS(Pull Up / Down Config. Field)������/�������ã�������Ҫ�������������źŵ�����������ȷ�������źŵĵ�ƽ����ֹ���ţ� 
��ѡ��ֵ�� 
00 PUS_0_100K_Ohm_Pull_Down �� 100K Ohm Pull Down ��100Kŷķ������ 
01 PUS_1_47K_Ohm_Pull_Up �� 47K Ohm Pull Up ��47Kŷķ������ 
10 PUS_2_100K_Ohm_Pull_Up �� 100K Ohm Pull Up ��100Kŷķ������ 
11 PUS_3_22K_Ohm_Pull_Up �� 22K Ohm Pull Up ��22Kŷķ������

2.77��HYS ����λ16 
HYS(Hyst. Enable Field)������ʹ���ֶΣ�������Ϊ����ʱ��Ч 
0 HYS_0_Hysteresis_Disabled �� Hysteresis Disabled����ֹ���� 
1 HYS_1_Hysteresis_Enabled �� Hysteresis Enabled�� ʹ�ܴ���
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"

//GPIO3_IO04 ------ �ܽ�P2   ----- >  ĸ�尴��K2
//GPIO2_IO27 ------ �ܽ�C13  ----- >  ĸ�尴��K0
//GPIO2_IO30 ------ �ܽ�C14  ----- >  ĸ�尴��k1
//GPIO5_I000 ------ �ܽ�L6   ----- >  ���İ尴��WUP

//һ������ڹܽŶ���
gpio_pin_config_t GPIO_Input_Config = {kGPIO_DigitalInput,    //GPIOΪ���뷽��
                               1,                    //�ߵ�ƽ
                               kGPIO_NoIntmode,      //�������ж�
                               };
//һ�������жϿڹܽŶ���
gpio_pin_config_t GPIO_ExInt_Config = {kGPIO_DigitalInput,//GPIOΪ���뷽��
                                  0,                    //�͵�ƽ
                                  kGPIO_IntRisingEdge,  //�����ش����ж�
                                  };
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵���������ܽų�ʼ��
������汾��V1.0
�������¡�2018��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
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

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵��������������
������汾��V1.0
�������¡�2017��11��24�� 
����������
������ֵ��0���ް������� 1������1����  2:����2����
������ֵ��mode:0,��֧��������;1,֧��������;
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
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

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵�������԰�����OLED��ʾ
������汾��V1.0
�������¡�2017��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_GPIO_KEY(void)
{ 
    LED_Init();
    LQ_KEY_Init(); 
    TFTSPI_Init();               //TFT1.8��ʼ��  
    TFTSPI_CLS(u16BLUE);           //����
    while (1)
    {  
        //���԰���      

        switch(LQ_KEY_Read(0))  //
        {
            case 1:
                TFTSPI_CLS(u16WHITE);           //����
                TFTSPI_P8X8Str(4,3,(uint8_t*)"KEY0 Pressed!   ",u16RED,u16BLUE);
                LED_Ctrl(LED_B, RVS);
                break;           
            case 2:      
                TFTSPI_CLS(u16WHITE);           //����
                TFTSPI_P8X8Str(4,5,(uint8_t*)"KEY1 Pressed!   ",u16RED,u16BLUE);
                LED_Ctrl(LED_R, RVS);
                break;
            case 3:      
                TFTSPI_CLS(u16WHITE);           //����
                TFTSPI_P8X8Str(4,7,(uint8_t*)"KEY2 Pressed!   ",u16RED,u16BLUE);
                LED_Ctrl(LED_G, RVS);
                break;
            default:
                TFTSPI_P8X8Str(4,0,(uint8_t*)"LQ Test KEY",u16RED,u16BLUE);
                break;
        }
        //��ʱ
        delayms(50);
//        LED_Color_Reverse(red);  //����˸
    }
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
