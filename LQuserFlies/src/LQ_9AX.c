#include "include.h"

/******************************************************************************
 * Code
 ******************************************************************************/



extern fxos_handle_t g_fxosHandle;
status_t FXOS_Init(fxos_handle_t *fxos_handle)
{
    uint8_t tmp[1] = {0};
    g_fxosHandle.xfer.slaveAddress = 0x1e;   //8700��ַ
    if(FXOS_ReadReg(fxos_handle, WHO_AM_I_REG, tmp, 1) != kStatus_Success) //��ȡWHO_AM_I �Ĵ���
    {
        return kStatus_Fail;
    }

    if (tmp[0] != kFXOS_WHO_AM_I_Device_ID)    //�ж� WHO_AM_I ��ֵ�Ƿ���ȷ
    {
        return kStatus_Fail;
    }

    /* setup auto sleep with FFMT trigger */
    /* go to standby */
    if(FXOS_ReadReg(fxos_handle, CTRL_REG1, tmp, 1) != kStatus_Success)  //��ȡCTRL_REG1�Ĵ���
    {
        return kStatus_Fail;
    }

    if(FXOS_WriteReg(fxos_handle, CTRL_REG1, tmp[0] & (uint8_t)~ACTIVE_MASK) != kStatus_Success)  //дCTRL_REG1�Ĵ�����ʹFX8700���ڴ���״̬ 
    {
        return kStatus_Fail;
    }

    /* Read again to make sure we are in standby mode. */
    if(FXOS_ReadReg(fxos_handle, CTRL_REG1, tmp, 1) != kStatus_Success)  //��һ�ζ���ȷ�����ڴ���״̬���Ա��������������Ĵ���
    {
        return kStatus_Fail;
    }
    if ((tmp[0] & ACTIVE_MASK) == ACTIVE_MASK)
    {
        return kStatus_Fail;
    }

    /* Disable the FIFO */
    if(FXOS_WriteReg(fxos_handle, F_SETUP_REG, F_MODE_DISABLED) != kStatus_Success)  //����FIFO
    {
        return kStatus_Fail;
    }

#ifdef LPSLEEP_HIRES
    /* enable auto-sleep, low power in sleep, high res in wake */
    if(FXOS_WriteReg(fxos_handle, CTRL_REG2, SLPE_MASK | SMOD_LOW_POWER | MOD_HIGH_RES) != kStatus_Success)  //ʹ�õ͹��ģ��Զ�˯�ߣ��߷ֱ�
    {
        return kStatus_Fail;
    }
#else
    /* enable auto-sleep, low power in sleep, high res in wake */
    if(FXOS_WriteReg(fxos_handle, CTRL_REG2, MOD_HIGH_RES) != kStatus_Success)  //ʹ�ø߷ֱ���ģʽ
    {
        return kStatus_Fail;
    }

#endif

    /* set up Mag OSR and Hybrid mode using M_CTRL_REG1, use default for Acc */
    if(FXOS_WriteReg(fxos_handle, M_CTRL_REG1, (M_RST_MASK | M_OSR_MASK | M_HMS_MASK)) != kStatus_Success)//���ģʽ���Ӽƺ͵شż�ͬʱʹ��
    {
        return kStatus_Fail;
    }

    /* Enable hyrid mode auto increment using M_CTRL_REG2 */
    if(FXOS_WriteReg(fxos_handle, M_CTRL_REG2, (M_HYB_AUTOINC_MASK)) != kStatus_Success)  //��hyb_autoinc_mode = 1�ҿ��ģʽ������(ctrl l_reg1 [f_read] = 0)ʱ���ڶ���Ĵ���x06 (OUT_Z_LSB)�󣬼Ĵ�����ַ���Զ�ǰ�����Ĵ���x33 (M_OUT_X_MSB)������hyb_autoinc_mode = 1�����ÿ��ٶ�ȡģʽ(ctrl l_reg1 [f_read = 1])����burstreadģʽ�¶�ȡ�Ĵ���x05 (OUT_Z_MSB)�󣬼Ĵ�����ַ���Զ�ǰ�����Ĵ���x33 (M_OUT_X_MSB)��
    {
        return kStatus_Fail;
    }

#ifdef EN_FFMT
    /* enable FFMT for motion detect for X and Y axes, latch enable */
    if(FXOS_WriteReg(fxos_handle, FF_MT_CFG_REG, XEFE_MASK | YEFE_MASK | ELE_MASK | OAE_MASK) != kStatus_Success)  //���������˶�/���üĴ���
    {
        return kStatus_Fail;
    }
#endif

#ifdef SET_THRESHOLD
    /* set threshold to about 0.25g */
    if(FXOS_WriteReg(fxos_handle, FT_MT_THS_REG, 0x04) != kStatus_Success)//��������/�˶������ֵ:Ĭ��ֵ:0b000_0000���ֱ��ʹ̶���63 mg/LSB��
    {
        return kStatus_Fail;
    }
#endif

#ifdef SET_DEBOUNCE
    /* set debounce to zero */
    if(FXOS_WriteReg(fxos_handle, FF_MT_COUNT_REG, 0x00) != kStatus_Success)
    {
        return kStatus_Fail;
    }
#endif

#ifdef EN_AUTO_SLEEP                
    /* set auto-sleep wait period to 5s (=5/0.64=~8) */
    if(FXOS_WriteReg(fxos_handle, ASLP_COUNT_REG, 8) != kStatus_Success)  //�Զ�˯��
    {
        return kStatus_Fail;
    }
#endif
    /* default set to 4g mode */
    if(FXOS_WriteReg(fxos_handle, XYZ_DATA_CFG_REG, FULL_SCALE_4G) != kStatus_Success)  //�Ӽ� ����4gģʽ
    {
        return kStatus_Fail;
    }
#ifdef EN_INTERRUPTS                        //ʹ���ж�
    /* enable data-ready, auto-sleep and motion detection interrupts */
    /* FXOS1_WriteRegister(CTRL_REG4, INT_EN_DRDY_MASK | INT_EN_ASLP_MASK | INT_EN_FF_MT_MASK); */
    if(FXOS_WriteReg(fxos_handle, CTRL_REG4, 0x0) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* route data-ready interrupts to INT1, others INT2 (default) */
    if(FXOS_WriteReg(fxos_handle, CTRL_REG5, INT_CFG_DRDY_MASK) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* enable ffmt as a wake-up source */
    if(FXOS_WriteReg(fxos_handle, CTRL_REG3, WAKE_FF_MT_MASK) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* finally activate accel_device with ASLP ODR=0.8Hz, ODR=100Hz, FSR=2g */
    if(FXOS_WriteReg(fxos_handle, CTRL_REG1, HYB_ASLP_RATE_0_8HZ | HYB_DATA_RATE_100HZ | ACTIVE_MASK) != kStatus_Success)
    {
        return kStatus_Fail;
    }
#else
    /* Setup the ODR for 200 Hz and activate the accelerometer */
    if(FXOS_WriteReg(fxos_handle, CTRL_REG1, (HYB_DATA_RATE_200HZ | ACTIVE_MASK)) != kStatus_Success)//�����������Ƶ�� 200hz ���Ҽ���FX8700
    {
        return kStatus_Fail;
    }
#endif

    /* Read Control register again to ensure we are in active mode */
    if(FXOS_ReadReg(fxos_handle, CTRL_REG1, tmp, 1) != kStatus_Success)  //ȷ��FX8700�����ڴ���״̬
    {
        return kStatus_Fail;
    }

    if ((tmp[0] & ACTIVE_MASK) != ACTIVE_MASK)
    {
        return kStatus_Fail;
    }

    return kStatus_Success;
}

status_t FXOS_ReadSensorData(fxos_handle_t *fxos_handle, fxos_data_t *sensorData)    //��FX8700ԭʼ���ݺ���
{
    g_fxosHandle.xfer.slaveAddress = 0x1e;   //8700��ַ
    status_t status = kStatus_Success;
    uint8_t tmp_buff[6] = {0};
    uint8_t i = 0;

    if (!FXOS_ReadReg(fxos_handle, OUT_X_MSB_REG, tmp_buff, 6) == kStatus_Success)  //��ȡ�Ӽ�����
    {
        status = kStatus_Fail;
    }

    for (i = 0; i < 6; i++)
    {
        ((int8_t *)sensorData)[i] = tmp_buff[i];                                     //�����ݴ��뻺����
    }

    if (!FXOS_ReadReg(fxos_handle, M_OUT_X_MSB_REG, tmp_buff, 6) == kStatus_Success) //��ȡ�شż�����
    {
        status = kStatus_Fail;
    }

    for (i = 0; i < 6; i++)
    {
        ((int8_t *)sensorData)[i + 6] = tmp_buff[i];                                  //�����ݴ��뻺����
    }

    return status;
}

status_t FXOS2100_ReadSensorData(fxos_handle_t *fxos_handle, fxos2100_data_t *sensorData)  //��FX2100ԭʼ����
{
    g_fxosHandle.xfer.slaveAddress = 0x20;   //2100��ַ
    status_t status = kStatus_Success;
    uint8_t tmp_buff[6] = {0};
    uint8_t i = 0;

    if (!FXOS_ReadReg(fxos_handle, OUT_X_MSB_REG, tmp_buff, 6) == kStatus_Success)      //��ȡ���ٶȼ�����
    {
        status = kStatus_Fail;
    }

    for (i = 0; i < 6; i++)
    {
        ((int8_t *)sensorData)[i] = tmp_buff[i];                                        //�����ݴ��뻺����
    } 
    return status;
}
status_t Init2100(fxos_handle_t *fxos_handle)                                           //���ٶȼƳ�ʼ��
{
    g_fxosHandle.xfer.slaveAddress = 0x20;   //2100��ַ
    if(FXOS_WriteReg(fxos_handle, 0x0d, 0x00) != kStatus_Success)  //дCTRL_REG1�Ĵ��� ���øߵ�ͨ�˲� �� ���� ��2000dps
    {
        return kStatus_Fail;
    }
    if(FXOS_WriteReg(fxos_handle, 0x13, 0x02) != kStatus_Success)  //дCTRL_REG1�Ĵ���  ���� �� ����������� 800Hz
    {
        return kStatus_Fail;
    }
    return kStatus_Success;
}


status_t FXOS_ReadReg(fxos_handle_t *handle, uint8_t reg, uint8_t *val, uint8_t bytesNumber)  //���Ĵ�������
{
    return IIC_ReadReg(handle, reg, val, bytesNumber);  //���Ĵ�������
}

status_t FXOS_WriteReg(fxos_handle_t *handle, uint8_t reg, uint8_t val)    //д�Ĵ�������
{
    return IIC_WriteReg(handle, reg, val);    //д�Ĵ�������
}
