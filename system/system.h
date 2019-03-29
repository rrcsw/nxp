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




//自己写的头文件
    #include "iic.h"
//    #include "LQ_GPIOmacro.h" //加到了system.h的后面
    #include "LQ_MT9V034M.h"   //神眼摄像头V3   
    #include "LQ_OV7725M.h"   //神眼摄像头V3   
    #include "LQ_SGP18T.h"    //TFT1.8吋彩屏模块
    #include "LQ_SGP18Test.h" //TFT1.8寸彩屏测试



    #include "LQ_PWM.h"       //电机，舵机PWM控制 XBARA


    #include "LQ_ADC.h"       //ADC转换采集
    #include "LQ_PIT.h"       //PIT定时


    #include "LQ_MPU6050.h"    //MPU6050
    #include "LQ_TRNG.h"      //随机数发生器
    #include "LQ_Encoder.h"   //编码器正交解码数据采集
//    #include "LQ_eLCDIF.h"    //480 *272液晶屏
    #include "LQ_PXP.h"       //图像处理模块
    #include "LQ_CSI.h"       //摄像头接口
    #include "m_systime.h"    //systick 定时器，用于计时
    #include "ANO_DT.h"       //匿名上位机协议
    #include "status.h"       //标志位
    #include "LQ_QTMR.h"      //计时器可用于生成PWM  和 正交解码
    #include "LQ_NRF2401.h"   //NRF2401驱动程序
    #include "LQ_SPI.h"
    #include "LQ_GPT.h"






//定义PT1_的端口  
#define PT1_0     GPIO1_BASE_PTR->DRs.DR0
#define PT1_1     GPIO1_BASE_PTR->DRs.DR1
#define PT1_2     GPIO1_BASE_PTR->DRs.DR2
#define PT1_3     GPIO1_BASE_PTR->DRs.DR3
#define PT1_4     GPIO1_BASE_PTR->DRs.DR4
#define PT1_5     GPIO1_BASE_PTR->DRs.DR5
#define PT1_6     GPIO1_BASE_PTR->DRs.DR6
#define PT1_7     GPIO1_BASE_PTR->DRs.DR7
#define PT1_8     GPIO1_BASE_PTR->DRs.DR8
#define PT1_9     GPIO1_BASE_PTR->DRs.DR9
#define PT1_10    GPIO1_BASE_PTR->DRs.DR10
#define PT1_11    GPIO1_BASE_PTR->DRs.DR11
#define PT1_12    GPIO1_BASE_PTR->DRs.DR12
#define PT1_13    GPIO1_BASE_PTR->DRs.DR13
#define PT1_14    GPIO1_BASE_PTR->DRs.DR14
#define PT1_15    GPIO1_BASE_PTR->DRs.DR15
#define PT1_16    GPIO1_BASE_PTR->DRs.DR16
#define PT1_17    GPIO1_BASE_PTR->DRs.DR17
#define PT1_18    GPIO1_BASE_PTR->DRs.DR18
#define PT1_19    GPIO1_BASE_PTR->DRs.DR19
#define PT1_20    GPIO1_BASE_PTR->DRs.DR20
#define PT1_21    GPIO1_BASE_PTR->DRs.DR21
#define PT1_22    GPIO1_BASE_PTR->DRs.DR22
#define PT1_23    GPIO1_BASE_PTR->DRs.DR23
#define PT1_24    GPIO1_BASE_PTR->DRs.DR24
#define PT1_25    GPIO1_BASE_PTR->DRs.DR25
#define PT1_26    GPIO1_BASE_PTR->DRs.DR26
#define PT1_27    GPIO1_BASE_PTR->DRs.DR27
#define PT1_28    GPIO1_BASE_PTR->DRs.DR28
#define PT1_29    GPIO1_BASE_PTR->DRs.DR29
#define PT1_30    GPIO1_BASE_PTR->DRs.DR30
#define PT1_31    GPIO1_BASE_PTR->DRs.DR31

//定义PT2_的端口  
#define PT2_0     GPIO2_BASE_PTR->DRs.DR0
#define PT2_1     GPIO2_BASE_PTR->DRs.DR1
#define PT2_2     GPIO2_BASE_PTR->DRs.DR2
#define PT2_3     GPIO2_BASE_PTR->DRs.DR3
#define PT2_4     GPIO2_BASE_PTR->DRs.DR4
#define PT2_5     GPIO2_BASE_PTR->DRs.DR5
#define PT2_6     GPIO2_BASE_PTR->DRs.DR6
#define PT2_7     GPIO2_BASE_PTR->DRs.DR7
#define PT2_8     GPIO2_BASE_PTR->DRs.DR8
#define PT2_9     GPIO2_BASE_PTR->DRs.DR9
#define PT2_10    GPIO2_BASE_PTR->DRs.DR10
#define PT2_11    GPIO2_BASE_PTR->DRs.DR11
#define PT2_12    GPIO2_BASE_PTR->DRs.DR12
#define PT2_13    GPIO2_BASE_PTR->DRs.DR13
#define PT2_14    GPIO2_BASE_PTR->DRs.DR14
#define PT2_15    GPIO2_BASE_PTR->DRs.DR15
#define PT2_16    GPIO2_BASE_PTR->DRs.DR16
#define PT2_17    GPIO2_BASE_PTR->DRs.DR17
#define PT2_18    GPIO2_BASE_PTR->DRs.DR18
#define PT2_19    GPIO2_BASE_PTR->DRs.DR19
#define PT2_20    GPIO2_BASE_PTR->DRs.DR20
#define PT2_21    GPIO2_BASE_PTR->DRs.DR21
#define PT2_22    GPIO2_BASE_PTR->DRs.DR22
#define PT2_23    GPIO2_BASE_PTR->DRs.DR23
#define PT2_24    GPIO2_BASE_PTR->DRs.DR24
#define PT2_25    GPIO2_BASE_PTR->DRs.DR25
#define PT2_26    GPIO2_BASE_PTR->DRs.DR26
#define PT2_27    GPIO2_BASE_PTR->DRs.DR27
#define PT2_28    GPIO2_BASE_PTR->DRs.DR28
#define PT2_29    GPIO2_BASE_PTR->DRs.DR29
#define PT2_30    GPIO2_BASE_PTR->DRs.DR30
#define PT2_31    GPIO2_BASE_PTR->DRs.DR31

//定义PT3_的端口  
#define PT3_0     GPIO3_BASE_PTR->DRs.DR0
#define PT3_1     GPIO3_BASE_PTR->DRs.DR1
#define PT3_2     GPIO3_BASE_PTR->DRs.DR2
#define PT3_3     GPIO3_BASE_PTR->DRs.DR3
#define PT3_4     GPIO3_BASE_PTR->DRs.DR4
#define PT3_5     GPIO3_BASE_PTR->DRs.DR5
#define PT3_6     GPIO3_BASE_PTR->DRs.DR6
#define PT3_7     GPIO3_BASE_PTR->DRs.DR7
#define PT3_8     GPIO3_BASE_PTR->DRs.DR8
#define PT3_9     GPIO3_BASE_PTR->DRs.DR9
#define PT3_10    GPIO3_BASE_PTR->DRs.DR10
#define PT3_11    GPIO3_BASE_PTR->DRs.DR11
#define PT3_12    GPIO3_BASE_PTR->DRs.DR12
#define PT3_13    GPIO3_BASE_PTR->DRs.DR13
#define PT3_14    GPIO3_BASE_PTR->DRs.DR14
#define PT3_15    GPIO3_BASE_PTR->DRs.DR15
#define PT3_16    GPIO3_BASE_PTR->DRs.DR16
#define PT3_17    GPIO3_BASE_PTR->DRs.DR17
#define PT3_18    GPIO3_BASE_PTR->DRs.DR18
#define PT3_19    GPIO3_BASE_PTR->DRs.DR19
#define PT3_20    GPIO3_BASE_PTR->DRs.DR20
#define PT3_21    GPIO3_BASE_PTR->DRs.DR21
#define PT3_22    GPIO3_BASE_PTR->DRs.DR22
#define PT3_23    GPIO3_BASE_PTR->DRs.DR23
#define PT3_24    GPIO3_BASE_PTR->DRs.DR24
#define PT3_25    GPIO3_BASE_PTR->DRs.DR25
#define PT3_26    GPIO3_BASE_PTR->DRs.DR26
#define PT3_27    GPIO3_BASE_PTR->DRs.DR27
#define PT3_28    GPIO3_BASE_PTR->DRs.DR28
#define PT3_29    GPIO3_BASE_PTR->DRs.DR29
#define PT3_30    GPIO3_BASE_PTR->DRs.DR30
#define PT3_31    GPIO3_BASE_PTR->DRs.DR31

//定义PT4_的端口  
#define PT4_0     GPIO4_BASE_PTR->DRs.DR0
#define PT4_1     GPIO4_BASE_PTR->DRs.DR1
#define PT4_2     GPIO4_BASE_PTR->DRs.DR2
#define PT4_3     GPIO4_BASE_PTR->DRs.DR3
#define PT4_4     GPIO4_BASE_PTR->DRs.DR4
#define PT4_5     GPIO4_BASE_PTR->DRs.DR5
#define PT4_6     GPIO4_BASE_PTR->DRs.DR6
#define PT4_7     GPIO4_BASE_PTR->DRs.DR7
#define PT4_8     GPIO4_BASE_PTR->DRs.DR8
#define PT4_9     GPIO4_BASE_PTR->DRs.DR9
#define PT4_10    GPIO4_BASE_PTR->DRs.DR10
#define PT4_11    GPIO4_BASE_PTR->DRs.DR11
#define PT4_12    GPIO4_BASE_PTR->DRs.DR12
#define PT4_13    GPIO4_BASE_PTR->DRs.DR13
#define PT4_14    GPIO4_BASE_PTR->DRs.DR14
#define PT4_15    GPIO4_BASE_PTR->DRs.DR15
#define PT4_16    GPIO4_BASE_PTR->DRs.DR16
#define PT4_17    GPIO4_BASE_PTR->DRs.DR17
#define PT4_18    GPIO4_BASE_PTR->DRs.DR18
#define PT4_19    GPIO4_BASE_PTR->DRs.DR19
#define PT4_20    GPIO4_BASE_PTR->DRs.DR20
#define PT4_21    GPIO4_BASE_PTR->DRs.DR21
#define PT4_22    GPIO4_BASE_PTR->DRs.DR22
#define PT4_23    GPIO4_BASE_PTR->DRs.DR23
#define PT4_24    GPIO4_BASE_PTR->DRs.DR24
#define PT4_25    GPIO4_BASE_PTR->DRs.DR25
#define PT4_26    GPIO4_BASE_PTR->DRs.DR26
#define PT4_27    GPIO4_BASE_PTR->DRs.DR27
#define PT4_28    GPIO4_BASE_PTR->DRs.DR28
#define PT4_29    GPIO4_BASE_PTR->DRs.DR29
#define PT4_30    GPIO4_BASE_PTR->DRs.DR30
#define PT4_31    GPIO4_BASE_PTR->DRs.DR31

//定义PT5_的端口  
#define PT5_0     GPIO5_BASE_PTR->DRs.DR0
#define PT5_1     GPIO5_BASE_PTR->DRs.DR1
#define PT5_2     GPIO5_BASE_PTR->DRs.DR2
#define PT5_3     GPIO5_BASE_PTR->DRs.DR3
#define PT5_4     GPIO5_BASE_PTR->DRs.DR4
#define PT5_5     GPIO5_BASE_PTR->DRs.DR5
#define PT5_6     GPIO5_BASE_PTR->DRs.DR6
#define PT5_7     GPIO5_BASE_PTR->DRs.DR7
#define PT5_8     GPIO5_BASE_PTR->DRs.DR8
#define PT5_9     GPIO5_BASE_PTR->DRs.DR9
#define PT5_10    GPIO5_BASE_PTR->DRs.DR10
#define PT5_11    GPIO5_BASE_PTR->DRs.DR11
#define PT5_12    GPIO5_BASE_PTR->DRs.DR12
#define PT5_13    GPIO5_BASE_PTR->DRs.DR13
#define PT5_14    GPIO5_BASE_PTR->DRs.DR14
#define PT5_15    GPIO5_BASE_PTR->DRs.DR15
#define PT5_16    GPIO5_BASE_PTR->DRs.DR16
#define PT5_17    GPIO5_BASE_PTR->DRs.DR17
#define PT5_18    GPIO5_BASE_PTR->DRs.DR18
#define PT5_19    GPIO5_BASE_PTR->DRs.DR19
#define PT5_20    GPIO5_BASE_PTR->DRs.DR20
#define PT5_21    GPIO5_BASE_PTR->DRs.DR21
#define PT5_22    GPIO5_BASE_PTR->DRs.DR22
#define PT5_23    GPIO5_BASE_PTR->DRs.DR23
#define PT5_24    GPIO5_BASE_PTR->DRs.DR24
#define PT5_25    GPIO5_BASE_PTR->DRs.DR25
#define PT5_26    GPIO5_BASE_PTR->DRs.DR26
#define PT5_27    GPIO5_BASE_PTR->DRs.DR27
#define PT5_28    GPIO5_BASE_PTR->DRs.DR28
#define PT5_29    GPIO5_BASE_PTR->DRs.DR29
#define PT5_30    GPIO5_BASE_PTR->DRs.DR30
#define PT5_31    GPIO5_BASE_PTR->DRs.DR31



//定义PT1_的输出输入方向  
#define DIR1_0       GPIO1_BASE_PTR->GDIRs.GDIR0
#define DIR1_1       GPIO1_BASE_PTR->GDIRs.GDIR1
#define DIR1_2       GPIO1_BASE_PTR->GDIRs.GDIR2
#define DIR1_3       GPIO1_BASE_PTR->GDIRs.GDIR3
#define DIR1_4       GPIO1_BASE_PTR->GDIRs.GDIR4
#define DIR1_5       GPIO1_BASE_PTR->GDIRs.GDIR5
#define DIR1_6       GPIO1_BASE_PTR->GDIRs.GDIR6
#define DIR1_7       GPIO1_BASE_PTR->GDIRs.GDIR7
#define DIR1_8       GPIO1_BASE_PTR->GDIRs.GDIR8
#define DIR1_9       GPIO1_BASE_PTR->GDIRs.GDIR9
#define DIR1_10      GPIO1_BASE_PTR->GDIRs.GDIR10
#define DIR1_11      GPIO1_BASE_PTR->GDIRs.GDIR11
#define DIR1_12      GPIO1_BASE_PTR->GDIRs.GDIR12
#define DIR1_13      GPIO1_BASE_PTR->GDIRs.GDIR13
#define DIR1_14      GPIO1_BASE_PTR->GDIRs.GDIR14
#define DIR1_15      GPIO1_BASE_PTR->GDIRs.GDIR15
#define DIR1_16      GPIO1_BASE_PTR->GDIRs.GDIR16
#define DIR1_17      GPIO1_BASE_PTR->GDIRs.GDIR17
#define DIR1_18      GPIO1_BASE_PTR->GDIRs.GDIR18
#define DIR1_19      GPIO1_BASE_PTR->GDIRs.GDIR19
#define DIR1_20      GPIO1_BASE_PTR->GDIRs.GDIR20
#define DIR1_21      GPIO1_BASE_PTR->GDIRs.GDIR21
#define DIR1_22      GPIO1_BASE_PTR->GDIRs.GDIR22
#define DIR1_23      GPIO1_BASE_PTR->GDIRs.GDIR23
#define DIR1_24      GPIO1_BASE_PTR->GDIRs.GDIR24
#define DIR1_25      GPIO1_BASE_PTR->GDIRs.GDIR25
#define DIR1_26      GPIO1_BASE_PTR->GDIRs.GDIR26
#define DIR1_27      GPIO1_BASE_PTR->GDIRs.GDIR27
#define DIR1_28      GPIO1_BASE_PTR->GDIRs.GDIR28
#define DIR1_29      GPIO1_BASE_PTR->GDIRs.GDIR29
#define DIR1_30      GPIO1_BASE_PTR->GDIRs.GDIR30
#define DIR1_31      GPIO1_BASE_PTR->GDIRs.GDIR31

//定义PT2_的输出输入方向  
#define DIR2_0       GPIO2_BASE_PTR->GDIRs.GDIR0
#define DIR2_1       GPIO2_BASE_PTR->GDIRs.GDIR1
#define DIR2_2       GPIO2_BASE_PTR->GDIRs.GDIR2
#define DIR2_3       GPIO2_BASE_PTR->GDIRs.GDIR3
#define DIR2_4       GPIO2_BASE_PTR->GDIRs.GDIR4
#define DIR2_5       GPIO2_BASE_PTR->GDIRs.GDIR5
#define DIR2_6       GPIO2_BASE_PTR->GDIRs.GDIR6
#define DIR2_7       GPIO2_BASE_PTR->GDIRs.GDIR7
#define DIR2_8       GPIO2_BASE_PTR->GDIRs.GDIR8
#define DIR2_9       GPIO2_BASE_PTR->GDIRs.GDIR9
#define DIR2_10      GPIO2_BASE_PTR->GDIRs.GDIR10
#define DIR2_11      GPIO2_BASE_PTR->GDIRs.GDIR11
#define DIR2_12      GPIO2_BASE_PTR->GDIRs.GDIR12
#define DIR2_13      GPIO2_BASE_PTR->GDIRs.GDIR13
#define DIR2_14      GPIO2_BASE_PTR->GDIRs.GDIR14
#define DIR2_15      GPIO2_BASE_PTR->GDIRs.GDIR15
#define DIR2_16      GPIO2_BASE_PTR->GDIRs.GDIR16
#define DIR2_17      GPIO2_BASE_PTR->GDIRs.GDIR17
#define DIR2_18      GPIO2_BASE_PTR->GDIRs.GDIR18
#define DIR2_19      GPIO2_BASE_PTR->GDIRs.GDIR19
#define DIR2_20      GPIO2_BASE_PTR->GDIRs.GDIR20
#define DIR2_21      GPIO2_BASE_PTR->GDIRs.GDIR21
#define DIR2_22      GPIO2_BASE_PTR->GDIRs.GDIR22
#define DIR2_23      GPIO2_BASE_PTR->GDIRs.GDIR23
#define DIR2_24      GPIO2_BASE_PTR->GDIRs.GDIR24
#define DIR2_25      GPIO2_BASE_PTR->GDIRs.GDIR25
#define DIR2_26      GPIO2_BASE_PTR->GDIRs.GDIR26
#define DIR2_27      GPIO2_BASE_PTR->GDIRs.GDIR27
#define DIR2_28      GPIO2_BASE_PTR->GDIRs.GDIR28
#define DIR2_29      GPIO2_BASE_PTR->GDIRs.GDIR29
#define DIR2_30      GPIO2_BASE_PTR->GDIRs.GDIR30
#define DIR2_31      GPIO2_BASE_PTR->GDIRs.GDIR31

//定义PT3_的输出输入方向  
#define DIR3_0       GPIO3_BASE_PTR->GDIRs.GDIR0
#define DIR3_1       GPIO3_BASE_PTR->GDIRs.GDIR1
#define DIR3_2       GPIO3_BASE_PTR->GDIRs.GDIR2
#define DIR3_3       GPIO3_BASE_PTR->GDIRs.GDIR3
#define DIR3_4       GPIO3_BASE_PTR->GDIRs.GDIR4
#define DIR3_5       GPIO3_BASE_PTR->GDIRs.GDIR5
#define DIR3_6       GPIO3_BASE_PTR->GDIRs.GDIR6
#define DIR3_7       GPIO3_BASE_PTR->GDIRs.GDIR7
#define DIR3_8       GPIO3_BASE_PTR->GDIRs.GDIR8
#define DIR3_9       GPIO3_BASE_PTR->GDIRs.GDIR9
#define DIR3_10      GPIO3_BASE_PTR->GDIRs.GDIR10
#define DIR3_11      GPIO3_BASE_PTR->GDIRs.GDIR11
#define DIR3_12      GPIO3_BASE_PTR->GDIRs.GDIR12
#define DIR3_13      GPIO3_BASE_PTR->GDIRs.GDIR13
#define DIR3_14      GPIO3_BASE_PTR->GDIRs.GDIR14
#define DIR3_15      GPIO3_BASE_PTR->GDIRs.GDIR15
#define DIR3_16      GPIO3_BASE_PTR->GDIRs.GDIR16
#define DIR3_17      GPIO3_BASE_PTR->GDIRs.GDIR17
#define DIR3_18      GPIO3_BASE_PTR->GDIRs.GDIR18
#define DIR3_19      GPIO3_BASE_PTR->GDIRs.GDIR19
#define DIR3_20      GPIO3_BASE_PTR->GDIRs.GDIR20
#define DIR3_21      GPIO3_BASE_PTR->GDIRs.GDIR21
#define DIR3_22      GPIO3_BASE_PTR->GDIRs.GDIR22
#define DIR3_23      GPIO3_BASE_PTR->GDIRs.GDIR23
#define DIR3_24      GPIO3_BASE_PTR->GDIRs.GDIR24
#define DIR3_25      GPIO3_BASE_PTR->GDIRs.GDIR25
#define DIR3_26      GPIO3_BASE_PTR->GDIRs.GDIR26
#define DIR3_27      GPIO3_BASE_PTR->GDIRs.GDIR27
#define DIR3_28      GPIO3_BASE_PTR->GDIRs.GDIR28
#define DIR3_29      GPIO3_BASE_PTR->GDIRs.GDIR29
#define DIR3_30      GPIO3_BASE_PTR->GDIRs.GDIR30
#define DIR3_31      GPIO3_BASE_PTR->GDIRs.GDIR31

//定义PT4_的输出输入方向  
#define DIR4_0       GPIO4_BASE_PTR->GDIRs.GDIR0
#define DIR4_1       GPIO4_BASE_PTR->GDIRs.GDIR1
#define DIR4_2       GPIO4_BASE_PTR->GDIRs.GDIR2
#define DIR4_3       GPIO4_BASE_PTR->GDIRs.GDIR3
#define DIR4_4       GPIO4_BASE_PTR->GDIRs.GDIR4
#define DIR4_5       GPIO4_BASE_PTR->GDIRs.GDIR5
#define DIR4_6       GPIO4_BASE_PTR->GDIRs.GDIR6
#define DIR4_7       GPIO4_BASE_PTR->GDIRs.GDIR7
#define DIR4_8       GPIO4_BASE_PTR->GDIRs.GDIR8
#define DIR4_9       GPIO4_BASE_PTR->GDIRs.GDIR9
#define DIR4_10      GPIO4_BASE_PTR->GDIRs.GDIR10
#define DIR4_11      GPIO4_BASE_PTR->GDIRs.GDIR11
#define DIR4_12      GPIO4_BASE_PTR->GDIRs.GDIR12
#define DIR4_13      GPIO4_BASE_PTR->GDIRs.GDIR13
#define DIR4_14      GPIO4_BASE_PTR->GDIRs.GDIR14
#define DIR4_15      GPIO4_BASE_PTR->GDIRs.GDIR15
#define DIR4_16      GPIO4_BASE_PTR->GDIRs.GDIR16
#define DIR4_17      GPIO4_BASE_PTR->GDIRs.GDIR17
#define DIR4_18      GPIO4_BASE_PTR->GDIRs.GDIR18
#define DIR4_19      GPIO4_BASE_PTR->GDIRs.GDIR19
#define DIR4_20      GPIO4_BASE_PTR->GDIRs.GDIR20
#define DIR4_21      GPIO4_BASE_PTR->GDIRs.GDIR21
#define DIR4_22      GPIO4_BASE_PTR->GDIRs.GDIR22
#define DIR4_23      GPIO4_BASE_PTR->GDIRs.GDIR23
#define DIR4_24      GPIO4_BASE_PTR->GDIRs.GDIR24
#define DIR4_25      GPIO4_BASE_PTR->GDIRs.GDIR25
#define DIR4_26      GPIO4_BASE_PTR->GDIRs.GDIR26
#define DIR4_27      GPIO4_BASE_PTR->GDIRs.GDIR27
#define DIR4_28      GPIO4_BASE_PTR->GDIRs.GDIR28
#define DIR4_29      GPIO4_BASE_PTR->GDIRs.GDIR29
#define DIR4_30      GPIO4_BASE_PTR->GDIRs.GDIR30
#define DIR4_31      GPIO4_BASE_PTR->GDIRs.GDIR31

//定义PT5_的输出输入方向  
#define DIR5_0       GPIO5_BASE_PTR->GDIRs.GDIR0
#define DIR5_1       GPIO5_BASE_PTR->GDIRs.GDIR1
#define DIR5_2       GPIO5_BASE_PTR->GDIRs.GDIR2
#define DIR5_3       GPIO5_BASE_PTR->GDIRs.GDIR3
#define DIR5_4       GPIO5_BASE_PTR->GDIRs.GDIR4
#define DIR5_5       GPIO5_BASE_PTR->GDIRs.GDIR5
#define DIR5_6       GPIO5_BASE_PTR->GDIRs.GDIR6
#define DIR5_7       GPIO5_BASE_PTR->GDIRs.GDIR7
#define DIR5_8       GPIO5_BASE_PTR->GDIRs.GDIR8
#define DIR5_9       GPIO5_BASE_PTR->GDIRs.GDIR9
#define DIR5_10      GPIO5_BASE_PTR->GDIRs.GDIR10
#define DIR5_11      GPIO5_BASE_PTR->GDIRs.GDIR11
#define DIR5_12      GPIO5_BASE_PTR->GDIRs.GDIR12
#define DIR5_13      GPIO5_BASE_PTR->GDIRs.GDIR13
#define DIR5_14      GPIO5_BASE_PTR->GDIRs.GDIR14
#define DIR5_15      GPIO5_BASE_PTR->GDIRs.GDIR15
#define DIR5_16      GPIO5_BASE_PTR->GDIRs.GDIR16
#define DIR5_17      GPIO5_BASE_PTR->GDIRs.GDIR17
#define DIR5_18      GPIO5_BASE_PTR->GDIRs.GDIR18
#define DIR5_19      GPIO5_BASE_PTR->GDIRs.GDIR19
#define DIR5_20      GPIO5_BASE_PTR->GDIRs.GDIR20
#define DIR5_21      GPIO5_BASE_PTR->GDIRs.GDIR21
#define DIR5_22      GPIO5_BASE_PTR->GDIRs.GDIR22
#define DIR5_23      GPIO5_BASE_PTR->GDIRs.GDIR23
#define DIR5_24      GPIO5_BASE_PTR->GDIRs.GDIR24
#define DIR5_25      GPIO5_BASE_PTR->GDIRs.GDIR25
#define DIR5_26      GPIO5_BASE_PTR->GDIRs.GDIR26
#define DIR5_27      GPIO5_BASE_PTR->GDIRs.GDIR27
#define DIR5_28      GPIO5_BASE_PTR->GDIRs.GDIR28
#define DIR5_29      GPIO5_BASE_PTR->GDIRs.GDIR29
#define DIR5_30      GPIO5_BASE_PTR->GDIRs.GDIR30
#define DIR5_31      GPIO5_BASE_PTR->GDIRs.GDIR31


//定义PT1_的8位端口  
#define PT1_BYTE0   GPIO1_BASE_PTR->DRByte.Byte0
#define PT1_BYTE1   GPIO1_BASE_PTR->DRByte.Byte1
#define PT1_BYTE2   GPIO1_BASE_PTR->DRByte.Byte2
#define PT1_BYTE3   GPIO1_BASE_PTR->DRByte.Byte3

//定义PT2_的8位端口  
#define PT2_BYTE0   GPIO2_BASE_PTR->DRByte.Byte0
#define PT2_BYTE1   GPIO2_BASE_PTR->DRByte.Byte1
#define PT2_BYTE2   GPIO2_BASE_PTR->DRByte.Byte2
#define PT2_BYTE3   GPIO2_BASE_PTR->DRByte.Byte3


//定义PT3_的8位端口  
#define PT3_BYTE0   GPIO3_BASE_PTR->DRByte.Byte0
#define PT3_BYTE1   GPIO3_BASE_PTR->DRByte.Byte1
#define PT3_BYTE2   GPIO3_BASE_PTR->DRByte.Byte2
#define PT3_BYTE3   GPIO3_BASE_PTR->DRByte.Byte3

//定义PT4_的8位端口  
#define PT4_BYTE0   GPIO4_BASE_PTR->DRByte.Byte0
#define PT4_BYTE1   GPIO4_BASE_PTR->DRByte.Byte1
#define PT4_BYTE2   GPIO4_BASE_PTR->DRByte.Byte2
#define PT4_BYTE3   GPIO4_BASE_PTR->DRByte.Byte3

//定义PT5_的8位端口  
#define PT5_BYTE0   GPIO5_BASE_PTR->DRByte.Byte0
#define PT5_BYTE1   GPIO5_BASE_PTR->DRByte.Byte1
#define PT5_BYTE2   GPIO5_BASE_PTR->DRByte.Byte2
#define PT5_BYTE3   GPIO5_BASE_PTR->DRByte.Byte3


//定义PT1_的8位输出输入方向  
#define DIR1_BYTE0   GPIO1_BASE_PTR->DIR2_yte.Byte0
#define DIR1_BYTE1   GPIO1_BASE_PTR->DIR2_yte.Byte1
#define DIR1_BYTE2   GPIO1_BASE_PTR->DIR2_yte.Byte2
#define DIR1_BYTE3   GPIO1_BASE_PTR->DIR2_yte.Byte3

//定义PT2_的8位输出输入方向  
#define DIR2_BYTE0   GPIO2_BASE_PTR->DIR2_yte.Byte0
#define DIR2_BYTE1   GPIO2_BASE_PTR->DIR2_yte.Byte1
#define DIR2_BYTE2   GPIO2_BASE_PTR->DIR2_yte.Byte2
#define DIR2_BYTE3   GPIO2_BASE_PTR->DIR2_yte.Byte3

//定义PT3_的8位输出输入方向  
#define DIR3_BYTE0   GPIO3_BASE_PTR->DIR2_yte.Byte0
#define DIR3_BYTE1   GPIO3_BASE_PTR->DIR2_yte.Byte1
#define DIR3_BYTE2   GPIO3_BASE_PTR->DIR2_yte.Byte2
#define DIR3_BYTE3   GPIO3_BASE_PTR->DIR2_yte.Byte3

//定义PT4_的8位输出输入方向  
#define DIR4_BYTE0   GPIO4_BASE_PTR->DIR2_yte.Byte0
#define DIR4_BYTE1   GPIO4_BASE_PTR->DIR2_yte.Byte1
#define DIR4_BYTE2   GPIO4_BASE_PTR->DIR2_yte.Byte2
#define DIR4_BYTE3   GPIO4_BASE_PTR->DIR2_yte.Byte3

//定义PT5_的8位输出输入方向  
#define DIR5_BYTE0   GPIO5_BASE_PTR->DIR2_yte.Byte0
#define DIR5_BYTE1   GPIO5_BASE_PTR->DIR2_yte.Byte1 
#define DIR5_BYTE2   GPIO5_BASE_PTR->DIR2_yte.Byte2
#define DIR5_BYTE3   GPIO5_BASE_PTR->DIR2_yte.Byte3


//定义PT1_的16位端口  
#define PT1_WORD0   GPIO1_BASE_PTR->DRWord.Word0
#define PT1_WORD1   GPIO1_BASE_PTR->DRWord.Word1

//定义PT2_的16位端口  
#define PT2_WORD0   GPIO2_BASE_PTR->DRWord.Word0
#define PT2_WORD1   GPIO2_BASE_PTR->DRWord.Word1

//定义PT3_的16位端口  
#define PT3_WORD0   GPIO3_BASE_PTR->DRWord.Word0
#define PT3_WORD1   GPIO3_BASE_PTR->DRWord.Word1


//定义PT4_的16位端口  
#define PT4_WORD0   GPIO4_BASE_PTR->DRWord.Word0
#define PT4_WORD1   GPIO4_BASE_PTR->DRWord.Word1


//定义PT5_的16位端口  
#define PT5_WORD0   GPIO5_BASE_PTR->DRWord.Word0
#define PT5_WORD1   GPIO5_BASE_PTR->DRWord.Word1


//定义PT1_的16位输出输入方向  
#define DIR1_WORD0   GPIO1_BASE_PTR->GDIRWord.Word0
#define DIR1_WORD1   GPIO1_BASE_PTR->GDIRWord.Word1


//定义PT2_的16位输出输入方向  
#define DIR2_WORD0   GPIO2_BASE_PTR->GDIRWord.Word0
#define DIR2_WORD1   GPIO2_BASE_PTR->GDIRWord.Word1


//定义PT3_的16位输出输入方向  
#define DIR3_WORD0   GPIO3_BASE_PTR->GDIRWord.Word0
#define DIR3_WORD1   GPIO3_BASE_PTR->GDIRWord.Word1


//定义PT4_的16位输出输入方向  
#define DIR4_WORD0   GPIO4_BASE_PTR->GDIRWord.Word0
#define DIR4_WORD1   GPIO4_BASE_PTR->GDIRWord.Word1


//定义PT5_的16位输出输入方向  
#define DIR5_WORD0   GPIO5_BASE_PTR->GDIRWord.Word0
#define DIR5_WORD1   GPIO5_BASE_PTR->GDIRWord.Word1



void delayms(uint32_t ms);
void delayus(uint32_t us);
void gpt_time_start(void);
uint32_t gpt_time_get(void);
void Test_GPT_Timer(void);
void LQ_GPT_Init(void);



#include "base.h"
#include "oled.h"






#endif



