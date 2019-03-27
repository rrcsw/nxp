/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1052���İ�-���ܳ���
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0������Դ���룬�����ο�������Ը�
�������¡�2018��2��1��
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
Board settings
================================================

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"

_LQ_TP_DEV tp_dev=
{
  TP_Init,
  GT9147_Scan,	
  0,
  0, 
  0,
  0,
  0,
  0,	  	 		
  0,
  0,	  	 		
};

const uint8_t GT9147_CFG_TBL[]=
{ 
  0x41,0xE0,0x01,0x10,0x01,0x05,0x0F,0x00,0x01,0x08,
  0x28,0x05,0x50,0x32,0x03,0x05,0x00,0x00,0xFF,0xFF,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x89,0x28,0x0A,
  0x17,0x15,0x31,0x0D,0x00,0x00,0x02,0x9B,0x03,0x25,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x32,0x00,0x00,
  0x00,0x0F,0x94,0x94,0xC5,0x02,0x07,0x00,0x00,0x04,
  0x8D,0x13,0x00,0x5C,0x1E,0x00,0x3C,0x30,0x00,0x29,
  0x4C,0x00,0x1E,0x78,0x00,0x1E,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x08,0x0A,0x0C,0x0E,0x10,0x12,0x14,0x16,
  0x18,0x1A,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0x00,0x02,0x04,0x05,0x06,0x08,0x0A,0x0C,
  0x0E,0x1D,0x1E,0x1F,0x20,0x22,0x24,0x28,0x29,0xFF,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0x30,0x01,
};  
/*
0x62,0xe0,0x01,0x20,0x03,0x05,0x34,0xc0,0x01,0x08, 
0x28,0x0f,0x50,0x32,0x03,0x05,0x00,0x00,0x00,0x00, 
0x00,0x00,0x06,0x16,0x16,0x1f,0x14,0x89,0x28,0x0a, 
0x17,0x15,0x31,0x0d,0x00,0x00,0x08,0x22,0x04,0x11, 
0x00,0x00,0x00,0x00,0x00,0x03,0x82,0x08,0x08,0x00, 
0x00,0x0f,0x2c,0x94,0xc5,0x02,0x07,0x00,0x00,0x04, 
0x9d,0x10,0x00,0x84,0x14,0x00,0x70,0x19,0x00,0x5f, 
0x20,0x00,0x55,0x27,0x00,0x54,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01, 
0x00,0x00,0x1a,0x18,0x16,0x14,0x12,0x10,0x0e,0x0c, 
0x0a,0x08,0x00,0x00,0x00,0x00,0x1f,0xff,0xff,0xff, 
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 
0xff,0x00,0x00,0x02,0x04,0x05,0x06,0x08,0x0a,0x0c, 
0x0e,0x1d,0x1e,0x1f,0x20,0x22,0x24,0x28,0x29,0xff, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff, 
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf6, 
0xff,0xff,0xff,0xff,
*/


//����GT9147���ò���
//mode:0,���������浽flash
//     1,�������浽flash
uint8_t GT9147_Send_Cfg(uint8_t mode)
{
  uint8_t buf[2];
  uint8_t i=0;
  buf[0]=0;
  //buf[1]=mode;	//�Ƿ�д�뵽GT9147 FLASH?  ���Ƿ���籣��
  for(i=0;i<(sizeof(GT9147_CFG_TBL)-2);i++)  buf[0]+=GT9147_CFG_TBL[i];//����У���
  buf[0]=(~buf[0])+1;
  printf("checksum:0x%x\r\n",buf[0]);
  GT9147_WR_Reg(GT_CFGS_REG,(uint8_t*)GT9147_CFG_TBL,sizeof(GT9147_CFG_TBL));//���ͼĴ�������
  //GT9147_WR_Reg(GT_CHECK_REG,buf,2);//д��У���,�����ø��±��
  return 0;
} 
#define GT_WriteReg(i2c, reg, val) SCCB_WriteReg(i2c, GT_SCCB_ADDR, kSCCB_RegAddr16Bit, (reg), (val))

#define GT_ReadReg(i2c, reg, val) SCCB_ReadReg(i2c, GT_SCCB_ADDR, kSCCB_RegAddr16Bit, (reg), (val))

//��GT9147д��һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:д���ݳ���
//����ֵ:0,�ɹ�;1,ʧ��.
uint8_t GT9147_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{    
  return  SCCB_WriteMultiRegs(LPI2C1,GT_SCCB_ADDR,kSCCB_RegAddr16Bit,reg,buf,len);
}

//��GT9147����һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:�����ݳ���			  
void GT9147_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{  
  SCCB_ReadMultiRegs(LPI2C1,GT_SCCB_ADDR,kSCCB_RegAddr16Bit,reg,buf,len);  
} 

//��ʼ��GT9147������
//����ֵ:0,��ʼ���ɹ�;1,��ʼ��ʧ�� 
uint8_t GT9147_Init(void)
{
    
    LPI2C1_Init(400000);
  uint8_t temp[5];  
  /*
  PUS ����λ15-14 
  PUS(Pull Up / Down Config. Field)������/�������ã�������Ҫ�������������źŵ�����������ȷ�������źŵĵ�ƽ����ֹ���ţ� 
  ��ѡ��ֵ�� 
  00 PUS_0_100K_Ohm_Pull_Down �� 100K Ohm Pull Down ��100Kŷķ������ 
  01 PUS_1_47K_Ohm_Pull_Up �� 47K Ohm Pull Up ��47Kŷķ������ 
  10 PUS_2_100K_Ohm_Pull_Up �� 100K Ohm Pull Up ��100Kŷķ������ 
  11 PUS_3_22K_Ohm_Pull_Up �� 22K Ohm Pull Up ��22Kŷķ������
  */
  //��λ�ܽų�ʼ��
  CLOCK_EnableClock(kCLOCK_Iomuxc);                 // IO��ʱ��ʹ��
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_02_GPIO1_IO02, 0U);
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_02_GPIO1_IO02, 0x10B0u|IOMUXC_SW_PAD_CTL_PAD_PUS_MASK);  
  GPIO_PinInit(GPIO1, 2, &GPIO_Output_Config);     //M11 RST 
  
  //�жϹܽų�ʼ��
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_11_GPIO1_IO11,0U);//�ܽ�M4  
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_11_GPIO1_IO11, IOMUXC_SW_PAD_CTL_PAD_PUS_MASK);  //��������
  GPIO_PinInit(GPIO1, 11, &GPIO_Input_Config);         //G10 INT    GPIO����ڣ����ж�
  
  //LQ_IIC_GPIO_Init(); 
  
  GPIO_PinWrite(GPIO1,2, 0U);//��λ
  delayms(50);  
  GPIO_PinWrite(GPIO1,2, 1U);//����
  delayms(10); 
  IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_11_GPIO1_IO11,0U);//�ܽ�M4  
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_11_GPIO1_IO11,0);  //ȡ������
  GPIO_PinInit(GPIO1, 11, &GPIO_Input_Config);         //G10 INT    GPIO����ڣ����ж�    
  
  delayms(50);  
  IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_11_GPIO1_IO11, 0);
  GT9147_RD_Reg(GT_PID_REG,temp,4);//��ȡ��ƷID
  temp[4]=0;
  PRINTF("\r\nCTP ID:0x%02X%02X%02X%02X\r\n",temp[0],temp[1],temp[2],temp[3]);	//��ӡID
  //printf("Default Ver:0x%x\r\n",temp[0]);
  //GT9147_Send_Cfg(1);
  
  if(strcmp((char*)temp,"9147")==0)//ID==9147
  {
    temp[0]=0X02;			
    GT9147_WR_Reg(GT_CTRL_REG,temp,1);//��λGT9147
    GT9147_RD_Reg(GT_CFGS_REG,temp,1);//��ȡGT_CFGS_REG�Ĵ���
    //if(temp[0]<0X60)//Ĭ�ϰ汾�Ƚϵ�,��Ҫ����flash����
    //{
    PRINTF("Default Ver:0x%x\r\n",temp[0]);
    //if(lcddev.id==0X5510)GT9147_Send_Cfg(1);//���²���������
    //GT9147_Send_Cfg(1);
    //}
    delayms(10);
    temp[0]=0X00;	 
    GT9147_WR_Reg(GT_CTRL_REG,temp,1);//������λ   
    return 0;
  } 
  return 1;
}

const uint16_t GT9147_TPX_TBL[5]={GT_TP1_REG,GT_TP2_REG,GT_TP3_REG,GT_TP4_REG,GT_TP5_REG};

//ɨ�败����(���ò�ѯ��ʽ)
//mode:0,����ɨ��.
//����ֵ:��ǰ����״̬.
//0,�����޴���;1,�����д���
uint8_t GT9147_Scan(uint8_t mode)
{
  uint8_t buf[4];
  uint8_t i=0;
  uint8_t res=0;
  uint8_t temp;
  uint8_t tempsta;
  static uint8_t t=0;//���Ʋ�ѯ���,�Ӷ�����CPUռ����   
  t++;
  if((t%10)==0||t<10)//����ʱ,ÿ����10��CTP_Scan�����ż��1��,�Ӷ���ʡCPUʹ����
  {
    GT9147_RD_Reg(GT_GSTID_REG,&mode,1);	//��ȡ�������״̬  
    if(mode&0X80&&((mode&0XF)<6))
    {
      temp=0;
      GT9147_WR_Reg(GT_GSTID_REG,&temp,1);//���־ 		
    }		
    if((mode&0XF)&&((mode&0XF)<6))
    {
      res=1;
      temp=0XFF<<(mode&0XF);		//����ĸ���ת��Ϊ1��λ��,ƥ��tp_dev.sta���� 
      tempsta=tp_dev.sta;		//���浱ǰ��tp_dev.staֵ
      tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES; 
      tp_dev.x[4]=tp_dev.x[0];	//���津��0������
      tp_dev.y[4]=tp_dev.y[0];
      for(i=0;i<5;i++)
      {
        if(tp_dev.sta&(1<<i))	//������Ч?
        {
          GT9147_RD_Reg(GT9147_TPX_TBL[i],buf,4);	//��ȡXY����ֵ
          if(tp_dev.touchtype&0X01)//����
          {
            tp_dev.x[i]=(((uint16_t)buf[1]<<8)+buf[0]);
            tp_dev.y[i]=(((uint16_t)buf[3]<<8)+buf[2]);
            
          }
          else
          {
            //tp_dev.y[i]=((uint16_t)buf[1]<<8)+buf[0];
            //tp_dev.x[i]=272-(((uint16_t)buf[3]<<8)+buf[2]);
            tp_dev.x[i]=(((uint16_t)buf[1]<<8)+buf[0]);
            tp_dev.y[i]=(((uint16_t)buf[3]<<8)+buf[2]);
          }

//          PRINTF("x[%d]:%d,y[%d]:%d\r\n",i,tp_dev.x[i],i,tp_dev.y[i]);          
        }			
      }    
//      delayms(50);
      if(tp_dev.x[0]>APP_IMG_WIDTH||tp_dev.y[0]>APP_IMG_HEIGHT)//�Ƿ�����(���곬����)
      { 
        if((mode&0XF)>1)		//��������������,�򸴵ڶ�����������ݵ���һ������.
        {
          tp_dev.x[0]=tp_dev.x[1];
          tp_dev.y[0]=tp_dev.y[1];
          t=0;				//����һ��,��������������10��,�Ӷ����������
        }else					//�Ƿ�����,����Դ˴�����(��ԭԭ����)  
        {
          tp_dev.x[0]=tp_dev.x[4];
          tp_dev.y[0]=tp_dev.y[4];
          mode=0X80;		
          tp_dev.sta=tempsta;	//�ָ�tp_dev.sta
        }
      }else t=0;			//����һ��,��������������10��,�Ӷ����������
    }
  }
  if((mode&0X8F)==0X80)//�޴����㰴��
  { 
    if(tp_dev.sta&TP_PRES_DOWN)	//֮ǰ�Ǳ����µ�
    {
      tp_dev.sta&=~(1<<7);	//��ǰ����ɿ�
    }else						//֮ǰ��û�б�����
    { 
      tp_dev.x[0]=0xffff;
      tp_dev.y[0]=0xffff;
      tp_dev.sta&=0XE0;	//�������Ч���	
    }	 
  } 	
  if(t>240)t=10;//���´�10��ʼ����
  return res;
}

void TP_Init(void)
{	  
  //ɨ�躯��ָ������ɨ��
  GT9147_Init();	
  tp_dev.scan=GT9147_Scan;  
}




