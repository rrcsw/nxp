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


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����PXP��ʼ��
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
pxp_ps_buffer_config_t psBufferConfig;  //PXP�������ýṹ��
pxp_output_buffer_config_t outputBufferConfig;//PXP������ýṹ��
void LQ_PXP_Init(void)
{
       //Configure the PXP for color space conversion.
    PXP_Init(PXP);    //��ʱ��
    /* Disable AS. */
    PXP_SetAlphaSurfacePosition(PXP, 0xFFFFU, 0xFFFFU, 0U, 0U);
    
    /* Input config. */
#ifdef LQMT9V034 //LQMT9V034ģ��
        psBufferConfig.pixelFormat =  kPXP_PsPixelFormatRGB888;//kPXP_PsPixelFormatRGB565,//kPXP_PsPixelFormatUYVY1P422,
#else                  //LQOV7725ģ��
        psBufferConfig.pixelFormat =  kPXP_PsPixelFormatRGB565;//kPXP_PsPixelFormatRGB565,//kPXP_PsPixelFormatUYVY1P422,
#endif
        psBufferConfig.swapByte = false;                 //��8λ��ǰ���ǵ�8λ��ǰ
        psBufferConfig.bufferAddrU = 0U;
        psBufferConfig.bufferAddrV = 0U;
        psBufferConfig.pitchBytes = APP_CAMERA_WIDTH * APP_BPP;    //һ�ж��ٸ��ֽ� 
        
    /* Output config. */
        outputBufferConfig.pixelFormat = kPXP_OutputPixelFormatARGB8888;//kPXP_OutputPixelFormatRGB888,
        outputBufferConfig.interlacedMode = kPXP_OutputProgressive;
        outputBufferConfig.buffer1Addr = 0U;
        outputBufferConfig.pitchBytes = APP_LCD_WIDTH * 4;
        outputBufferConfig.width = APP_LCD_WIDTH;
        outputBufferConfig.height = APP_LCD_HEIGHT;
     
    
#ifdef LQMT9V034 //LQMT9V034ģ��
    PXP_EnableCsc1(PXP, false);              //��ʹ��  LQMT9V034ģ��Ϊ��ɫ��ʽ
    PXP_SetProcessSurfaceScaler(PXP,IMAGEW/4, IMAGEH, 376, 272);//����ͼ��, ��������ͷ752 * 480�ֱ��ʣ����������ʽΪ ��λ��ɫ�ʣ�Ҳ����һ���ֽھ���һ�����ص㣬���ǵ�Ƭ����csi�ӿ�����Ϊrgb8888��ʽ����������ͷ����һ���ֽڱ�ʾһ�����ص㣬������ĸ��ֽڱ�ʾһ�����ص㣩��֡���
    PXP_SetProcessSurfacePosition(PXP, 52u, 0u, 428 - 1U, 272 - 1U);                //������ʾλ��
#else  //LQOV7725ģ��
    PXP_SetCsc1Mode(PXP, kPXP_Csc1YCbCr2RGB);//���� csc1  kPXP_Csc1YCbCrת��Ϊrgb888
    PXP_EnableCsc1(PXP, false);               //������7725���ͼ���ʽΪyuyvʱ��ʹ��ʹ��csc1
    PXP_SetProcessSurfaceScaler(PXP, APP_CAMERA_WIDTH, APP_CAMERA_HEIGHT, 376, 272);//����ͼ��
    PXP_SetProcessSurfacePosition(PXP, 52u, 0u, 428 - 1U, 272 - 1U);                //������ʾλ��
#endif
    
    PXP_SetProcessSurfaceBackGroundColor(PXP, 0u);  //���ñ�����ɫ


    PXP_SetRotateConfig(PXP, kPXP_RotateOutputBuffer, kPXP_Rotate180, kPXP_FlipDisable);//ͼ����ת���ٶȣ���ת���
    delayms(200);        
}


