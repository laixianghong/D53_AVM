#ifndef	_APP_H_
#define _APP_H_
#include "cpu.h"

#define		APP_TURN_LAMP_OFF		0
#define		APP_TURN_LAMP_ON		1
/* display mode */
#define		APP_DISPLAY_MODE_BUSCTL		0
#define		APP_DISPLAY_MODE_MANUAL		1
/* display view for dsp */
#define		APP_DISPLAY_VIEW_NONE		0
#define		APP_DISPLAY_VIEW_FRONT  	1
#define		APP_DISPLAY_VIEW_REAR   	2
#define		APP_DISPLAY_VIEW_LEFT		3
#define		APP_DISPLAY_VIEW_RIGHT  	4
#define		APP_DISPLAY_VIEW_FRONT_ALL  	5
#define		APP_DISPLAY_VIEW_REAR_ALL  	6
#define		APP_DISPLAY_VIEW_LEFT_ALL  	7
#define		APP_DISPLAY_VIEW_RIGHT_ALL  	8
#define		APP_DISPLAY_VIEW_NO_DEFINE  	9
/* msgbox status */
#define         APP_MSGBOX_STATUS_NONE          0
#define         APP_MSGBOX_STATUS_CAMERA_FAULT  1
#define         APP_MSGBOX_STATUS_CALIBRATING   2
#define         APP_MSGBOX_STATUS_CALIBRATION_SUCCESS 3
#define         APP_MSGBOX_STATUS_CALIBRATION_FAILD   4
#define         APP_MSGBOX_STATUS_OVER_SPEED    5
#define         APP_MSGBOX_STATUS_MIRROR_FOLD   6
#define		APP_MSGBOX_STATUS_MAX_NUM	7
/* msgbox display mode */
#define         APP_MSGBOX_TYPE_TIME_INFINIT    0
#define         APP_MSGBOX_TYPE_DELAY_CLOSE     1
/* msgbox active status */
#define		APP_MSGBOX_STATUS_OFF		0
#define		APP_MSGBOX_STATUS_ON		1
/* msgbox delay time */
#define		APP_MSGBOX_DISPLAY_TYPE_CONTINUS_VALUE		0xFFFF
#define		APP_MSGBOX_DISPLAY_TYPE_OVERSPEED_TIME		300
/* continus over speed chk times */
#define		APP_SPEED_CHECK_PRIOD				(500/20)

#define		APP_CALIBRATION_START		0
#define		APP_CALIBRATION_SET_DSP		1
#define		APP_CALIBRATION_WAITTING_RES	2
#define		APP_CALIBRATION_WAIT_OFFLINE	3
#define		APP_CALIBRATION_WAIT_RESTART	4
#define		APP_CALIBRATION_WAIT_KEYDOWN	5
typedef struct StAVMStatus 
{
	BOOL	bBirdViewInUse;
	BOOL	bOfflineFlag;
	WORD	wOfflineCnt;
	BOOL    bStarting;
	BYTE	Steering_angle[2];
	BYTE	Display_view_state;
	BOOL    Active_state;
	BOOL	Dyn_trace_state;
	BYTE	DisplayMod;
	
	BOOL    CaliTaskRun;
	BYTE    CaliStatus;
	BOOL    Calibrated;
	WORD	Timer;
	
	BOOL    bSingleMode;
	BOOL	bSpeedValid;
	WORD    CalibrationFaultTimer;
}AVMStatus;

typedef struct StMsgBox
{
        BOOL    bActive;
        WORD    wTimer;
        BYTE    BoxType;
	WORD	BoxList;
}MessageBox;

typedef  enum	EnLanguage
{
	AVM_LANGUAGE_CHINESE = 0,
	AVM_LANGUAGE_ENGLISH = 1,
}EnLanguage;

void App_SetActiveState (BOOL bActive);
void App_SetDisplayView (BYTE view);
void App_SetCtlMode (BYTE mode);
void App_AVM_StatusInit (void);
void App_OtherTask (void);
void App_SetMsgBoxStatus (BYTE BoxIndex,BYTE btStatus);
void 	App_SetLanguage (EnLanguage lang);

extern	AVMStatus AVM;
extern  MessageBox MsgBox;
#endif