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
#ifndef _LQ_INLUDE_FILES_H_
#define _LQ_INLUDE_FILES_H_
    #include "stdio.h"
    #include "math.h"
//SDK�ײ�������
    #include "fsl_adc.h"
    #include "fsl_cache.h"
    #include "fsl_csi.h"
    #include "fsl_csi_camera_adapter.h"
    #include "fsl_camera.h"
    #include "fsl_camera_receiver.h"
    #include "fsl_camera_device.h"
    #include "fsl_csi.h"
    #include "fsl_common.h"
    #include "fsl_clock.h"
    #include "fsl_debug_console.h"
    #include "fsl_elcdif.h"
    #include "fsl_enc.h"    
    #include "fsl_gpio.h"
    #include "fsl_gpt.h"
    #include "fsl_iomuxc.h"
    #include "fsl_lpuart.h"
    #include "fsl_lpi2c.h"
    #include "fsl_pxp.h"
    #include "fsl_pwm.h"
    #include "fsl_pit.h"
    #include "fsl_qtmr.h"
    #include "fsl_trng.h"
    #include "fsl_usdhc.h"
    #include "fsl_video_common.h"
    #include "fsl_wdog.h"
    #include "fsl_xbara.h"
    #include "board.h"
    #include "pin_mux.h"
    #include "fsl_sccb.h"
    #include "fsl_flexspi.h"
    #include "fsl_lpuart_edma.h"
    #include "fsl_edma.h"
    #include "fsl_dmamux.h"

//�û��Զ����ļ�    
//    #include "LQ_TFT480x272.h"//4.3����
//    #include "LQ_GT9147TP.h"  //���ݴ�����
    #include "LQ_IIC.h"
    #include "LQ_GPIOmacro.h" //GPIO��51������ʽ 
    #include "LQ_MT9V034M.h"   //��������ͷV3   
    #include "LQ_OV7725M.h"   //��������ͷV3   
    #include "LQ_SGP18T.h"    //TFT1.8������ģ��
    #include "LQ_SGP18Test.h" //TFT1.8���������
    #include "LQ_12864.h"      //OLEDģ�麯�����壬����IIC��SPI���ֽӿ�
    #include "LQ_LED.h"       //LEDָʾ
    #include "LQ_KEY.h"       //��������
    #include "LQ_PWM.h"       //��������PWM���� XBARA
    #include "LQ_UART.h"       //UART����
    #include "LQ_ADC.h"       //ADCת���ɼ�
    #include "LQ_PIT.h"       //PIT��ʱ
    #include "LQ_9AX.h"       //����ģ��
    #include "LQ_MPU6050.h"    //MPU6050
    #include "LQ_TRNG.h"      //�����������
    #include "LQ_Encoder.h"   //�����������������ݲɼ�
//    #include "LQ_eLCDIF.h"    //480 *272Һ����
    #include "LQ_PXP.h"       //ͼ����ģ��
    #include "LQ_CSI.h"       //����ͷ�ӿ�
    #include "m_systime.h"    //systick ��ʱ�������ڼ�ʱ
    #include "ANO_DT.h"       //������λ��Э��
    #include "status.h"       //��־λ
    #include "LQ_QTMR.h"      //��ʱ������������PWM  �� ��������
    #include "LQ_NRF2401.h"   //NRF2401��������
    #include "LQ_SPI.h"
    #include "LQ_GPT.h"
//�û��Զ��庯��
//    void delayus(uint32_t us);
//    void delayms(uint32_t ms);   
#endif //_LQ_INLUDE_FILES_H_
