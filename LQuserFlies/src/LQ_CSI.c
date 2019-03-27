/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�RT1052���İ�
����    д��Z
����    ע��
������汾��V1.0
�������¡�2018��11��27��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
���������䡿chiusir@163.com
----------------------------------------------------------------
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"

/*******************************************************************************
*  SDK�ṩ��������Noncacheable�����建�����ͱ����ķ�����
*  AT_NONCACHEABLE_SECTION_ALIGN(var, alignbytes)
*  AT_NONCACHEABLE_SECTION(var)
******************************************************************************/
AT_NONCACHEABLE_SECTION_ALIGN(uint16_t csiFrameBuf[APP_CAMERA_FRAME_BUFFER_COUNT][APP_CAMERA_HEIGHT][APP_CAMERA_WIDTH], FRAME_BUFFER_ALIGN); //��������ͷ���ݻ�����
static void BOARD_PullCameraPowerDownPin(bool pullUp)  //�����
{
//    if (pullUp)
//    {
//        GPIO_PinWrite(GPIO1, 4, 1);
//    }
//    else
//    {
//        GPIO_PinWrite(GPIO1, 4, 0);
//    }
}
static void BOARD_PullCameraResetPin(bool pullUp)  //����ͷ��λ����
{
    /* Reset pin is connected to DCDC_3V3. */
    return;
}

#ifdef LQMT9V034 //LQMT9V034ģ��
static LQMT9V034_resource_t LQMT9V034Resource = {   //����ͷ��ʼ���ṹ��
    .sccbI2C = LPI2C1,
 
    .inputClockFreq_Hz = 27000000,
};

camera_device_handle_t cameraDevice = {           //����ͷ�������ýṹ��
    .resource = &LQMT9V034Resource,
    .ops = &LQMT9V034_ops,
};
#else //LQOV7725ģ��
static ov7725_resource_t ov7725Resource = {       //����ͷ��ʼ���ṹ��
    .sccbI2C = LPI2C1,
    .pullResetPin = BOARD_PullCameraResetPin,
    .pullPowerDownPin = BOARD_PullCameraPowerDownPin,
    .inputClockFreq_Hz = 24000000,                 //�޸���������޸�֡�� ���忴static const ov7725_clock_config_t ov7725ClockConfigs[]
};
camera_device_handle_t cameraDevice = {            //����ͷ�������ýṹ��
    .resource = &ov7725Resource,
    .ops = &ov7725_ops,
};
#endif

/* connect to CSI. */
static csi_resource_t csiResource = {   //ָ��csi����ַ
    .csiBase = CSI,
};

static csi_private_data_t csiPrivateData;  //csi˽������

camera_receiver_handle_t cameraReceiver = {//����ͷ�������ýṹ��
    .resource = &csiResource, 
    .ops = &csi_ops, 
    .privateData = &csiPrivateData,
};


extern void CSI_DriverIRQHandler(void);

void CSI_IRQHandler(void)
{
    CSI_DriverIRQHandler();
}


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵��������ͷCSI�ӿں�I2C�ӿ�ʱ������
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void BOARD_InitCameraResource(void)
{
    LPI2C_Init(LPI2C1, 400000);
    /* CSI MCLK select 24M. */
    /*
    * CSI clock source: 
    * 00 derive clock from osc_clk (24M)
    * 01 derive clock from PLL2 PFD2
    * 10 derive clock from pll3_120M
    * 11 derive clock from PLL3 PFD1
    */
    CLOCK_SetMux(kCLOCK_CsiMux, 2);
    /*
    * CSI clock divider:
    *
    * 000 divide by 1
    * 001 divide by 2
    * 010 divide by 3
    * 011 divide by 4
    * 100 divide by 5
    * 101 divide by 6
    * 110 divide by 7
    * 111 divide by 8
    */
    CLOCK_SetDiv(kCLOCK_CsiDiv, 2);
    
    /*
    * For RT1050, there is not dedicate clock gate for CSI MCLK, it use CSI
    * clock gate.
    */
    
    /* Set the pins for CSI reset and power down. */
//    gpio_pin_config_t pinConfig = {
//        kGPIO_DigitalOutput, 1,
//    };
//    
//    GPIO_PinInit(GPIO1, 4, &pinConfig);
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵��������ͷ��ʼ��
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
camera_config_t cameraConfig;   //����ͷ���ýṹ��
#ifdef LQMT9V034 //LQMT9V034ģ��
    // Configure camera device and receiver.
    camera_config_t cameraConfig = {
        .pixelFormat   = kVIDEO_PixelFormatYUYV,//kVIDEO_PixelFormatYUYV,//kVIDEO_PixelFormatBGR565,
        .bytesPerPixel = APP_BPP,//   ÿ�����ص㼸������
        .resolution = FSL_VIDEO_RESOLUTION(APP_CAMERA_WIDTH, APP_CAMERA_HEIGHT), //�ֱ���
        .frameBufferLinePitch_Bytes = APP_CAMERA_WIDTH * APP_BPP,                //�м��
        .interface     = kCAMERA_InterfaceGatedClock,                            //������ӿ�����
        .controlFlags = APP_CAMERA_CONTROL_FLAGS,
        .framePerSec   = 60,                                                     //fps �޸���Ҫ�޸��ع�ʱ�� �� �ֱ��� ���
    };
#else            //LQOV7725ģ��
    camera_config_t cameraConfig = {
        .pixelFormat = kVIDEO_PixelFormatRGB565,//kVIDEO_PixelFormatRGB565,//kVIDEO_PixelFormatYUYV,
        .bytesPerPixel = APP_BPP,
        .resolution = FSL_VIDEO_RESOLUTION(APP_CAMERA_WIDTH, APP_CAMERA_HEIGHT),  //�ֱ���
        .frameBufferLinePitch_Bytes = APP_CAMERA_WIDTH * APP_BPP,                 //�м��
        .interface =  kCAMERA_InterfaceCCIR656,                                   //������ӿ�����
        .controlFlags = APP_CAMERA_CONTROL_FLAGS,
        .framePerSec = 75,                                                        //fps �޸���Ҫ�޸�plck �� �ֱ��� ���
    };
#endif
void LQ_Camera_Init(void)  
{
    BOARD_InitCSIPins();      //����ͷCSI�ܽŸ���  
    BOARD_InitLPI2C1Pins();   //����ͷ I2C1�ܽŸ���  
    BOARD_InitCameraResource();//csi and I2C clock config   
    
     /*
    * Configure the camera.
    */
    CAMERA_RECEIVER_Init(&cameraReceiver, &cameraConfig, NULL, NULL);  //��ʼ��csi
    
    CAMERA_DEVICE_Init(&cameraDevice, &cameraConfig);                  //��ʼ���������
    
    CAMERA_DEVICE_Start(&cameraDevice);                                //�������
    
    /* Submit the empty frame buffers to buffer queue. */
    for (uint32_t i = 0; i < APP_CAMERA_FRAME_BUFFER_COUNT; i++) //����֡�������ύ������������
    {
        CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, (uint32_t)(csiFrameBuf[i]));
    }
    
    CAMERA_RECEIVER_Start(&cameraReceiver);   // ��������camera����
    delayms(200);        //��ʱ200����  ����ͷ���������ϵ� ���Բ�Ҫ��ʱ
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵������λ����ͼ ��Ҫ��DAPlink�Ĵ��ڣ����׿��� ʹ��ɽ����λ�� ʹ������ʱ��λ������Ϊ�Ҷ� 7725ʱ����λ������ΪRGB565 С��ģʽ
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_Camera_Reprot(void)
{
    uint32_t fullCameraBufferAddr;  
#if (defined LQOV7725) && (defined LQOV7725YUV)
    cameraConfig.pixelFormat = kVIDEO_PixelFormatYUYV;
#endif
    LQ_Camera_Init();
    delayms(200);        //��ʱ200����   
    uint8_t count = 0;
    /* Disable I cache and D cache */
//    if (SCB_CCR_IC_Msk == (SCB_CCR_IC_Msk & SCB->CCR)) {   
//        SCB_DisableICache();
//    }
    if (SCB_CCR_DC_Msk == (SCB_CCR_DC_Msk & SCB->CCR)) {//ע�⣬ʹ��csiFrameBuf����ʱ����ùر�Cache ��Ȼ�ϴ����ݿ��ܻ�����cache���棬������ݴ���
        SCB_DisableDCache();
    }
    while (1)
    {     
        // Wait to get the full frame buffer to show. 
        while (kStatus_Success != CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &fullCameraBufferAddr))  //����ͷCSI����������
        {
        }       
        CAMERA_RECEIVER_Stop(&cameraReceiver);//ֹͣcsi����
        for(count = 0; count < 4; count++)    //��ȡ��ǰ����������������
        {
            if(fullCameraBufferAddr == (uint32_t )csiFrameBuf[count])
                break;
        }
        LQ_UART_PutChar(LPUART1, 0x01);  //֡ͷ
        LQ_UART_PutChar(LPUART1, 0xfe);  //֡ͷ
        for(int i = 0; i < APP_CAMERA_HEIGHT; i++)  //�ֱ���Խ�� ����ͼԽ��
        {
#if  (defined LQMT9V034) || (defined LQOV7725RGB)   //��λ���� 7725 RGB565ͼ�� �� ���ۻҶ�ͼ��  7725ʹ��RGB565��ʽ cameraConfig = { .pixelFormat = kVIDEO_PixelFormatRGB565 }
            for(int j = 0; j < APP_CAMERA_WIDTH * 2; j++)
            {
                if(*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j) == 0xfe )  //��ֹ������֡β
                {
                    *((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j) = 0xff;  
                }
                LQ_UART_PutChar(LPUART1, *((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j)); //��������
            }
//            for(int j = 0; j < APP_CAMERA_WIDTH; j++)  //���������ָ�벻����⣬�����������
//            {
//                    LQ_UART_PutChar(LPUART1, (uint8_t)csiFrameBuf[count][i][j]); //��������
//                    LQ_UART_PutChar(LPUART1, (csiFrameBuf[count][i][j]>>8)); //��������
//                
//            }
#else     //��λ���� 7725 �ĻҶ�ͼ��  ע�⣬���Ҷ�ͼ��ʱ��7725ʹ��YUYV��ʽ cameraConfig = { .pixelFormat = kVIDEO_PixelFormatYUYV }
            for(int j = 1; j < APP_CAMERA_WIDTH * 2; j+=2)  //UYVY ��ʽͼ�� ��Y�ǻҶȣ����Ҷ�ͼ��ֻ���Yֵ
            {
                if(*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j) == 0xfe )  //��ֹ������֡β
                {
                    *((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j) = 0xff;  
                }
                LQ_UART_PutChar(LPUART1, *((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j)); //��������
            }
#endif
        }  
        LQ_UART_PutChar(LPUART1, 0xfe);  //֡β
        LQ_UART_PutChar(LPUART1, 0x01);  //֡β
        
         // Return the camera buffer to camera queue. 
        CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, fullCameraBufferAddr);//��������������ύ���������
        CAMERA_RECEIVER_Start(&cameraReceiver);   // ��������camera����
        LED_Ctrl(LED_R, RVS); //EVK LED��˸  
    }
}



