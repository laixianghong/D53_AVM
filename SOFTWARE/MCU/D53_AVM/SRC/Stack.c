#include "Stack.h"
#include "Can_User.h"

//#include "common.h"
#include "Can.h"
#include "CanIf.h"
#include "Com.h"
//#include "OsekNm.h"
#include "CanTp.h"
#include "Dcm.h"
#include "Nm.h"
#include "App.h"
#include "DdmCfg.h"
#include "Ddm.h"
const	CALLBACK CbkTable[256] = 
{
	Cbk_NULL,Cbk_NULL,Cbk_FRM2_CALI_RES,Cbk_NULL,Cbk_NULL,Cbk_FRM5_SYNC,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,
	FILL(Cbk_NULL),
	FILL(Cbk_NULL),
	FILL(Cbk_NULL),
	FILL(Cbk_NULL),
	FILL(Cbk_NULL),
	FILL(Cbk_NULL),
	FILL(Cbk_NULL),
	FILL(Cbk_NULL),
	FILL(Cbk_NULL),
	FILL(Cbk_NULL),
	FILL(Cbk_NULL),
	FILL(Cbk_NULL),
	FILL(Cbk_NULL),
	FILL(Cbk_NULL),
	Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_NULL,Cbk_FRM_ACK,
};

FRM Frm_Reset;
volatile   BYTE	 Buffer[BUFFER_SIZE];
volatile   TX_STAT  TxStat;
volatile   FRM	 FrmTx;
volatile   FRM	 FrmRx;

volatile   BYTE	 TxBuffer[MAX_DATA_SIZE + 4];
volatile   FRM	 Frm_RRM060;
//FRM   Frm_Reset;
volatile   FRM	 Frm_AVM_391;
volatile   FRM   Frm_AVM_RECEIVE_ALL;
	   FRM   FRM1_CALI_REQ;

volatile   FRM   Frm_ACK;
	   FRM   Frm_Version_Disp;
BOOL    ValidData = FALSE;

WORD	Steering_angle;

void Stack_Init (void)
{
	//Can_App_Signal_Init();
	AVM.bStarting = TRUE;
	TxStat.Indicator = FALSE;
	TxStat.CurByteFlag = TRUE;
	TxStat.CurTransmitPos = 0;
	FrmTx.Code = FRM_ACK;
	FrmTx.Length = 0;
	
	Frm_Version_Disp.Code = 0x14;
	Frm_Version_Disp.Length = 1;
	Frm_Version_Disp.Data[0] = 5;
	// Frame init
	Frm_ACK.Code = FRM_ACK;		// ACK frame
	Frm_ACK.Length = 2;
	Frm_ACK.Data[0] = 0x00;
	
	Frm_AVM_RECEIVE_ALL.Code = FRM_AVM_ALL;
	Frm_AVM_RECEIVE_ALL.Data[0] = 90;
	Frm_AVM_RECEIVE_ALL.Data[1] = 90;
	Frm_AVM_RECEIVE_ALL.Data[2] = 0x58 + 4;
        Frm_AVM_RECEIVE_ALL.Data[3] = 0x00;
	Frm_AVM_RECEIVE_ALL.Length = 5;

	FRM1_CALI_REQ.Code = 1;
	FRM1_CALI_REQ.Length = 9;
	FRM1_CALI_REQ.Data[0] = 0x55;
	FRM1_CALI_REQ.Data[1] = 0xAA;
	FRM1_CALI_REQ.Data[2] = 0xAA;
	FRM1_CALI_REQ.Data[3] = 0x55;
	FRM1_CALI_REQ.Data[7] = 2;
	
	Frm_Reset.Code = FRM_RESET; 
	Frm_Reset.Length = 2;
}

void Stack_Can_Task (void)
{
    Com_MainFunctionRx();
    Com_MainFunctionTx();
    Dcm_MainFunction();  
    CanTp_MainFunction();
    IndirNm_MainTask();
           // DDM_MainTask();
}

void Stack_Uart_Task (void)
{
	Stack_RxHandler ();
	Stack_TxHandler ();
}

void Stack_ClrTheFrame (BYTE pos,BYTE nLength)
{
	BYTE i;
	for(i = 0; i < (nLength + 5);i ++)
	{
		Buffer[POS(i)] = 0x00;
	}
}

void Stack_TransmitFrame (FRM* frm)
{
	if(TxStat.Indicator == FALSE)         // If it is the first time call this function
	{
		TxStat.CurTransmitPos = 0;
		TxStat.CurByteFlag = TRUE;
		TxStat.Indicator = TRUE;
	}
	if(TxStat.CurTransmitPos)
	{
		if(TxStat.CurTransmitPos < (frm->Length + 5))
		{
			UF0TX = TxBuffer[TxStat.CurTransmitPos];        // Transmit other data
		}
		else							// All data has been transmitted
		{
			TxStat.CurTransmitPos = 0;
			TxStat.CurByteFlag = TRUE;
			TxStat.Indicator = FALSE;			// There is no data need to be transmitted
			return;
		}
	}
	else
	{
		BYTE i;
		BYTE len = frm->Length;
		BYTE sum = 0;
		FrmTx =   *frm;
		TxBuffer[0] = FRAME_HEADER;				// Transmit first data
		TxBuffer[1] = len;
		TxBuffer[2] = frm->Code;
		sum = len + frm->Code;

		for( i = 0; i < len -1 ; i++)
		{
			TxBuffer[3 + i] = frm->Data[i];
			sum += frm->Data[i];
		}
	
		TxBuffer[len + 2] = sum;
		TxBuffer[len + 3] = FRAME_TRAIL;
		UF0TX = TxBuffer[TxStat.CurTransmitPos];
	}
	TxStat.CurTransmitPos ++;
	TxStat.CurByteFlag = FALSE;
}

void Stack_TxHandler (void)
{
	BYTE i;
	if(TxStat.Indicator)		// Tx in use, there is some data in transmitting
	{
		if(TxStat.CurByteFlag) 	// Wait for current byte to be transmitted
		{
			Stack_TransmitFrame(&FrmTx);   // Transmit data
		}
	}
	else				// Tx is idle,check if there are some data need to be transmitted
	{
		if(TxStat.bTxTimeFlag)
		{
			if(!TxStat.bTickFlag)return;
			TxStat.bTickFlag = FALSE;
			for(i = 0;i < 8;i ++)
			{
				if(TxStat.bTxTimeFlag & (0x01 << i))
				{
					TxStat.bTxTimeFlag &= ~((BYTE)0x01 << i);
					break;
				}
			}
			switch(i)
			{
				case ACK_PRIO:
					Stack_TransmitFrame(&Frm_ACK);
				break;
				case FRM_AVM_CALI_PRIO:
					Stack_TransmitFrame(&FRM1_CALI_REQ);
				break;
				case AVM_RESET_PRIO:
					Stack_TransmitFrame(&Frm_Reset);
				break;
				case RRM_395_PRIO:
				break;
				case AVM_391_PRIO:
				break;
				case AVM_ALL_PRIO:
				{
					Stack_TransmitFrame(&Frm_AVM_RECEIVE_ALL);
				}
				break;
				case CMD_DISPLAY_SOFTWARE_VERSION_PRIO:
					Stack_TransmitFrame(&Frm_Version_Disp);
				break;
				default:
				break;
			}
		}
	}
}

void Stack_RxHandler (void)
{
	static BYTE pos = 0;
	if(Buffer[pos] == FRAME_HEADER) // Get Header
	{
		BYTE	length = Buffer[POS(FRAME_LENGTH_OFFSET)];
		if(length < MAX_DATA_SIZE)	// Get length, max. length 10
		{
			if(Buffer[POS(FRAME_TRAIL_OFFSET)] == 0x03)	// Get Trail
			{
				BYTE i,sum;
				sum = Buffer[POS(FRAME_LENGTH_OFFSET)];   // Calculate sum
				sum += Buffer[POS(FRAME_CODE_OFFSET)];
				for(i = 0;i < length - 1; i++)
				{
					sum += Buffer[POS((FRAME_DATA_OFFSET + i))];
				}
				if(sum == Buffer[POS(FRAME_SUM_OFFSET)]) // Compare the sum
				{
					FrmRx.Code = Buffer[POS(FRAME_CODE_OFFSET)];
					FrmRx.Length = Buffer[POS(FRAME_LENGTH_OFFSET)];
					for(i = 0; i < length - 1; i++)
					{
						FrmRx.Data[i] = Buffer[POS((FRAME_DATA_OFFSET + i))];
					}
					Stack_ClrTheFrame(pos,length);
					Stack_FrameRxIndicator();
				}
			}
		}
	}
	pos ++;
	if(pos > (BUFFER_SIZE - 1))
	{
		pos -= BUFFER_SIZE;
	}
}

void Stack_FrameRxIndicator (void)
{
	CALLBACK callback;

	callback = CbkTable[FrmRx.Code];
	callback();
}

void Stack_ReceiveSignal_Steering_angle (WORD wSteering_angle)
{	
	signed short angle;
	//if(Steering_angle == wSteering_angle)return;
	Steering_angle = wSteering_angle;
	angle += 0xFFFF;
	angle = angle/174;
	angle += 90;

	Frm_AVM_RECEIVE_ALL.Data[0] = (BYTE)angle;   // Steering_angle 
}

void Cbk_NULL (void)
{
	if(FrmRx.Code == 0x02)
	{
		FrmRx.Data[9] = 0;
	}
	if(FrmRx.Code == 0xFF)
	{
		FrmRx.Data[9] = 0;
	}
}

void Cbk_FRM_RRM_060 (void)
{
	//SetTxFlag(ACK_FLAG);
}

void Cbk_FRM_AVM_070 (void)	// Event, AVM --> CAN
{
	if(FrmRx.Length == 2)
	{
		//Frm_Reset.Data[0] = FrmRx.Data[0];
		//Frm_Reset.Data[1] = FrmRx.Data[1];
		Can_App_AVM_070_OnWrite();
		SetTxFlag(ACK_FLAG);
	}
}

void Cbk_FRM_AVM_391 (void)	// Cycle, AVM --> CAN
{
	if(FrmRx.Length == 3)
	{
		Frm_AVM_391.Data[0] = FrmRx.Data[0];
		Frm_AVM_391.Data[1] = FrmRx.Data[1];
		Frm_AVM_391.Data[2] = FrmRx.Data[2];
		Can_App_AVM_391_OnWrite();
	}
}

void Cbk_FRM_AVM_ALL (void)
{
	
}

void Cbk_FRM_ACK (void)
{
	
}

void Cbk_FRM_Test (void)
{
	FrmTx.Code = FRM_TEST_REQ;
	FrmTx.Length = 0;
	Stack_TransmitFrame(&FrmTx);
}

void Stack_MakeAVMFrame (void)
{

}

void Cbk_FRM5_SYNC (void)
{
	static BYTE bySensorFaultCnt = 0;
	AVM.bStarting = FALSE;
	if(AVM.CaliTaskRun == TRUE)
	{
		AVM.wOfflineCnt = 0;
	}
	
	if(FrmRx.Data[0])
	{
		bySensorFaultCnt ++;
		if(bySensorFaultCnt >= 5)
		{
			bySensorFaultCnt = 5;
		}
	}
	else
	{
		bySensorFaultCnt = 0;
	}
	if((FrmRx.Data[0] & 0x80) == 0)
		DDMTestPreResultProcess(DTC_FRONT_SENSOR_FAULT_INDEX,DTC_TEST_PREPASSED);
	if((FrmRx.Data[0] & 0x40) == 0)
		DDMTestPreResultProcess(DTC_REAR_SENSOR_FAULT_INDEX,DTC_TEST_PREPASSED);
	if((FrmRx.Data[0] & 0x20) == 0)
		DDMTestPreResultProcess(DTC_LEFT_SENSOR_FAULT_INDEX,DTC_TEST_PREPASSED);
	if((FrmRx.Data[0] & 0x10) == 0)
		DDMTestPreResultProcess(DTC_RIGHT_SENSOR_FAULT_INDEX,DTC_TEST_PREPASSED);
        if(bySensorFaultCnt == 5)
        {
          	App_SetMsgBoxStatus(APP_MSGBOX_STATUS_CAMERA_FAULT,TRUE);
		if(FrmRx.Data[0] & 0x80)	// front sensor
			DDMTestPreResultProcess(DTC_FRONT_SENSOR_FAULT_INDEX,DTC_TEST_PREFAILED);
		if(FrmRx.Data[0] & 0x40)	// rear sensor
			DDMTestPreResultProcess(DTC_REAR_SENSOR_FAULT_INDEX,DTC_TEST_PREFAILED);
		if(FrmRx.Data[0] & 0x20)	// left sensor
			DDMTestPreResultProcess(DTC_LEFT_SENSOR_FAULT_INDEX,DTC_TEST_PREFAILED);
		if(FrmRx.Data[0] & 0x10)	// right sensor
			DDMTestPreResultProcess(DTC_RIGHT_SENSOR_FAULT_INDEX,DTC_TEST_PREFAILED);
        }
        else
        {
               	App_SetMsgBoxStatus(APP_MSGBOX_STATUS_CAMERA_FAULT,FALSE);
        }
}
void Cbk_FRM2_CALI_RES (void)
{
	AVM_St_Calibration = FrmRx.Data[0];
	if( AVM_St_Calibration  == 2)
	{
		AVM.CalibrationFaultTimer = 3505;
	}
	if(AVM_St_Calibration == 3 || AVM_St_Calibration == 4)
	{
		AVM.CalibrationFaultTimer = 0;
	}
}