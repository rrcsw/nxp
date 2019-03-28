#include "ANO_DT.h"
#include "system.h"

#define USE_DMA  1    //是否使用DMA模式，注意使用DMA模式，串口初始化时要配置DMA模式
//使用匿名4.3上位机协议
/////////////////////////////////////////////////////////////////////////////////////
//数据拆分宏定义，在发送大于1字节的数据类型时，比如int16、float等，需要把数据拆分成单独字节进行发送
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )


/////////////////////////////////////////////////////////////////////////////////////
//Send_Data函数是协议中所有发送数据功能使用到的发送函数
//移植时，用户应根据自身应用的情况，根据使用的通信方式，实现此函数
#if USE_DMA
extern lpuart_transfer_t sendXfer;
extern lpuart_edma_handle_t g_lpuartEdmaHandle;
#endif
void ANO_DT_Send_Data(uint8_t *dataToSend , uint8_t length)
{
#if USE_DMA
     /* If TX is idle and g_txBuffer is full, start to send data. */
    /*使用DMA + 串口，无需占用CPU时间 */
    sendXfer.data = dataToSend;   
    sendXfer.dataSize = length;
    if ((!_status.txOnGoing) )
    {
        _status.txOnGoing = true;
        LPUART_SendEDMA(LPUART8, &g_lpuartEdmaHandle, &sendXfer);
    }
#else
    /**使用串口正常发送数据，大概需要1.5ms*/
	LQ_UART_PutBuff(LPUART8, dataToSend, length);     //可以修改不同的串口发送数据
#endif  
   
}
uint8_t data_to_send[50];	//发送数据缓存
static void ANO_DT_Send_Check(uint8_t head, uint8_t check_sum)
{
    
	data_to_send[0]=0xAA;
	data_to_send[1]=0xAA;
	data_to_send[2]=0xEF;
	data_to_send[3]=2;
	data_to_send[4]=head;
	data_to_send[5]=check_sum;
	
	
	uint8_t sum = 0;
	for(uint8_t i=0;i<6;i++)
		sum += data_to_send[i];
	data_to_send[6]=sum;

	ANO_DT_Send_Data(data_to_send, 7);
}

/*发送给上位机的数据协议*/
void ANO_DT_send_int16(short data1, short data2, short data3, short data4, short data5, short data6, short data7, short data8 /*,short data7, short data8, short .....可根据需要自行添加 */)
{
    uint8_t _cnt=0;
    data_to_send[_cnt++] = 0xAA;      //匿名协议帧头  0xAAAA
	data_to_send[_cnt++] = 0xAA;
	data_to_send[_cnt++] = 0xF1;      //使用用户协议帧0xF1  
    data_to_send[_cnt++] = 16;        //8个short 长度 16个字节
    
	data_to_send[_cnt++]=BYTE1(data1);
	data_to_send[_cnt++]=BYTE0(data1);

	data_to_send[_cnt++]=BYTE1(data2);
	data_to_send[_cnt++]=BYTE0(data2);

	data_to_send[_cnt++]=BYTE1(data3);
	data_to_send[_cnt++]=BYTE0(data3);
    
    data_to_send[_cnt++]=BYTE1(data4);
	data_to_send[_cnt++]=BYTE0(data4);

	data_to_send[_cnt++]=BYTE1(data5);
	data_to_send[_cnt++]=BYTE0(data5);

	data_to_send[_cnt++]=BYTE1(data6);
	data_to_send[_cnt++]=BYTE0(data6);
    
    data_to_send[_cnt++]=BYTE1(data7);
	data_to_send[_cnt++]=BYTE0(data7);

	data_to_send[_cnt++]=BYTE1(data8);
	data_to_send[_cnt++]=BYTE0(data8);
    
    uint8_t sum = 0;
	for(uint8_t i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;
	
	ANO_DT_Send_Data(data_to_send, _cnt);
}

///////////////////////////////////////////////////////////////////////////////////////
////Data_Receive_Prepare函数是协议预解析，根据协议的格式，将收到的数据进行一次格式性解析，格式正确的话再进行数据解析
////移植时，此函数应由用户根据自身使用的通信方式自行调用，比如串口每收到一字节数据，则调用此函数一次
////此函数解析出符合格式的数据帧后，会自行调用数据解析函数

void ANO_DT_Data_Receive_Anl(uint8_t *data_buf,uint8_t num);
void ANO_DT_Data_Receive_Prepare(uint8_t data)
{
    static uint8_t RxBuffer[50];
	static uint8_t _data_len = 0,_data_cnt = 0;
	static uint8_t state = 0;
	
	if(state==0&&data==0xAA)
	{
		state=1;
		RxBuffer[0]=data;
	}
	else if(state==1&&data==0xAF)
	{
		state=2;
		RxBuffer[1]=data;
	}
	else if(state==2&&data<0XF1)
	{
		state=3;
		RxBuffer[2]=data;
	}
	else if(state==3&&data<50)
	{
		state = 4;
		RxBuffer[3]=data;
		_data_len = data;
		_data_cnt = 0;
	}
	else if(state==4&&_data_len>0)
	{
		_data_len--;
		RxBuffer[4+_data_cnt++]=data;
		if(_data_len==0)
			state = 5;
	}
	else if(state==5)
	{
		state = 0;
		RxBuffer[4+_data_cnt]=data;
		ANO_DT_Data_Receive_Anl(RxBuffer,_data_cnt+5);
	}
	else
		state = 0;
}


void ANO_DT_Send_PID(uint8_t group,float p1_p,float p1_i,float p1_d,float p2_p,float p2_i,float p2_d,float p3_p,float p3_i,float p3_d)
{
	uint8_t _cnt=0;
	short _temp;
	
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x10+group-1;
	data_to_send[_cnt++]=0;
	
	
	_temp = (short)(p1_p * 1000);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (short)(p1_i  * 1000);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (short)(p1_d  * 1000);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (short)(p2_p  * 1000);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (short)(p2_i  * 1000);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (short)(p2_d * 1000);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (short)(p3_p  * 1000);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (short)(p3_i  * 1000);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (short)(p3_d * 1000);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[3] = _cnt-4;
	
	uint8_t sum = 0;
	for(uint8_t i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;

	ANO_DT_Send_Data(data_to_send, _cnt);
}
/////////////////////////////////////////////////////////////////////////////////////
//Data_Receive_Anl函数是协议数据解析函数，函数参数是符合协议格式的一个数据帧，该函数会首先对协议数据进行校验
//校验通过后对数据进行解析，实现相应功能
//此函数可以不用用户自行调用，由函数Data_Receive_Prepare自动调用
void ANO_DT_Data_Receive_Anl(uint8_t *data_buf,uint8_t num)
{
	uint8_t sum = 0;
	for(uint8_t i=0;i<(num-1);i++)
		sum += *(data_buf+i);
	if(!(sum==*(data_buf+num-1)))		return;		//判断sum
	if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAF))		return;		//判断帧头
	
	if(*(data_buf+2)==0X01) //校准
	{
        LED_Color(red);     //红灯
		if(*(data_buf+4)==0X01)
			_status.ins_calibration = 1;    //陀螺仪校准
		if(*(data_buf+4)==0X02)
			_status.ins_calibration = 1;
		if(*(data_buf+4)==0X03)
		{
			_status.ins_calibration = 1;				
		}
	}
	
	if(*(data_buf+2)==0X02)    //读取参数
	{
		if(*(data_buf+4)==0X01)    //读取pid
		{
            _status.get_pid_group1 = 1;
            //ANO_DT_Send_PID(1, Motor_pid._kp, Motor_pid._ki, Motor_pid._kd, Servo_pid._kp, Servo_pid._ki, Servo_pid._kd, 0,0,0);
		}
		if(*(data_buf+4)==0X02)//读取飞行模式
		{
			
		}
		if(*(data_buf+4)==0XA0)//读取版本信息
		{
//			f.send_version = 1;
		}
		if(*(data_buf+4)==0XA1)	//恢复默认参数
		{
//			Para_ResetToFactorySetup();
		}
	}

	if(*(data_buf+2)==0X10)								//PID1      写入参数
    {
//        Motor_pid._kp  = 0.001*( (short)(*(data_buf+4)<<8)|*(data_buf+5) );   //上位机的ROW PID
//        Motor_pid._ki  = 0.001*( (short)(*(data_buf+6)<<8)|*(data_buf+7) );
//        Motor_pid._kd  = 0.001*( (short)(*(data_buf+8)<<8)|*(data_buf+9) );
//        Speed_pid._kp  = 0.001*( (short)(*(data_buf+10)<<8)|*(data_buf+11) ); //上位机的PITCH PID
//        Speed_pid._ki  = 0.001*( (short)(*(data_buf+12)<<8)|*(data_buf+13) );
//        Speed_pid._kd  = 0.001*( (short)(*(data_buf+14)<<8)|*(data_buf+15) );
//        Dir_pid._kp 	= 0.001*( (short)(*(data_buf+16)<<8)|*(data_buf+17) );
//        Dir_pid._ki 	= 0.001*( (short)(*(data_buf+18)<<8)|*(data_buf+19) );
//        Dir_pid._kd 	= 0.001*( (short)(*(data_buf+20)<<8)|*(data_buf+21) );
        ANO_DT_Send_Check(*(data_buf+2),sum);    //校验
    }
    if(*(data_buf+2)==0X11)								//PID2
    {
//        ctrl_1.PID[PID4].kp 	= 0.001*( (vs16)(*(data_buf+4)<<8)|*(data_buf+5) );
//        ctrl_1.PID[PID4].ki 	= 0.001*( (vs16)(*(data_buf+6)<<8)|*(data_buf+7) );
//        ctrl_1.PID[PID4].kd 	= 0.001*( (vs16)(*(data_buf+8)<<8)|*(data_buf+9) );
//        ctrl_1.PID[PID5].kp 	= 0.001*( (vs16)(*(data_buf+10)<<8)|*(data_buf+11) );
//        ctrl_1.PID[PID5].ki 	= 0.001*( (vs16)(*(data_buf+12)<<8)|*(data_buf+13) );
//        ctrl_1.PID[PID5].kd 	= 0.001*( (vs16)(*(data_buf+14)<<8)|*(data_buf+15) );
//        ctrl_1.PID[PID6].kp	  = 0.001*( (vs16)(*(data_buf+16)<<8)|*(data_buf+17) );
//        ctrl_1.PID[PID6].ki 	= 0.001*( (vs16)(*(data_buf+18)<<8)|*(data_buf+19) );
//        ctrl_1.PID[PID6].kd 	= 0.001*( (vs16)(*(data_buf+20)<<8)|*(data_buf+21) );
//        ANO_DT_Send_Check(*(data_buf+2),sum);
//				Param_SavePID();
    }
    if(*(data_buf+2)==0X12)								//PID3
    {	
//        ctrl_2.PID[PIDROLL].kp  = 0.001*( (vs16)(*(data_buf+4)<<8)|*(data_buf+5) );
//        ctrl_2.PID[PIDROLL].ki  = 0.001*( (vs16)(*(data_buf+6)<<8)|*(data_buf+7) );
//        ctrl_2.PID[PIDROLL].kd  = 0.001*( (vs16)(*(data_buf+8)<<8)|*(data_buf+9) );
//        ctrl_2.PID[PIDPITCH].kp = 0.001*( (vs16)(*(data_buf+10)<<8)|*(data_buf+11) );
//        ctrl_2.PID[PIDPITCH].ki = 0.001*( (vs16)(*(data_buf+12)<<8)|*(data_buf+13) );
//        ctrl_2.PID[PIDPITCH].kd = 0.001*( (vs16)(*(data_buf+14)<<8)|*(data_buf+15) );
//        ctrl_2.PID[PIDYAW].kp 	= 0.001*( (vs16)(*(data_buf+16)<<8)|*(data_buf+17) );
//        ctrl_2.PID[PIDYAW].ki 	= 0.001*( (vs16)(*(data_buf+18)<<8)|*(data_buf+19) );
//        ctrl_2.PID[PIDYAW].kd 	= 0.001*( (vs16)(*(data_buf+20)<<8)|*(data_buf+21) );
//        ANO_DT_Send_Check(*(data_buf+2),sum);
//				Param_SavePID();
    }
	if(*(data_buf+2)==0X13)								//PID4
	{
//		ANO_DT_Send_Check(*(data_buf+2),sum);
	}
	if(*(data_buf+2)==0X14)								//PID5
	{
//		ANO_DT_Send_Check(*(data_buf+2),sum);
	}
	if(*(data_buf+2)==0X15)								//PID6
	{
//		ANO_DT_Send_Check(*(data_buf+2),sum);
	}
}

void Test_ANO_DT(void)    
{
    float data1 = 0.0f;
    float data2 = 45.0f; 
    float data3 = 90.0f;   
    float data4 = 135.0f;   
    float data5 = 60.0f;
    const float PI = 3.1415926;
    LQ_UART_Init(LPUART1, 115200);       //串口1初始化 可以使用 printf函数    不使用DMA模式，请将宏定义#define USE_DMA  0
    while(1)
    {
        ANO_DT_send_int16((short)(sin(data1/180.0f * PI) * 100),
                          (short)(sin(data2/180.0f * PI) * 100),
                          (short)(sin(data3/180.0f * PI) * 100),
                          (short)(sin(data4/180.0f * PI) * 100), 
                          (short)(sin(data5/180.0f * PI) * 100), 
                          0, 
                          0,
                          0);   
        delayms(20);
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



