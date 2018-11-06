#include "cpu.h"
#include "uart.h"
#include "Stack.h"
#include "timer.h"
#include "..\FDL\fdl.h"
#include "..\FDL\fdl_descriptor.h"
#include "..\FDL\fdl_types.h"
#include "DataFlash.h"

#include "Can.h"
#include "CanIf.h"
#include "Com.h"
#include "CanTp.h"
#include "Dcm.h"
#include "Nm.h"
#include "control.h"
#include "App.h"
#include "Event.h"
#include "Ddm.h"
void delay (void)
{
	WORD i;
	for(i = 0; i < 10000; i++);
}

void Can_PortInit(void)
{
    STSEL |= 0x80;
    P1 |= 0x0001;
    PM1 &= 0xfe;
    //P1.5 = 0;
    //PM1.5 = 0;
    P1.2 &= 0;
    PM1.2 &= 0;
}

void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    PM1.2 = 0;
    P1.2 = 0;
    EI();
    /* End user code. Do not edit comment generated here */
}

void Can_HardwareInit (void)
{
    C0TRXMK = 0;
    C0RECMK = 0;
    C0WUPMK = 0;
    C0ERRMK = 0;
    
    IndirNm_Init();
    (void)IndirNm_StartUp();
    
    R_MAIN_UserInit();
}

void main (void)
{
	BYTE i;
	Cpu_FeedDog();
	MODULE_POWERON;
 	Cpu_InitTheSystemClock();
	Uart_Init();
	DataFlash_Init();
	Stack_Init ();
	Event_Init();
	Can_HardwareInit();
	Timer00_10ms_Init();
	App_AVM_StatusInit();
	DDMInit();
        DDMSetOperationMode(DDM_STARTCYCLE);
	Ctl_DisableNetworkDiagnostic();
	while(1)
	{
		if(b10msFlag)
		{
			static	WORD	cnt = 0;

			b10msFlag = FALSE;	
			cnt ++;
			if(cnt%5 == 0)
			{
				SetTxFlag(AVM_RECEIVE_ALL_FLAG);
				TxStat.bTickFlag = TRUE;
			}
			Stack_Can_Task ();
			App_OtherTask();
			Ctl_WriteDataFlash();
			Cpu_FeedDog();
		}	
		Stack_Uart_Task ();
	}
}
