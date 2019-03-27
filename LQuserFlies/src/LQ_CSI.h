#ifndef __LQ_CSI_H
#define __LQ_CSI_H


#define LQMT9V034    //ѡ��ʹ����������ͷģ��
//#define LQOV7725   //����ѡ��һ

#ifdef LQMT9V034 //LQMT9V034ģ��
#define APP_CAMERA_WIDTH  (IMAGEW)
#define APP_CAMERA_HEIGHT (IMAGEH/2)  //һ��uint16_t����װ���������أ� һ��IMAGEW ������ʵװ�����е����ص㣬���Ը߶�/2
#define APP_BPP 2 //���ظ�ʽ��
#define  Use_ROWS  60    //ʹ��ͼ��߶�
#define  Use_Line  94   //ʹ��ͼ����
#else            //LQOV7725ģ��
//#define LQOV7725RGB   //ʹ��7725RGB   ʹ����λ����ͼʱ��ѡ��RGB���ǻҶ�
#define LQOV7725YUV   //ʹ��7725�Ҷ�  ʹ����λ����ͼʱ��ѡ��RGB���ǻҶ�
#define APP_CAMERA_WIDTH  320
#define APP_CAMERA_HEIGHT 240
/* Pixel format YUV422, bytesPerPixel is 2. */
#define APP_BPP 2 //���ظ�ʽ
#define  Use_ROWS  60    //ʹ��ͼ��߶�
#define  Use_Line  80    //ʹ��ͼ����
#endif

#define APP_CAMERA_FRAME_BUFFER_COUNT 4 
#define FRAME_BUFFER_ALIGN 64  //���� 


#define APP_CAMERA_CONTROL_FLAGS (kCAMERA_HrefActiveHigh | kCAMERA_DataLatchOnRisingEdge) //ʹ������ͷ��������
extern void LQ_Camera_Init(void);
extern camera_device_handle_t cameraDevice;    
extern camera_receiver_handle_t cameraReceiver;
extern uint16_t csiFrameBuf[APP_CAMERA_FRAME_BUFFER_COUNT][APP_CAMERA_HEIGHT][APP_CAMERA_WIDTH];
extern void Test_Camera_Reprot(void);
extern camera_config_t cameraConfig;   //����ͷ���ýṹ��
#endif