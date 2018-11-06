#pragma interrupt INTTM00 Timer_Isp_10ms

#include "Timer.h"
#include "control.h"
#include "Stack.h"
BYTE	b10msFlag;
void Timer00_10ms_Init (void)
{
	TAU0EN = ENABLE;
	TPS0 = 0x0005;		// CK00 , Frequency divided by 32, Frequency = 16/32 = 0.5Mhz
	TMR00 = 0x0000;         // Interval timer mode
	TDR00 = 5000;		// 100ms period
	TMMK00 = 0;
	TS0 |= 0x01;
}

__interrupt void Timer_Isp_10ms (void)
{
	b10msFlag = TRUE;	
//	if(Signal.DetFlag)
//	{
//		if(Signal.TimeCnt == 1) // Close module power
//		{
//			MODULE_POWEROFF;
//		}	
//		if(Signal.TimeCnt == 100) // supplu module power
//		{
//			MODULE_POWERON;
//				//P8.1 = 1;
//				//Signal.DetFlag = FALSE;
//		}
//		//if(Signal.TimeCnt == 101)
//		//{
//				//P8.4 = 1;
//		//}
//		if(Signal.TimeCnt == 300) // enable communication
//		{
//			MODULE_ENABLE_COMMUNICAITON;
//			Signal.DetFlag = TRUE;
//		}
//		//if(Signal.TimeCnt > 300)
//		{
//			Power_TriggerSample();
//		}
//		if(Signal.TimeCnt > 650)  // 8 second passed,but faild
//		{
//			if(Signal.bSystemReady == 0)   // start faild
//			{
//				//Signal.TimeCnt = 0;
//				MODULE_DISABLE_COMMUNICAITON;
//				//Signal.DetFlag = FALSE;
//				Signal.TimeCnt = 0;
//				MODULE_POWEROFF;///test
//				Signal.CriticalCnt = 0;
//			}
//		}
//		if(Signal.TimeCnt == 1000)
//		{
//			if(Signal.CriticalCnt >= 90)
//			{
//				MODULE_DISABLE_COMMUNICAITON;
//				//Signal.DetFlag = FALSE;
//				Signal.TimeCnt = 0;
//				MODULE_POWEROFF;///test
//				Signal.CriticalCnt = 0;
//				Signal.bSystemReady = FALSE;
//			}
//			else
//			{
//				Signal.DetFlag = FALSE;
//			}
//		}
//		Signal.TimeCnt ++;
//	}	
}