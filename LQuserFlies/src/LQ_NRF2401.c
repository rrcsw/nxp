/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1052���İ�-���ܳ���
����    д��Z
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2018��12��22��
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
================================================*/
#include "include.h"

/************************************************************************
*������ֲ�޸���
*ֻ��Ҫ����ԭ��ͼ�޸Ķ�Ӧ�Ķ˿�ʱ�� �˿� ����
************************************************************************/
//�������ŵ�ƽ
#define NRF_SCN_LOW   PT2_0 = 0
#define NRF_SCN_HIGH  PT2_0 = 1
#define NRF_CE_LOW    PT2_1 = 0
#define NRF_CE_HIGH   PT2_1 = 1
//��ȡ���ŵ�ƽ
//#define NRF_IRQ_READ  (NRF_IRQ_PORT->IDR & NRF_IRQ)
#define NRFAddrMax 50 //NRF���һ���ֽڵ�ַ���Ϊ50
uint8_t NRFaddr = 0xFF; //��ʼ��NRF���һ�ֽڵ�ַ

uint8_t NRF_TX_DATA[TX_PAYLO_WIDTH];//NRF���ͻ�����
uint8_t NRF_RX_DATA[RX_PAYLO_WIDTH];//NRF���ջ�����

uint8_t TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0xFF}; //���͵�ַ
uint8_t RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0xFF}; //���յ�ַ

void NRF24L01_Config(void);
void NRF_GetAddr(void);

uint8_t NRF_WriteReadByte(uint8_t data)
{
    return LP_SPI_ReadWriteByte(LPSPI1, data);
}

/*****************************************************************************
*��  ����void NRF24l01_Init(void)
*��  �ܣ�NRF����GPIO��ʼ��
*��  ������
*����ֵ����
*��  ע����
*****************************************************************************/
void NRF24l01_Init(void)
{
    
    CLOCK_EnableClock(kCLOCK_Iomuxc);           
    //Ƭѡ CS
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_00_GPIO2_IO00,     0U);                                          
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_00_GPIO2_IO00,0x10B0u);  
    GPIO_PinInit(GPIO2,0, &GPIO_Output_Config); 
    //CE
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_01_GPIO2_IO01,     0U);                                          
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_01_GPIO2_IO01,0x10B0u); 
    GPIO_PinInit(GPIO2,1, &GPIO_Output_Config); 
    
    LP_SPI_Master_Init(LPSPI1, 8000000);
    NRF24L01_Check(); //���NRF24L01�Ƿ���MCUͨ��                                    
	
    NRF_SCN_HIGH; //ʧ��NRF
    NRF_CE_LOW; //����ģʽ
	
    // NRF24L01_Config();  //����NRF����ʼ��Ϊ����ģʽ
}

/*****************************************************************************
*��  ����uint8_t NRF24l01_write_reg(uint8_t reg,uint8_t value)
*��  �ܣ�дһ�ֽ����ݵ��Ĵ���
*��  ����reg�� �Ĵ�����ַ
*        val:  Ҫд�������
*����ֵ��status
*��  ע��NRF2401������ֲֻ���SPI�����޸ĳ��Լ��ļ���
*****************************************************************************/
uint8_t NRF24l01_write_reg(uint8_t reg,uint8_t value)
{
	uint8_t status;
	NRF_SCN_LOW;
	status=NRF_WriteReadByte(reg);
	NRF_WriteReadByte(value);
	NRF_SCN_HIGH;
	return status;
}

/*****************************************************************************
*��  ����uint8_t NRF24l01_read_reg(uint8_t reg)
*��  �ܣ���һ�ֽ����ݵ��Ĵ���
*��  ����reg�� �Ĵ�����ַ
*����ֵ��reg_val
*��  ע��NRF2401������ֲֻ���SPI�����޸ĳ��Լ��ļ���
*****************************************************************************/
uint8_t NRF24l01_read_reg(uint8_t reg)
{
	uint8_t reg_val;
	NRF_SCN_LOW;
	NRF_WriteReadByte(reg);
	reg_val = NRF_WriteReadByte(0xff);
	NRF_SCN_HIGH;
	return reg_val;
}

/*****************************************************************************
*��  ����uint8_t NRF24L01_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
*��  �ܣ�дһ�����ݵ��Ĵ���
*��  ����reg�� �Ĵ�����ַ
*       pBuf�� Ҫд�����ݵĵ�ַ
*        len:  Ҫд������ݳ���
*����ֵ��status
*��  ע��NRF2401������ֲֻ���SPI�����޸ĳ��Լ��ļ���
*****************************************************************************/
uint8_t NRF24L01_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
	uint8_t status;
	int i;
	NRF_SCN_LOW;
	status = NRF_WriteReadByte(reg);
	for( i=0;i<len;i++)
	{
		NRF_WriteReadByte(*pBuf);
		pBuf++;
	}
	NRF_SCN_HIGH;
	return status;
}

/*****************************************************************************
*��  ����uint8_t NRF24L01_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
*��  �ܣ���һ�����ݵ��Ĵ���
*��  ����reg�� �Ĵ�����ַ
*       pBuf�� Ҫ��ȡ���ݵĵ�ַ
*        len:  Ҫ��ȡ�����ݳ���
*����ֵ��status
*��  ע��NRF2401������ֲֻ���SPI�����޸ĳ��Լ��ļ���
*****************************************************************************/
uint8_t NRF24L01_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
	uint8_t status;
	int i;
	NRF_SCN_LOW;
	status = NRF_WriteReadByte(reg);
	for(i = 0;i < len ;i++)
	{
		*pBuf = NRF_WriteReadByte(0xff);
		pBuf++;
	}
	NRF_SCN_HIGH;
	return status;
}

/*****************************************************************************
*��  ����void NRFset_Mode(uint8_t mode)
*��  �ܣ��л�NRF2401�Ĺ���ģʽģʽ
*��  ������
*����ֵ����
*��  ע����
*****************************************************************************/
void NRFset_Mode(uint8_t mode)
{
	if(mode == IT_TX)
	{
        NRF_CE_LOW;
        NRF24l01_write_reg(W_REGISTER+CONFIG,IT_TX);//�����ж�
//        NRF24l01_write_reg(W_REGISTER+STATUS,0X7E); //��������ж�,��ֹһ��ȥ����ģʽ�ʹ����ж�	
        NRF_CE_HIGH;
        // delay_us(15);
	}
	else
	{
        NRF_CE_LOW;
        NRF24l01_write_reg(W_REGISTER+CONFIG,IT_RX);//����Ϊ����ģʽ �����ж�
//        NRF24l01_write_reg(W_REGISTER+STATUS,0X7E); //��������ж�,��ֹһ��ȥ����ģʽ�ʹ����ж�
        NRF_CE_HIGH;
     	delayus(200);
	}
    
}

/*****************************************************************************
*��  ����void NRF24L01_Config(void)
*��  �ܣ�NRF�����������ã�����ʼ��Ϊ����ģʽ
*��  ������
*����ֵ����
*��  ע����
*****************************************************************************/
void NRF24L01_Config(void)
{
	NRF_CE_LOW;
	NRF24l01_write_reg(W_REGISTER+SETUP_AW, 0x03); //����ͨ�ŵ�ַ�ĳ��ȣ�Ĭ��ֵʱ0x03,����ַ����Ϊ5�ֽ�
	NRF24L01_Write_Buf(W_REGISTER+TX_ADDR,(uint8_t*)TX_ADDRESS,TX_ADR_WIDTH); //дTX�ڵ��ַ 
	NRF24L01_Write_Buf(W_REGISTER+RX_ADDR_P0,(uint8_t*)TX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK
	NRF24l01_write_reg(W_REGISTER+SETUP_RETR,0x1A); //�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10�� 0x1A
	
	NRF24l01_write_reg(W_REGISTER+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ  
	NRF24l01_write_reg(W_REGISTER+EN_AA,0x01); //ʹ��ͨ��0�Զ�Ӧ��
	NRF24l01_write_reg(W_REGISTER+RX_PW_P0,RX_PAYLO_WIDTH);//ѡ��ͨ��0����Ч���ݿ��  
	NRF24L01_Write_Buf(W_REGISTER+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH); //дRX�ڵ��ַ
	NRF24l01_write_reg(W_REGISTER+RF_CH,30); //����RFͨ��Ϊ40hz(1-64Hz������)
	NRF24l01_write_reg(W_REGISTER+RF_SETUP,0x07); //����TX�������,0db����,2Mbps,����������ر� ��ע�⣺����������ر�/����ֱ��Ӱ��ͨ��,Ҫ������������Ҫ�رն��ر�0x0f��
	NRFset_Mode(IT_RX); //Ĭ��Ϊ����ģʽ
	
	NRF_CE_HIGH;
}	

/*****************************************************************************
*��  ����uint8_t NRF24L01_testConnection(void)
*��  �ܣ����NRF2401��MCU��SPI�����Ƿ�ͨ������
*��  ������
*����ֵ��1������ 0δ����
*��  ע����
*****************************************************************************/
uint8_t NRF24L01_testConnection(void)
{
	uint8_t buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	uint8_t i; 	 
	NRF24L01_Write_Buf(W_REGISTER+TX_ADDR,buf,5); //д��5���ֽڵĵ�ַ.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //����д��ĵ�ַ  
	for(i=0;i<5;i++)
        if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 0; //���24L01����	
	return 1;	//��⵽24L01
}	
void NRF24L01_Check(void)
{
	while(!NRF24L01_testConnection())
	{
		printf("\rNRF2401 no connect...\r\n");
		LED_Color(red);//��Ƴ���
	}
}


/*****************************************************************************
*��  ����uint8_t NRF24L01_TxPacket(uint8_t *txbuf)
*��  �ܣ�NRF����һ������
*��  ����txbuf��Ҫ�������ݵ�ַ
*����ֵ���� 
*��  ע����
*****************************************************************************/
void NRF24L01_TxPacket(uint8_t *txbuf)
{
	NRF_CE_LOW;	
	NRF24L01_Write_Buf(W_REGISTER+TX_ADDR,(uint8_t*)TX_ADDRESS,TX_ADR_WIDTH);  //дTX�ڵ��ַ 
	NRF24L01_Write_Buf(W_REGISTER+RX_ADDR_P0,(uint8_t*)TX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK
	NRF24L01_Write_Buf(W_RX_PAYLOAD,txbuf,TX_PAYLO_WIDTH); //д���ݵ�TX_BUFF
    NRF24l01_write_reg(W_REGISTER+CONFIG,0x7e);	//����Ϊ����ģʽ,��ʹ�������ж�
//	NRF24l01_write_reg(W_REGISTER+STATUS,0X7E); //��������ж�,��ֹһ��ȥ����ģʽ�ʹ����ж�
    NRF_CE_HIGH;
	delayus(10);  //CE�����ߵ�ƽ10us
}

/*****************************************************************************
*��  ����uint8_t NRF24L01_RxPacket(uint8_t *rxbuf)
*��  �ܣ�NRF����һ������
*��  ����rxbuf���������ݴ洢��ַ
*����ֵ����
*��  ע����
*****************************************************************************/
void NRF24L01_RxPacket(uint8_t *rxbuf)
{
	NRF_CE_LOW;
	NRF24L01_Read_Buf(R_RX_PAYLOAD,rxbuf,TX_PAYLO_WIDTH);//��ȡRX����Ч����
	NRF24l01_write_reg(FLUSH_RX,0xff); //���RX FIFO(ע�⣺��仰�ܱ�Ҫ)
	NRF_CE_HIGH;
}


/*****************************************************************************
*��  ����void NRF_Test(void)
*��  �ܣ�MRFͨ�Ų��Ժ���
*��  ������
*����ֵ���� 
*��  ע������ʱ��
*****************************************************************************/
void NRF_Test(void)
{
	uint8_t t=0;
	static uint8_t mode,key;
	mode = ' ';
	key=mode;
	for(t=0;t<32;t++)
	{
		key++;
		if(key>('~'))key=' ';
		NRF_TX_DATA[t]=key;	
	}
	mode++; 
	if(mode>'~')mode=' ';  	  		
	NRF24L01_TxPacket(NRF_TX_DATA);
}
