/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������RT1052���İ��׼�
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2018��1��28��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR8.20.1������
��Target  ��i.MX RT1052DVLA
��Crystal �� 24.000Mhz
��busclock��264.500MHz
��pllclock��528.000MHz  
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#ifndef __LQ_TFT480x272_H__
#define __LQ_TFT480x272_H__

#include "fsl_common.h"

extern  uint32_t MYCOLOR[10];
 
/*******************�ӿڶ���******************************/
/* LCD definition. */
#define LCDIF_DATA_BUS              kELCDIF_DataBus16Bit //TFT�������߿��
#define LCD_WIDTH   480
#define LCD_HEIGHT  272
#define LCD_HSW 41
#define LCD_HFP 4
#define LCD_HBP 8
#define LCD_VSW 10
#define LCD_VFP 4
#define LCD_VBP 2

#define LCD_POL_FLAGS (kELCDIF_DataEnableActiveHigh | kELCDIF_VsyncActiveLow | kELCDIF_HsyncActiveLow | kELCDIF_DriveDataOnRisingClkEdge)

/* Display. */
#define LCD_DISP_GPIO GPIO1
#define LCD_DISP_GPIO_PIN   2

/* Back light. */
#define LCD_BL_GPIO GPIO2
#define LCD_BL_GPIO_PIN     31

#define APP_IMG_HEIGHT 272
#define APP_IMG_WIDTH  480

#define	RED		0xFF0000
#define	GREEN		0x00FF00
#define	BLUE		0x0000FF
#define	PURPLE		0xFF00FF
#define	YELLOW		0xFFFF00
#define	CYAN		0x00FFFF //����ɫ
#define	ORANGE		0xFF1080
#define	BLACK		0x000000
#define	WHITE		0xFFFFFF

extern uint16_t logo[];	
extern void delay(uint32_t t);								 //��ʱ����
extern void TFT_CLS(uint32_t fcolor);					                 //ȫ����ʾĳ����ɫ
extern void TFT_Draw_Part(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye,uint32_t fcolor,uint8_t clr);     //��������������ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
extern void TFT_Draw_Line(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye,uint32_t fcolor,uint8_t clr);     //���ߣ�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
extern void TFT_Draw_Rectangle(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye,uint32_t fcolor,uint8_t clr);//�����α߿�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
extern void TFT_Draw_Circle(uint16_t x,uint16_t y,uint16_t r,uint32_t fcolor,uint8_t clr);                 //��Բ�α߿�Բ�ĺ����ꡢ�����꣬�뾶����ɫ
extern void TFT_Draw_CircleCake(uint16_t x,uint16_t y,uint16_t r,uint32_t fcolor,uint8_t clr);
extern void TFT_Draw_Dot(uint16_t x,uint16_t y,uint32_t fcolor);	                         //���㣬�����꣬�����꣬��ɫ
extern void TFT_P6X8(uint16_t x, uint16_t y, uint8_t c_dat, uint32_t fcolor, uint32_t bcolor, uint8_t clr);
extern void TFT_P6X8Str(uint16_t x, uint16_t y, uint8_t *s_dat,uint32_t fcolor, uint32_t bcolor, uint8_t clr);
extern void TFT_P8X8(uint16_t x, uint16_t y, uint8_t c_dat,uint32_t fcolor, uint32_t bcolor, uint8_t clr);
extern void TFT_P8X8Str(uint16_t x, uint16_t y, uint8_t *s_dat,uint32_t fcolor, uint32_t bcolor, uint8_t clr);
extern void TFT_P8X16(uint16_t x, uint16_t y, uint8_t c_dat,uint32_t fcolor, uint32_t bcolor, uint8_t clr);
extern void TFT_P8X16Str(uint16_t x, uint16_t y, uint8_t *s_dat,uint32_t fcolor, uint32_t bcolor, uint8_t clr);
extern void TFT_P16x16Str(uint16_t x,uint16_t y,uint8_t *s_dat,uint32_t fcolor, uint32_t bcolor, uint8_t clr);
extern void TFT_Show_Pic(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye,uint8_t *PicArray);
extern void TFT_Show_Logo(uint16_t xs,uint16_t ys);
extern void TFT_Test(void);

#endif 