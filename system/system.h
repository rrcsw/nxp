#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "MIMXRT1052.h"
#include "fsl_clock.h"
#include "board.h"
#include "core_cm7.h"
#include "MIMXRT1052_features.h"


#include "fsl_adc.h"
#include "fsl_adc_etc.h"
#include "fsl_aipstz.h"
#include "fsl_aoi.h"
#include "fsl_bee.h"
#include "fsl_cache.h"
#include "fsl_clock.h"
#include "fsl_cmp.h"
#include "fsl_common.h"
#include "fsl_csi.h"
#include "fsl_dcdc.h"
#include "fsl_dmamux.h"
#include "fsl_edma.h"
#include "fsl_elcdif.h"
#include "fsl_enc.h"
#include "fsl_enet.h"
#include "fsl_ewm.h"
#include "fsl_flexcan.h"
#include "fsl_flexio.h"
#include "fsl_flexio_i2c_master.h"
#include "fsl_flexio_i2s.h"
#include "fsl_flexio_i2s_edma.h"
#include "fsl_flexio_uart.h"
#include "fsl_flexio_uart_edma.h"
#include "fsl_flexram.h"
#include "fsl_flexspi.h"
#include "fsl_gpc.h"
#include "fsl_gpio.h"
#include "fsl_gpt.h"
#include "fsl_iomuxc.h"
#include "fsl_kpp.h"
#include "fsl_lpi2c.h"
#include "fsl_lpi2c_edma.h"
#include "fsl_lpspi.h"
#include "fsl_lpspi_edma.h"
#include "fsl_lpuart.h"
#include "fsl_lpuart_edma.h"
#include "fsl_pit.h"
#include "fsl_pmu.h"
#include "fsl_pwm.h"
#include "fsl_pxp.h"
#include "fsl_qtmr.h"
#include "fsl_rtwdog.h"
#include "fsl_sai.h"
#include "fsl_sai_edma.h"
#include "fsl_semc.h"
#include "fsl_snvs_hp.h"
#include "fsl_snvs_lp.h"
#include "fsl_spdif.h"
#include "fsl_src.h"
#include "fsl_trng.h"
#include "fsl_tsc.h"
#include "fsl_usdhc.h"
#include "fsl_wdog.h"
#include "fsl_xbara.h"
#include "fsl_xbarb.h"




/* Includes ------------------------------------------------------------------*/
    #include "stdio.h"
    #include "math.h"
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


    #include "LQ_PWM.h"       //��������PWM���� XBARA

    #include "LQ_ADC.h"       //ADCת���ɼ�
    #include "LQ_PIT.h"       //PIT��ʱ

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




void delayms(uint32_t ms);
void delayus(uint32_t us);
void gpt_time_start(void);
uint32_t gpt_time_get(void);
void Test_GPT_Timer(void);
void LQ_GPT_Init(void);



#include "base.h"
#include "oled.h"






#endif



