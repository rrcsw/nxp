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
#include "include.h"


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵������������ܽŸ��ó�ʼ��
������汾��V1.0
�������¡�2018��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void QTMR_QD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);          /* iomuxc clock (iomuxc_clk_enable): 0x03u */

 
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_B1_00_QTIMER3_TIMER0,    /* GPIO_AD_B1_00 is configured as QTIMER3_TIMER0 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_B1_01_QTIMER3_TIMER1,    /* GPIO_AD_B1_01 is configured as QTIMER3_TIMER1 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_B1_00_QTIMER3_TIMER0,    /* GPIO_AD_B1_00 PAD functional properties : */
      0x10B0u);                               /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Keeper
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Down
                                                 Hyst. Enable Field: Hysteresis Disabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_B1_01_QTIMER3_TIMER1,    /* GPIO_AD_B1_01 PAD functional properties : */
      0x10B0u);                               /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Keeper
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Down
                                                 Hyst. Enable Field: Hysteresis Disabled */
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵���������������빦��
������汾��V1.0
�������¡�2018��11��19�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_QTMR_QD(void)
{
    qtmr_config_t qtmrConfig;
    
    QTMR_QD_InitPins();      //��ʼ����ʱ�����������
     /*
     * qtmrConfig.debugMode = kQTMR_RunNormalInDebug;
     * qtmrConfig.enableExternalForce = false;
     * qtmrConfig.enableMasterMode = false;
     * qtmrConfig.faultFilterCount = 0;
     * qtmrConfig.faultFilterPeriod = 0;
     * qtmrConfig.primarySource = kQTMR_ClockDivide_2;
     * qtmrConfig.secondarySource = kQTMR_Counter0InputPin;
     */
    QTMR_GetDefaultConfig(&qtmrConfig);   //�õ�Ĭ�ϵĲ���

    qtmrConfig.primarySource = kQTMR_ClockCounter0InputPin;    //Counter0InputPin��Ϊ��Ҫ������Դ�������������룬J11�������������A������
    qtmrConfig.secondarySource = kQTMR_Counter1InputPin;       //Counter1InputPin��Ϊ��Ҫ������Դ�����ڷ������룬K11�������������Dir����
    
    QTMR_Init(TMR3, kQTMR_Channel_0, &qtmrConfig);             //��ʼ��TMR3��ͨ��0

    QTMR_StartTimer(TMR3, kQTMR_Channel_0, kQTMR_PriSrcRiseEdgeSecDir);   //����TMR3ͨ��0�ļ�����������ģʽʹ�ô��������ģʽ

    while (1)
    {   
      printf("\r\nInput Captured value=%d\n", (int16_t)TMR3->CHANNEL[kQTMR_Channel_0].CNTR);  //��ӡλ��
      TMR3->CHANNEL[kQTMR_Channel_0].CNTR = 0;            //��ռ�����
      LED_Ctrl(LED_R, RVS); 
      delayms(100);
    }
    
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵����PWM���ܹܽų�ʼ��
������汾��V1.0
�������¡�2018��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void QTMR_PWM_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);         
  IOMUXC_SetPinMux(IOMUXC_GPIO_B0_03_QTIMER2_TIMER0,0U);   //BGA�ܽ�D8  GPIO_B0_03                              
  IOMUXC_SetPinMux(IOMUXC_GPIO_B0_04_QTIMER2_TIMER1,0U);   //BGA�ܽ�C8  GPIO_B0_05
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_03_QTIMER2_TIMER0,0x10B0u); 
  IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_04_QTIMER2_TIMER1,0x10B0u); 
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����QTMR ��ʼ��ΪPWM����
������汾��V1.0
�������¡�2018��11��19�� 
����������ʹ��Ipgʱ�ӵ�64��Ƶ  150Mhz / 64 = 2.34375 Mhz   qtmr��16λ�ļ����������65535  ��СƵ�� = 2.34375 Mhz / 65535 = 36hz
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_QTMR2_PWM_Init(uint32_t  frequency, uint16_t duty)
{
    QTMR_PWM_InitPins();    //��ʼ����ʱ�����������
    
    qtmr_config_t qtmrConfig;    //qtmr���ýṹ��

    /*
     * qtmrConfig.debugMode = kQTMR_RunNormalInDebug;
     * qtmrConfig.enableExternalForce = false;
     * qtmrConfig.enableMasterMode = false;
     * qtmrConfig.faultFilterCount = 0;
     * qtmrConfig.faultFilterPeriod = 0;
     * qtmrConfig.primarySource = kQTMR_ClockDivide_2;   //ʱ����Ҫ��Դ
     * qtmrConfig.secondarySource = kQTMR_Counter0InputPin;  //ʱ�ӵڶ���Դ
     */
    QTMR_GetDefaultConfig(&qtmrConfig);        //�õ�Ĭ�Ͻṹ��
    /* Use IP bus clock div by 64 */
    qtmrConfig.primarySource = kQTMR_ClockDivide_64;  //ʹ��Ipgʱ�ӵ�64��Ƶ  150Mhz / 64 = 2.34375 Mhz   qtmr��16λ�ļ����������65535  

    QTMR_Init(TMR2, kQTMR_Channel_0, &qtmrConfig);      //��ʼ��TMR2 �� ͨ�� 0
    QTMR_Init(TMR2, kQTMR_Channel_1, &qtmrConfig);      //��ʼ��TMR2 �� ͨ�� 1
    printf("\r\n****Ipg clock is %d.****\n",(CLOCK_GetFreq(kCLOCK_IpgClk)));   //��ӡIPGʱ��
    //��ʼ��PWM   TMR2   ͨ��0          PWMƵ��   ռ�ձ�  ����    ʱ��Ƶ��
    QTMR_SetupPwm(TMR2,kQTMR_Channel_0,frequency,duty,false,CLOCK_GetFreq(kCLOCK_IpgClk)/64); //��ʼ��PWM
    QTMR_SetupPwm(TMR2,kQTMR_Channel_1,frequency,duty,false,CLOCK_GetFreq(kCLOCK_IpgClk)/64); 
    
    QTMR_StartTimer(TMR2,kQTMR_Channel_0,kQTMR_PriSrcRiseEdge); //ͨ��0��primaryʱ��Դ�������ؼ���
    QTMR_StartTimer(TMR2,kQTMR_Channel_1,kQTMR_PriSrcRiseEdge); //ͨ��0��primaryʱ��Դ�������ؼ���
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵��������PWMƵ�ʺ�ռ�ձ�  ��ʱ��ʹ�ñ�ƵPWM����ģʽ������ʹ�ù̶�Ƶ�ʣ�Ҳ����ʹ�ñ�Ƶ
������汾��V1.0
�������¡�2018��11��19�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_QTMR_Set_Duty(uint32_t  frequency, uint16_t duty)
{
    uint32_t srcclk,period,hightime,lowtime;
    
    srcclk=CLOCK_GetFreq(kCLOCK_IpgClk)/64;   // ʱ���Լ����ã����������õ���IPG��64��Ƶ 150Mhz / 64 = 2.34375 Mhz
    
    period=(srcclk/frequency);          //һ��PWM������Ҫ�ļ���ֵ =  ������1s��������  /  Ƶ�� 
    hightime=(period*duty)/100;         //һ��PWM�����иߵ�ƽʱ��(����ֵ)  hightime=(period*duty)/1000;  duty���ֵ 1000
    lowtime=period-hightime;            //һ��PWM�����е͵�ƽʱ��(����ֵ)
    
    TMR2->CHANNEL[kQTMR_Channel_0].CMPLD1=lowtime;
    TMR2->CHANNEL[kQTMR_Channel_0].CMPLD2=hightime;
    
    TMR2->CHANNEL[kQTMR_Channel_1].CMPLD1=hightime;     //��ͨ��0�෴
    TMR2->CHANNEL[kQTMR_Channel_1].CMPLD2=lowtime;

}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵��������PWM����
������汾��V1.0
�������¡�2018��11��19�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_QTMR_PWM(void)
{
    LQ_QTMR2_PWM_Init(12000, 0);//BGA�ܽ�D8  GPIO_B0_03 
                                //BGA�ܽ�C8  GPIO_B0_04
    delayms(1000);
    uint8_t i = 1;
    while(1)
    {
        LQ_QTMR_Set_Duty(i * 100, i);
        i++;
        delayms(2000);
        if(i > 100) i = 1;
        LED_Color_Reverse(red); //�����˸
    }

}