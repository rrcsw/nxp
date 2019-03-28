/**
  *
  * @file    system.c
  * @author  
  * @version 
  * @date    2019/3/7
  * @brief   GPT��ʱ��������ʱ�Ͷ�ʱ
  *
  */
#include "system.h"



volatile bool gptIsrFlag = false;
void GPT2_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    GPT_ClearStatusFlags(GPT2, kGPT_OutputCompare1Flag);
    gptIsrFlag = true;
/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F, Cortex-M7, Cortex-M7F Store immediate overlapping
  exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U || __CORTEX_M == 7U)
    __DSB();
#endif
}


// ��ʼ��GPT������  GPT1�ü�ʱ  GPT2������ʱ
void LQ_GPT_Init(void)
{
    gpt_config_t gptConfig;
    /*Clock setting for GPT 150M*/
    CLOCK_SetMux(kCLOCK_PerclkMux, 0);
    CLOCK_SetDiv(kCLOCK_PerclkDiv, 0);
    
    GPT_GetDefaultConfig(&gptConfig);
    gptConfig.enableRunInDbg = true;   //����debug����¿���ʹ��
    GPT_Init(GPT1, &gptConfig);
    GPT_Init(GPT2, &gptConfig);
    
    GPT_SetClockDivider(GPT1, 150);      // GPT ʱ�� 150M / 15 = 10M
    GPT_SetClockDivider(GPT2, 15);      // GPT ʱ�� 150M / 150 = 10M
    
    GPT_SetOutputCompareValue(GPT1, kGPT_OutputCompare_Channel1, 0XFFFFFFFF);   //GPT ��32Ϊ������ ��� 0xFFFF FFFF 
    GPT_SetOutputCompareValue(GPT2, kGPT_OutputCompare_Channel1, 0XFFFFFFFF);   //GPT ��32Ϊ������ ��� 0xFFFF FFFF 

}

/*
����GPI��ʱ�жϹ���
*/
void Test_GPT_Timer(void)
{
    LQ_GPT_Init();
    printf("GPT1 : %d \n", GPT_GetClockSource(GPT1));
    printf("GPT2 : %d \n", GPT_GetClockSource(GPT2));
    uint32_t time = 0, last_time = 0;
    gpt_time_start();
    while(1)
    {
        delayus(10);
        GPIO_PinReverse (GPIO2, 22); 
        time = gpt_time_get();
        printf("delay 10 us is %u \n", time - last_time);
        last_time = gpt_time_get(); //ע�� ��ӡҲ��Ҫʱ��
        delayms(10);
        time = gpt_time_get();
        printf("delay 10 ms is %u \n", time - last_time);
        last_time = gpt_time_get(); //ע�� ��ӡҲ��Ҫʱ��
    }
}

/*GPT ��������ʱ*/
void delayms(uint32_t ms)
{
    delayus(ms * 1000);
}

/*GPT ��������ʱ*/
void delayus(uint32_t us)
{
    /* Start Timer */
    GPT_StartTimer(GPT2);
    uint32_t time = us * 10 - 7;
    while(GPT_GetCurrentTimerCount(GPT2) < time);
    
    GPT_StopTimer(GPT2);
}

/*GPT ��������ʼ��ʱ*/
void gpt_time_start(void)
{
    GPT_StopTimer(GPT1);
    GPT_StartTimer(GPT1);   //ˢ�� GPT1
    GPT_StartTimer(GPT1);
}

/*GPT �������õ�ʱ�� us
*/
uint32_t gpt_time_get(void)
{
    if(GPT_GetStatusFlags(GPT1, kGPT_RollOverFlag))   //���
        return 0;
    else
        return GPT_GetCurrentTimerCount(GPT1) - 1;
}