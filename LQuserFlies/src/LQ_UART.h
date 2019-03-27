/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1052���İ�-���ܳ���
����    д��Z
��E-mail  ��chiusir@163.com
������汾��V1.0������Դ���룬�����ο�������Ը�
�������¡�2018��10��18��
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
================================================
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef __LQ_UART_H
#define __LQ_UART_H

#include "include.h"

extern void LQ_UART_Init(LPUART_Type *base, uint32_t bound);
extern void LQ_UART_PutChar(LPUART_Type *base, uint8_t data);
extern void LQ_UART_PutBuff(LPUART_Type *base, uint8_t * buff, uint32_t length);
extern void Test_UART(void);
extern void Test_UART_DMA(void);
extern void UART_DMA_Init(void);
#endif