#ifndef		_CONTROL_H_
#define		_CONTROL_H_
#include	"cpu.h"

#define		MODULE_POWEROFF		{P3.0 = 0;}
#define		MODULE_POWERON		{PM3.0 = 0;P3.0 = 1;}

#define		MODULE_ENABLE_COMMUNICAITON	{P12.5 = 1;}
#define		MODULE_DISABLE_COMMUNICAITON	{P12.5 = 0;}

typedef struct Tag_ADC
{
  BOOL    VoltageNormal;
  BYTE   ErrLvlCounter;
  BYTE   SampleInterval;  
  WORD   wSampleValue;
  DWORD  SampleTimes;
  
  BOOL   bSystemReady;
  BOOL   DetFlag;
  WORD   TimeCnt;
  WORD	 CriticalCnt;
}ADC;

extern ADC Signal;
extern WORD wResetTime;

void    Ctl_PowerCtl_Init (void);
void 	Power_TriggerSample (void);
void    Ctl_WriteDataFlash (void);
void 	Ctl_EnableNetworkDiagnostic	(void);
void 	Ctl_DisableNetworkDiagnostic	(void);
#endif