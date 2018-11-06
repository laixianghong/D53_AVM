#ifndef		_CAN_USER_H_
#define		_CAN_USER_H_
#include 	"Stack.h"

#ifndef		_CAN_USER_C_
#define		EXTERN		extern
#else
#define		EXTERN		
#endif

#define		SYS_STATUS_ACTIVE	0
#define		SYS_STATUS_INACTIVE	1

#define		DISPLAY_VIEW_FRONT	0
#define		DISPLAY_VIEW_REAR	1
#define		DISPLAY_VIEW_LEFT	2
#define		DISPLAY_VIEW_RIGHT	3
#define		DISPLAY_VIEW_WHOLE	4

/* Message SAS_0x224 */
EXTERN		DWORD		SteeringAngle;
EXTERN		BOOL		AngleFailure;
EXTERN		BYTE		MessageCounter; 
EXTERN		BYTE		CRCCheck; 
/* Message ABS_0x330 */
EXTERN		BOOL		ABS_Vehicle_speed_valid; 
EXTERN		WORD		vehicle_speed; 
EXTERN		BYTE		ABS2_RollingCounter; 
EXTERN		BYTE		ABS2_CheckSum; 
/* Message AVM_0x341 */
EXTERN		BOOL		AVM_St_sys; 
EXTERN		BYTE		AVM_St_ViewDisplay; 
EXTERN		BYTE		AVM_St_Calibration; 
EXTERN		BOOL		AVM_L_FrontCamCaliFault; 
EXTERN		BOOL		AVM_L_RearCamCaliFault; 
EXTERN		BOOL		AVM_R_FrontCamCaliFault; 
EXTERN		BOOL		AVM_R_RearCamCaliFault; 
/* Message BCM_0x350 */
EXTERN		BYTE		BCM_TurnIndicatorLeft; 
EXTERN		BYTE		BCM_TurnIndicatorRight; 
EXTERN		BOOL		BCM_ReverseGearSwitchStatus; 
/* Message MP5_0x361 */
EXTERN		BYTE		MP5_AVM_SwitchRequest; 
EXTERN		BYTE		MP5_Laguage_Change;
/* Message MP5_0x366 */
EXTERN		DWORD		Calibrate_start; 
EXTERN		BOOL		cali_info_req; 
EXTERN		DWORD		time_information; 
EXTERN		WORD 		x_coordinate;
EXTERN		WORD 		y_coordinate;

void Can_App_Signal_Init (void);
void Can_App_RRM_060_OnChange(void);
void Can_App_RRM_395_OnChange(void);
void Can_App_AVM_070_OnWrite(void);
void Can_App_AVM_391_OnWrite (void);

extern  const BYTE NetworkMatrixInformationDataIdentifier[4];
extern  const BYTE FunctionSpecificationDataIdentifier[4];
extern  const BYTE DiagnosticDefinitionDataIdentifier[4];
extern 	const BYTE vehicleManufacturerSparePartNumberDataIdentifier[14];
extern  const BYTE systemSupplierIdentifierDataIdentifier[10];
extern  const BYTE SystemName[10];
extern  const BYTE systemSupplierECUHardwareVersionNumberDataIdentifier[2];
extern  const BYTE SystemSupplierECUSoftwareVersionNumberDataIdentifier[2];

extern  DWORD ECUSerialNumberDataIdentifier[4];
extern  DWORD VINDataIdentifier[5];
#endif