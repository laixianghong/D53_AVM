#ifndef 	_TIMER_H_
#define		_TIMER_H_

#include 	"cpu.h"


void Timer00_10ms_Init (void);
__interrupt void Timer_Isp_10ms (void);

extern  BYTE	b10msFlag;
#endif