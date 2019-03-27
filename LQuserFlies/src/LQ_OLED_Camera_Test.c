/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1052���İ�-���ܳ���
����    д��Z
��E-mail  ��chiusir@163.com
������汾��V1.0������Դ���룬�����ο�������Ը�
�������¡�2018��11��7��
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


/*************************************************************** 
* 
* �������ƣ�uint8_t GetOSTU(uint8_t tmImage[IMAGEH][IMAGEW]) 
* ����˵��������ֵ��С 
* ����˵���� 
* �������أ���ֵ��С 
* �޸�ʱ�䣺2018��3��27�� 
* �� ע�� 
�ο���https://blog.csdn.net/zyzhangyue/article/details/45841255
      https://www.cnblogs.com/moon1992/p/5092726.html
      https://www.cnblogs.com/zhonghuasong/p/7250540.html     
Ostu������������������ͨ��ͳ������ͼ���ֱ��ͼ������ʵ��ȫ����ֵT���Զ�ѡȡ�����㷨����Ϊ��
1) �ȼ���ͼ���ֱ��ͼ������ͼ�����е����ص㰴��0~255��256��bin��ͳ������ÿ��bin�����ص�����
2) ��һ��ֱ��ͼ��Ҳ����ÿ��bin�����ص����������ܵ����ص�
3) i��ʾ�������ֵ��Ҳ��һ���Ҷȼ�����0��ʼ����
4) ͨ����һ����ֱ��ͼ��ͳ��0~i �Ҷȼ�������(��������ֵ�ڴ˷�Χ�����ؽ���ǰ������) ��ռ����ͼ��ı���w0����ͳ��ǰ�����ص�ƽ���Ҷ�u0��ͳ��i~255�Ҷȼ�������(��������ֵ�ڴ˷�Χ�����ؽ�����������) ��ռ����ͼ��ı���w1����ͳ�Ʊ������ص�ƽ���Ҷ�u1��
5) ����ǰ�����غͱ������صķ��� g = w0*w1*(u0-u1) (u0-u1)
6) i++��ת��4)��ֱ��iΪ256ʱ��������
7�������g��Ӧ��iֵ��Ϊͼ���ȫ����ֵ
ȱ��:OSTU�㷨�ڴ�����ղ����ȵ�ͼ���ʱ��Ч�������Բ��ã���Ϊ���õ���ȫ��������Ϣ��
***************************************************************/ 
uint32_t GetOSTU(void) 
{ 
  int16_t i,j; 
  uint32_t Amount = 0; 
  uint32_t PixelBack = 0; 
  uint32_t PixelIntegralBack = 0; 
  uint32_t PixelIntegral = 0; 
  int32_t PixelIntegralFore = 0; 
  int32_t PixelFore = 0; 
  double OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // ��䷽��; 
  int16_t MinValue, MaxValue; 
  uint32_t Threshold = 0;
  uint8_t HistoGram[256];              //  

  for (j = 0; j < 256; j++)  HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ 
  
  if(counter % 2)
  {
      for (j = 0; j < Use_ROWS; j++) 
      { 
        for (i = 0; i < Use_Line; i++) 
        { 
          HistoGram[(uint8_t)lcdFrameBuf[1][j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
        } 
      }
  }
  else
  {
      for (j = 0; j < Use_ROWS; j++) 
      { 
        for (i = 0; i < Use_Line; i++) 
        { 
          HistoGram[(uint8_t)lcdFrameBuf[0][j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
        } 
      } 
  }

  for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++) ;        //��ȡ��С�Ҷȵ�ֵ
  for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--) ; //��ȡ���Ҷȵ�ֵ
      
  if (MaxValue == MinValue)     return MaxValue;         // ͼ����ֻ��һ����ɫ    
  if (MinValue + 1 == MaxValue)  return MinValue;        // ͼ����ֻ�ж�����ɫ
    
  for (j = MinValue; j <= MaxValue; j++)    Amount += HistoGram[j];        //  ��������
    
  PixelIntegral = 0;
  for (j = MinValue; j <= MaxValue; j++)
  {
    PixelIntegral += HistoGram[j] * j;//�Ҷ�ֵ����
  }
  SigmaB = -1;
  for (j = MinValue; j < MaxValue; j++)
  {
    PixelBack = PixelBack + HistoGram[j];    //ǰ�����ص���
    PixelFore = Amount - PixelBack;         //�������ص���
    OmegaBack = (double)PixelBack / Amount;//ǰ�����ذٷֱ�
    OmegaFore = (double)PixelFore / Amount;//�������ذٷֱ�
    PixelIntegralBack += HistoGram[j] * j;  //ǰ���Ҷ�ֵ
    PixelIntegralFore = PixelIntegral - PixelIntegralBack;//�����Ҷ�ֵ
    MicroBack = (double)PixelIntegralBack / PixelBack;   //ǰ���ҶȰٷֱ�
    MicroFore = (double)PixelIntegralFore / PixelFore;   //�����ҶȰٷֱ�
    Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//������䷽��
    if (Sigma > SigmaB)                    //����������䷽��g //�ҳ������䷽���Լ���Ӧ����ֵ
    {
      SigmaB = Sigma;
      Threshold = j;
    }
  }
  return Threshold;                        //���������ֵ;
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
uint8_t Pixle [Use_ROWS][Use_Line];
void Camera_0_1_Handle(void)
{
    int i = 0;
    int j = 0;
//    uint32_t threshold = 0x60;  //ʹ�ù̶���ֵ
    uint32_t threshold = GetOSTU();//ʹ�ô��
    
    char txt[8];
    sprintf(txt,"%03d",threshold);//ǰ��Ϊ�����õ���ֵ������Ϊƽ��ֵ  
    LCD_P6x8Str(85,1,(uint8_t*)txt);
    
    if(counter % 2)
    {
        for(i = 0; i < 64; i++)
        {           
            for(j = 0; j < 128; j++)
            {
                
                if((lcdFrameBuf[1][i][j] & 0x000000ff) > threshold)   //�˴���ֵ���ã����ݻ����Ĺ������趨    
                    Pixle[Use_ROWS - 1 - i][Use_Line - 1 - j] = 1;                       //ͼ�񷴵ģ�������
                else                                        
                    Pixle[Use_ROWS - 1 - i][Use_Line - 1 - j] = 0;
            }    
        }   
    }
    else
    {
        for(i = 0; i < 64; i++)
        {           
            for(j = 0; j < 128; j++)
            {
                
                if((lcdFrameBuf[0][i][j] & 0x000000ff) > threshold)   //�˴���ֵ���ã����ݻ����Ĺ������趨    
                    Pixle[Use_ROWS - 1 - i][Use_Line - 1 - j] = 1;                       //ͼ�񷴵ģ�������
                else                                        
                    Pixle[Use_ROWS - 1 - i][Use_Line - 1 - j] = 0;
            }    
        }   
    }
    
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����oled����ʾ
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Draw_Road(void)
{ 	 
  uint8_t i = 0, j = 0,temp=0;
  for(i=0;i<56;i+=8)//6*8=48�� 
  {
    LCD_Set_Pos(0,i/8+1);
    for(j=0;j<128;j++) 
    { 
      temp=0;
      if(Pixle[0+i][j]) temp|=1;
      if(Pixle[1+i][j]) temp|=2;
      if(Pixle[2+i][j]) temp|=4;
      if(Pixle[3+i][j]) temp|=8;
      if(Pixle[4+i][j]) temp|=0x10;
      if(Pixle[5+i][j]) temp|=0x20;
      if(Pixle[6+i][j]) temp|=0x40;
      if(Pixle[7+i][j]) temp|=0x80;
      LCD_WrDat(temp); 	  	  	  	  
    }
  }  
}

//�������Ϸ���Χ��������
void Pixle_Filter(void)
{  
  int nr; //��
  int nc; //��
  
  for(nr=1; nr<60-1; nr++)
  {  	    
    for(nc=1; nc<100-1; nc=nc+1)
    {
      if((Pixle[nr][nc]==0)&&(Pixle[nr-1][nc]+Pixle[nr+1][nc]+Pixle[nr][nc+1]+Pixle[nr][nc-1]>2))         
      {
        Pixle[nr][nc]=1;
      }	
      else if((Pixle[nr][nc]==1)&&(Pixle[nr-1][nc]+Pixle[nr+1][nc]+Pixle[nr][nc+1]+Pixle[nr][nc-1]<2))         
      {
        Pixle[nr][nc]=0;
      }	
    }	  
  }  
}





/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����oled + camera test
������汾��V1.0
�������¡�2018��11��7�� 
����������
������ֵ����
������ֵ����
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

void Test_OLED_Camera(void)
{
    LCD_Init();               //OLED��ʼ�� 
    
    LQ_Camera_Init();         //����ͷ��ʼ��
    uint32_t fullCameraBufferAddr; //���CSI����������ַ
    

       //Configure the PXP for color space conversion.
    PXP_Init(PXP);    //��ʱ��
    /* Disable AS. */
    PXP_SetAlphaSurfacePosition(PXP, 0xFFFFU, 0xFFFFU, 0U, 0U);
    
    
#ifdef LQMT9V034 //LQMT9V034ģ��
    PXP_EnableCsc1(PXP, false);              //��ʹ��  LQMT9V034ģ��Ϊ��ɫ��ʽ

    PXP_SetProcessSurfaceScaler(PXP,IMAGEW/4, IMAGEH, Use_Line, Use_ROWS);//����ͼ��, ��������ͷ752 * 480�ֱ��ʣ����������ʽΪ ��λ��ɫ�ʣ�Ҳ����һ���ֽھ���һ�����ص㣬���ǵ�Ƭ����csi�ӿ�����Ϊrgb888��ʽ����������ͷ����һ���ֽڱ�ʾһ�����ص㣬������ĸ��ֽڱ�ʾһ�����ص㣩��֡���
    PXP_SetProcessSurfacePosition(PXP, 0u, 0u, Use_Line - 1U, Use_ROWS - 1U);                //������ʾλ��
#else  //LQOV7725ģ��
    PXP_SetCsc1Mode(PXP, kPXP_Csc1YCbCr2RGB);//���� csc1  kPXP_Csc1YCbCrת��Ϊrgb888
    PXP_EnableCsc1(PXP, false);               //ʹ��csc1
    
    PXP_SetProcessSurfaceScaler(PXP,APP_CAMERA_WIDTH, APP_CAMERA_HEIGHT, Use_Line, Use_ROWS);//����
    PXP_SetProcessSurfacePosition(PXP, 0u, 0u, Use_Line - 1U, Use_ROWS - 1U);                //������ʾλ��
#endif
   
    PXP_SetProcessSurfaceBackGroundColor(PXP, 0u);  //���ñ�����ɫ

    PXP_SetRotateConfig(PXP, kPXP_RotateOutputBuffer, kPXP_Rotate0, kPXP_FlipDisable);//ͼ����ת���ٶȣ���ת���
    
    
    /* Input config. */
#ifdef LQMT9V034 //LQMT9V034ģ��
        psBufferConfig.pixelFormat =  kPXP_PsPixelFormatRGB888;//kPXP_PsPixelFormatRGB565,//kPXP_PsPixelFormatUYVY1P422,
#else                  //LQOV7725ģ��
        psBufferConfig.pixelFormat =  kPXP_PsPixelFormatRGB565;//kPXP_PsPixelFormatRGB565,//kPXP_PsPixelFormatUYVY1P422,
#endif
        psBufferConfig.swapByte = false;                 //��8λ��ǰ���ǵ�8λ��ǰ
        psBufferConfig.bufferAddrU = 0U;
        psBufferConfig.bufferAddrV = 0U;
        psBufferConfig.pitchBytes = APP_CAMERA_WIDTH * APP_BPP;    //һ�ж��ٸ��ֽ� 
        
    /* Output config. */  
        outputBufferConfig.pixelFormat = kPXP_OutputPixelFormatARGB8888;//kPXP_OutputPixelFormatY8,
        outputBufferConfig.interlacedMode = kPXP_OutputProgressive;
        outputBufferConfig.buffer1Addr = 0U;
        outputBufferConfig.pitchBytes = APP_LCD_WIDTH * 4;
        outputBufferConfig.width = APP_LCD_WIDTH;
        outputBufferConfig.height = APP_LCD_HEIGHT;
        

        uint64_t now, time;
        while(1)
        {
            now = _systime.get_time_us();
            /* cpu������������� */
            /*����ͷΪ60֡��  ��֡���15ms  �����������û�����  ִ������ٵȴ�csi��*/
            while (kStatus_Success != CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &fullCameraBufferAddr))  //�ȴ�����ͷCSI��������
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
            CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, fullCameraBufferAddr);//��������������ύ���������
            time = _systime.get_time_us() - now;
            printf("�ɼ�����ʱ�� %lld \n", time);
            now = _systime.get_time_us();
            /* cpu������������� */
            /*PXPͼ����   ���3ms  �����������û�����  ִ������ټ��PXPת�����*/
            while (!(kPXP_CompleteFlag & PXP_GetStatusFlags(PXP)))  //�ȴ�pXPת�����
            {
            }
            PXP_ClearStatusFlags(PXP, kPXP_CompleteFlag);   //�����־λ  
            
            
            time = _systime.get_time_us() - now;
            printf("PXPʱ�� %lld \n", time);
            now = _systime.get_time_us();
            
            Camera_0_1_Handle();   //��ֵ��
            
            time = _systime.get_time_us() - now;
            printf("��ֵ��ʱ�� %lld \n", time);
            now = _systime.get_time_us();
            
            Pixle_Filter();        //�˲������
            
            time = _systime.get_time_us() - now;
            printf("�˲�ʱ�� %lld \n", time);
            now = _systime.get_time_us();
            Draw_Road(); 

            time = _systime.get_time_us() - now;
            printf("��ʾ %lld \n", time);
            counter ++;
            
        }
       
    

}
