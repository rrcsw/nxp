// Header:
// File Name: 
// Author: Z
// Date:2018/08/03

#include "m_systime.h"

#define EACH_PER_MS    25   //ÿ�� 25 ms �ж�һ��  systick ��ʱ����24λ���¼����Ķ�ʱ��  ���װ��ֵ16777215 / 600 000 000= 0.2796 ����ʱ27ms

struct time{
	
    uint32_t fac_us;   //us��Ƶϵ��
	uint32_t fac_ms;   //ms��Ƶϵ��
	volatile uint32_t millisecond;   //ms
	uint64_t microsecond;   //us
	uint8_t ms_per_tick;         //1ms����systick��������
	
}timer;
void systime_init()
{
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	//ѡ��APBʱ��    600M Hz
	
	timer.fac_us = SystemCoreClock / 1000000;
	timer.fac_ms = SystemCoreClock / 1000;
	timer.ms_per_tick = EACH_PER_MS;
    timer.millisecond = 100;
	SysTick_Config((SystemCoreClock / 1000) * timer.ms_per_tick );   //����systick�ж�

}

void SysTick_Handler(void)
{
	timer.millisecond += timer.ms_per_tick;
}


uint32_t get_current_time_ms(void)
{
    uint32_t val = SysTick->VAL;
	return timer.millisecond -  val/timer.fac_ms;
}

uint64_t get_current_time_us(void)
{
    uint32_t val = SysTick->VAL;
	return (uint64_t)((timer.millisecond * 1000) -  val / timer.fac_us);
}

//��ʱ1us ʵ��Ϊ1.28us   ��ʱ10us ʵ��Ϊ10.27us   ��ʱ100us ʵ��Ϊ100.26us  ���Ҫʹ�ã�����ص��Ż�,����׼
void delay_us( uint64_t us)     
{
    uint32_t val = SysTick->VAL;
    int now = 1;
	uint64_t end_time = ( -val + ((uint64_t)timer.millisecond * 1000 + us) * timer.fac_us);
	while( now > 0)
    {
        val = SysTick->VAL;
        now = (int)(end_time - ( -val + ((uint64_t)timer.millisecond * 1000) * timer.fac_us)) ;
    }
}

void delay_ms( uint32_t ms) //���Ҫʹ�ã�����ص��Ż�
{
	delay_us(ms * 1000);
}

systime_t  _systime = 
{

	systime_init,
	get_current_time_us,
	get_current_time_ms,
	delay_us,
	delay_ms

};



