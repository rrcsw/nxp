/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1052���İ�-���ܳ���
����    д��Z
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2018��11��22��
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
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "Beacon_Smart_Car.h"




void Test_BeaconSmart_Car(void)
{
    BOARD_ConfigMPU();                   /* ��ʼ���ڴ汣����Ԫ */      
    BOARD_InitSDRAMPins();               /* SDRAM��ʼ�� */
    BOARD_BootClockRUN();                /* ��ʼ��������ʱ�� */           
    LED_Init();                          //��ʼ�����İ�Ϳ������ϵ�LED�ӿ�
    LQ_UART_Init(LPUART1, 115200);       //����1��ʼ�� ����ʹ�� printf����
    _systime.init();                     //����systick��ʱ��
    NVIC_SetPriorityGrouping(2);         /*�����ж����ȼ���  0: 0����ռ���ȼ�16λ�������ȼ�
                                          *1: 2����ռ���ȼ� 8�������ȼ� 2: 4����ռ���ȼ� 4�������ȼ� 
                                          *3: 8����ռ���ȼ� 2�������ȼ� 4: 16����ռ���ȼ� 0�������ȼ�
                                          */
    
    LQ_PXP_Init();                       //ͼ�����ʼ��
    LQ_Camera_Init();                    //����ͷ��ʼ��
    
    LQ_TFT480_272_Init();                //������ʼ��
    GT9147_Init();                       //��ʼ��������
    
    while(1)
    {
        LQ_Get_CameraBuff();    //�õ�ԭʼ����

    
    }

}

































