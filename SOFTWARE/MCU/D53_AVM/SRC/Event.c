#include "App.h"
#include "Stack.h"
#include "Com.h"
#include "Can_USer.h"
#include "Event.h"

EVENT	Event;
const	WORD	wOverSpeedMaxValue = (WORD)((double)EVENT_OVER_SPEED_VALUE/(double)0.01);
const	WORD	wRestoreSpeedMinValue = (WORD)((double)EVENT_RESTORE_SPEED_VALUE/(double)0.01);

/******************************************************************************************************
*FUNC NAME:	Event_Init
*ABSTRACT:	Initialize the variables of the Event struct.
*PARAMETER:	None.
*				
*RETURN:	None.
*AUTHOR:	Xianghong.Lai   20170724
******************************************************************************************************/
void Event_Init (void)
{
	Event.bInReverseGear = FALSE;
	Event.byRearCnt = 0;
	Event.wReverseExitTime = 0;
	Event.bTurnLeftRequest = FALSE;
	Event.bTurnRightRequest = FALSE;
	Event.bOverSpeedFlag = FALSE;
	Event.byOverSpeedCnt = 0;
}

/******************************************************************************************************
*FUNC NAME:	Event_GetReverseGearSignal
*ABSTRACT:	This function should be called when Vechile gear signal received from the bus.
*PARAMETER:	bCurInRGear	0: not in reverse gear
*				1: in reverse gear
*RETURN:	None.
*AUTHOR:	Xianghong.Lai   20170722
******************************************************************************************************/
void Event_GetReverseGearSignal (BOOL bCurInRGear)
{
	if(bCurInRGear)		/* current gear is reverse gear */
	{
		Event.byRearCnt ++;
		if(Event.byRearCnt >= EVENT_ENTER_REVERSE_GEAR_STABLE_CNT)
		{
			Event.byRearCnt = EVENT_ENTER_REVERSE_GEAR_STABLE_CNT;
			if(Event.bInReverseGear == FALSE)   		/*  enter reverse gear */
			{
				Event.bInReverseGear = TRUE;
				App_SetActiveState(TRUE);
				App_SetDisplayView(APP_DISPLAY_VIEW_REAR_ALL);
			}
		}
               	Event.wReverseExitTime = EVENT_REVERSE_GEAR_HOLD_ON_TIME;
	}
	else			/* current gear is not reverse gear */
	{
		Event.byRearCnt = 0;
		if(Event.bInReverseGear)	/* leave reverse gear */
		{
                        Event.wReverseExitTime = EVENT_REVERSE_GEAR_HOLD_ON_TIME;
			Event.bInReverseGear = FALSE;
			Event.bTurnLeftRequest = FALSE;
 			Event.bTurnRightRequest = FALSE;
		}
	}	
}

/******************************************************************************************************
*FUNC NAME:	Event_GetTurnDirectionLightSignal
*ABSTRACT:	This function should be called when Vechile Turn-Direction Light Signal received from the bus.
*PARAMETER:	bLeftTurnON
*		bRightTurnON
*				0: no turn direction request
*				1: turn direction request exist
*RETURN:	None.
*AUTHOR:	Xianghong.Lai   20170722
******************************************************************************************************/
void Event_GetTurnDirectionLightSignal (BOOL bLeftTurnON,BOOL bRightTurnON)
{
	static BYTE cntL = EVENT_TURN_DIRECTION_HOLD_CNT;
	static BYTE cntR = EVENT_TURN_DIRECTION_HOLD_CNT;
	
	if(Event.bInReverseGear)return;
	if(bLeftTurnON == 1 && bRightTurnON == 0)
	{
		cntL = EVENT_TURN_DIRECTION_HOLD_CNT;
		if(Event.bTurnLeftRequest == FALSE)
		{
			Event.bTurnLeftRequest = TRUE;
			App_SetDisplayView(APP_DISPLAY_VIEW_LEFT_ALL);
		}
	}
	else
	{
		if(cntL)
		{
			cntL --;
			if(cntL == 0 && cntR == 0)
			{
				App_SetDisplayView(APP_DISPLAY_VIEW_FRONT_ALL);
			}
		}
		else
		{
			Event.bTurnLeftRequest = FALSE;
			if(cntR == 0)
			{
				Event.bTurnRightRequest = FALSE;
			}
			//App_SetDisplayView(APP_DISPLAY_VIEW_FRONT_ALL);
		}
	}
	if(bLeftTurnON == 0 && bRightTurnON == 1)
	{
		cntR = EVENT_TURN_DIRECTION_HOLD_CNT;
		if(Event.bTurnRightRequest == FALSE)
		{
			Event.bTurnRightRequest = TRUE;
			App_SetDisplayView(APP_DISPLAY_VIEW_RIGHT_ALL);
		}
	}
	else
	{
		if(cntR)
		{
			cntR --;
			if(cntR == 0 && cntL == 0)
			{
				App_SetDisplayView(APP_DISPLAY_VIEW_FRONT_ALL);
			}
		}
		else
		{
			Event.bTurnRightRequest = FALSE;
			if(cntL == 0)
			{
				Event.bTurnLeftRequest = FALSE;
			}
			//App_SetDisplayView(APP_DISPLAY_VIEW_FRONT_ALL);
		}
	}
}
/******************************************************************************************************
*FUNC NAME:	Event_GetVechileSpeedSignal
*ABSTRACT:	This function should be called when Vechile Speed Signal received from the bus.
*PARAMETER:	wVechileSpeed:	Current speed 
*		bSpeedValid:	Vechile speed valid flag
*				0: no turn direction request
*				1: turn direction request exist
*RETURN:	None.
*AUTHOR:	Xianghong.Lai   20170724
******************************************************************************************************/
void Event_GetVechileSpeedSignal (WORD wVechileSpeed,BOOL bSpeedValid)
{   
	
#if(EVENT_SPEED_VALID_VALUE == EVENT_SPEED_VALID_ZERO)
    if(bSpeedValid == 0)  // valid
#else
    if(bSpeedValid == 1)  // valid
#endif
    {
            if(AVM.bBirdViewInUse)          //360view  in use
            {
                    if(Event.bInReverseGear == FALSE && Event.wReverseExitTime == 0) // not in reverse gear
                    {
                            if(Event.bOverSpeedFlag == FALSE)
                            {
	                             if(wVechileSpeed > wOverSpeedMaxValue)
	                             {
						Event.byOverSpeedCnt ++;
						if(Event.byOverSpeedCnt >= EVENT_VECHILE_OVER_SPEED_STABLE_CNT) 
						{
							Event.bOverSpeedFlag = TRUE;
		                                        App_SetMsgBoxStatus(APP_MSGBOX_STATUS_OVER_SPEED,TRUE);
		                                        MsgBox.wTimer = APP_MSGBOX_DISPLAY_TYPE_OVERSPEED_TIME;
							Event.byOverSpeedCnt = 0;
						}
	                             }
				     else
				     {
					    Event.byOverSpeedCnt = 0;
				     }
                            }
                            else // over speed
                            {
                                    if(wVechileSpeed < wRestoreSpeedMinValue)
                                    {
					    Event.byOverSpeedCnt ++;
					    if(Event.byOverSpeedCnt >= EVENT_VECHILE_RESTORE_SPEED_STABLE_CNT)
					    {
	                                            App_SetActiveState(TRUE);
	                                            App_SetMsgBoxStatus(APP_MSGBOX_STATUS_OVER_SPEED,FALSE);
	                                            MsgBox.wTimer = APP_MSGBOX_DISPLAY_TYPE_CONTINUS_VALUE;
	                                            Event.bOverSpeedFlag = FALSE;
						    Event.byOverSpeedCnt = 0;
					    }
                                    }
				    else
				    {
					    Event.byOverSpeedCnt = 0;
				    }
                            }
                    }
            }
	}
}
/******************************************************************************************************
*FUNC NAME:	Event_GetActiveSignal
*ABSTRACT:	This function should be called when the activcation Signal received from the bus.
*PARAMETER:	None.
*RETURN:	None.
*AUTHOR:	Xianghong.Lai   20170724
******************************************************************************************************/
void Event_GetActiveSignal (void)
{
	
        
        if(Event.bInReverseGear | Event.bOverSpeedFlag)
        {
		if(Event.bOverSpeedFlag == FALSE)
		{
			App_SetActiveState(TRUE);
		}
        	return;
        }
	else
	{
		App_SetActiveState(TRUE);
		AVM.bBirdViewInUse = TRUE;
		Event.bOverSpeedFlag = FALSE;
		Event.byOverSpeedCnt = 0;
		if(Event.bTurnLeftRequest + Event.bTurnRightRequest == 1)
		{
			return;
		}
		switch(MP5_AVM_SwitchRequest)
		{
			case 1:
				App_SetDisplayView(APP_DISPLAY_VIEW_FRONT_ALL);
			break;
			case 2:
				App_SetDisplayView(APP_DISPLAY_VIEW_REAR_ALL);
			break;
			case 3:
				if(MsgBox.BoxType == APP_MSGBOX_STATUS_CALIBRATION_SUCCESS || MsgBox.BoxType == APP_MSGBOX_STATUS_CALIBRATION_FAILD)
				{
					Event.bLeftKeyDown = TRUE;
				}
				else
				{
					App_SetDisplayView(APP_DISPLAY_VIEW_LEFT_ALL);
				}
			break;
			case 4:
				if(MsgBox.BoxType == APP_MSGBOX_STATUS_CALIBRATION_SUCCESS || MsgBox.BoxType == APP_MSGBOX_STATUS_CALIBRATION_FAILD)
				{
					Event.bRightKeyDown = TRUE;
				}
				else
				{
					App_SetDisplayView(APP_DISPLAY_VIEW_RIGHT_ALL);
				}
			break;
			case 5:
				App_SetDisplayView(APP_DISPLAY_VIEW_FRONT);
			break;
			case 6:
				App_SetDisplayView(APP_DISPLAY_VIEW_REAR);
			break;
			case 7:
				App_SetDisplayView(APP_DISPLAY_VIEW_LEFT);
			break;
			case 8:
				App_SetDisplayView(APP_DISPLAY_VIEW_RIGHT);
			break;
		}
	}
}

/******************************************************************************************************
*FUNC NAME:	Event_GetDeactiveSignal
*ABSTRACT:	This function should be called when deactivication Signal received from the bus.
*PARAMETER:	None.
*RETURN:	None.
*AUTHOR:	Xianghong.Lai   20170725
******************************************************************************************************/
void Event_GetDeactiveSignal (void)
{
	AVM.bBirdViewInUse = FALSE;
	Event.bOverSpeedFlag = FALSE;
	Event.byOverSpeedCnt = 0;
        App_SetActiveState(FALSE);
}
/******************************************************************************************************
*FUNC NAME:	Event_GetCalibrationSignal
*ABSTRACT:	This function should be called when calibration Signal received from the bus.
*PARAMETER:	None.
*RETURN:	None.
*AUTHOR:	Xianghong.Lai   20170725
******************************************************************************************************/
void Event_GetCalibrationSignal (void)
{
	if(AVM.Calibrated == FALSE)
	{
		AVM.Calibrated = TRUE;    
		AVM.CaliTaskRun = TRUE;
		AVM.CaliStatus = 0;
		AVM_St_Calibration = 2; //Calibrating
//		Can_SendSignal(AVM_St_Calibration);
	}
}