#ifndef	_EVENT_H_
#define _EVENT_H_

#include "cpu.h"

/* reverse gear hold on time before reverse view return */
#define		EVENT_VECHILE_GEAR_SIGNAL_CYCLE			50	/* unit ms */
#define		EVENT_ENTER_REVERSE_GEAR_STABLE_CNT		4	/* 200ms cycle */
#define		EVENT_REVERSE_GEAR_HOLD_ON_TIME			300	/* unit ms */

/* left and right turn direction light signal parameter */
#define		EVENT_TURN_DIRECTION_SIGNAL_CYCLE		50	/* unit ms */
#define		EVENT_TURN_DIRECTION_HOLD_TIME			720	/* 400 unit ms */
#define		EVENT_TURN_DIRECTION_HOLD_CNT			(EVENT_TURN_DIRECTION_HOLD_TIME/EVENT_TURN_DIRECTION_SIGNAL_CYCLE)

/* vechile speed  */
#define		EVENT_VECHILE_SPEED_SIGNAL_CYCLE		50	/* unit ms */
#define		EVENT_OVER_SPEED_VALUE				25	/* unit km/h */
#define		EVENT_RESTORE_SPEED_VALUE			21	/* unit km/h */
#define		EVENT_VECHILE_OVER_SPEED_STABLE_CNT		4
#define		EVENT_VECHILE_RESTORE_SPEED_STABLE_CNT		4

#define		EVENT_SPEED_VALID_VALUE				EVENT_SPEED_VALID_ZERO
#define		EVENT_SPEED_VALID_ZERO				0
#define		EVENT_SPEED_VALID_ONE				1

/* MP5 command */
#define		EVENT_ACTIVE_THE_AVM				EVENT_ENABLE_VALUE_ZERO
#define		EVENT_ENABLE_VALUE_ZERO				0
#define		EVENT_ENABLE_VALUE_ONE				1
/* power-on parity & reverse gear parity */
#define		POWER_ON_CHK()					{if(AVM.bStarting)return;}
#define		POWER_ON_CHK_AND_REVERSE_CHK()			{if(AVM.bStarting | Event.bInReverseGear)return;}


typedef struct StEvent
{
	/* reverse gear */
        BOOL    bInReverseGear;
	BYTE	byRearCnt;
	WORD	wReverseExitTime;
	/* turn direction light */
	BOOL	bTurnLeftRequest;
	BOOL	bTurnRightRequest;
	/* vechile speed */
	BOOL	bOverSpeedFlag;
	BYTE	byOverSpeedCnt;
	BOOL	bLeftKeyDown;
	BOOL	bRightKeyDown;
}EVENT;

extern	EVENT	Event;
void Event_Init (void);
void Event_GetReverseGearSignal (BOOL bCurInRGear);
void Event_GetTurnDirectionLightSignal (BOOL bLeftTurnON,BOOL bRightTurnON);
void Event_GetVechileSpeedSignal (WORD wVechileSpeed,BOOL bSpeedValid);
void Event_GetActiveSignal (void);
void Event_GetDeactiveSignal (void);
void Event_GetCalibrationSignal (void);
#endif