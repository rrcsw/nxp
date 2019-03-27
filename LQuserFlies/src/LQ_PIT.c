/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1052���İ�-���ܳ���
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2018��2��1��
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
#include "include.h"

volatile uint16_t pitIsrCnt0 = 0;   //�����õ�  volatile�ױ�ģ����ж������ı�ı�������ʱ��ü��ϣ����߱�������Ҫ�Ż���ÿ�ζ�ȡ���Ӹñ����ĵ�ַ��ȡ
volatile uint16_t pitIsrCnt1 = 0;  //�����õ�  volatile�ױ�ģ����ж������ı�ı�������ʱ��ü��ϣ����߱�������Ҫ�Ż���ÿ�ζ�ȡ���Ӹñ����ĵ�ַ��ȡ
volatile uint16_t pitIsrCnt2 = 0;  //�����õ�  volatile�ױ�ģ����ж������ı�ı�������ʱ��ü��ϣ����߱�������Ҫ�Ż���ÿ�ζ�ȡ���Ӹñ����ĵ�ַ��ȡ
volatile uint16_t pitIsrCnt3 = 0; //�����õ�  volatile�ױ�ģ����ж������ı�ı�������ʱ��ü��ϣ����߱�������Ҫ�Ż���ÿ�ζ�ȡ���Ӹñ����ĵ�ַ��ȡ

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵����PIT�жϷ�����
������汾��V1.0
�������¡�2018��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void PIT_IRQHandler(void)
{
    
    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_0)&kPIT_TimerFlag)==kPIT_TimerFlag)
    {
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);    /* Clear interrupt flag.*/
        /*�û���������Ӵ���*/     
        pitIsrCnt0++;
//        LED_Ctrl(LED0, RVS);
    }
    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_1)&kPIT_TimerFlag)==kPIT_TimerFlag)
    {
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_1, kPIT_TimerFlag);    /* Clear interrupt flag.*/
        /*�û���������Ӵ���*/
        pitIsrCnt1++;
    }
    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_2)&kPIT_TimerFlag)==kPIT_TimerFlag)
    {
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_2, kPIT_TimerFlag);    /* Clear interrupt flag.*/
        /*�û���������Ӵ���*/        
        pitIsrCnt2++;
    }
    if((PIT_GetStatusFlags(PIT,kPIT_Chnl_3)&kPIT_TimerFlag)==kPIT_TimerFlag)
    {
        PIT_ClearStatusFlags(PIT, kPIT_Chnl_3, kPIT_TimerFlag);    /* Clear interrupt flag.*/
        /*�û���������Ӵ���*/        
        pitIsrCnt3++;
    }
    
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵��������PIT��ʱ�ж�
������汾��V1.0
�������¡�2018��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_PIT(void)
{ 
    LQ_PIT_Init(kPIT_Chnl_2, 1000000);    //1000 000us һ���ж�
    LQ_PIT_Init(kPIT_Chnl_3, 2000000);    //2000 000us һ���ж�
    while (true)
    {
        /* Check whether occur interupt and toggle LED */
         if (pitIsrCnt2)
        {
            printf("\r\n PITͨ��2�ж��ѷ���!");
            LED_Color(red);   //�̵� 
            pitIsrCnt2=0;
        }
         if (pitIsrCnt3)
        {
            printf("\r\n PITͨ��3�ж��ѷ���!");
            LED_Color(blue);   //���� 
            pitIsrCnt3=0;
        }
    }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵����PIT��ʱ�жϳ�ʼ��
������汾��V1.0
�������¡�2018��11��24�� 
����������
������ֵ����
������ֵ����    LQ_PIT_Init(kPIT_Chnl_0, 100000);  //����ͨ��0��ʱ���жϣ�ÿ100000us�ж�һ��
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LQ_PIT_Init(pit_chnl_t channel, uint32_t count)
{
     /* PIT��ʼ���ṹ�� */
    pit_config_t pitConfig;  
    
    /* Set PERCLK_CLK source to OSC_CLK*/
    CLOCK_SetMux(kCLOCK_PerclkMux, 1U);
    /* Set PERCLK_CLK divider to 1 */
    CLOCK_SetDiv(kCLOCK_PerclkDiv, 0U);

    /*
     * pitConfig.enableRunInDebug = false;  //Ĭ�ϲ���
     */
    PIT_GetDefaultConfig(&pitConfig);   //�õ�PITĬ�ϲ���

    /* Init pit module */
    PIT_Init(PIT, &pitConfig);    //��ʼ��PIT

    /* Set timer period for channel  */
    PIT_SetTimerPeriod(PIT, channel, USEC_TO_COUNT(count, CLOCK_GetFreq(kCLOCK_OscClk))); //����PITͨ���Ͷ�ʱʱ��

    /* Enable timer interrupts for channel  */
    PIT_EnableInterrupts(PIT, channel, kPIT_TimerInterruptEnable);  //ʹ��ͨ���ж�

    //���ȼ����� ��ռ���ȼ�0  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
    NVIC_SetPriority(PIT_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,2));
    
    /* Enable at the NVIC */
    EnableIRQ(PIT_IRQn);   //ʹ���ж�

    /* Start channel  */
    PRINTF("\r\nStarting channel ...");
    
    PIT_StartTimer(PIT, channel);   //������ʱ��

}

