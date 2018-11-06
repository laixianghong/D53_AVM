#include "App.h"
#include "control.h"
#include "Stack.h"
#include "Com.h"
#include "Can_USer.h"
#include "Event.h"

AVMStatus AVM;
MessageBox MsgBox;
DWORD	PowerUpTime = 1500;
DWORD	CaliTime = 0;
void App_AVM_StatusInit (void)
{
	AVM.bStarting = TRUE;
	AVM.Display_view_state = APP_DISPLAY_VIEW_NONE;
	App_SetActiveState(FALSE);
	App_SetDisplayView (APP_DISPLAY_VIEW_FRONT_ALL);
	//App_SetCtlMode(APP_DISPLAY_MODE_BUSCTL);
	App_SetCtlMode(APP_DISPLAY_MODE_MANUAL);
	//App_SetMsgBoxStatus(APP_MSGBOX_STATUS_CALIBRATION_SUCCESS,TRUE);
}

void App_SetActiveState (BOOL bActive)
{
        if(bActive == 0)
	{
		AVM_St_sys = 0;  // Inactive
	}
	else
	{
		AVM_St_sys = 1;  // Active 
	}
//	Can_SendSignal(AVM_St_sys);
	bActive = 1;
	AVM.Active_state = bActive;
	////AVM.Active_state = 1;/////////////////////////////
	Frm_AVM_RECEIVE_ALL.Data[2] = Frm_AVM_RECEIVE_ALL.Data[2] & 0xF7;
	Frm_AVM_RECEIVE_ALL.Data[2] += (bActive << 0x03);
}

void App_SetDisplayView (BYTE view)
{
	if(AVM.Display_view_state == view)return;
	AVM.Display_view_state = view;
	Frm_AVM_RECEIVE_ALL.Data[2] = Frm_AVM_RECEIVE_ALL.Data[2] & 0x0F;
	Frm_AVM_RECEIVE_ALL.Data[2] += (view << 0x04);
	if(view == APP_DISPLAY_VIEW_LEFT_ALL)
		AVM_St_ViewDisplay = 3;
	else if(view == APP_DISPLAY_VIEW_RIGHT_ALL)
		AVM_St_ViewDisplay = 4;
	else if(view == APP_DISPLAY_VIEW_REAR_ALL)
		AVM_St_ViewDisplay = 2;
	else if(view == APP_DISPLAY_VIEW_FRONT)
		AVM_St_ViewDisplay = 5;
	else if(view == APP_DISPLAY_VIEW_REAR)
		AVM_St_ViewDisplay = 6;
	else if(view == APP_DISPLAY_VIEW_LEFT)
		AVM_St_ViewDisplay = 7;
	else if(view == APP_DISPLAY_VIEW_RIGHT)
		AVM_St_ViewDisplay = 8;
	else
		AVM_St_ViewDisplay = 1;
//	Can_SendSignal(AVM_St_ViewDisplay);	
}

void App_SetCtlMode (BYTE mode)
{
	AVM.DisplayMod = mode;
	Frm_AVM_RECEIVE_ALL.Data[2] = Frm_AVM_RECEIVE_ALL.Data[2] & 0xFC;
	Frm_AVM_RECEIVE_ALL.Data[2] += mode;
}

extern BOOL bSpeedValid;
void App_OtherTask (void)    // called every 10ms
{
        static BOOL bExitvalid = FALSE;
	
	/* Reverse Gear View Hold Time */
        if(Event.wReverseExitTime)	
        {
                bExitvalid = TRUE;
                Event.wReverseExitTime = Event.wReverseExitTime - 10;
        }
        else	
        {
                if(bExitvalid)			/* delay time end */
                {
                        bExitvalid = FALSE;
                        if(AVM.bBirdViewInUse)	/* AVM in use */
                        {
                                //if(AVM.bSpeedValid)	/* speed ok */
                                //{					
                                //}
                                //else			/* speed ng */
                                //{
                                //        App_SetActiveState(FALSE);
                                //}     
                        }
                        else			/* AVM not in use,AVM exit  */
                        {
                                App_SetActiveState(FALSE);	
                        }
			if((Event.bTurnRightRequest + Event.bTurnLeftRequest) != 1)
			{
				App_SetDisplayView(APP_DISPLAY_VIEW_FRONT_ALL);
			}
                }
        }
	/* calibration task */
	if(AVM.CaliTaskRun)
	{
		switch(AVM.CaliStatus)
		{
			case APP_CALIBRATION_START:  // begin
			{
				AVM.Timer = 0;
				App_SetActiveState(TRUE);
				App_SetDisplayView(APP_DISPLAY_VIEW_FRONT_ALL);
				AVM_St_Calibration = 2;
				AVM.CaliStatus = APP_CALIBRATION_SET_DSP;
			}
			break;
			case APP_CALIBRATION_SET_DSP:  //
				if(AVM.Timer == 50)
				{
					SetTxFlag(FRM_AVM_CALI_FLAG);
					AVM.CaliStatus = APP_CALIBRATION_WAITTING_RES;
				}
			break;
			case APP_CALIBRATION_WAITTING_RES:
				if(AVM_St_Calibration == 3 || AVM_St_Calibration == 4)
				{
					AVM.wOfflineCnt = 0;
					AVM.CaliStatus = APP_CALIBRATION_WAIT_OFFLINE;
                                        if(AVM_St_Calibration == 4)
                                        {
                                                App_SetMsgBoxStatus(APP_MSGBOX_STATUS_CALIBRATION_FAILD,TRUE);
                                        }
					else
					{
						App_SetMsgBoxStatus(APP_MSGBOX_STATUS_CALIBRATION_SUCCESS,TRUE);
					}
				}
			break;
			case APP_CALIBRATION_WAIT_OFFLINE:
				if((AVM.Timer % 20) == 0)
				{
                                        AVM.wOfflineCnt += 200;
                                        if(AVM.wOfflineCnt > 2000)
                                        {
                                                AVM.wOfflineCnt = 0;
						AVM.bOfflineFlag = TRUE;
                                                //AVM.Calibrated = FALSE;
                                                //AVM.CaliTaskRun = FALSE;
						AVM.CaliStatus = APP_CALIBRATION_WAIT_RESTART;
						AVM.bStarting = TRUE;
                                        }
				}
			break;
			case APP_CALIBRATION_WAIT_RESTART:
				if(AVM.bStarting == FALSE)
				{
					AVM.CaliStatus = APP_CALIBRATION_WAIT_KEYDOWN;
					Event.bLeftKeyDown = 0;
					Event.bRightKeyDown = 0;
				}
			break;
			case APP_CALIBRATION_WAIT_KEYDOWN: /* keydown */
				/*if(Event.bLeftKeyDown + Event.bRightKeyDown)
				{
					if(MsgBox.BoxType == APP_MSGBOX_STATUS_CALIBRATION_SUCCESS)
					{
						App_SetMsgBoxStatus(APP_MSGBOX_STATUS_CALIBRATION_SUCCESS,FALSE);
						AVM.CaliTaskRun = FALSE;
						AVM.Calibrated = FALSE;
					}
					if(MsgBox.BoxType == APP_MSGBOX_STATUS_CALIBRATION_FAILD)
					{
						if(Event.bLeftKeyDown)
						{
							App_SetMsgBoxStatus(APP_MSGBOX_STATUS_CALIBRATION_FAILD,FALSE);
							AVM.CaliTaskRun = FALSE;
							AVM.Calibrated = FALSE;
				
						}
						else
						{
							App_SetMsgBoxStatus(APP_MSGBOX_STATUS_CALIBRATION_FAILD,FALSE);
							AVM.Calibrated = FALSE;
							Event_GetCalibrationSignal();
						}
						
					}
				}*/
			break;
		}
		AVM.Timer ++;
	}
        
        /* message box task */
        if(MsgBox.bActive)
        {
                if(MsgBox.wTimer == APP_MSGBOX_DISPLAY_TYPE_CONTINUS_VALUE)
                {
                        
                }
                else
                {
                        if(MsgBox.wTimer)
                        {
                                MsgBox.wTimer --;
                        }
                        else
                        {
				if(MsgBox.BoxType == APP_MSGBOX_STATUS_OVER_SPEED)
				{	
	                                App_SetActiveState(FALSE);
					App_SetMsgBoxStatus(APP_MSGBOX_STATUS_OVER_SPEED,FALSE);
				}
                        }
                }
        }
	if(wResetTime)
	{
		if(wResetTime%20 == 0)
		{
			SetTxFlag(AVM_RESET_FLAG);
		}
		if(wResetTime == 10)
		{
			Cpu_Reset();
		}
		else
		{
			wResetTime -= 10;
		}
		
	}
	if(PowerUpTime)
	{
		PowerUpTime -= 10;
		if(PowerUpTime == 10)
		{
			Ctl_EnableNetworkDiagnostic();
		}
	}
	if(CaliTime)
	{
		CaliTime -= 10;
		if(CaliTime == 10)
		{
			AVM_St_Calibration = 0; //Invalid
//			Can_SendSignal(AVM_St_Calibration);
		}
	}
	
	if(AVM.CalibrationFaultTimer)
	{
		AVM.CalibrationFaultTimer --;
		
		if(AVM.CalibrationFaultTimer == 105)
		{
			MODULE_POWEROFF;
		}
		if(AVM.CalibrationFaultTimer == 5)
		{
			App_SetMsgBoxStatus(APP_MSGBOX_STATUS_CALIBRATION_FAILD,TRUE);
			MODULE_POWERON;	
		}
	}
	
}

void App_SetMsgBoxStatus (BYTE BoxIndex,BYTE btStatus)
{
	BYTE i,index = 0;
	WORD ret;
	
	if(btStatus)	/* Update status*/
	{
		MsgBox.BoxList |= (1 << BoxIndex);
	}
	else
	{
		MsgBox.BoxList &= ~(1 << BoxIndex);
	}
	if(MsgBox.BoxList)	/* message box exist */
	{

		for(i = 0;i < APP_MSGBOX_STATUS_MAX_NUM;i ++)
		{
			ret = MsgBox.BoxList & (1 << i);
			if(ret)
			{
				index = i;
				break;
			}
		}
		MsgBox.bActive = TRUE;
	}
	else			/* No message box  */
	{
		index = 0;
		MsgBox.bActive = FALSE;
	}
	Frm_AVM_RECEIVE_ALL.Data[3] &= 0x0F;
        Frm_AVM_RECEIVE_ALL.Data[3] |= (index << 4);
	MsgBox.BoxType = index;
	if(index == BoxIndex)
	{
		switch(MsgBox.BoxType)
		{
			case APP_MSGBOX_STATUS_NONE:
			case APP_MSGBOX_STATUS_CAMERA_FAULT:
			case APP_MSGBOX_STATUS_CALIBRATING:
			case APP_MSGBOX_STATUS_CALIBRATION_SUCCESS:
			case APP_MSGBOX_STATUS_CALIBRATION_FAILD:
			case APP_MSGBOX_STATUS_MIRROR_FOLD:
				MsgBox.wTimer = APP_MSGBOX_DISPLAY_TYPE_CONTINUS_VALUE;
			break;
			case APP_MSGBOX_STATUS_OVER_SPEED:
				MsgBox.wTimer = APP_MSGBOX_DISPLAY_TYPE_OVERSPEED_TIME;
			break;
		}
	}
}

void 	App_SetLanguage (EnLanguage lang)
{
	Frm_AVM_RECEIVE_ALL.Data[3] &= 0xF0;
	if(lang == AVM_LANGUAGE_CHINESE)
	{
		  Frm_AVM_RECEIVE_ALL.Data[3] += AVM_LANGUAGE_CHINESE;
	}
	else
	{
		 Frm_AVM_RECEIVE_ALL.Data[3] += AVM_LANGUAGE_ENGLISH;
	}
}