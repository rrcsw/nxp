#ifndef __LQ_UART_H
#define __LQ_UART_H

#include "system.h"

extern void LQ_UART_Init(LPUART_Type *base, uint32_t bound);
extern void LQ_UART_PutChar(LPUART_Type *base, uint8_t data);
extern void LQ_UART_PutBuff(LPUART_Type *base, uint8_t * buff, uint32_t length);
extern void Test_UART(void);
extern void Test_UART_DMA(void);
extern void UART_DMA_Init(void);

#endif