#include "system.h"
#include "stdio.h"
#include "uart.h"

//LPUART1_TX     K14
//LPUART1_RX     L14

//LPUART2_TX     L11
//LPUART2_RX     M12

//LPUART3_TX     J12
//LPUART3_RX     K10

//LPUART4_TX     L5
//LPUART4_RX     M5

//LPUART5_TX     D13
//LPUART5_RX     D14

//LPUART6_TX     M11
//LPUART6_RX     J11

//LPUART7_TX     P3
//LPUART7_RX     N4

//LPUART8_TX     H2
//LPUART8_RX     J2

volatile uint8_t res = 0;
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
//IAR����Ҫ��options -> C/C++compiler -> Preprocessor ��Ӻ궨�� _DLIB_FILE_DESCRIPTOR
#if 1
//#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((LPUART1->STAT&LPUART_STAT_TDRE_MASK)==0);
	LPUART1->DATA=(uint8_t)ch;	
	return ch;
}
#endif 


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵�����õ�����ʱ��Ƶ�� һ��Ϊ80Mhz
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
/* Get uart console frequency. */
uint32_t LQ_GetUartSrcFreq(void)
{
    uint32_t freq;

    /* To make it simple, we assume default PLL and divider settings, and the only variable
       from application is use PLL3 source or OSC source */
    if (CLOCK_GetMux(kCLOCK_UartMux) == 0) /* PLL3 div6 80M */
    {
        freq = (CLOCK_GetPllFreq(kCLOCK_PllUsb1) / 6U) / (CLOCK_GetDiv(kCLOCK_UartDiv) + 1U);
    }
    else
    {
        freq = CLOCK_GetOscFreq() / (CLOCK_GetDiv(kCLOCK_UartDiv) + 1U);
    }

    return freq;
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵������ʼ�����ڣ����ò�����
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� LQ_UART_Init(LPUART1, 115200);
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_UART_Init(LPUART_Type *base, uint32_t bound)
{	
    if(base == LPUART1)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart1);	//ʹ��LPUART1ʱ��
        //LPUART1��ʹ�õ�IO�������ã�������ALT0~ALT7ѡ����ʵĹ��ܡ�
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_LPUART1_TX,0U);	//LPUART1_TX   K14
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_LPUART1_RX,0U);	//LPUART1_RX   L14
        
        //����IO����GPIO_AD_B0_12��GPIO_AD_B0_13�Ĺ���
        //��ת���ٶ�,��������ΪR0/6,�ٶ�Ϊ100Mhz���رտ�·���ܣ�ʹ��pull/keepr
        //ѡ��keeper���ܣ�����100K Ohm���ر�Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_12_LPUART1_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_13_LPUART1_RX,0x10B0u); 
        
    }
    else if(base == LPUART2)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart2);	//ʹ��LPUART1ʱ��
        //LPUART1��ʹ�õ�IO�������ã�������ALT0~ALT7ѡ����ʵĹ��ܡ�
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_LPUART2_TX,0U);	//LPUART2_TX    L11
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_LPUART2_RX,0U);	//LPUART2_RX    M12
        
        //����IO����GPIO_AD_B0_12��GPIO_AD_B0_13�Ĺ���
        //��ת���ٶ�,��������ΪR0/6,�ٶ�Ϊ100Mhz���رտ�·���ܣ�ʹ��pull/keepr
        //ѡ��keeper���ܣ�����100K Ohm���ر�Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_02_LPUART2_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_03_LPUART2_RX,0x10B0u); 
    }
    else if(base == LPUART3)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart3);	//ʹ��LPUART1ʱ��
        //LPUART1��ʹ�õ�IO�������ã�������ALT0~ALT7ѡ����ʵĹ��ܡ�
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_06_LPUART3_TX,0U);	//LPUART3_TX     J12
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_LPUART3_RX,0U);	//LPUART3_RX     K10
        
//        IOMUXC_SetPinMux(IOMUXC_GPIO_B0_08_LPUART3_TX,0U);	
//        IOMUXC_SetPinMux(IOMUXC_GPIO_B0_09_LPUART3_RX,0U);	
        //����IO����GPIO_AD_B0_12��GPIO_AD_B0_13�Ĺ���
        //��ת���ٶ�,��������ΪR0/6,�ٶ�Ϊ100Mhz���رտ�·���ܣ�ʹ��pull/keepr
        //ѡ��keeper���ܣ�����100K Ohm���ر�Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_06_LPUART3_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_07_LPUART3_RX,0x10B0u); 
        
//        IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_08_LPUART3_TX,0x10B0u); 
//        IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_09_LPUART3_RX,0x10B0u); 
    }
    else if(base == LPUART4)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart4);	//ʹ��LPUART1ʱ��
        //LPUART1��ʹ�õ�IO�������ã�������ALT0~ALT7ѡ����ʵĹ��ܡ�
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_LPUART4_TX,0U);	//LPUART4_TX     L5
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_01_LPUART4_RX,0U);	//LPUART4_RX     M5
        
        //����IO����GPIO_AD_B0_12��GPIO_AD_B0_13�Ĺ���
        //��ת���ٶ�,��������ΪR0/6,�ٶ�Ϊ100Mhz���رտ�·���ܣ�ʹ��pull/keepr
        //ѡ��keeper���ܣ�����100K Ohm���ر�Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_00_LPUART4_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_01_LPUART4_RX,0x10B0u); 
    }
    else if(base == LPUART5)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart5);	//ʹ��LPUART1ʱ��
        //LPUART1��ʹ�õ�IO�������ã�������ALT0~ALT7ѡ����ʵĹ��ܡ�
        IOMUXC_SetPinMux(IOMUXC_GPIO_B1_12_LPUART5_TX,0U);	//LPUART5_TX       D13
        IOMUXC_SetPinMux(IOMUXC_GPIO_B1_13_LPUART5_RX,0U);	//LPUART5_RX       D14
        
        //����IO����GPIO_AD_B0_12��GPIO_AD_B0_13�Ĺ���
        //��ת���ٶ�,��������ΪR0/6,�ٶ�Ϊ100Mhz���رտ�·���ܣ�ʹ��pull/keepr
        //ѡ��keeper���ܣ�����100K Ohm���ر�Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_12_LPUART5_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_13_LPUART5_RX,0x10B0u); 
    }
    else if(base == LPUART6)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart6);	//ʹ��LPUART1ʱ��
        //LPUART1��ʹ�õ�IO�������ã�������ALT0~ALT7ѡ����ʵĹ��ܡ�
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_02_LPUART6_TX,0U);	//LPUART6_TX   M11
        IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_03_LPUART6_RX,0U);	//LPUART6_RX   J11
        
        //����IO����GPIO_AD_B0_12��GPIO_AD_B0_13�Ĺ���
        //��ת���ٶ�,��������ΪR0/6,�ٶ�Ϊ100Mhz���رտ�·���ܣ�ʹ��pull/keepr
        //ѡ��keeper���ܣ�����100K Ohm���ر�Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_02_LPUART6_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_03_LPUART6_RX,0x10B0u); 
    }
    else if(base == LPUART7)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart7);	//ʹ��LPUART1ʱ��
        //LPUART1��ʹ�õ�IO�������ã�������ALT0~ALT7ѡ����ʵĹ��ܡ�
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_08_LPUART7_TX,0U);	//LPUART7_TX   P3
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_09_LPUART7_RX,0U);	//LPUART7_RX   N4
        
        //����IO����GPIO_AD_B0_12��GPIO_AD_B0_13�Ĺ���
        //��ת���ٶ�,��������ΪR0/6,�ٶ�Ϊ100Mhz���رտ�·���ܣ�ʹ��pull/keepr
        //ѡ��keeper���ܣ�����100K Ohm���ر�Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_08_LPUART7_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_09_LPUART7_RX,0x10B0u); 
    }
    else if(base == LPUART8)
    {
        CLOCK_EnableClock(kCLOCK_Lpuart8);	//ʹ��LPUART1ʱ��
        //LPUART1��ʹ�õ�IO�������ã�������ALT0~ALT7ѡ����ʵĹ��ܡ�
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_04_LPUART8_TX,0U);	//LPUART8_TX    H2
        IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B0_05_LPUART8_RX,0U);	//LPUART8_RX    J2
        
        //����IO����GPIO_AD_B0_12��GPIO_AD_B0_13�Ĺ���
        //��ת���ٶ�,��������ΪR0/6,�ٶ�Ϊ100Mhz���رտ�·���ܣ�ʹ��pull/keepr
        //ѡ��keeper���ܣ�����100K Ohm���ر�Hyst
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_04_LPUART8_TX,0x10B0u); 
        IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B0_05_LPUART8_RX,0x10B0u); 
    }
	CLOCK_SetMux(kCLOCK_UartMux,0); 	//����UARTʱ��ԴΪPLL3 80Mhz��PLL3/6=480/6=80MHz
    CLOCK_SetDiv(kCLOCK_UartDiv,0); 	//����UARTʱ��1��Ƶ����UARTʱ��Ϊ80Mhz
	
    lpuart_config_t lpuart_config;              //�������ýṹ��
	LPUART_GetDefaultConfig(&lpuart_config);    //�õ�Ĭ�����ã������ڸ���ʵ���������
	
	lpuart_config.baudRate_Bps=bound;						//������
	lpuart_config.dataBitsCount=kLPUART_EightDataBits;		//8λ
	lpuart_config.stopBitCount=kLPUART_OneStopBit;			//1λֹͣλ
	lpuart_config.parityMode=kLPUART_ParityDisabled;		//����żУ��
	lpuart_config.enableRx=true;							//ʹ�ܽ���
	lpuart_config.enableTx=true;							//ʹ�ܷ���
	
    uint32_t  freq=0;							//���ڵ�ʱ��ԴƵ��
	freq=LQ_GetUartSrcFreq();	                //�õ�����ʱ��Ƶ��
    
	LPUART_Init(base,&lpuart_config,freq);				//��ʼ��LPUART1 

	//LPUART�ж�����
	LPUART_EnableInterrupts(base,kLPUART_RxDataRegFullInterruptEnable); //kLPUART_RxDataRegFullInterruptEnable��ʹ�ܽ����ж�  ʹ�������ж��������޸�
   
    if(base == LPUART1)
    {
        //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
       NVIC_SetPriority(LPUART1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
       EnableIRQ(LPUART1_IRQn);	                            //ʹ��LPUART1�ж�      
    }
    else if(base == LPUART2)
    {
        //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
        NVIC_SetPriority(LPUART2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART2_IRQn);	                            //ʹ��LPUART1�ж�      
    }
    else if(base == LPUART3)
    {
        //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
        NVIC_SetPriority(LPUART3_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART3_IRQn);	                            //ʹ��LPUART1�ж�    
    }
    else if(base == LPUART4)
    {
        //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
        NVIC_SetPriority(LPUART4_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART4_IRQn);	                            //ʹ��LPUART1�ж�     
    }
    else if(base == LPUART5)
    {
        //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
        NVIC_SetPriority(LPUART5_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART5_IRQn);	                            //ʹ��LPUART1�ж�     
    }
    else if(base == LPUART6)
    {
        //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
        NVIC_SetPriority(LPUART6_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART6_IRQn);	                            //ʹ��LPUART1�ж�    
    }
    else if(base == LPUART7)
    {
        //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
        NVIC_SetPriority(LPUART7_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART7_IRQn);	                            //ʹ��LPUART1�ж�       
    }
    else if(base == LPUART8)
    {
        //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
        NVIC_SetPriority(LPUART8_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        EnableIRQ(LPUART8_IRQn);	                            //ʹ��LPUART1�ж�       
    }   

}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵��������һ���ַ�
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� LQ_UART_PutChar(LPUART1, char);
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_UART_PutChar(LPUART_Type *base, uint8_t data)
{
    while (!(base->STAT & LPUART_STAT_TDRE_MASK));    //�ȴ�base->STATΪ��
    base->DATA = data;
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵��������һ���ַ���
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� LQ_UART_PutBuff(LPUART1, buff, 10);
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
//    LPUART_WriteBlocking(LPUART_Type *base, const uint8_t *data, size_t length);   //�������ƵĿ⺯��
void LQ_UART_PutBuff(LPUART_Type *base, uint8_t * buff, uint32_t length)
{
    while (length--)
    {
        while (!(base->STAT & LPUART_STAT_TDRE_MASK));    //�ȴ�base->STATΪ��
        base->DATA = *(buff++);
    }
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵�������Դ���ģ��
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����  ע�⣺ʹ��DAPlink�Դ��Ĵ���ʱ���п��ܽ��ղ�������
��ʵ���� LQ_UART_PutBuff(LPUART1, buff, 10);
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_UART(void)
{
    LQ_UART_Init(LPUART1, 115200);  //��BOARD_InitDebugConsole()����һ��
    LQ_UART_Init(LPUART2, 115200);  
    LQ_UART_Init(LPUART3, 57600);
    LQ_UART_Init(LPUART4, 38400);
    LQ_UART_Init(LPUART5, 19200);
    LQ_UART_Init(LPUART6, 9600);
//    LQ_UART_Init(LPUART7, 256000);  //SPIFlashʹ�ø�����
    LQ_UART_Init(LPUART8, 256000);
    printf("LPUART2 init: 115200!\n");
    printf("LPUART3 init: 57600!\n");
    printf("LPUART4 init: 38400!\n");
    printf("LPUART5 init: 19200!\n");
    printf("LPUART6 init: 9600!\n");
    printf("LPUART1 init: 115200!\n");
    printf("LPUART8 init: 256000!\n");
    while(1)
    {
    uint8_t a = 'a';
    LQ_UART_PutChar(LPUART1, a);
    LQ_UART_PutChar(LPUART2, a+1);
    LQ_UART_PutChar(LPUART3, a+2);
    LQ_UART_PutChar(LPUART4, a+3);
    LQ_UART_PutChar(LPUART5, a+4);
    LQ_UART_PutChar(LPUART6, a+5);
//    LQ_UART_PutChar(LPUART7, a+6);
    LQ_UART_PutChar(LPUART8, a+7);
    delayms(100);
    uint8_t buff[10] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
    LQ_UART_PutBuff(LPUART1, buff, 10);
    LQ_UART_PutBuff(LPUART2, buff, 10);
    LQ_UART_PutBuff(LPUART3, buff, 10);
    LQ_UART_PutBuff(LPUART4, buff, 10);
    LQ_UART_PutBuff(LPUART5, buff, 10);
    LQ_UART_PutBuff(LPUART6, buff, 10);
//    LQ_UART_PutBuff(LPUART7, buff, 10);//SPIFlashʹ�ø�����
    LQ_UART_PutBuff(LPUART8, buff, 10);
    delayms(100);
         if(res > 9)
        {
            res = 0;                   //���ܻ���������ֱ�Ӹ���
            printf("UART1 �����ж� OK��\n");
            delayms(100);
        }
    }
    
    
    
}
//LPUART1�жϷ�������Ϊ�˽���Ч��ֱ�Ӳ����Ĵ���
uint8_t LPUART_RX_BUF[100]; //���ջ�����
void LPUART1_IRQHandler(void)
{
	if((LPUART1->STAT)&kLPUART_RxDataRegFullFlag) //�����ж�
	{
//		LPUART_RX_BUF[res] = LPUART_ReadByte(LPUART1);					//��ȡ����
        ANO_DT_Data_Receive_Prepare(LPUART_ReadByte(LPUART1));          //����������λ��Э��
		res ++;
	}
	__DSB();				//����ͬ������ָ��
}
void LPUART2_IRQHandler(void)
{
	static uint8_t res=0;
	
	if((LPUART2->STAT)&kLPUART_RxDataRegFullFlag) //�����ж�
	{
		LPUART_RX_BUF[res] = LPUART_ReadByte(LPUART2);				//��ȡ����
		res ++;
	}
	__DSB();				//����ͬ������ָ��
}

void LPUART3_IRQHandler(void)
{
	static uint8_t res=0;
	
	if((LPUART3->STAT)&kLPUART_RxDataRegFullFlag) //�����ж�
	{
		LPUART_RX_BUF[res] = LPUART_ReadByte(LPUART3);					//��ȡ����
		res ++;
        if(res == 100) res = 0;                   //���ܻ���������ֱ�Ӹ���
	}
	__DSB();				//����ͬ������ָ��
}

void LPUART4_IRQHandler(void)
{
	static uint8_t res=0;
	
	if((LPUART4->STAT)&kLPUART_RxDataRegFullFlag) //�����ж�
	{
		LPUART_RX_BUF[res] = LPUART_ReadByte(LPUART4);				//��ȡ����
		res ++;
        if(res == 100) res = 0;                   //���ܻ���������ֱ�Ӹ���
	}
	__DSB();				//����ͬ������ָ��
}

void LPUART5_IRQHandler(void)
{
	static uint8_t res=0;
	
	if((LPUART5->STAT)&kLPUART_RxDataRegFullFlag) //�����ж�
	{
		LPUART_RX_BUF[res] = LPUART_ReadByte(LPUART5);				//��ȡ����
		res ++;
        if(res == 100) res = 0;                   //���ܻ���������ֱ�Ӹ���
	}
	__DSB();				//����ͬ������ָ��
}

void LPUART6_IRQHandler(void)
{
	static uint8_t res=0;
	
	if((LPUART6->STAT)&kLPUART_RxDataRegFullFlag) //�����ж�
	{
		LPUART_RX_BUF[res] = LPUART_ReadByte(LPUART6);					//��ȡ����
		res ++;
        if(res == 100) res = 0;                   //���ܻ���������ֱ�Ӹ���
	}
	__DSB();				//����ͬ������ָ��
}

void LPUART7_IRQHandler(void)
{
	static uint8_t res=0;
	
	if((LPUART7->STAT)&kLPUART_RxDataRegFullFlag) //�����ж�
	{
		LPUART_RX_BUF[res] = LPUART_ReadByte(LPUART7);					//��ȡ����
		res ++;
        if(res == 100) res = 0;                   //���ܻ���������ֱ�Ӹ���
	}
	__DSB();				//����ͬ������ָ��
}

void LPUART8_IRQHandler(void)
{
	static uint8_t res=0;
	
	if((LPUART8->STAT)&kLPUART_RxDataRegFullFlag) //�����ж�
	{
		LPUART_RX_BUF[res] = LPUART_ReadByte(LPUART8);					//��ȡ����
		res ++;
        if(res == 100) res = 0;                   //���ܻ���������ֱ�Ӹ���
	}
	__DSB();				//����ͬ������ָ��
}





/* LPUART user callback */
//����DMA�Ļص���������DMAִ�н����󣬻��Զ����øú����������ڸú����ڼ����û��Լ��Ĵ��룬ʵ��DMA������ɺ���Ҫִ�еĲ���
void LPUART_UserCallback(LPUART_Type *base, lpuart_edma_handle_t *handle, status_t status, void *userData)
{
    userData = userData;

    if (kStatus_LPUART_TxIdle == status)     //������Ϳ���
    {
        _status.txBufferFull = false;
        _status.txOnGoing = false;
        return;
    }

    if (kStatus_LPUART_RxIdle == status)     //���տ���
    {
        _status.rxBufferEmpty = false;
        _status.rxOnGoing = false;
    }
    else
    {
        while(kStatus_LPUART_RxIdle == status);
         _status.rxBufferEmpty = false;
        _status.rxOnGoing = false;
    }
}


AT_NONCACHEABLE_SECTION_INIT(uint8_t g_tipString[]) =
    "LPUART EDMA example\r\nSend back received data\r\nEcho every 8 characters\r\n";  //DMA�����ַ�������
lpuart_transfer_t xfer;
lpuart_transfer_t sendXfer;
lpuart_edma_handle_t g_lpuartEdmaHandle;
edma_handle_t g_lpuartTxEdmaHandle;
edma_handle_t g_lpuartRxEdmaHandle;
void Test_UART_DMA(void)
{
    UART_DMA_Init();

//    /* Start to echo. */
//    sendXfer.data = g_txBuffer;              //DMA������ַ����׵�ַ   ��ANO_DT_Send_Data()�����ڲ���ֵ
//    sendXfer.dataSize = ECHO_BUFFER_LENGTH;  //DMA����ĳ���
//    
    float data1 = 0.0f;
    float data2 = 45.0f; 
    float data3 = 90.0f;   
    float data4 = 135.0f;   
    float data5 = 60.0f;
    const float PI = 3.1415926;

    while(1)
    {
        uint64_t now = _systime.get_time_us();         //��ʱ����  �õ���ǰʱ��
        if(!_status.txOnGoing)           //�������ڷ��͹���
        {


                ANO_DT_send_int16((short)(sin(data1/180.0f * PI) * 100),   //�ϱ�������λ�� ��������
                                  (short)(sin(data2/180.0f * PI) * 100), 
                                  (short)(sin(data3/180.0f * PI) * 100), 
                                  (short)(sin(data4/180.0f * PI) * 100), 
                                  (short)(sin(data5/180.0f * PI) * 100), 
                                  0, 
                                  0, 
                                  0);
        }
        
        
        delayms(10);
        uint64_t time = _systime.get_time_us() - now;  //�õ�ʱ��
        //        printf("time is %llu \r\n", time);
        
        
        if(data1 > 180) data1 = -180;
        if(data2 > 180) data2 = -180;
        if(data3 > 180) data3 = -180;
        if(data4 > 180) data4 = -180;
        if(data5 > 180) data5 = -180;
        
        data1 += 1;
        data2 += 2;
        data3 += 3;
        data4 += 4;
        data5 += 5;
    }

}
void UART_DMA_Init(void)
{
    LQ_UART_Init(LPUART1, 115200);   //���� + DMA �շ�
    
    /* Init DMAMUX */
    DMAMUX_Init(DMAMUX);              //��ʼ��DMA��·������
    /* Set channel for LPUART */
    DMAMUX_SetSource(DMAMUX, 0, kDmaRequestMuxLPUART1Tx);   //����DMAͨ��0 ӳ�䵽 LPUART1Tx
    DMAMUX_SetSource(DMAMUX, 1, kDmaRequestMuxLPUART1Rx);   //����DMAͨ��1 ӳ�䵽 LPUART1Rx
    DMAMUX_EnableChannel(DMAMUX, 0);                        //ʹ��ͨ��0
    DMAMUX_EnableChannel(DMAMUX, 1);                        //ʹ��ͨ��1
    
    edma_config_t config;     //DMA���ýṹ��
    /* Init the EDMA module */
    EDMA_GetDefaultConfig(&config); //�õ�Ĭ��DMA����
    EDMA_Init(DMA0, &config);       //��ʼ������DMA
    

    EDMA_CreateHandle(&g_lpuartTxEdmaHandle, DMA0, 0);  // ����DMA�������DMA0�� ͨ��0�� ����Ϣ�����g_lpuartTxEdmaHandle�ṹ����
    EDMA_CreateHandle(&g_lpuartRxEdmaHandle, DMA0, 1);  // ����DMA�������DMA0�� ͨ��1�� ����Ϣ�����g_lpuartRxEdmaHandle�ṹ����


    /* Create LPUART DMA handle. */
    LPUART_TransferCreateHandleEDMA(LPUART1, &g_lpuartEdmaHandle, LPUART_UserCallback, NULL, &g_lpuartTxEdmaHandle,
                                    &g_lpuartRxEdmaHandle);    // ��������DMA���  ����LPUART1��LPUART_UserCallback, NULL, &g_lpuartTxEdmaHandle, &g_lpuartRxEdmaHandle��Ϣ�����g_lpuartEdmaHandle��

}

