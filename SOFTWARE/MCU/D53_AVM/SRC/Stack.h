#ifndef _STACK_H_
#define _STACK_H_

#include "cpu.h"


#define		GEAR_POS_NOT_IN_REVERSE	0
#define		GEAR_POS_IN_REVERSE	1

#define 	BUFFER_SIZE		20
#define		MAX_DATA_SIZE		11
#define		FRAME_HEADER		0x02
#define		FRAME_TRAIL		0x03

#define		FRAME_LENGTH_OFFSET	1
#define		FRAME_TRAIL_OFFSET	(3 + length)
#define		FRAME_CODE_OFFSET	2
#define		FRAME_DATA_OFFSET	3
#define		FRAME_SUM_OFFSET	(2 + length)

// Position of data to be transmitted
#define 	POS_HEADER		0
#define		POS_LENGTH		1
#define		POS_CODE		2

// Frame type definition
#define		FRM5_SYNC		0x05
#define		FRM_AVM_CALI		0x01
#define		FRM_RESET		0x25
#define		FRM_RRM_395		0x03
#define		FRM_AVM_391		0x04
#define		FRM_AVM_ALL		0x04
#define		FRM_TEST_REQ		0xFE
#define		FRM_ACK			0xFF

// Tx Frame Flag
#define		PERIOD_FLAG		0x80
#define		ACK_FLAG		(0x01 << ACK_PRIO)
#define		AVM_RECEIVE_ALL_FLAG	(0x01 << AVM_ALL_PRIO)
#define		FRM_AVM_CALI_FLAG	(0x01 << FRM_AVM_CALI_PRIO)
#define		AVM_RESET_FLAG		(0x01 << AVM_RESET_PRIO)
#define		RRM_395_FLAG		(0x01 << RRM_395_PRIO)
#define		AVM_391_FALG		(0x01 << AVM_391_PRIO)
#define		CMD_DISPLAY_SOFTWARE_VERSION_FLAG	(0x01 << CMD_DISPLAY_SOFTWARE_VERSION_PRIO)

#define		BIT(byte,pos)		(byte & (0x01 << pos)) > 0?1:0
#define		SetTxFlag(x)		TxStat.bTxTimeFlag |= x
#define 	POS(tp)		((pos + tp) > (BUFFER_SIZE - 1)) ? ((pos + tp)%BUFFER_SIZE) : (pos + tp)
#define		FILL(x)		x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x

// Frame Tx priority
#define		ACK_PRIO		0
#define		FRM_AVM_CALI_PRIO	1
#define		AVM_RESET_PRIO		2
#define		RRM_395_PRIO		3
#define		AVM_391_PRIO		4
#define		AVM_ALL_PRIO		5
#define		CMD_DISPLAY_SOFTWARE_VERSION_PRIO	6

typedef 	void (*CALLBACK)(void);
typedef		struct		_FRM
{
	BYTE	Code;
	BYTE    Length;
	BYTE	Data[MAX_DATA_SIZE - 1];
}FRM;

typedef 	struct		_TXSTATUS
{
	BOOL	Indicator;		// Indicate that there is some data in transmitting	
	BOOL	CurByteFlag;		
	BYTE	CurTransmitPos;
	BOOL	bTxTimeFlag;		
	BOOL    bTickFlag;		// Period Tx transmit point,it is time to transmit period frame
}TX_STAT;


extern 	volatile   BYTE		Buffer[BUFFER_SIZE];
extern 	volatile   TX_STAT	TxStat;
extern 	volatile   FRM	 	FrmTx;
extern 	volatile   FRM	 	FrmRx;
extern	volatile   FRM	 	Frm_RRM060;
extern	FRM Reset;
extern	volatile   FRM	 	Frm_AVM_391;
extern	volatile   FRM   	Frm_AVM_RECEIVE_ALL;
extern	volatile   FRM   	Frm_ACK;
extern FRM   FRM1_CALI_REQ;
extern   BOOL    ValidData;

void Stack_Can_Task (void);
void Stack_Uart_Task (void);
void Stack_Init (void);
void Stack_ClrTheFrame (BYTE pos,BYTE nLength);
void Stack_TransmitFrame (FRM* frm);
void Stack_TxHandler (void);
void Stack_RxHandler (void);

void Stack_FrameRxIndicator (void);
void Stack_ReceiveSignal_Steering_angle (WORD wSteering_angle);

void Stack_MakeAVMFrame (void);

void Cbk_NULL (void);
void Cbk_FRM_RRM_060 (void);
void Cbk_Frm_Reset (void);
void Cbk_FRM_AVM_391 (void);
void Cbk_FRM_AVM_ALL (void);
void Cbk_FRM_Test (void);
void Cbk_FRM_ACK (void);
void Cbk_FRM5_SYNC (void);
void Cbk_FRM2_CALI_RES (void);
#endif