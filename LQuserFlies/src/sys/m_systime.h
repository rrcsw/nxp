
// Header:
// File Name: 
// Author: Z
// Date:2018/08/03

#ifndef __M_SYSTIME_H
#define __M_SYSTIME_H

#include "include.h"

typedef struct
{
		
	void (* init) (void);  
	uint64_t (* get_time_us) (void);
	uint32_t (* get_time_ms) (void);
	void (* delay_us)(uint64_t);//��ʱ1us ʵ��Ϊ1.23us   ��ʱ10us ʵ��Ϊ10.23us   ��ʱ100us ʵ��Ϊ100.23us
	void (* delay_ms)(uint32_t);

}systime_t;

extern systime_t  _systime;


#endif //__M_SYSTIME_H




