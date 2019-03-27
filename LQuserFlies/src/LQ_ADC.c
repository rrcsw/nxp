/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1052���İ�-���ܳ���
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2017��2��1��
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

/* //ADC��Դ������Ӧ�Ĺܽţ�      �ܽ�����      BGA�ܽű��
ADC1_IN0  Analog channel 1 input0   GPIO_AD_B1_11   J13
ADC1_IN1  Analog channel 1 input1   GPIO_AD_B0_12   K14 
ADC1_IN2  Analog channel 1 input2   GPIO_AD_B0_13   L14
ADC1_IN3  Analog channel 1 input3   GPIO_AD_B0_14   H14
ADC1_IN4  Analog channel 1 input4   GPIO_AD_B0_15   L10
ADC1_IN5  Analog channel 1 input5   GPIO_AD_B1_00   J11
ADC1_IN6  Analog channel 1 input6   GPIO_AD_B1_01   K11
ADC1_IN7  Analog channel 1 input7   GPIO_AD_B1_02   L11
ADC1_IN8  Analog channel 1 input8   GPIO_AD_B1_03   M12
ADC1_IN9  Analog channel 1 input9   GPIO_AD_B1_04   L12
ADC1_IN10 Analog channel 1 input10  GPIO_AD_B1_05   K12
ADC1_IN11 Analog channel 1 input11  GPIO_AD_B1_06   J12
ADC1_IN12 Analog channel 1 input12  GPIO_AD_B1_07   K10
ADC1_IN13 Analog channel 1 input13  GPIO_AD_B1_08   H13
ADC1_IN14 Analog channel 1 input14  GPIO_AD_B1_09   M13
ADC1_IN15 Analog channel 1 input15  GPIO_AD_B1_10   L13

ADC2_IN0  Analog channel 2 input0   GPIO_AD_B1_11   J13
ADC2_IN1  Analog channel 2 input1   GPIO_AD_B1_12   H12
ADC2_IN2  Analog channel 2 input2   GPIO_AD_B1_13   H11
ADC2_IN3  Analog channel 2 input3   GPIO_AD_B1_14   G12
ADC2_IN4  Analog channel 2 input4   GPIO_AD_B1_15   J14
ADC2_IN5  Analog channel 1 input5   GPIO_AD_B1_00   J11
ADC2_IN6  Analog channel 1 input6   GPIO_AD_B1_01   K11
ADC2_IN7  Analog channel 1 input7   GPIO_AD_B1_02   L11
ADC2_IN8  Analog channel 1 input8   GPIO_AD_B1_03   M12
ADC2_IN9  Analog channel 1 input9   GPIO_AD_B1_04   L12
ADC2_IN10 Analog channel 1 input10  GPIO_AD_B1_05   K12
ADC2_IN11 Analog channel 1 input11  GPIO_AD_B1_06   J12
ADC2_IN12 Analog channel 1 input12  GPIO_AD_B1_07   K10
ADC2_IN13 Analog channel 1 input13  GPIO_AD_B1_08   H13
ADC2_IN14 Analog channel 1 input14  GPIO_AD_B1_09   M13
ADC2_IN15 Analog channel 1 input15  GPIO_AD_B1_10   L13
*/

//LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
//����  �ߡ�CHIUSIR
//������˵������ʼ��ADC
//������汾��V1.0
//�������¡�2017��8��4�� 
//����������void LQADC_Init(ADC_Type *base)
//������ֵ��ADC1,ADC2
//������ֵ����
//����  ����ADC_init��ADC1����ʼ��ADC1ģ�� 
//QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ

void LQADC_Init(ADC_Type *base)
{          
    adc_config_t adcConfigStrcut;   

    /*
    *  config->enableAsynchronousClockOutput = true;
     *  config->enableOverWrite =                 false;
       *  config->enableContinuousConversion =    false;
       *  config->enableHighSpeed =               false;
       *  config->enableLowPower =                false;
       *  config->enableLongSample =              false;
       *  config->referenceVoltageSource =        kADC_ReferenceVoltageSourceVref;
       *  config->samplePeriodMode =              kADC_SamplePeriod2or12Clocks;
       *  config->clockSource =                   kADC_ClockSourceAD;
       *  config->clockDriver =                   kADC_ClockDriver1;
       *  config->resolution =                    kADC_Resolution12Bit;
       */
    ADC_GetDefaultConfig(&adcConfigStrcut);
    //adcConfigStrcut.resolution=kADC_Resolution12Bit;              //Ĭ�Ͼ�Ϊ12λ
    ADC_Init(base, &adcConfigStrcut);                               //��ʼ��
    
    ADC_SetHardwareAverageConfig(base, kADC_HardwareAverageCount32);//Ӳ��ƽ��ֵ
    /* Do auto hardware calibration. */
    ADC_DoAutoCalibration(base);                                    //Ӳ��У׼
    
 }
//LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
//����  �ߡ�CHIUSIR
//������˵������ȡADC �� ͨ����ֵ
//������汾��V1.0
//�������¡�2017��8��4�� 
//����������uint16_t ReadADC(ADC_Type *base,ADCn_Ch_e CH)
//������ֵ��base��ADC1,ADC2��CH��0~31
//������ֵ��12λadcֵ
//����  ����batv=ReadADC(ADC1,ADC1_CH0)����ȡADC1��0ͨ����ֵ
//QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
uint16_t ReadADC(ADC_Type *base,ADCn_Ch_e CH)
{     
  adc_channel_config_t adcChannelConfigStruct;                          //���ýṹ��
  
  adcChannelConfigStruct.channelNumber = CH;
  adcChannelConfigStruct.enableInterruptOnConversionCompleted = false;  //ת������ж�
  ADC_SetChannelConfig(base, 0, &adcChannelConfigStruct);                //����ת��
  while (0U == ADC_GetChannelStatusFlags(base,0)){;}                    //�ȴ�ת�����
  return (ADC_GetChannelConversionValue(base,0));                       //����ת�����
}


//LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
//����  �ߡ�CHIUSIR
//������˵�������Զ�ȡK12��ѹֵ����ת��ΪС��ֵ�����ں�OLED���
//������汾��V1.0
//�������¡�2017��8��4�� 
//����������uint16_t ReadADC(ADC_Type *base,ADCn_Ch_e CH)
//������ֵ����
//������ֵ����
//����  ����Test_ADC()��
//QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
void Test_ADC(void)
{
    char txt[16];
      
    TFTSPI_Init();                  //LCD��ʼ�� 
    TFTSPI_CLS(u16BLUE);           //����
    TFTSPI_P8X16Str(2,0,(uint8_t*)"LQ ADC Test Bat",u16RED,u16BLUE);
    printf("\r\nLQ ADC Test Bat");

    LQADC_Init(ADC1);             //��Դ��ѹ����ADC��ʼ��
    uint16_t batv0=(uint16_t)(ReadADC(ADC1,ADC1_CH10)*0.46);  //��ȡADCֵ K12 ��ص�ѹ * 100
    uint16_t batv1=(uint16_t)(ReadADC(ADC1,ADC1_CH4)*0.806);  //��ȡADCֵ L10
    uint16_t batv2=(uint16_t)(ReadADC(ADC1,ADC1_CH7)*0.806);  //��ȡADCֵ L11
    uint16_t batv3=(uint16_t)(ReadADC(ADC1,ADC1_CH8)*0.806);  //��ȡADCֵ M12
    uint16_t batv4=(uint16_t)(ReadADC(ADC1,ADC1_CH3)*0.806);  //��ȡADCֵ H14
    uint16_t batv5=(uint16_t)(ReadADC(ADC1,ADC1_CH1)*0.806);  //��ȡADCֵ K14
    uint16_t batv6=(uint16_t)(ReadADC(ADC1,ADC1_CH2)*0.806);  //��ȡADCֵ L14
    while (1)
    {           
        //����ADCת��   ADC�Ļ�׼��ѹ��3.3V�ģ�RT1052ĸ���ϣ�K12ͨ��1K��4.7K�ķ�ѹ���������ص�ѹ ��ص�ѹ =  ��ReadADC / 4095�� * 3.3 * ��1 + 4.7��
        batv0 = (uint16_t)(batv0*0.7 + 0.3*(uint16_t)(ReadADC(ADC1,ADC1_CH10)*0.46));//��ѹ�ɼ� 
        
        batv1 = (uint16_t)(batv1*0.7 + 0.3*ReadADC(ADC1,ADC1_CH4)*0.806);             //��ȡADCֵ L10
        batv2 = (uint16_t)(batv2*0.7 + 0.3*ReadADC(ADC1,ADC1_CH7)*0.806);             //��ȡADCֵ L11
        batv3 = (uint16_t)(batv3*0.7 + 0.3*ReadADC(ADC1,ADC1_CH8)*0.806);             //��ȡADCֵ M12
        batv4 = (uint16_t)(batv4*0.7 + 0.3*ReadADC(ADC1,ADC1_CH3)*0.806);             //��ȡADCֵ H14
        batv5 = (uint16_t)(batv5*0.7 + 0.3*ReadADC(ADC1,ADC1_CH1)*0.806);             //��ȡADCֵ K14
        batv6 = (uint16_t)(batv6*0.7 + 0.3*ReadADC(ADC1,ADC1_CH2)*0.806);  
        
        printf("\r\n/***********************%3.2fV\r\n ",batv0/100.0f);
        sprintf(txt,"BAT:%3.2fV ",batv0/100.0f);
        TFTSPI_P8X16Str(5,1,(uint8_t*)txt,u16RED,u16BLUE);
                           
//        printf("\r\nADC2_IN10  :%d.%dV ",batv/100,batv%100);     //�������������Ƚϴ󣬿��Բ������ַ������С����
//        sprintf(txt,"BAT:%d.%dV ",batv/100,batv%100);
//        LCD_P8x16Str(20,3,(uint8_t*)txt); 
        //LED��˸
        
        printf("\r\n/***********************%3.2fV\r\n ",batv1/1000.0f);
        sprintf(txt,"L10:%3.2fV ",batv1/1000.0f);
        TFTSPI_P8X16Str(5,2,(uint8_t*)txt,u16RED,u16BLUE);
        
        printf("\r\n/***********************%3.2fV\r\n ",batv2/1000.0f);
        sprintf(txt,"L11:%3.2fV ",batv2/1000.0f);
        TFTSPI_P8X16Str(5,3,(uint8_t*)txt,u16RED,u16BLUE);
        
        printf("\r\n/***********************%3.2fV\r\n ",batv3/1000.0f);
        sprintf(txt,"M12:%3.2fV ",batv3/1000.0f);
        TFTSPI_P8X16Str(5,4,(uint8_t*)txt,u16RED,u16BLUE);
        
        printf("\r\n/***********************%3.2fV\r\n ",batv4/1000.0f);
        sprintf(txt,"H14:%3.2fV ",batv4/1000.0f);
        TFTSPI_P8X16Str(5,5,(uint8_t*)txt,u16RED,u16BLUE);
        
        printf("\r\n/***********************%3.2fV\r\n ",batv5/1000.0f);
        sprintf(txt,"K14:%3.2fV ",batv5/1000.0f);
        TFTSPI_P8X16Str(5,6,(uint8_t*)txt,u16RED,u16BLUE);
        
        printf("\r\n/***********************%3.2fV\r\n ",batv6/1000.0f);
        sprintf(txt,"L14:%3.2fV ",batv6/1000.0f);
        TFTSPI_P8X16Str(5,7,(uint8_t*)txt,u16RED,u16BLUE);
        
        LED_Color_Reverse(blue);    //����   
        delayms(100);
    }
}
