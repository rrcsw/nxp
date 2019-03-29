/**
  *
  * @file    iic.h
  * @author  
  * @version 
  * @date    2019/3/7
  * @brief   iicÏà¹ØµÄº¯ÊýÓë±äÁ¿ÉùÃ÷
  *
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _LQ_INLUDE_FILES_H_
#define _LQ_INLUDE_FILES_H_




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

//用户自定义文件    
//    #include "LQ_TFT480x272.h"//4.3彩屏
//    #include "LQ_GT9147TP.h"  //电容触摸板
    #include "LQ_IIC.h"
//   #include "LQ_GPIOmacro.h" //GPIO口51操作格式 




    #include "LQ_PWM.h"       //电机，舵机PWM控制 XBARA

    #include "LQ_ADC.h"       //ADC转换采集
    #include "LQ_PIT.h"       //PIT定时

    #include "LQ_MPU6050.h"    //MPU6050
    #include "LQ_TRNG.h"      //随机数发生器
    #include "LQ_Encoder.h"   //编码器正交解码数据采集
//    #include "LQ_eLCDIF.h"    //480 *272液晶屏
    #include "LQ_PXP.h"       //图像处理模块


    #include "m_systime.h"    //systick 定时器，用于计时
    #include "ANO_DT.h"       //匿名上位机协议
    #include "status.h"       //标志位
    #include "LQ_QTMR.h"      //计时器可用于生成PWM  和 正交解码
    #include "LQ_NRF2401.h"   //NRF2401驱动程序
    #include "LQ_SPI.h"
    #include "LQ_GPT.h"
//用户自定义函数
//    void delayus(uint32_t us);
//    void delayms(uint32_t ms);   
#endif //_LQ_INLUDE_FILES_H_
