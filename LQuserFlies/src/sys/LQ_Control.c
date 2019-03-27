#include "LQ_control.h"

#include "status.h"
#include "Scheduler.h"



_pid_param_t  Motor_pid =      //���PID�����ṹ��
{
     ._kp             =  1.5 ,         //P
     ._ki             =  0.5 ,         //I
     ._kd             =  0.1 ,         //D
     ._imax           = 1000 ,          //�����޷�
                                       
     ._pid_out_p      =   0,           //KP���
     ._pid_out_i      =   0,           //KI���
     ._pid_out_d      =   0,           //KD���
     ._pid_out        =   0,           //pid���
     
     ._integrator     =   0,           //����ֵ
     ._last_error     =   0,           //��һ�����
     ._last_derivative=   0,           //�ϴ�΢��
     ._last_t         =   0,           //�ϴ�ʱ��
     .scaler          =   100,           //���ű�

};
_pid_param_t  Servo_pid =    //���PID�����ṹ��
{
     ._kp             =  1.5 ,
     ._ki             =  0.5 ,
     ._kd             =  0.1 ,
     ._imax           =  500 , 
     
     ._pid_out_p      =   0,  
     ._pid_out_i      =   0,  
     ._pid_out_d      =   0,  
     ._pid_out        =   0,
     
     ._integrator     =   0, 
     ._last_error     =   0, 
     ._last_derivative=   0,
     ._last_t         =   0,  
     .scaler          =   1,  

};

uint8_t Left[Use_ROWS], Right[Use_ROWS];  //��ű���λ��
/*�ҵ�������Ե���� δ�������� */
void LQ_Line_Hunting(uint8_t Pixle [Use_ROWS][Use_Line])
{

    uint8_t i,j;

    for(j = Use_Line/2; j > 0; j--)              //���
    {
        if(!Pixle[Use_ROWS - 1][j] && !Pixle[Use_ROWS - 1][j-1])  //�����һ��   ����������ڵ��ж�Ϊ����
        {
            Left[Use_ROWS - 1] = j;                               //����߱���λ�ô��������
        }
        
    }
    for(j = Use_Line/2; j < Use_Line; j++)       //�ұ�
    {
        if(!Pixle[Use_ROWS - 1][j] && !Pixle[Use_ROWS - 1][j-1])  //�����һ��   ����������ڵ��ж�Ϊ����
        {
            Right[Use_ROWS - 1] = j;                               //���ұ߱���λ�ô��������
        }
    }
    if(Right[Use_ROWS - 1] - Left[Use_ROWS - 1] < 30)              // �ұ��� - �����  < 30 �����ص�  �ж�Ϊ������
    {
        _status.stop = 1;                                            //ͣ�� 
        return;
    }
    if((Right[Use_ROWS - 1] == Use_Line/2 && Left[Use_ROWS - 1]) == Use_Line/2)              // ���߾��Ǻڵ�  �ж�Ϊ��·������ʹ������ͷ
    {
        _status.camera_run = 0;                                            //��������ͷ 
        return;
    }
    else
    {
        _status.camera_run = 1;
    }
    
    for(i = Use_ROWS - 2; i > 0; i--)
    {
        for(j = Left[i+1] + 5; j > 0; j--)              //���   ����Ӧ������  ����һ�б���λ���ұ�5�����ص㴦��ʼ��
        {
            if(!Pixle[i][j] && !Pixle[i][j-1])  //����������ڵ��ж�Ϊ����
            {
                Left[i] = j;
                break;
            }        
        }
        
        if(j == 0)    //û�кڱߣ� ��������Ϊ�ڱ�
        {
            Left[i] = j;
        }
        
        for(j = Right[i+1] - 5; j < Use_Line; j++)       //�ұ�  ����һ�б���λ�����5�����ص㴦��ʼ��
        {
            if(!Pixle[i][j] && !Pixle[i][j-1])  //����������ڵ��ж�Ϊ����
            {
                Right[i] = j;
                break;
            }   
        }
        
        if(j == Use_Line)    //û�кڱߣ� ��������Ϊ�ڱ�
        {
            Left[i] = j;
        }

    }
    
}
extern int OFFSET0;      //��Զ������������ֵ�ۺ�ƫ����
extern int OFFSET1;      //�ڶ���
extern int OFFSET2;      //�����������
void seek_road(void)     //�õ�·��ƫ��� δ��������
{
    uint8_t i;
    uint64_t sum = 0;
    static uint32_t time;
    for(i = 0; i < (uint8_t)(Use_ROWS/3); i++)
    {
        sum += Left[i] + Right[i] - Use_Line; 
    }
    OFFSET0 = sum / (uint8_t)(Use_ROWS/3);
    sum = 0;
    
    for(i = (uint8_t)(Use_ROWS/3); i < (uint8_t)(Use_ROWS/3*2); i++)
    {
        sum += Left[i] + Right[i]  - Use_Line ; 
    }
    OFFSET1 = sum / ((uint8_t)(Use_ROWS/3*2) - (uint8_t)(Use_ROWS/3));
    sum = 0;
    
    for(i = (uint8_t)(Use_ROWS/3*2); i < Use_ROWS; i++)
    {
        sum += Left[i] + Right[i] - Use_Line; 
    }
    OFFSET2 = sum / (Use_ROWS - (uint8_t)(Use_ROWS/3*2));
    
    if(abs(OFFSET0) < 100 && abs(OFFSET1) < 100 && abs(OFFSET2) < 100 )   //ֱ��
    {
        _status.straight_speed = 1;
    }
    else if(_status.straight_speed == 1 && abs(OFFSET0) > 100 )           //����
    {
        _status.brake_speed = 1;
        _status.straight_speed = 0; 
        
        
        time = _systime.get_time_ms();                                    //��ס�����ʱ��
    }
    else                                                                 //���
    {
        _status.curve_speed = 1;
    }

    
    if(_systime.get_time_ms() - time > 1000)                              //1s��ȡ������
    {
        _status.brake_speed = 0;
    }
}

void LQ_Control_Servo(void)    //PID�������
{
    pid.get_pid(&Servo_pid, OFFSET2);
    LQ_SetServoDty(Servo_pid._pid_out + 3440);
}

void LQ_Control_Motor(int16_t velocity) //PID�������
{
    float error;
    if((fabs)(Servo_pid._pid_out) > 200 )    //��Ƕ�ת��  ʹ�ò���  
    {
    
    }
    if(_status.straight_speed)  //�ж���ֱ��
    {
        error = STRAIGHT_SPEED - velocity;    
    }
    else if(_status.brake_speed)  //�ж�����  ����
    {
        error = BRAKE_SPEED - velocity;   
    }
    else if(_status.curve_speed)  //�ж������
    {
        error = CURVE_SPEED - velocity;   
    } 
    pid.get_pid(&Motor_pid, error);
    if(Motor_pid._pid_out > 5000)  //�޷�
    {
        Motor_pid._pid_out = 5000;
    }
    if(Motor_pid._pid_out < -2000) //�޷�
    {
        Motor_pid._pid_out = -2000;
    }
    LQ_PWMA_B_SetDuty(PWM1, kPWM_Module_3, 2000 + Motor_pid._pid_out, 0);
}

/****************xia************************///
void pxp_init(void)
{
       //Configure the PXP for color space conversion.
    PXP_Init(PXP);    //��ʱ��
    /* Disable AS. */
    PXP_SetAlphaSurfacePosition(PXP, 0xFFFFU, 0xFFFFU, 0U, 0U);
    
    
#ifdef LQMT9V034 //LQMT9V034ģ��
    PXP_EnableCsc1(PXP, false);              //��ʹ��  LQMT9V034ģ��Ϊ��ɫ��ʽ

    PXP_SetProcessSurfaceScaler(PXP,IMAGEW/4, IMAGEH,  Use_Line, Use_ROWS);//����ͼ��, ��������ͷ752 * 480�ֱ��ʣ����������ʽΪ ��λ��ɫ�ʣ�Ҳ����һ���ֽھ���һ�����ص㣬���ǵ�Ƭ����csi�ӿ�����Ϊrgb888��ʽ����������ͷ����һ���ֽڱ�ʾһ�����ص㣬������ĸ��ֽڱ�ʾһ�����ص㣩
    PXP_SetProcessSurfacePosition(PXP, 0u, 0u, Use_Line - 1U, Use_ROWS - 1U);                //������ʾλ��
#else  //LQOV7725ģ��
    PXP_SetCsc1Mode(PXP, kPXP_Csc1YCbCr2RGB);//���� csc1  kPXP_Csc1YCbCrת��Ϊrgb
    PXP_EnableCsc1(PXP, false);               //ʹ��csc1
    
    PXP_SetProcessSurfaceScaler(PXP,APP_CAMERA_WIDTH, APP_CAMERA_HEIGHT, Use_Line, Use_ROWS);//����
    PXP_SetProcessSurfacePosition(PXP, 0u, 0u, Use_Line - 1U, Use_ROWS - 1U);                //������ʾλ��
#endif
   
    PXP_SetProcessSurfaceBackGroundColor(PXP, 0u);  //���ñ�����ɫ

    PXP_SetRotateConfig(PXP, kPXP_RotateOutputBuffer, kPXP_Rotate0, kPXP_FlipDisable);//ͼ����ת���ٶȣ���ת���
    
    
    /* Input config. */
#ifdef LQMT9V034 //LQMT9V034ģ��
        psBufferConfig.pixelFormat =  kPXP_PsPixelFormatRGB888;//���ظ�ʽ
#else                  //LQOV7725ģ��
        psBufferConfig.pixelFormat =  kPXP_PsPixelFormatRGB565;//���ظ�ʽ
#endif
        psBufferConfig.swapByte = false;                 //��8λ��ǰ���ǵ�8λ��ǰ
        psBufferConfig.bufferAddrU = 0U;
        psBufferConfig.bufferAddrV = 0U;
        psBufferConfig.pitchBytes = APP_CAMERA_WIDTH * APP_BPP;    //һ�ж��ٸ��ֽ� 
        
    /* Output config. */
        outputBufferConfig.pixelFormat = kPXP_OutputPixelFormatARGB8888;//���ظ�ʽ
        outputBufferConfig.interlacedMode = kPXP_OutputProgressive;
        outputBufferConfig.buffer1Addr = 0U;
        outputBufferConfig.pitchBytes = APP_LCD_WIDTH * 4;
        outputBufferConfig.width = APP_LCD_WIDTH;
        outputBufferConfig.height = APP_LCD_HEIGHT;
}
void sys_init(void)
{
    BOARD_ConfigMPU();                   //Config MPU.      
    BOARD_InitSDRAMPins();
    BOARD_BootClockRUN();                //Configure clock            
    LED_Init();                          //��������LED0���õ�
    LQ_UART_Init(LPUART1, 115200);       //����1��ʼ�� ����ʹ�� printf����
    _systime.init();                     //����systick��ʱ��
    NVIC_SetPriorityGrouping(2);//�����ж����ȼ�0: 0����ռ���ȼ�16λ�������ȼ� 1: 2����ռ���ȼ� 8�������ȼ� 2: 4����ռ���ȼ� 4�������ȼ� 3: 8����ռ���ȼ� 2�������ȼ� 4: 16����ռ���ȼ� 0�������ȼ� 


     /*��ʼ�����PWM�ӿ�  kPWM_PwmA  L5      kPWM_PwmB M5 */
    LQ_PWM_Init(PWM1, kPWM_Module_3, kPWM_PwmA_B, 12000);//PWM�����Ƶ�� = 6250 000 / VAL1  = 96Hz
    
    /*��ʼ�����PWM�ӿ�  kPWM_PwmA  M3  */
    LQ_PWM_Init(PWM2, kPWM_Module_3, kPWM_PwmA,  200);//PWM�����Ƶ�� = 6250 000 / VAL1  = 96Hz
    
    LQ_SetServoDty(3440);  //��ֵ
    
    LQ_ENC_Init(ENC1);                   //��������1��ʼ��
    LQ_ENC_Init(ENC2);                   //��������2��ʼ��
    LQADC_Init(ADC1);                    //ADC��ʼ��
//    LQ_PIT_Init(kPIT_Chnl_0, 10000);     //��ʼ��PIT chnl0�жϣ�10 000us
    LQ_KEY_Init();                       //������ʼ��
    LCD_Init();               //OLED��ʼ�� 
    UART_DMA_Init();          //����DMA��ʼ���������ϱ�����
    LQ_Camera_Init();
    pxp_init();
    
}
/*δ��֤  ֻ�п��  ����Ȥ�Ŀ�����������*/
       
void 
TEST(void)
{
    sys_init();                     //�����ʼ��
    _sched.init();                  //��ʼ�����������
    
    uint32_t current_time;   
    uint64_t last_time;
 
    while(1)
    {
        current_time = _systime.get_time_us() - last_time;
        if(current_time > 5000)  // һ������5ms
        {         
            last_time = _systime.get_time_us();
            GPIO_PinReverse(GPIO2, 22);      //��ʾ�����۲죬��ʱ���Ƿ�����
            _sched.run(5000);                //����
        }
    }
}





