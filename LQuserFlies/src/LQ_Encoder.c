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
================================================
���������ߣ�
G13--A��
F14--B��
M14--I����

H2--A��
J2--B��
//J1--I����

J3    A��
K1 B����߷���
J4 Z��

C11   A��
B11   B����߷���
//C10   Z��
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"	

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵���������������빦�����ų�ʼ��
������汾��V1.0
�������¡�2018��11��24�� 
����������
������ֵ����
������ֵ����
��ʵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_ENC_InitPin(uint8_t enc_num)
{
    CLOCK_EnableClock(kCLOCK_Iomuxc);          /* ��ioʱ�� */
    
    switch(enc_num)//ѡ��ENCģ��
    {
        case 1:    //ENC1ģ��
        {
            
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_10_XBAR1_IN22,1U); //GPIO_AD_B0_10 ����Ϊ XBAR1_IN22        G13   
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_XBAR1_IN21,1U); //GPIO_AD_B0_09 ����Ϊ XBAR1_IN21        F14                                         
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_00_XBAR1_INOUT14,1U); //GPIO_AD_B0_00 ����Ϊ XBAR1_INOUT14  M14     
            IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_10_XBAR1_IN22,0x10B0u);  
            IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_09_XBAR1_IN21,0x10B0u);                               
            IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_00_XBAR1_INOUT14,0x10B0u);   
            break;
        }
        case 2:    //ENC2ģ��
        {
//            IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_02_XBAR1_INOUT06,1U); //GPIO_AD_B0_02 ����Ϊ XBAR1_INOUT06   J1
            IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_04_XBAR1_INOUT08,1U); //GPIO_AD_B0_04 ����Ϊ XBAR1_INOUT08   H2                                         
            IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_05_XBAR1_INOUT09,1U); //GPIO_AD_B0_05 ����Ϊ XBAR1_INOUT09   J2
//            IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_02_XBAR1_INOUT06,0x10B0u);   /* GPIO_AD_B0_09 PAD functional properties : */                                                
            IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_04_XBAR1_INOUT08,0x10B0u);                               
            IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_05_XBAR1_INOUT09,0x10B0u);
            break;
        }
        case 3:    //ENC3ģ��
        {
            /*�û����������ã������Ÿ���ΪXBARģʽ*/
//            IOMUXC_SetPinMux(IOMUXC_GPIO_B0_13_XBAR1_INOUT11,1U);    //  D10��֮ǰȷ��û�е��������;
            IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_01_XBAR1_INOUT05,1U); //  J3  ��֮ǰȷ��û�е��������;  
            IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_00_XBAR1_INOUT04,1U); //  J4  ��֮ǰȷ��û�е��������; 
            IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_03_XBAR1_INOUT07,1U); //  K1   ��֮ǰȷ��û�е��������; 
//            IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_13_XBAR1_INOUT11,0x10B0u);  
            IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_01_XBAR1_INOUT05,0x10B0u);
            IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_00_XBAR1_INOUT04,0x10B0u);
            IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_03_XBAR1_INOUT07,0x10B0u);  
            break;
        }
        case 4:    //ENC4ģ��
        {
            /*�û����������ã������Ÿ���ΪXBARģʽ*/
//            IOMUXC_SetPinMux(IOMUXC_GPIO_B0_12_XBAR1_INOUT10,1U); //        C10  ��֮ǰȷ��û�е��������;
            IOMUXC_SetPinMux(IOMUXC_GPIO_B1_02_XBAR1_INOUT16,1U); //        C11  ��֮ǰȷ��û�е��������;                                       
            IOMUXC_SetPinMux(IOMUXC_GPIO_B1_01_XBAR1_INOUT15,1U); //        B11   ��֮ǰȷ��û�е��������; 
//            IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_12_XBAR1_INOUT10,0x10B0u);  
            IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_02_XBAR1_INOUT16,0x10B0u);                               
            IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_01_XBAR1_INOUT15,0x10B0u);
            break;
        }
        default:
            break;    
    }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵���������������빦�ܳ�ʼ��
������汾��V1.0
�������¡�2018��11��24�� 
����������
������ֵ����
������ֵ����
��ʵ���� LQ_ENC_Init(ENC1)  //��ʼ��ENC1ģ��
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_ENC_Init(ENC_Type *base)
{
    if(base == ENC1)   //ECR 
    {
        LQ_ENC_InitPin(1); //�ܽŸ���ѡ��
        XBARA_Init(XBARA1);    //��ʼ��XBARA1ģ��
        
        /*����Ƭ���������ӵ�ENC1���ڲ������ź���*/
        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputIomuxXbarIn22, kXBARA1_OutputEnc1PhaseAInput);//G13   A��
        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputIomuxXbarIn21, kXBARA1_OutputEnc1PhaseBInput);//F14   B����߷���
        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputIomuxXbarInout14, kXBARA1_OutputEnc1Index);   //M14   Z��
    }
    else if(base == ENC2) //ECL
    {
        LQ_ENC_InitPin(2); //�ܽŸ���ѡ��
        XBARA_Init(XBARA1);    //��ʼ��XBARA1ģ��
        
        /*����Ƭ���������ӵ�ENC2���ڲ������ź���*/
        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputIomuxXbarInout08, kXBARA1_OutputEnc2PhaseAInput);//H2  A��
        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputIomuxXbarInout09, kXBARA1_OutputEnc2PhaseBInput);//J2  B����߷���
//        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputIomuxXbarInout06, kXBARA1_OutputEnc2Index);      //J1  Z��
    }
    else if(base == ENC3)
    {
        LQ_ENC_InitPin(3); //�ܽŸ���ѡ��
        /*�û��������޸�*/
        XBARA_Init(XBARA1);    //��ʼ��XBARA��ģ��  ��ѡ����XBARA1
        
        /*����Ƭ���������ӵ�ENC2���ڲ������ź���*/
        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputIomuxXbarInout05, kXBARA1_OutputEnc3PhaseAInput);//J3    A��
        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputIomuxXbarInout07, kXBARA1_OutputEnc3PhaseBInput);//K1 B����߷���
//        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputIomuxXbarInout11, kXBARA1_OutputEnc3Index);      //D10    Z��
        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputIomuxXbarInout04, kXBARA1_OutputEnc3Index);      //J4 Z��
    }
    else if(base == ENC4)
    {
        LQ_ENC_InitPin(4); //�ܽŸ���ѡ��
        /*�û��������޸�*/
        XBARA_Init(XBARA1);    //��ʼ��XBARA��ģ��  ��ѡ����XBARA1
        
        /*����Ƭ���������ӵ�ENC2���ڲ������ź���*/
        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputIomuxXbarInout16, kXBARA1_OutputEnc4PhaseAInput);//C11   A��
        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputIomuxXbarInout15, kXBARA1_OutputEnc4PhaseBInput);//B11   B����߷���
//        XBARA_SetSignalsConnection(XBARA1, kXBARA1_InputIomuxXbarInout10, kXBARA1_OutputEnc4Index);      //C10   Z��
    }

    enc_config_t mEncConfigStruct;  //ENC��ʼ���ṹ��
    ENC_GetDefaultConfig(&mEncConfigStruct);  //�õ�Ĭ�ϲ���
    /* mEncConfigStructĬ�ϲ���
    config->enableReverseDirection = false;  
    config->decoderWorkMode = kENC_DecoderWorkAsNormalMode;  //A B����ģʽ
    config->HOMETriggerMode = kENC_HOMETriggerDisabled;
    config->INDEXTriggerMode = kENC_INDEXTriggerDisabled;
    config->enableTRIGGERClearPositionCounter = false;
    config->enableTRIGGERClearHoldPositionCounter = false;
    config->enableWatchdog = false;
    config->watchdogTimeoutValue = 0U;
    config->filterCount = 0U;
    config->filterSamplePeriod = 0U;
    config->positionMatchMode = kENC_POSMATCHOnPositionCounterEqualToComapreValue;
    config->positionCompareValue = 0xFFFFFFFFU;
    config->revolutionCountCondition = kENC_RevolutionCountOnINDEXPulse;
    config->enableModuloCountMode = false;
    config->positionModulusValue = 0U;
    config->positionInitialValue = 0U;*/
    if(base == ENC2 || base == ENC4)  
    {
        mEncConfigStruct.enableReverseDirection = true;  //������
    }
    
    mEncConfigStruct.decoderWorkMode = kENC_DecoderWorkAsSignalPhaseCountMode;  //LSB+Dirģʽ   kENC_DecoderWorkAsNormalMode�� ��ͨ��������
    ENC_Init(base, &mEncConfigStruct);     //��ʼ����������ģ��
    ENC_DoSoftwareLoadInitialPositionValue(base); /* λ�ü�������ʼֵ���³�0. */  
    
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵�������������������빦��
������汾��V1.0
�������¡�2018��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_ENCoder(void)
{   
    TFTSPI_Init();               //TFT1.8��ʼ�� 
    TFTSPI_CLS(u16BLUE);        //����
    LQ_ENC_Init(ENC1);   //���������ʼ��
    LQ_ENC_Init(ENC2);
    LQ_ENC_Init(ENC3);
    LQ_ENC_Init(ENC4);
    short velocity1, velocity2, velocity3, velocity4;
    char txt[16];
    printf("\r\n�����������������:\r\n");    
    while (1)
    { 
        
        delayms(100);        //��ʱ100����
        velocity1 = (int16_t)ENC_GetPositionDifferenceValue(ENC1);  //�õ�������΢��ֵ
        sprintf(txt,"ENC1:  %5d ",velocity1); 
        TFTSPI_P8X16Str(0,0,(uint8_t*)txt,u16RED,u16BLUE);
        printf("ENC1:  %5d \n",velocity1);
        velocity2 = (int16_t)ENC_GetPositionDifferenceValue(ENC2);  //�õ�������΢��ֵ
        sprintf(txt,"ENC2:  %5d ",velocity2); 
        TFTSPI_P8X16Str(0,1,(uint8_t*)txt,u16RED,u16BLUE);
        printf("ENC2:  %5d \n",velocity2);
        velocity3 = (int16_t)ENC_GetPositionDifferenceValue(ENC3);  //�õ�������΢��ֵ
        sprintf(txt,"ENC3:  %5d ",velocity3); 
        TFTSPI_P8X16Str(0,2,(uint8_t*)txt,u16RED,u16BLUE);
        printf("ENC3:  %5d \n",velocity3);
        velocity4 = (int16_t)ENC_GetPositionDifferenceValue(ENC4);  //�õ�������΢��ֵ
        sprintf(txt,"ENC4:  %5d ",velocity4); 
        TFTSPI_P8X16Str(0,3,(uint8_t*)txt,u16RED,u16BLUE);
        printf("ENC4:  %5d \n",velocity4);
        printf("\n####################################\n");
        
        LED_Ctrl(LED_R, RVS); 
        delayms(100);       //��ʱ0.1��
    }
}

