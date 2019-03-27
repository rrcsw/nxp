/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1052���İ�-���ܳ���
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0������Դ���룬�����ο�������Ը�
�������¡�2018��6��22��
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
#include "include.h"

volatile uint8_t LQ_LCD = 0;       //ֱ����ʾ��LCD�ϻ��߶�ֵ������ʾ��LCD��  480*272��LCD
int OFFSET0=0;      //��Զ������������ֵ�ۺ�ƫ����
int OFFSET1=0;      //�ڶ���
int OFFSET2=0;      //�����������


#define MAX_ROW   60       
#define MAX_COL   480 

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����������������
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_Touch_Handle(void)
{
    /*        ������         */
    TFT_P8X16Str(315,210,"Start",BLUE,RED,0); //�ַ�����ʾ
    TFT_P8X16Str(395,210,"Stop",BLUE,RED,0); //�ַ�����ʾ
    TFT_P8X16Str(395,170,"ON",BLUE,RED,0); //�ַ�����ʾ
    
    TFT_P8X16Str(315,130,"LED1",BLUE,RED,0); //�ַ�����ʾ
    TFT_P8X16Str(395,130,"LED2",BLUE,RED,0); //�ַ�����ʾ
    TFT_Draw_Rectangle(380,200,460,240,GREEN,1);            //�����α߿�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
    TFT_Draw_Rectangle(300,200,379,240,RED,1);            //�����α߿�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
    TFT_Draw_Rectangle(380,160,460,199,RED,1);            //�����α߿�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
    
    TFT_Draw_Rectangle(380,120,460,160,GREEN,1);            //�����α߿�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
    TFT_Draw_Rectangle(300,120,379,160,RED,1);            //�����α߿�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
    
    if(GT9147_Scan(0))   //����������
    {
        uint8_t i; 
        for(i=0;i<5;i++)
        {
            if(tp_dev.x[i] < 460 && tp_dev.x[i] > 380 && tp_dev.y[i] < 240 && tp_dev.y[i] > 200) //stop����
            { 
                LED_Ctrl(LED_R, RVS);
                LQ_PWMA_B_SetDuty(PWM1, kPWM_Module_3, 0, 0);  //���pwm
            }
            if(tp_dev.x[i] < 379 && tp_dev.x[i] > 300 && tp_dev.y[i] < 240 && tp_dev.y[i] > 200) //start����
            {
                LED_Ctrl(LED_R, RVS);
                LQ_PWMA_B_SetDuty(PWM1, kPWM_Module_3, 1000, 1000);       //���pwm
            }
            
            if(tp_dev.x[i] < 460 && tp_dev.x[i] > 380 && tp_dev.y[i] < 199 && tp_dev.y[i] > 160) //ON����
            {
                LED_Ctrl(LED_R, RVS);
                
                if(LQ_LCD)LQ_LCD = 0;                             
                else LQ_LCD = 1;
            }
            if(tp_dev.x[i] < 379 && tp_dev.x[i] > 300 && tp_dev.y[i] < 160 && tp_dev.y[i] > 120) //LED1����
            {
                LED_Ctrl(LED_R, RVS);
                
                GPIO_PinReverse (GPIO2, 22);
                
            }
            if(tp_dev.x[i] < 460 && tp_dev.x[i] > 380 && tp_dev.y[i] < 160 && tp_dev.y[i] > 120) //LED2����
            {
                LED_Ctrl(LED_R, RVS);
                GPIO_PinReverse (GPIO2, 25);
                
            }
            TFT_Draw_CircleCake(tp_dev.x[i],tp_dev.y[i],40,RED,1);   //�����ĵط���Բ
            TFT_Draw_CircleCake(tp_dev.x[i],tp_dev.y[i],20,BLUE,1);
            TFT_Draw_CircleCake(tp_dev.x[i],tp_dev.y[i], 8,BLACK,1);
            tp_dev.x[i] = 0;
            tp_dev.y[i] = 0;
        }
    }      
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵��������ͷ+TFT480*752��������
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

void Test_TFT_Camera(void)
{      

    uint32_t fullCameraBufferAddr;     
    LQ_Camera_Init();
    LQ_PXP_Init();
    LQ_TFT480_272_Init();
 
    GT9147_Init();//��ʼ��������
    delayms(200);        //��ʱ200���� 
//    PRINTF("Camera demo starting...\r\n");    
    while (1)
    {     
        // Wait to get the full frame buffer to show. 
        while (kStatus_Success != CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &fullCameraBufferAddr))  //����ͷCSI����������
        {
        }
        // Convert the camera input picture to RGB format. 
        psBufferConfig.bufferAddr = fullCameraBufferAddr;    //����PXPת��Դ��ַ
        PXP_SetProcessSurfaceBufferConfig(PXP, &psBufferConfig); // ��PXP�����������
        
        if(counter % 2)
        {
            outputBufferConfig.buffer0Addr = (uint32_t)lcdFrameBuf[1]; //����PXPת����Ŀ�ĵ�ַ
        }
        else
        {
            outputBufferConfig.buffer0Addr = (uint32_t)lcdFrameBuf[0]; //����PXPת����Ŀ�ĵ�ַ
        }
        PXP_SetOutputBufferConfig(PXP, &outputBufferConfig);   // ��PXP�����������
        
        PXP_Start(PXP);    //����PXPת��
         
        // Wait for PXP process complete.
        while (!(kPXP_CompleteFlag & PXP_GetStatusFlags(PXP)))  //�ȴ�pXPת�����
        {
        }
        PXP_ClearStatusFlags(PXP, kPXP_CompleteFlag);   //�����־λ
        
        ELCDIF_ClearInterruptStatus(LCDIF, kELCDIF_CurFrameDone);  //���LCD�жϱ�־λ
        
         // Return the camera buffer to camera queue. 
        CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, fullCameraBufferAddr);//��������������ύ���������

        
        // Wait for the new set LCD frame buffer active.
        while (!(kELCDIF_CurFrameDone & ELCDIF_GetInterruptStatus(LCDIF))) 
        {
        }    
       
        TFT_P16x16Str(184,5,"�����������ܿƼ�",BLUE,RED,0); //�ַ�����ʾ

        LQ_Touch_Handle();                                  //������������
        
        if(counter % 2)
        {
            ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)lcdFrameBuf[1]);  //��LCD������lcdFrameBuf ��ʾ��TFT����
        }
        else
        {
            ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)lcdFrameBuf[0]);  //��LCD������lcdFrameBuf ��ʾ��TFT����
        }
        delayms(15);        //��ʱ15���룬������
       
        counter ++;
        
        LED_Ctrl(LED_R, RVS); //EVK LED��˸  
    }
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵�����õ�ÿ����ֵ
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
//static uint8_t counter = 0;
uint32_t LQ_Get_Threshold(void)
{
    
    uint64_t value = 0;
    int nr; //��
    int nc; //��
    if(counter % 2)
    {
        for(nr=0;nr<272;nr++)
        {  
            for(nc=0;nc<480;nc++)
            {
                value += (lcdFrameBuf[1][nr][nc] & 0x00ffffff);
                
            }
        }
    }
    else
    {
        for(nr=0;nr<272;nr++)
        {  
            for(nc=0;nc<480;nc++)
            {
                value += (lcdFrameBuf[0][nr][nc] & 0x00ffffff);
                
            } 
        }   
    }
  return  value / 480 / 272;
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵������ֵ������
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

//uint32_t threshold = 0x606060;   //��ֵ
void LQ_Camera_0_1_Handle(void)
{
    int i = 0;
    int j = 0;
    uint32_t threshold = 0x606060;
//    threshold = LQ_Get_Threshold();   //ʹ��ƽ��ֵ
    for(i = 0; i < 272; i++)
    {
        if(counter % 2)
        {
            
            for(j = 0; j < 480; j++)
            {
                
                if((lcdFrameBuf[1][i][j] & 0x00ffffff) > threshold)   //�˴���ֵ���ã����ݻ����Ĺ������趨    
                    lcdFrameBuf[2][i][j] = 0xffffff;
                else                                        
                    lcdFrameBuf[2][i][j] = 0x00;
            } 
        }
        else
        {
            
            for(j = 0; j < 480; j++)
            {
                if((lcdFrameBuf[0][i][j] & 0x00ffffff) > threshold)   //�˴���ֵ���ã����ݻ����Ĺ������趨    
                    lcdFrameBuf[3][i][j] = 0xffffff;
                else                                        
                    lcdFrameBuf[3][i][j] = 0x00;    
            }          
        }    
    }
    
    
}

/***************************************************************************
*                                                                          *
*  �������ƣ�int Seek_Road(void)                                           *
*  ����˵����Ѱ�Ұ�ɫ����ƫ��ֵ                                            *
*  ����˵������                                                            *
*  �������أ�ֵ�Ĵ�С                                                      *
*  �޸�ʱ�䣺2017-07-16                                                    *
*  ��    ע�����м�Ϊ0������һ���Ҳ��һ����ֵ����1�����                *
*            ��������ӵ�һ�п�ʼ�������ڶ��н�����                        *
*            ������Ϊ��������ֵԽ��˵��Խƫ��ߣ�                        *
*            ������Ϊ��������ֵԽ��˵��Խƫ�ұߡ�                        *
***************************************************************************/ 
void Seek_Road(void)
{  
  int nr; //��
  int nc; //��
  int temp=0;//��ʱ��ֵ
  //for(nr=1; nr<MAX_ROW-1; nr++)
  temp=0;
  if(counter % 2)
  {
  for(nr=20; nr<100; nr++)
  {  	    
    for(nc=MAX_COL/2;nc<MAX_COL;nc=nc+1)//240to480
    {
      if(lcdFrameBuf[2][nr][nc])
      {
        ++temp;
      }			   
    }
    for(nc=0; nc<MAX_COL/2; nc=nc+1)
    {
      if(lcdFrameBuf[2][nr][nc])
      {
        --temp;
      }			   
    }		  
  }
  OFFSET0=temp;
  temp=0;
  for(nr=100; nr<180; nr++)
  {  	    
    for(nc=MAX_COL/2;nc<MAX_COL;nc=nc+1)
    {
      if(lcdFrameBuf[2][nr][nc])
      {
        ++temp;
      }			   
    }
    for(nc=0; nc<MAX_COL/2; nc=nc+1)
    {
      if(lcdFrameBuf[2][nr][nc])
      {
        --temp;
      }			   
    }		  
  }
  OFFSET1=temp;    	
  temp=0;
  for(nr=180; nr<260; nr++)
  {  	    
    for(nc=MAX_COL/2;nc<MAX_COL;nc=nc+1)
    {
      if(lcdFrameBuf[2][nr][nc])
      {
        ++temp;
      }			   
    }
    for(nc=0; nc<MAX_COL/2; nc=nc+1)
    {
      if(lcdFrameBuf[2][nr][nc])
      {
        --temp;
      }			   
    }		  
  }
  OFFSET2=temp;   	
  
  }
  else
  {
  for(nr=20; nr<100; nr++)
  {  	    
    for(nc=MAX_COL/2;nc<MAX_COL;nc=nc+1)//240to480
    {
      if(lcdFrameBuf[3][nr][nc])
      {
        ++temp;
      }			   
    }
    for(nc=0; nc<MAX_COL/2; nc=nc+1)
    {
      if(lcdFrameBuf[3][nr][nc])
      {
        --temp;
      }			   
    }		  
  }
  OFFSET0=temp;
  temp=0;
  for(nr=100; nr<180; nr++)
  {  	    
    for(nc=MAX_COL/2;nc<MAX_COL;nc=nc+1)
    {
      if(lcdFrameBuf[3][nr][nc])
      {
        ++temp;
      }			   
    }
    for(nc=0; nc<MAX_COL/2; nc=nc+1)
    {
      if(lcdFrameBuf[3][nr][nc])
      {
        --temp;
      }			   
    }		  
  }
  OFFSET1=temp;    	
  temp=0;
  for(nr=180; nr<260; nr++)
  {  	    
    for(nc=MAX_COL/2;nc<MAX_COL;nc=nc+1)
    {
      if(lcdFrameBuf[3][nr][nc])
      {
        ++temp;
      }			   
    }
    for(nc=0; nc<MAX_COL/2; nc=nc+1)
    {
      if(lcdFrameBuf[3][nr][nc])
      {
        --temp;
      }			   
    }		  
  }
  OFFSET2=temp; 
  
  }
    
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵��������ͷ+TFT480*752��������
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void  LQ_Get_CameraBuff(void)
{      
    
    uint32_t fullCameraBufferAddr;  
    
    // Wait to get the full frame buffer to show. 
    while (kStatus_Success != CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &fullCameraBufferAddr))  //����ͷCSI����������
    {
    }
    
    
    
    // Convert the camera input picture to RGB format. 
    psBufferConfig.bufferAddr = fullCameraBufferAddr;    //����PXPת��Դ��ַ
    PXP_SetProcessSurfaceBufferConfig(PXP, &psBufferConfig); // ��PXP�����������
    if(counter % 2)
    {
        outputBufferConfig.buffer0Addr = (uint32_t)lcdFrameBuf[1]; //����PXPת����Ŀ�ĵ�ַ
    }
    else
    {
        outputBufferConfig.buffer0Addr = (uint32_t)lcdFrameBuf[0]; //����PXPת����Ŀ�ĵ�ַ
    }
    
    PXP_SetOutputBufferConfig(PXP, &outputBufferConfig);   // ��PXP�����������
    
    PXP_Start(PXP);    //����PXPת��
    
    
    /*cpu���Դ���������*/
    // Wait for PXP process complete.
    while (!(kPXP_CompleteFlag & PXP_GetStatusFlags(PXP)))  //�ȴ�pXPת�����
    {
    }
    PXP_ClearStatusFlags(PXP, kPXP_CompleteFlag);   //�����־λ
    
    ELCDIF_ClearInterruptStatus(LCDIF, kELCDIF_CurFrameDone);  //���LCD�жϱ�־λ
    // Set the new frame to LCD. 
    
    
    // Return the camera buffer to camera queue. 
    CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, fullCameraBufferAddr);//��������������ύ���������
    
    // Wait for the new set LCD frame buffer active.
    while (!(kELCDIF_CurFrameDone & ELCDIF_GetInterruptStatus(LCDIF)))  //�ȴ������õ�LCD֡����������    
    {
    }    
    
    TFT_P16x16Str(184,5,"�����������ܿƼ�",BLUE,RED,0); //�ַ�����ʾ
    TFT_P8X16Str(315,210,"Start",BLUE,RED,0); //�ַ�����ʾ
    TFT_P8X16Str(395,210,"Stop",BLUE,RED,0); //�ַ�����ʾ
    TFT_P8X16Str(395,170,"ON",BLUE,RED,0); //�ַ�����ʾ
    
    TFT_P8X16Str(315,130,"LED1",BLUE,RED,0); //�ַ�����ʾ
    TFT_P8X16Str(395,130,"LED2",BLUE,RED,0); //�ַ�����ʾ
    TFT_Draw_Rectangle(380,200,460,240,GREEN,1);            //�����α߿�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
    TFT_Draw_Rectangle(300,200,379,240,RED,1);            //�����α߿�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
    TFT_Draw_Rectangle(380,160,460,199,RED,1);            //�����α߿�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
    
    TFT_Draw_Rectangle(380,120,460,160,GREEN,1);            //�����α߿�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
    TFT_Draw_Rectangle(300,120,379,160,RED,1);            //�����α߿�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
    
    if (LQ_LCD)
    {
//        LQ_Touch_Handle();                                  //������������ 
        if(counter % 2)
        {
            ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)lcdFrameBuf[3]);  //��LCD������lcdFrameBuf ��ʾ��TFT����
        }
        else
        {
            ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)lcdFrameBuf[2]);  //��LCD������lcdFrameBuf ��ʾ��TFT����
        }
        
    }
    if (LQ_LCD == 0)
    {
        
        LQ_Touch_Handle();                                  //������������ 
        if(counter % 2)
        {
            ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)lcdFrameBuf[1]);  //��LCD������lcdFrameBuf ��ʾ��TFT����
        }
        else
        {
            ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)lcdFrameBuf[0]);  //��LCD������lcdFrameBuf ��ʾ��TFT����
        }
        
    }  
    counter ++;   
}


