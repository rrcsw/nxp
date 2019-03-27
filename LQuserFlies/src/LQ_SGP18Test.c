
#include "include.h"
/*******************************************************************************
*  SDK�ṩ��������Noncacheable�����建�����ͱ����ķ�����
*  AT_NONCACHEABLE_SECTION_ALIGN(var, alignbytes)
*  AT_NONCACHEABLE_SECTION(var)
******************************************************************************/
AT_NONCACHEABLE_SECTION_ALIGN(uint16_t lcdFrameBuf[2][LCD_HEIGHT][LCD_WIDTH], FRAME_BUFFER_ALIGN);               //LCD���ݻ�����

uint8_t counter;       //LCD��������������һ����ǰ��ʾ�ã�һ��������

int OFFSET0=0;      //��Զ������������ֵ�ۺ�ƫ����
int OFFSET1=0;      //�ڶ���
int OFFSET2=0;      //�����������


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����oled + camera test
������汾��V1.0
�������¡�2018��11��7�� 
����������
������ֵ����
������ֵ����
��ʵ���� TFT1.8��ʾOV7725 RGBͼ�����  7725�ֱ�������Ϊ320*240
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_SGP18_OV7725(void)
{
    TFTSPI_Init();               //TFT1.8��ʼ��     
    uint32_t fullCameraBufferAddr;     
    LQ_Camera_Init();
//    if (SCB_CCR_IC_Msk == (SCB_CCR_IC_Msk & SCB->CCR)) {   
//        SCB_DisableICache();
//    }
    if (SCB_CCR_DC_Msk == (SCB_CCR_DC_Msk & SCB->CCR)) {//ע�⣬ʹ��csiFrameBuf����ʱ����ùر�Cache ��Ȼ�ϴ����ݿ��ܻ�����cache���棬������ݴ���
        SCB_DisableDCache();
    }
    delayms(200);        //��ʱ200����     
    while (1)
    {     
        // Wait to get the full frame buffer to show. 
        while (kStatus_Success != CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &fullCameraBufferAddr))  //����ͷCSI����������
        {
        }   
        CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, fullCameraBufferAddr);//��������������ύ���������        
        TFTSPI_Set_Pos(20,0,(APP_CAMERA_WIDTH/4-1) + 20,APP_CAMERA_HEIGHT/4);
        for(int i = 0; i < APP_CAMERA_HEIGHT; i+=4)  //��һ��ȡһ��
        {
            for(int j = 0; j < APP_CAMERA_WIDTH ; j+=4)//��һ��ȡһ��
            {
                TFTSPI_Write_Word (*((uint16_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH + j)); //��ʾ����
            }
        }
        
        LED_Color_Reverse(red); //EVK LED��˸    
    }
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����TFT1.8 + camera test
������汾��V1.0
�������¡�2018��11��7�� 
����������
������ֵ����
������ֵ����
��ʵ���� TFT1.8��ʾ���۶�ֵ�� ͼ�����  ���۷ֱ�������Ϊ752*480
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_SGP18_Camera(void)
{
    TFTSPI_Init();               //TFT1.8��ʼ��  
    TFTSPI_CLS(u16BLUE);           //����
    uint32_t fullCameraBufferAddr;   
#ifdef LQOV7725
    cameraConfig.pixelFormat = kVIDEO_PixelFormatYUYV;
#endif
    LQ_Camera_Init();
    delayms(200);        //��ʱ200����  
    uint16_t color = 0;
//    if (SCB_CCR_IC_Msk == (SCB_CCR_IC_Msk & SCB->CCR)) {   
//        SCB_DisableICache();
//    }
    if (SCB_CCR_DC_Msk == (SCB_CCR_DC_Msk & SCB->CCR)) {//ע�⣬ʹ��csiFrameBuf����ʱ����ùر�D-Cache ��Ȼ�ϴ����ݿ��ܻ�����cache���棬������ݴ���
        SCB_DisableDCache();
    }
    while (1)
    {     
        // Wait to get the full frame buffer to show. 
        while (kStatus_Success != CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &fullCameraBufferAddr))  //����ͷCSI����������
        {
        }   
        
#ifdef LQMT9V034  
#if (IMAGEH == 480/4  && IMAGEW == 752/4)
        TFTSPI_Set_Pos(15,0,(uint8_t)(APP_CAMERA_WIDTH/2-1)+15 ,APP_CAMERA_HEIGHT);//ע�� ������ʾ��СҪ�������ʵ����ʾ��С��ȣ���Ȼ����ʾ���������߻���
        for(int i = 0; i < APP_CAMERA_HEIGHT; i+=2)  //  480/4/2/2 = 30
        {
            for(int j = 0; j < APP_CAMERA_WIDTH*2; j+=2)//��2��ȡһ��  752*2/4/2 = 188   //�������� һ��94����  ʵ����ʾ�ֱ���  94*60
            {
                //�Ҷ���ʾ
                color = 0;
                color=(((*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j))>>3))<<11;
                color=color|((((*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j))>>2))<<5);
                color=color|(((*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j))>>3));
                TFTSPI_Write_Word(color);
                //��ֵ����ʾ
//                if(*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j) > 0x60)  //��ֵ0x60 ��ֵ����ʾ
//                  TFTSPI_Write_Word (0xffff); //��ʾ����
//                else
//                  TFTSPI_Write_Word (0x0000); //��ʾ����
            }
        }
#elif (IMAGEH == 480/2  && IMAGEW == 752/2)
        TFTSPI_Set_Pos(15,0,(uint8_t)(APP_CAMERA_WIDTH/4-1)+15 ,APP_CAMERA_HEIGHT/2);//ע�� ������ʾ��СҪ�������ʵ����ʾ��С��ȣ���Ȼ����ʾ���������߻���
        for(int i = 0; i < APP_CAMERA_HEIGHT; i+=4)  //  480/2/2/4 = 30
        {
            for(int j = 0; j < APP_CAMERA_WIDTH*2; j+=4)//��2��ȡһ��  752*2/2/4 = 188   //�������� һ��94����  ʵ����ʾ�ֱ���  94*60
            {
                //�Ҷ���ʾ
                color = 0;
                color=(((*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j))>>3))<<11;
                color=color|((((*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j))>>2))<<5);
                color=color|(((*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j))>>3));
                TFTSPI_Write_Word(color);
                //��ֵ����ʾ
//                if(*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j) > 0x60)  //��ֵ0x60 ��ֵ����ʾ
//                  TFTSPI_Write_Word (0xffff); //��ʾ����
//                else
//                  TFTSPI_Write_Word (0x0000); //��ʾ����
            }
        }
#elif (IMAGEH == 480  && IMAGEW == 752)
        TFTSPI_Set_Pos(15,0,(uint8_t)(APP_CAMERA_WIDTH/8-1)+15 ,APP_CAMERA_HEIGHT/4);//ע�� ������ʾ��СҪ�������ʵ����ʾ��С��ȣ���Ȼ����ʾ���������߻���
        for(int i = 0; i < APP_CAMERA_HEIGHT; i+=8)  //  480/1/2/8 = 30
        {
            for(int j = 0; j < APP_CAMERA_WIDTH*2; j+=8)//��2��ȡһ��  752*2/1/8 = 188   //�������� һ��94����  ʵ����ʾ�ֱ���  94*60
            {
                //�Ҷ���ʾ
                color = 0;
                color=(((*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j))>>3))<<11;
                color=color|((((*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j))>>2))<<5);
                color=color|(((*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j))>>3));
                TFTSPI_Write_Word(color);
                //��ֵ����ʾ
//                if(*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j) > 0x60)  //��ֵ0x60 ��ֵ����ʾ
//                  TFTSPI_Write_Word (0xffff); //��ʾ����
//                else
//                  TFTSPI_Write_Word (0x0000); //��ʾ����
            }
        }
#endif
#else  // 7725 �ĻҶ�ͼ��  ע�⣬���Ҷ�ͼ��ʱ��7725ʹ��YUYV��ʽ cameraConfig = { .pixelFormat = kVIDEO_PixelFormatYUYV }
//        TFTSPI_Set_Pos(0,0,APP_CAMERA_WIDTH/2,APP_CAMERA_HEIGHT/2);
//        for(int i = 0; i < APP_CAMERA_HEIGHT; i+=2)  //��2��ȡһ�� 240 / 2 = 120
//        {
//            for(int j = 1; j < APP_CAMERA_WIDTH *2 ; j+=4)//��4��ȡһ�� ����ͷUYVY��ʽ  Y�ǻҶȣ�320/2=160
//            {
//                if(*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j) > 0x60)  //��ֵ0x60 ��ֵ����ʾ
//                  TFTSPI_Write_Word (0xffff); //��ʾ����
//                else
//                  TFTSPI_Write_Word (0x0000); //��ʾ����
//            }
//        }
        TFTSPI_Set_Pos(20,0,(APP_CAMERA_WIDTH/4-1) + 20,APP_CAMERA_HEIGHT/4);
        for(int i = 0; i < APP_CAMERA_HEIGHT; i+=4)  //��4��ȡһ�� 240 / 4 = 60
        {
            for(int j = 1; j < APP_CAMERA_WIDTH *2 ; j+=8)//��8��ȡһ�� ����ͷUYVY��ʽ  Y�ǻҶȣ�320/4=80
            {
                if(*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j) > 0x60)  //��ֵ0x60 ��ֵ����ʾ
                  TFTSPI_Write_Word (0xffff); //��ʾ����
                else
                  TFTSPI_Write_Word (0x0000); //��ʾ����
            }
        }
#endif
        CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, fullCameraBufferAddr);//��������������ύ���������  
        LED_Color_Reverse(red); //EVK LED��˸  
    }
}

/**/











uint8_t Image_Use[Use_ROWS][Use_Line]; //ѹ����֮�����ڴ�Ҫʹ������
uint8_t Pixle[Use_ROWS][Use_Line];     //��Ŷ�ֵ���������
uint32_t fullCameraBufferAddr;
// ��ȡ��Ҫ��ͼ������
__ramfunc void Get_Use_Image(void)
{
    if (SCB_CCR_DC_Msk == (SCB_CCR_DC_Msk & SCB->CCR)) {//ע�⣬ʹ��csiFrameBuf����ʱ�����ˢ��һ��D-Cache ��Ȼ�ϴ����ݿ��ܻ�����cache���棬������ݴ���
        SCB_DisableDCache();
    }
    SCB_EnableDCache();
#ifdef LQMT9V034
#if (IMAGEH == 480  && IMAGEW == 752)
    for(int i = 0, x = 0; i < APP_CAMERA_HEIGHT; i+=8, x++)  //  480/1/2/8 = 30
        {
            for(int j = 0, y = 0; j < APP_CAMERA_WIDTH*2; j+=8, y++)//��2��ȡһ��  752*2/1/8 = 188   //�������� һ��94����  ʵ����ʾ�ֱ���  94*60
            {
                if(y < Use_Line)
                    Image_Use[x*2][y] = (*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j));
                else
                    Image_Use[x*2 + 1][y - Use_Line] = (*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j));
            }
        }
    
#elif (IMAGEH == 480/4  && IMAGEW == 752/4)
    for(int i = 0, x = 0; i < APP_CAMERA_HEIGHT; i+=2, x++)  //  480/4/2/2 = 30
        {
            for(int j = 0, y = 0; j < APP_CAMERA_WIDTH*2; j+=2, y++)//��2��ȡһ��  752*2/4/2 = 188   //�������� һ��94����  ʵ����ʾ�ֱ���  94*60
            {
                if(y < Use_Line)
                    Image_Use[x*2][y] = (*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j));
                else
                    Image_Use[x*2 + 1][y - Use_Line] = (*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j));
            }
        }
    
#elif (IMAGEH == 480/2  && IMAGEW == 752/2)
    for(int i = 0, x = 0; i < APP_CAMERA_HEIGHT; i+=4, x++)  //  480/2/2/4 = 30
        {
            for(int j = 0, y = 0; j < APP_CAMERA_WIDTH*2; j+=4, y++)//��2��ȡһ��  752*2/2/4 = 188   //�������� һ��94����  ʵ����ʾ�ֱ���  94*60
            {
                if(y < Use_Line)
                    Image_Use[x*2][y] = (*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j));
                else
                    Image_Use[x*2 + 1][y - Use_Line] = (*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j));
            }
        }
#endif  
#elif (APP_CAMERA_WIDTH == 320 && APP_CAMERA_HEIGHT == 240)
    for(int i = 0, x = Use_ROWS-1; i < APP_CAMERA_HEIGHT; i+=4, x--)  //��4��ȡһ�� 240 / 4 = 60
        {
            for(int j = 1, y = Use_Line - 1; j < APP_CAMERA_WIDTH *2; j+=8, y--)//��8��ȡһ�� ����ͷUYVY��ʽ  Y�ǻҶȣ�320/4=80
            {
                Image_Use[x][y] = (*((uint8_t *)fullCameraBufferAddr +  i * APP_CAMERA_WIDTH * 2 + j)); 
            }
        }
    
#endif
}


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
__ramfunc uint8_t GetOSTU(uint8_t tmImage[Use_ROWS][Use_Line]) 
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
    uint8_t Threshold = 0;
    uint8_t HistoGram[256];              //  
    
    for (j = 0; j < 256; j++)  HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ 
    
    for (j = 0; j < Use_ROWS; j++) 
    { 
        for (i = 0; i < Use_Line; i++) 
        { 
            HistoGram[tmImage[j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
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

//��ֵ������
__ramfunc void Camera_0_1_Handle(void)
{
    int i = 0,j = 0;
    uint8_t GaveValue;
    uint32_t tv=0;
    uint8_t Threshold = 0;
    //�ۼ�
    for(i = 0; i <Use_ROWS; i++)
    {    
        for(j = 0; j <Use_Line; j++)
        {                            
            tv+=Image_Use[i][j];   //�ۼ�  
        } 
    }
    GaveValue = tv/Use_ROWS/Use_Line;     //��ƽ��ֵ,����Խ��ԽС��ȫ��Լ35��������ĻԼ160��һ������´�Լ100 
//    Threshold = GetOSTU(Image_Use);  //�������ֵ
    //���վ�ֵ�ı������ж�ֵ��
    Threshold = GaveValue*7/10+10;        //�˴���ֵ���ã����ݻ����Ĺ������趨 
    for(i = 0; i < Use_ROWS; i++)
    {
        for(j = 0; j < Use_Line; j++)
        {                                
            if(Image_Use[i][j] >Threshold) //��ֵ��    
                Pixle[i][j] =1;        
            else                                        
                Pixle[i][j] =0;
        }    
    }
    
}

//�������Ϸ���Χ��������
__ramfunc void Pixle_Filter(void)
{  
  int nr; //��
  int nc; //��
  
  for(nr=1; nr<Use_ROWS-1; nr++)
  {  	    
    for(nc=1; nc<Use_Line-1; nc=nc+1)
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
  for(i=0;i<56;i+=8)// 56�� 
  {
    LCD_Set_Pos(24,i/8+1);
    for(j=0;j<Use_Line;j++) 
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

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����oled + camera test
������汾��V1.0
�������¡�2018��11��7�� 
����������
������ֵ����
������ֵ����
��ʵ���� OLED��ʾ���� OV7725��ֵ�� ͼ�����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/   
void Test_OLED_Camera(void)
{
    LCD_Init();               //LCD��ʼ�� 
    LCD_CLS();                //LCD���� 
    LCD_Show_Frame94();
#ifdef LQOV7725
    LCD_CLS();                //LCD���� 
    LCD_Show_Frame80();
    cameraConfig.pixelFormat = kVIDEO_PixelFormatYUYV;
#endif
    LQ_Camera_Init();
    delayms(200);        //��ʱ200����  
//    if (SCB_CCR_IC_Msk == (SCB_CCR_IC_Msk & SCB->CCR)) {   
//        SCB_DisableICache();
//    }
    
    while (1)
    {     
        // Wait to get the full frame buffer to show. 
        while (kStatus_Success != CAMERA_RECEIVER_GetFullBuffer(&cameraReceiver, &fullCameraBufferAddr))  //����ͷCSI����������
        {
        }   
        Get_Use_Image();     //��ȡʹ������
        Camera_0_1_Handle(); //��ֵ��
        Pixle_Filter();      //�˲�
        Draw_Road();         //��ʾ
        CAMERA_RECEIVER_SubmitEmptyBuffer(&cameraReceiver, fullCameraBufferAddr);//��������������ύ���������  
        LED_Color_Reverse(red); //EVK LED��˸  
    }
}
