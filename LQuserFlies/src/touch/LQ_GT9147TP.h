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

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef _LQ_GT9147TP_H_
#define _LQ_GT9147TP_H_

#include "include.h"  


#define TP_PRES_DOWN    0x80            //����������	  
#define TP_CATH_PRES    0x40            //�а��������� 
#define CT_MAX_TOUCH    5               //������֧�ֵĵ���,�̶�Ϊ5��
//I2C��д����	
#define GT_SCCB_ADDR	0X14            //0X14����0X5D��
#define GT_CMD_WR	0X28     	//0X28    0XBAд���� 
#define GT_CMD_RD	0X29		//0X29    0XBB������

//GT9147 ���ּĴ������� 
#define GT_CTRL_REG 	0X8040   	//GT9147���ƼĴ���
#define GT_CFGS_REG 	0X8047   	//GT9147������ʼ��ַ�Ĵ���
#define GT_CHECK_REG 	0X80FF   	//GT9147У��ͼĴ���
#define GT_PID_REG	0X8140   	//GT9147��ƷID�Ĵ���

#define GT_GSTID_REG 	0X814E   	//GT9147��ǰ��⵽�Ĵ������
#define GT_TP1_REG	0X8150  	//��һ�����������ݵ�ַ
#define GT_TP2_REG	0X8158		//�ڶ������������ݵ�ַ
#define GT_TP3_REG	0X8160		//���������������ݵ�ַ
#define GT_TP4_REG	0X8168		//���ĸ����������ݵ�ַ
#define GT_TP5_REG	0X8170		//��������������ݵ�ַ  

//������������
typedef struct
{  
  void   (*init)(void);		//��ʼ��������������
  uint8_t (*scan)(uint8_t);		//ɨ�败����.0,��Ļɨ��;1,��������;
  uint16_t x[CT_MAX_TOUCH]; 		//��ǰ����
  uint16_t y[CT_MAX_TOUCH];		//�����������5������,����������x[0],y[0]����:�˴�ɨ��ʱ,����������,��  
  uint8_t  sta;				//�ʵ�״̬ 
  //b7:����1/�ɿ�0; 
  //b6:0,û�а�������;1,�а�������. 
  //b5:����
  //b4~b0:���ݴ��������µĵ���(0,��ʾδ����,1��ʾ����)
  /////////////////////������У׼����(����������ҪУ׼)//////////////////////								
  float xfac;					
  float yfac;
  short xoff;
  short yoff;	   
  //�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
  //b0:0,����(�ʺ�����ΪX����,����ΪY�����TP)
  //   1,����(�ʺ�����ΪY����,����ΪX�����TP) 
  //b1~6:����.
  //b7:0,������
  //   1,������ 
  uint8_t touchtype;
}_LQ_TP_DEV;

extern _LQ_TP_DEV tp_dev;	 	//������������touch.c���涨��

uint8_t GT9147_Send_Cfg(uint8_t mode);
uint8_t GT9147_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
void   GT9147_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len); 
uint8_t GT9147_Init(void);
uint8_t GT9147_Scan(uint8_t mode); 
//������/������ ���ú���
uint8_t TP_Scan(uint8_t tp);  //ɨ��						
void   TP_Init(void);//��ʼ��
#endif
