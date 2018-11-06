#pragma interrupt INTAD ADC_Isp

#include 	"control.h"
#include	"DataFlash.h"
#include	"Ddm.h"
#include	"Can_User.h"

ADC Signal;
WORD wResetTime = 0;
const WORD VOLTAGE_CRITIAL = (WORD)(((double)0.4 / (double)5)*(double)1024);
const WORD VOLTAGE_CRITIAL_MIN = (WORD)(((double)0.3 / (double)5)*(double)1024);
void    Ctl_PowerCtl_Init (void)
{
	WORD i;
	
	//
	
	PM8.1 = 0;
	PM8.4 = 0;
P8.4 = 0;P8.1 = 0;
	
	//
	
	
	PM8.0 = 1;	// ADC port
	P8.0 = 1;
	
	PM3.0 = 0;	// Power control
	P3.0 = 1;
	
	PM12.5 = 0;	// Communicaiton control
	P12.5 = 0;
	
	ADCEN = 1;            //ADC上电
	ADPC = 0x01;          //配置P80/ANI00为ANI00功能
	ADM0 = 0x44;          //选择通道模式
	ADCE = 1;             //转换等待模式
	ADTMD = 0;            //软件触发模式
	ADM1 = 0x00;
	ADS = 0x00;           //选择模拟通道ANI00
	ADSMP = 0x0F;         //选择转换时间
	for(i = 0; i < 2500; i ++);
	ADMK = 0;             //打开AD中断
  
	MODULE_POWEROFF;
  ///Power.SampleInterval = 1;  //10 ticks  
}

void Power_TriggerSample (void)
{
  ADCS = 1;
}

extern DTCStatusInfoType  DtcStatusInfo[NUMBER_OF_DTC];
BOOL    bDtcWriteFlag = FALSE;
DWORD   DtcFlagStatic = 0x12345678;
void    Ctl_WriteDataFlash (void)
{
	BYTE ret = 0;
	static BYTE blockIndex = 0;
	static WORD wStartIndex = 0;
	static WORD wLength = 1;
	static DWORD *pData = 0;
	if(Flash.Status)
	{
		switch (Flash.ProcStatus)
		{
			case PS_STATUS_COMPLETE:
				// Prepare data for operation
				if(Flash.Status == DF_STATUS_WRITE_DTC)
				{
					blockIndex = 0;
					wStartIndex = 0;
					wLength = sizeof(DtcStatusInfo)/4;
					pData = (DWORD*)DtcStatusInfo;
					bDtcWriteFlag = FALSE;
				}
				if(Flash.Status == DF_STATUS_WRITE_DID_F190)
				{
					blockIndex = 2;
					wStartIndex = DID_F190_INDEX;
					wLength = 5;
					pData = (DWORD*)VINDataIdentifier;
				}
				if(Flash.Status == DF_STATUS_WRITE_DID_F18C)
				{
					blockIndex = 1;
					wStartIndex = DID_F18C_INDEX;
					wLength = 4;
					pData = (DWORD*)ECUSerialNumberDataIdentifier;
				}
				Flash.ProcStatus = PS_STATUS_EREAE_FLASH;
			break;
			case PS_STATUS_EREAE_FLASH:
				ret = Data_Flash_Erease(blockIndex);
				if(ret == EREASE_END)
				{	
					// Erease complete
					Flash.ProcStatus = PS_STATUS_WRITE_DATA;
				}
			break;
			case PS_STATUS_WRITE_DATA:
				ret = Data_Flash_Write(wStartIndex,pData);
				if(ret == WRITE_END)
				{
					wLength --;
					if(wLength)
					{
						wStartIndex ++;
						pData ++;
					}
					else
					{
                                                if(Flash.Status == DF_STATUS_WRITE_DTC)
                                                {
                                                        if(bDtcWriteFlag == FALSE)
                                                        {
                                                                wStartIndex ++;
                                                                wLength ++;
                                                                pData = &DtcFlagStatic;
                                                                bDtcWriteFlag = TRUE;
                                                                return;
                                                        }
                                                }
						// All data write complete
						Flash.ProcStatus = PS_STATUS_COMPLETE;
						Flash.Status = DF_STATUS_IDLE;
					}
				}
			break;
		}
	}
}

void 	Ctl_EnableNetworkDiagnostic	(void)
{
    DDMSetDTCSwitch(DTC_LOST_COMMUNICATION_WITH_SAS_INDEX,DTC_SWITCH_ENABLE);
    DDMSetDTCSwitch(DTC_LOST_COMMUNICATION_WITH_ABS_INDEX,DTC_SWITCH_ENABLE);
    DDMSetDTCSwitch(DTC_LOST_COMMUNICATION_WITH_BCM_INDEX,DTC_SWITCH_ENABLE);
    DDMSetDTCSwitch(DTC_LOST_COMMUNICATION_WITH_MP5_INDEX,DTC_SWITCH_ENABLE);
    DDMSetDTCSwitch(DTC_BUSOFF_INDEX,DTC_SWITCH_ENABLE);
}
void 	Ctl_DisableNetworkDiagnostic	(void)
{
    DDMSetDTCSwitch(DTC_LOST_COMMUNICATION_WITH_SAS_INDEX,DTC_SWITCH_DISABLE);
    DDMSetDTCSwitch(DTC_LOST_COMMUNICATION_WITH_ABS_INDEX,DTC_SWITCH_DISABLE);
    DDMSetDTCSwitch(DTC_LOST_COMMUNICATION_WITH_BCM_INDEX,DTC_SWITCH_DISABLE);
    DDMSetDTCSwitch(DTC_LOST_COMMUNICATION_WITH_MP5_INDEX,DTC_SWITCH_DISABLE);
    //DDMSetDTCSwitch(DTC_BUSOFF_INDEX,DTC_SWITCH_DISABLE);
}

__interrupt void ADC_Isp (void)
{

	Signal.wSampleValue = (ADCR >> 6);
	if(Signal.bSystemReady == FALSE)
	{
		if(Signal.wSampleValue > VOLTAGE_CRITIAL)
		{
			Signal.CriticalCnt ++;

		}
		else
		{
			if(Signal.CriticalCnt)Signal.CriticalCnt --;

		}
		if(Signal.CriticalCnt > 10)
		{
			Signal.bSystemReady = TRUE;
			//Signal.DetFlag = FALSE;
			Signal.CriticalCnt = 0;
			//Signal.TimeCnt = 0;
		}
	}
	else
	{
		if(Signal.wSampleValue < VOLTAGE_CRITIAL_MIN)
		{
			Signal.CriticalCnt ++;
		}
		else
		{
			Signal.CriticalCnt = 0;
		}
	}
}