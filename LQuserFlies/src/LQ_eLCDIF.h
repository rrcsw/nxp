#ifndef __LQ_ELCDIF_H
#define __LQ_ELCDIF_H


/*******************************************************************************
* Definitions
******************************************************************************/ 
#define APP_LCD_WIDTH  480//Һ�������
#define APP_LCD_HEIGHT 272//Һ�����߶�
#define APP_HSW 41  //��ʾˮƽͬ���źŵĿ�ȣ���VCLK����
#define APP_HFP 4   //��ʾһ�е���Ч���ݽ�������һ��ˮƽͬ���źſ�ʼ֮���VCLK�ĸ���
#define APP_HBP 8   //��ʾ��ˮƽͬ���źſ�ʼ��һ�е���Ч���ݿ�ʼ֮���VCLK�ĸ���
#define APP_VSW 10  //��ʾ��ֱͬ������Ŀ�ȣ�����������
#define APP_VFP 4   //��ʾ��һ֡ͼ������󣬴�ֱͬ���ź���ǰ����Ч������
#define APP_VBP 2   //��ʾ��һ֡ͼ��ʼʱ����ֱͬ���ź��Ժ����Ч������
#define APP_LCD_POL_FLAGS (kELCDIF_DataEnableActiveHigh | kELCDIF_VsyncActiveLow | kELCDIF_HsyncActiveLow | kELCDIF_DriveDataOnRisingClkEdge)
#define APP_LCDIF_DATA_BUS kELCDIF_DataBus16Bit



/* Frame buffer data alignment. */
#define FRAME_BUFFER_ALIGN 64  //֡���������� 








extern void LQ_TFT480_272_Init(void);
extern void Test_TFT_480_272(void);

extern uint8_t counter;
extern volatile uint8_t LQ_LCD;  
extern int OFFSET2;
extern uint32_t lcdFrameBuf[4][LCD_HEIGHT][LCD_WIDTH];


#endif