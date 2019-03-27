/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�RT1052���İ�
����    д��Z
����    ע��
������汾��V1.0
�������¡�2018��12��17��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
���������䡿chiusir@163.com
----------------------------------------------------------------
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"
/* Select USB1 PLL (480 MHz) as master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for master lpi2c clock source */
#define LPI2C_CLOCK_SOURCE_DIVIDER (5U)
/* Get frequency of lpi2c clock */
#define LPI2C_CLOCK_FREQUENCY ((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (LPI2C_CLOCK_SOURCE_DIVIDER + 1U))

/*
# ���������ϵ� �첽IO ��˵�ں�ֱ�ӽ����ݿ������û�̬���ڴ浥Ԫ����֪ͨ����ֱ��ȥ��ȡ���ݡ�
# select / poll / epoll ����ͬ��IO�Ķ�·����ģʽ

# 1.ͬ�����첽
# ͬ�����첽��ע������Ϣͨ�Ż���
# ��νͬ���������ڷ���һ��*����*ʱ��û�õ����֮ǰ����*����*�Ͳ����ء�����һ�����÷��ؾ͵õ�����ֵ�ˣ�*������*�����ȴ����*����*�Ľ��
# ��ν�첽�������ڷ���һ��*����*ʱ�����*����*��ֱ�ӷ����ˣ����ܷ�����û�н������һ���첽���̵��÷�����*��������*ͨ��״̬��֪ͨ��֪ͨ*������*������ͨ���ص����������������

# 2.�����ͷ�����
# �����ͷ�������ע���ǳ����ڵȴ����ý��ʱ��״̬
# ����������ָ���ý������֮ǰ����ǰ�̻߳ᱻ���𡣵����߳�ֻ���ڵõ����֮��ŷ���
# ������������ָ�ڲ��������õ����֮ǰ���õ��ò���������ǰ�߳�

# �����ϵ�����
#���Ű��Ȳ裬�ϻ���˵����ˮ��
#����������ţ�ˮ�����ѣ���ͨˮ�������ˮ���������ˮ���������ˮ������
#1 ���Ű�ˮ���ŵ����ϣ�����ˮ������ͬ�������������Ⱦ�������������ȥ�ɱ���£����ŵ�һֱ�����Ŀ���ˮ��û�������ͬ��
#2 ���Ű�ˮ���ŵ����ϣ�ȥ���������ӣ�ʱ��ʱȥ��������ˮ��û�С���ͬ����������������ȥ�������ˣ�����Ƿ������ˣ��������Ż��ǵù�ע��ˮ��û����Ҳ����ͬ����
#3 ���Ű���ˮ���ŵ����ϣ�����ˮ�������첽�����������Ⱦ�������������ȥ�ɱ���£��������Ų���ʱ�̹�עˮ��û����Ϊˮ���ˣ���ˮ������������������첽��
#4 ���Ű���ˮ���ŵ����ϣ�ȥ���������ӣ�ˮ����֮ǰ����ȥ�����ˣ�������ȥ�ú������첽��������������ȥ�������ˣ�����Ƿ������ˣ����ң���ˮ���ˣ���ˮ������������������첽��
#��νͬ���첽��ֻ�Ƕ���ˮ�����ԡ���ͨˮ����ͬ������ˮ�����첽����Ӧ��Ҳ������Ϣͨ�Ż���
#��Ȼ���ܸɻ����ˮ���������Լ��깤֮����ʾ����ˮ���ˡ�������ͨˮ�������ܼ��ġ�ͬ��ֻ���õ�����ȥ��ѯ�Լ������2�У����������Ч�ʵĵ��¡�
#��ν�����������������������Ŷ��ԡ����ȵ����ţ���������Ӧ��Ҳ���ǳ���ȴ����ʱ��״̬
#�����ӵ����ţ���������
#���1�����3�����ž��������ģ�ϱ����������֪������Ȼ3����ˮ�����첽�ģ��ɶ������ȵ�����û��̫������塣����һ���첽����Ϸ�����ʹ�õģ��������ܷ����첽��Ч�á�
*/

//IIC1   SCLk    J11
//IIC1   SDA     K11

#ifndef  IICBlocking   //IIC�Ƕ���ģʽ

lpi2c_master_handle_t g_MasterHandle;  
fxos_handle_t g_fxosHandle;    //��ȡ��ַ����



volatile static bool g_completionFlag = false;
volatile static bool g_nakFlag = false;

//IIC�ص�����
void IIC_master_callback(LPI2C_Type *base, lpi2c_master_handle_t *handle, status_t status, void *userData)   //I2C�ص�����
{
    /* Signal transfer success when received success status. */
    if (status == kStatus_Success)       //�źŴ���ɹ�
    {
        g_completionFlag = true;
    }
    /* Signal transfer success when received success status. */
    if (status == kStatus_LPI2C_Nak)   
    {
        g_nakFlag = true;
    }
}


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����IIC��ʼ������
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ��base��LPI2C1~ LPI2C4   baudrate:IIC������
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LPI2C_Init(LPI2C_Type *base, uint32_t baudrate)
{ 
    
    lpi2c_master_config_t i2cConfig;  //I2C(����)���ýṹ��
    uint32_t i2cSourceClock;    //I2C   ʱ��
    
    BOARD_InitLPI2C1Pins();      //I2C1  ���Ÿ�������   ʹ�ñ��IIC ��Ҫ�����޸�����
    
    /*Clock setting for LPI2C*/
    CLOCK_SetMux(kCLOCK_Lpi2cMux, LPI2C_CLOCK_SOURCE_SELECT); //USB1 PLL (480 MHz) as master lpi2c clock source  480/8 = 60 MHz
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, LPI2C_CLOCK_SOURCE_DIVIDER);// 60 / 6 = 10MHz

    i2cSourceClock = LPI2C_CLOCK_FREQUENCY;                   //  10M
    /*
     * i2cConfig.debugEnable = false;
     * i2cConfig.ignoreAck = false;
     * i2cConfig.pinConfig = kLPI2C_2PinOpenDrain;
     * i2cConfig.baudRate_Hz = 100000U;
     * i2cConfig.busIdleTimeout_ns = 0;
     * i2cConfig.pinLowTimeout_ns = 0;
     * i2cConfig.sdaGlitchFilterWidth_ns = 0;
     * i2cConfig.sclGlitchFilterWidth_ns = 0;
     */
    i2cConfig.baudRate_Hz = baudrate;
    LPI2C_MasterGetDefaultConfig(&i2cConfig);                //�õ�Ĭ�Ͻṹ��
    
    LPI2C_MasterInit(base, &i2cConfig, i2cSourceClock);//��Ĭ������

    LPI2C_MasterTransferCreateHandle(base, &g_MasterHandle, IIC_master_callback, NULL);  //ʹ��IIC����������
    
    g_fxosHandle.base = base;
    g_fxosHandle.i2cHandle = &g_MasterHandle;
}
//iic ���Ĵ���
status_t IIC_ReadReg(fxos_handle_t *handle, uint8_t reg, uint8_t *val, uint8_t bytesNumber)  //���Ĵ�������
{
    status_t status = kStatus_Success;

    /* Configure I2C xfer */
    handle->xfer.subaddress = (uint32_t)reg;              //�Ĵ�����ַ
    handle->xfer.subaddressSize = 1U;                     //��8λ��
    handle->xfer.data = val;                              //��Ŷ���������
    handle->xfer.dataSize = bytesNumber;                  //Ҫ�����ٸ�����
    handle->xfer.direction = kLPI2C_Read;                 //I2C��ģʽ
    handle->xfer.flags = kLPI2C_TransferDefaultFlag;

    if(LPI2C_MasterTransferNonBlocking(handle->base, handle->i2cHandle, &handle->xfer) == kStatus_Fail) 
    {
        return kStatus_Fail;
    }
    /*  wait for transfer completed. */
    while ((!g_nakFlag) && (!g_completionFlag))//�ȴ��������  �൱���첽����   ���Բ��ȴ������
    {
    }

    g_nakFlag = false;

    if (g_completionFlag == true)
    {
        g_completionFlag = false;
    }
    else
    {
        status = kStatus_Fail;
    }


    return status;
}
//iic д�Ĵ���
status_t IIC_WriteReg(fxos_handle_t *handle, uint8_t reg, uint8_t val)    //д�Ĵ�������
{
    status_t status = kStatus_Success;
    uint8_t buff[1];

    buff[0] = val;
    /* Set I2C xfer structure */
    handle->xfer.subaddress = (uint32_t)reg;      //�Ĵ�����ַ
    handle->xfer.subaddressSize = 1U;             //��8λ��
    handle->xfer.data = buff;                     //���Ҫд�������
    handle->xfer.dataSize = 1;          //Ҫ�����ٸ�����                                            
    handle->xfer.direction = kLPI2C_Write;        //I2C��ģʽ
    handle->xfer.flags = kLPI2C_TransferDefaultFlag;


    if(LPI2C_MasterTransferNonBlocking(handle->base, handle->i2cHandle, &handle->xfer) == kStatus_Fail)
    {
        return kStatus_Fail;
    }

    /*  wait for transfer completed. */
    while ((!g_nakFlag) && (!g_completionFlag))   //�ȴ��������
    {
    }

    g_nakFlag = false;

    if (g_completionFlag == true)
    {
        g_completionFlag = false;
    }
    else
    {
        status = kStatus_Fail;
    }
    return status;
}


#else  //iic ����ģʽ

lpi2c_master_transfer_t master_transfer; //����ṹ��
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����IIC��ʼ������
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ��base��LPI2C1~ LPI2C4   baudrate:IIC������
��ʵ���� 
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LPI2C_Init(LPI2C_Type *base, uint32_t baudrate)
{ 
    
    lpi2c_master_config_t i2cConfig;  //I2C1(����)���ýṹ��
    uint32_t i2cSourceClock;    //I2C   ʱ��
    
    BOARD_InitLPI2C1Pins();      //I2C  ���Ÿ�������   ʹ�ñ��IIC ��Ҫ�����޸�����
    
    /*Clock setting for LPI2C*/
    CLOCK_SetMux(kCLOCK_Lpi2cMux, LPI2C_CLOCK_SOURCE_SELECT); //USB1 PLL (480 MHz) as master lpi2c clock source  480/8 = 60 MHz
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, LPI2C_CLOCK_SOURCE_DIVIDER);// 60 / 6 = 10MHz

    i2cSourceClock = LPI2C_CLOCK_FREQUENCY;                   //  10M
    /*
     * i2cConfig.debugEnable = false;
     * i2cConfig.ignoreAck = false;
     * i2cConfig.pinConfig = kLPI2C_2PinOpenDrain;
     * i2cConfig.baudRate_Hz = 100000U;
     * i2cConfig.busIdleTimeout_ns = 0;
     * i2cConfig.pinLowTimeout_ns = 0;
     * i2cConfig.sdaGlitchFilterWidth_ns = 0;
     * i2cConfig.sclGlitchFilterWidth_ns = 0;
     */
    i2cConfig.baudRate_Hz = baudrate;
    LPI2C_MasterGetDefaultConfig(&i2cConfig);                //�õ�Ĭ�Ͻṹ��
    
    LPI2C_MasterInit(base, &i2cConfig, i2cSourceClock);//��Ĭ������

}
//iic ���Ĵ���
status_t IIC_ReadReg(uint16_t addr, uint8_t reg, uint8_t *val, uint8_t bytesNumber)  //���Ĵ�������
{
    status_t status = kStatus_Success;
    
    /* Configure I2C xfer */
    master_transfer.slaveAddress = addr;
    master_transfer.subaddress = (uint32_t)reg;              //�Ĵ�����ַ
    master_transfer.subaddressSize = 1U;                     //��8λ��
    master_transfer.data = val;                              //��Ŷ���������
    master_transfer.dataSize = bytesNumber;                  //Ҫ�����ٸ�����
    master_transfer.direction = kLPI2C_Read;                 //I2C��ģʽ
    master_transfer.flags = kLPI2C_TransferDefaultFlag;

    if(LPI2C_MasterTransferBlocking(LPI2C1,&master_transfer)==kStatus_Fail)
    {
        return kStatus_Fail;
    }
    return status;
}
//iic д�Ĵ���
status_t IIC_WriteReg(uint16_t addr, uint8_t reg, uint8_t val)    //д�Ĵ�������
{
    status_t status = kStatus_Success;
    uint8_t buff[1];

    buff[0] = val;
    /* Set I2C xfer structure */
    master_transfer.slaveAddress = addr;
    master_transfer.subaddress = (uint32_t)reg;              //�Ĵ�����ַ
    master_transfer.subaddressSize = 1U;                     //��8λ��
    master_transfer.data = buff;                              //Ҫд�������
    master_transfer.direction = kLPI2C_Write;                 //I2Cдģʽ
    master_transfer.flags = kLPI2C_TransferDefaultFlag;

    if(LPI2C_MasterTransferBlocking(LPI2C1,&master_transfer)==kStatus_Fail)
    {
        return kStatus_Fail;
    }
    return status;
}


#endif