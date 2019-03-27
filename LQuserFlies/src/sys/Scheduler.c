// Header:
// File Name: ���������������ֲ��APM
// Author:Z
// Date:2018/08/03

#include "Scheduler.h"
#include "m_systime.h"
#include "status.h"
void battery_update(void)   //��ѹ���
{
    static float Voltage = 7.8;
    static uint8_t count;
    Voltage = Voltage * 0.9 + 0.1 * ReadADC(ADC1,ADC1_CH10)*4.6;
    if(Voltage < 7200) //��ص�ѹ����7.2V
    {
        count++;
    }
    if(count > 50)
    {
        count = 0;
        _status.low_power_flag = 1;        //�͵�ѹ��־λ��1
    }
}

//void ins_update(void)                   //������̬
//{
//    _AHRS.update();
//
//}
void notify_update(void)    //���µ�����ڱ�ʾ����״̬
{
    static uint16_t count;
    count++;
    if(_status.low_power_flag)   //�͵�ѹ
    {
       if(count % 20 == 1)                     //���Ʊ���
       {
            LED_Color_Reverse(red);         //�����˸  ����Ȥ�Ŀ���ʹ�ú�ƣ����ƣ��ϵƵ�
       }
    }
//    else if()

}

void electromagnetic_update(void)  //���µ�Ŵ�����
{
//    static int ADC_left,ADC_right,ADC_centre;
//    if(_status.electromagnetism)  //ʹ�õ�Ŵ�����
//    {
//        ADC_left = ADC_left*0.9 + 0.1*ReadADC(ADC1,ADC1_CH4)*0.806;
//        ADC_right = ADC_left*0.9 + 0.1*ReadADC(ADC1,ADC1_CH2)*0.806;
//        ADC_centre = ADC_left*0.9 + 0.1*ReadADC(ADC1,ADC1_CH3)*0.806;
//    }
}


extern void Draw_Road(void);
void display_update(void)   //������ʾ
{
    /*���3ms*/
    Draw_Road();
}


short velocity_upper_left, velocity_upper_right, velocity_lower_left, velocity_lower_right;  //�������ٶ�
void report_update(void)    //�ϱ����ݸ���λ��
{
    if(_status.get_pid_group1)   //�յ���λ�����͵� ��ȡ�ɿ� ָ��   ��Ƭ������pid��������λ��
    {
        _status.get_pid_group1 = 0;
        ANO_DT_Send_PID(1, Motor_pid._kp, Motor_pid._ki, Motor_pid._kd, Servo_pid._kp, Servo_pid._ki, Servo_pid._kd, 0,0,0);
    }
    else 
    {
        ANO_DT_send_int16((short)(Motor_pid._pid_out_p),   //�ϱ�������λ�� PID����
                          (short)(Motor_pid._pid_out_i), 
                          (short)(Motor_pid._pid_out_d), 
                          (short)(Motor_pid._pid_out), 
                          (short)(Motor_pid._integrator ), 
                          (short)(Motor_pid._last_error ), 
                          CURVE_SPEED, 
                          (short)velocity_lower_left);
    }
    
}



void camera_update(void)
{
    uint32_t fullCameraBufferAddr; //���CSI����������ַ
    counter ++;
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
}



void pxp_update(void)
{
    /*PXPͼ����   ���3ms  �����������û�����  ִ������ټ��PXPת�����*/
    while (!(kPXP_CompleteFlag & PXP_GetStatusFlags(PXP)))  //�ȴ�pXPת�����
    {
    }
    PXP_ClearStatusFlags(PXP, kPXP_CompleteFlag);   //�����־λ  

}



extern uint8_t Pixle [Use_ROWS][Use_Line];
extern void Camera_0_1_Handle(void);
extern void Pixle_Filter(void);
void camera_data_dispose(void)
{
    Camera_0_1_Handle();   //��ֵ��
    Pixle_Filter();        //�˲�
    LQ_Line_Hunting(Pixle);//Ѱ�ұ���
    seek_road();           //�õ�ƫ��
}



void main_loop(void)
{
//    LQ_Control_Servo();                 //���ƶ��
    velocity_lower_left = (int16_t)ENC_GetPositionDifferenceValue(ENC2);  //�õ�������΢��ֵ
    LQ_Control_Motor(velocity_lower_left);          //���Ƶ��
}




sched_task_t sched_task[] =
{
//    { update_GPS,            2,     900        ,0},
//    { update_navigation,     10,    500 },
//    { medium_loop,           2,     700 },
//    ����ָ��     ÿ����������ִ��һ��  �ú�������һ�εĴ��ʱ��  ��һ�κ�������ʱtick
//      { baro_update,          10,                 20,               0   }, //���¸߶�
//	  { radio_update,          3,                200,               0   }, //����ң������
    
//      { camera_update  ,       4,                850,               0   }, //��������ͷ����
      { main_loop    ,         1,                 50,               0   }, //����PWM
	  { notify_update,        10,                 50,               0   }, //����led
	  { battery_update,       10,                100,               0   }, //���µ�ص�ѹ

	  { report_update,        5,                500,               0   }, //�ϱ����ݸ���λ��
//      { pxp_update,            4,               1500,               0   }, //����ͷ����PXP����
//      { camera_data_dispose,   4,               2000,               0   }, //����ͷ���ݴ���
//      { display_update,       10,               4000,               0   }, //������ʾ
      
      
      
//	  { motors_status_update,  5,                 10,               0   }, //���µ��״̬
//    { fifty_hz_loop,         2,     950 },
//    { run_nav_updates,      10,     800 },
//    { slow_loop,            10,     500 },
//    { gcs_check_input,	   2,     700 },
//    { gcs_send_heartbeat,  100,     700 },
//    { gcs_data_stream_send,  2,    1500 },
//    { gcs_send_deferred,     2,    1200 },
//    { compass_accumulate,    2,     700 },
//    { barometer_accumulate,  2,     900 },
//    { super_slow_loop,     100,    1100 },
//    { perf_update,        1000,     500 }


};

static uint8_t num_task;  //��������
void shceduler_init()
{
	num_task = sizeof (sched_task) / sizeof (sched_task[0]);
}

static uint32_t tick_counter = 0;  //shceduler_runִ�д���
void shceduler_tick()
{
	tick_counter++;
}

/*
  run one tick
  this will run as many scheduler tasks as we can in the specified time
 */
//#define UART_DEBUG

void shceduler_run(uint32_t time_available)
{
    uint64_t now;
    uint16_t dt;
    uint16_t interval_ticks;
    
	for (uint8_t i = 0; i < num_task; i++)
	{
		now = _systime.get_time_us();//��ȡ��ǰʱ��
		dt = tick_counter - sched_task[i].last_tick_counter;//���������ϴ����е����������������
        interval_ticks = sched_task[i].interval_ticks;  //�������������������һ��

		if( dt >= interval_ticks)
		{
			//����ʱʹ�ã�����ʱ��δ���У�˵���������������̫������shceduler_run�Ŀ�����ʱ��̫��
			if (dt >= interval_ticks*2)
			{
                // we've slipped a whole run of this task!
				#ifdef UART_DEBUG
				printf("Scheduler slip task[%u] (%u/%u/%u)\n",
									  (unsigned)i,
									  (unsigned)dt,
									  (unsigned)interval_ticks,
									  (unsigned)sched_task[i].max_time_micros);
				#endif //UART_DEBUG

            }
			if (sched_task[i].max_time_micros <= time_available)
			{
				//��������
				sched_task[i].task_func();
				//����last_tick_counter
				sched_task[i].last_tick_counter = tick_counter;

				#ifdef UART_DEBUG
				uint32_t end_time = _systime.get_time_us() - now;
//����������й�����ʱ�䳬��shceduler_run�Ŀ�����ʱ��time_available��˵�������max_time_micros����С��
				if(end_time > time_available)
				{
					printf("Scheduler slip task[%u] (%u/%u)\n",
                                          (unsigned)i,
                                          (unsigned)end_time,
                                          (unsigned)sched_task[i].max_time_micros);
					return;

				}
				#endif //UART_DEBUG

			}

		}
		//����time_available
		time_available -= (_systime.get_time_us() - now);
	}
	//����tick_counter
	_sched.tick();  // �ú�������Ϊtick_counter++
}


sched_t _sched =
{
	shceduler_init,
	shceduler_tick,
	shceduler_run,
};
