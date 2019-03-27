/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�RT1052���İ�
����    д��Z
����    ע��
������汾��V1.0
�������¡�2017��11��27��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
���������䡿chiusir@163.com
----------------------------------------------------------------
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"

/*******************************************************************************
*  SDK�ṩ��������Noncacheable�����建�����ͱ����ķ�����
*  AT_NONCACHEABLE_SECTION_ALIGN(var, alignbytes)
*  AT_NONCACHEABLE_SECTION(var)
******************************************************************************/
AT_NONCACHEABLE_SECTION_ALIGN(uint32_t lcdFrameBuf[4][LCD_HEIGHT][LCD_WIDTH], FRAME_BUFFER_ALIGN);               //LCD���ݻ�����

uint8_t counter;       //LCD��������������һ����ǰ��ʾ�ã�һ��������
//volatile uint8_t LQ_LCD;  
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵������ʼ��LCDʱ��
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void BOARD_InitLcdifPixClock(void)
{
    /*
    * �������LCD��120Hz֡����ʾ. ��ôLCD��ʱ��Ӧ������Ϊ:
    *��LCD��� + APP_HSW + APP_HFP + APP_HBP��* ��LCD�߶� +��APP_VSW������APP_VSW������APP_VBP����*��֡�ʡ�
    * ����(480 + 41 + 4 + 18) * (272 + 10 + 4 + 2) * 120 = 9.3M * 2.
    * Here set the LCDIF pixel clock to 9.3M.
    */
    
    /*
    * Initialize the Video PLL.
    * Video PLL output clock is OSC24M * (loopDivider + (denominator / numerator)) / postDivider = 93MHz.
    */
    clock_video_pll_config_t config = {
        .loopDivider = 31, 
        .postDivider = 8, 
        .numerator   = 0, 
        .denominator = 0,
    };
    
    CLOCK_InitVideoPll(&config);
    
    /*
    * 000 derive clock from PLL2
    * 001 derive clock from PLL3 PFD3
    * 010 derive clock from PLL5
    * 011 derive clock from PLL2 PFD0
    * 100 derive clock from PLL2 PFD1
    * 101 derive clock from PLL3 PFD1
    */
    CLOCK_SetMux(kCLOCK_LcdifPreMux, 2);//ѡ��PLL5 
    CLOCK_SetDiv(kCLOCK_LcdifPreDiv, 4);//93Mhz  ����Ƶ
    CLOCK_SetDiv(kCLOCK_LcdifDiv, 0);//��1��Ƶ

}



//��16λRGB565��ɫ����ͷ����ת��Ϊ24λRGB������ʾ
//static void rgb565_2_rgb888(uint8_t *rgb565, uint8_t *rgb888, int pixels)
//{
//// RGB565 in little-endian: "G2G1G0B4B3B2B1B0 R4R3R2R1R0G5G4G3 
//for(uint32_t i=0; i<pixels; i++)
//{
//rgb888[3*i] = ((rgb565[2*i] & 0x1F)<<3) | (rgb565[2*i] & 0x07);//B4B3B2B1B0B2B1B0
//rgb888[3*i+1] = ((rgb565[2*i+1] & 0x07)<<5) | ((rgb565[2*i] & 0xE0)>>3) | ((rgb565[2*i] & 0x60)>>5);//G5G4G3G2G1G0G1G0
//rgb888[3*i+2] = (rgb565[2*i+1] & 0xF8) | ((rgb565[2*i+1] & 0x38)>>3); //R4R3R2R1R0R2R1R0
//    }
//}

void FillLCDBuffer(unsigned char page,unsigned char *PicArray)
{
    uint32_t i, j,cnt=0;
    
    for (i = 0; i < LCD_HEIGHT; i++)
    {
        for (j = 0; j < LCD_WIDTH; j++)
        {    //ˮƽɨ�裬24λ���ɫ����λ��ǰ
            lcdFrameBuf[page][i][j] = ((uint32_t)PicArray[cnt]<<16)|((uint32_t)PicArray[cnt+1]<<8)|((uint32_t)PicArray[cnt+2]);
            cnt+=3;
        }
    }
}
void APP_LCDIF_IRQHandler(void)
{
    uint32_t intStatus;
    
    intStatus = ELCDIF_GetInterruptStatus(LCDIF);
    
    ELCDIF_ClearInterruptStatus(LCDIF, intStatus);
    
    if (intStatus & kELCDIF_CurFrameDone)
    {
//        s_frameDone = true;
    }
}
void LCDIF_IRQHandler(void)           //Һ�����жϴ�����
{
    APP_LCDIF_IRQHandler();
}

/* Enable interrupt. */
void BOARD_EnableLcdInterrupt(void)   //Һ����ʹ���ж�
{
    EnableIRQ(LCDIF_IRQn);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����Һ������ʼ��
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_TFT480_272_Init(void)
{ 
    BOARD_InitLCDPins();      //��ɫLCD�ܽŸ��� 
    BOARD_InitLcdifPixClock();//LCDʱ��config  
    
    uint8_t  txt[32]="LongQiu";
    //Configure the LCDIF.  
    const elcdif_rgb_mode_config_t lcdConfig = {
        .panelWidth = APP_LCD_WIDTH,      //LCD width
        .panelHeight = APP_LCD_HEIGHT,    //LCD height
        .hsw = APP_HSW,                             //��ʾˮƽͬ���źŵĿ�ȣ���VCLK����
        .hfp = APP_HFP,                             //��ʾһ�е���Ч���ݽ�������һ��ˮƽͬ���źſ�ʼ֮���VCLK�ĸ���
        .hbp = APP_HBP,                             //��ʾ��ˮƽͬ���źſ�ʼ��һ�е���Ч���ݿ�ʼ֮���VCLK�ĸ���
        .vsw = APP_VSW,                             //��ʾ��ֱͬ������Ŀ�ȣ�����������
        .vfp = APP_VFP,                             //��ʾ��һ֡ͼ������󣬴�ֱͬ���ź���ǰ����Ч������
        .vbp = APP_VBP,                             //��ʾ��һ֡ͼ��ʼʱ����ֱͬ���ź��Ժ����Ч������
        .bufferAddr = (uint32_t)lcdFrameBuf[0],    //��������ַ
        .polarityFlags = APP_LCD_POL_FLAGS,         //LCD��һЩ����
        .pixelFormat = kELCDIF_PixelFormatXRGB8888, //���ظ�ʽ
        .dataBus = APP_LCDIF_DATA_BUS,              //LCD������������
    };
    
    ELCDIF_RgbModeInit(LCDIF, &lcdConfig);  //��ʱ�ӣ�config lcd
    
    ELCDIF_RgbModeStart(LCDIF);               //��ʼ��ʾ
    
    TFT_Draw_Part(40,44,440,250,BLACK,1);                 //��������������ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
    TFT_Draw_Part(60,64,420,230,GREEN,1);
    TFT_Draw_Line(40,44,440,250,RED,1);                   //���ߣ�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
    TFT_Draw_Line(40,250,440,44,RED,1); 
    TFT_Draw_Rectangle(50,54,430,240,GREEN,1);            //�����α߿�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
    TFT_Draw_Circle(240,136,100,RED,1);                   //��Բ�α߿�Բ�ĺ����ꡢ�����꣬�뾶����ɫ
    TFT_P16x16Str(184,115,"�����������ܿƼ�",RED,WHITE,1);//�ַ�����ʾ
    TFT_P8X16Str(208,140,(uint8_t*)txt,BLACK,WHITE,1);   //�ַ�����ʾ 
    ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)lcdFrameBuf[0]); //��������lcdFrameBuf ��ʾ��TFT����
    
//    GT9147_Init();//��ʼ��������
    delayms(200);        //��ʱ2000���� 
}





/**********************************************************
�������ƣ�TFT_Draw_Dot()
��ڲ�������ʼ������(0-127)��������(0-159),��ʾ��ɫuint16
���ڲ�������
ʱ�䣺2018-01-28
����˵��������
����˵����0<=x<=127
0<=y<=159
**********************************************************/
void TFT_Draw_Dot(uint16_t x,uint16_t y,uint32_t fcolor)
{  
    if(counter % 2)
    {
        lcdFrameBuf[1][y][x]=fcolor;
    }
    else
    {
        lcdFrameBuf[0][y][x]=fcolor;
    }
}

/*
�����ܡ� ���ָ������
�������� ��ʼ��x���꣬��ʼ��y���꣬��ֹ��x���꣬��ֹ�������꣬���ɫ
����TFT_Show_line(0,5,WHITE);  //��������
TFT_Show_line(2,5,WHITE);  //�ӵڶ����ַ���ʼ��������
*/
void TFT_Fill_Area(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye,uint32_t fcolor,uint8_t clr)
{
    unsigned int i,j;  
    
    for(i=xs;i<xe;i++)  
    {
        for(j=ys;j<ye;j++)
        {
            
                if(counter % 2)
                {
                    if(clr) lcdFrameBuf[1][j][i]=fcolor;
                    else   lcdFrameBuf[1][j][i]|=fcolor;
                }
                else
                {
                    if(clr) lcdFrameBuf[0][j][i]=fcolor;
                    else   lcdFrameBuf[0][j][i]|=fcolor;
                }
        }
    }
}

/**********************************************************
�������ƣ�TFT_CLS()
��ڲ�����colorΪ���õ���Ҫ��ʾ����ɫ(�Ѿ���ǰ����)��colorΪ
NULLʱ����ɽ���������ɫ����dat�м�����ʾ
���ڲ�������
ʱ�䣺2018-01-28
����˵����ȫ����ʾ��ɫ����
����˵������
**********************************************************/
void TFT_CLS(uint32_t fcolor)
{
    unsigned int i,j;
    
    for(i=0;i<APP_IMG_WIDTH;i++)      //480
    {
        for(j=0;j<APP_IMG_HEIGHT;j++)
        {
                if(counter % 2)
                {
                    lcdFrameBuf[1][j][i]=fcolor;
                }
                else
                {
                    lcdFrameBuf[0][j][i]=fcolor;
                }
        }
    }
}

/**********************************************************
�������ƣ�TFT_Draw_part()
��ڲ�������ʼ����ֹ������(0-127)��������(0-159),��ʾ��ɫuint16
���ڲ�������
ʱ�䣺2018-01-28
����˵��������������
����˵����0<=xs<xe<=127
0<=ys<ye<=159
**********************************************************/
void TFT_Draw_Part(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye,uint32_t fcolor,uint8_t clr)
{
    uint32_t i,j;  
    
    for(j=ys;j<(ye+1);j++)
    {
        for(i=xs;i<(xe+1);i++)
        {
            if(counter % 2)
            {
                if(clr) lcdFrameBuf[1][j][i]=fcolor;
                else   lcdFrameBuf[1][j][i]|=fcolor;
            }
            else
            {
                if(clr) lcdFrameBuf[0][j][i]=fcolor;
                else   lcdFrameBuf[0][j][i]|=fcolor;
            }
            
        }
    }   
}


/**********************************************************
�������ƣ�TFT_Draw_line()
��ڲ�������ʼ����ֹ������(0-127)��������(0-159),��ʾ��ɫuint16
���ڲ�������
ʱ�䣺2018-01-28
����˵������ֱ��
����˵����0<=xs<xe<=127
0<=ys<ye<=159
**********************************************************/
void TFT_Draw_Line(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye,uint32_t fcolor,uint8_t clr)
{
    uint32_t i,ds;
    int dx,dy,inc_x, inc_y;
    int xerr = 0, yerr = 0;				        //��ʼ������
    
    if(xs==xe)	  						//����ǻ���ֱ����ֻ�����ֱ�������
    {    
        for(i=ys;i<(ye+1);i++)
        {
            if(counter % 2)
            {
                if(clr) lcdFrameBuf[1][i][xs]=fcolor;
                else   lcdFrameBuf[1][i][xs]|=fcolor;
            }
            else
            {
                if(clr) lcdFrameBuf[0][i][xs]=fcolor;
                else   lcdFrameBuf[0][i][xs]|=fcolor;
            }
            
        }
    }
    else if(ys==ye)						//�����ˮƽ����ֻ��Ҫ��ˮƽ�������
    {   
        for(i=xs;i<(xe+1);i++)
        {
            
            if(counter % 2)
            {
                if(clr) lcdFrameBuf[1][ys][i]=fcolor;
                else   lcdFrameBuf[1][ys][i]|=fcolor;
            }
            else
            {
                if(clr) lcdFrameBuf[0][ys][i]=fcolor;
                else   lcdFrameBuf[0][ys][i]|=fcolor;
            }
        }
    } 
    else								//�����б�ߣ������¼��㣬ʹ�û��㺯������ֱ��
    {
        dx = xe - xs;						//������������
        dy = ye - ys;
        
        if(dx > 0) inc_x = 1;					//���õ�������
        else 
        {
            inc_x = -1; dx = -dx;
        }
        if(dy > 0) inc_y = 1;					//���õ�������
        else
        {
            inc_y = -1; dy = -dy;
        }
        
        if(dx > dy) ds = dx;					//ѡȡ��������������
        else		ds = dy;
        
        for(i = 0; i <= ds+1; i++)					//�������
        {
            TFT_Draw_Dot(xs, ys,fcolor);	//����
            xerr += dx;
            yerr += dy;
            if(xerr > ds)
            {
                xerr -= ds;
                xs   += inc_x;
            }
            if(yerr > ds)
            {
                yerr -= ds;
                ys   += inc_y;
            }
        }
    }  
}

/****************��ʾͼƬ���ӵ�Ƭ����DATA����********************************/	

void TFT_Show_Pic(uint16_t xs,uint16_t ys,uint16_t xe,uint16_t ye,uint8_t *PicArray)
{
    uint16_t i, j,cnt=0;
    
    for(i=0;i<ye-ys;i++)
    { 
        for(j=0;j<xe-xs;j++)
        {			
            lcdFrameBuf[0][j][i]=((uint32_t)PicArray[cnt]<<16)|((uint32_t)PicArray[cnt+1]<<8)|((uint32_t)PicArray[cnt+2]);		
            cnt+=3; 
        }
    }    
}



/**********************************************************
�������ƣ�Text_TFT_480_272()
��ڲ�����
���ڲ�������
ʱ�䣺2018-01-28
����˵������ֱ��
����˵����Һ�������Ժ���
**********************************************************/
void Test_TFT_480_272(void)
{
    
    LQ_TFT480_272_Init();
    GT9147_Init();//��ʼ��������
    
    char  txt[100]="LongQiu";
    static uint8_t i, count;
    while(1)
    {
        count ++;
        if (count > 20) count = 0;
        TFT_Draw_Part(40,44,440,250,BLACK,1);                 //��������������ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
        TFT_Draw_Part(60,64,420,230,GREEN,1);
        TFT_Draw_Line(40,44,440,250,RED,1);                   //���ߣ�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
        TFT_Draw_Line(40,250,440,44,RED,1); 
        TFT_Draw_Rectangle(50,54,430,240,GREEN,1);            //�����α߿�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
        TFT_Draw_Circle(240,136,100,RED,1);                   //��Բ�α߿�Բ�ĺ����ꡢ�����꣬�뾶����ɫ
        TFT_P16x16Str(184,115,"�����������ܿƼ�",RED,WHITE,1);//�ַ�����ʾ
        
        for(i = 0; i < count; i ++)  //��LongQiuǰ��ӿո�
        {
            sprintf(txt + i, " ");
        }
        
        sprintf(txt + count, "LongQiu");
        TFT_P8X16Str(108,140,(uint8_t*)txt,BLACK,WHITE,1);   //�ַ�����ʾ 
        ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)lcdFrameBuf[0]); //��������lcdFrameBuf ��ʾ��TFT����
        
        //    GT9147_Init();//��ʼ��������
        delayms(1000);        //��ʱ1000���� 
        while(1)
        {
            if(GT9147_Scan(0))   //����������
            {
                uint8_t i;
                for(i=0;i<5;i++)
                {         
                    TFT_Draw_CircleCake(tp_dev.x[i],tp_dev.y[i],40,RED,1);   //�����ĵط���Բ
                    TFT_Draw_CircleCake(tp_dev.x[i],tp_dev.y[i],20,BLUE,1);
                    TFT_Draw_CircleCake(tp_dev.x[i],tp_dev.y[i], 8,BLACK,1);
                }
            }      
            
        }        
    } 
}










