
#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_
/*******************************************************************************
 * API
 ******************************************************************************/
void BOARD_InitPins(void);
void BOARD_InitSemcPins(void);
//UART���Զ˿ڹܽŸ���
void BOARD_InitDEBUG_UARTPins(void);

//�ⲿSDRAM�ܽŸ���
void BOARD_InitSDRAMPins(void);

//����ͷCSI�ܽŸ���
void BOARD_InitCSIPins(void);

//����ͷ��I2C1�ܽŸ���
void BOARD_InitLPI2C1Pins(void);

//��ɫLCD�ܽŸ���
void BOARD_InitLCDPins(void); 

//SD��/TF���ܽŸ���
void BOARD_InitSDPins(void);

#endif /* _PIN_MUX_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
