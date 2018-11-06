#define		_CAN_USER_C_
#include 	"Can_User.h"
#include 	"Com.h"
//DID list
/* 0xF120 */ const BYTE NetworkMatrixInformationDataIdentifier[4] = "V2.3";
/* 0xF121 */ const BYTE FunctionSpecificationDataIdentifier[4] = "V1.2";
/* 0xF122 */ const BYTE DiagnosticDefinitionDataIdentifier[4] = "V1.0";

/* 0xF187 */ const BYTE vehicleManufacturerSparePartNumberDataIdentifier[14] = "D7917-00100014";
/* 0xF18A */ const BYTE systemSupplierIdentifierDataIdentifier[10] = "101625";
/* 0xF197 */ const BYTE SystemName[10] = "N3_AVM";
/* 0xF193 */ const BYTE systemSupplierECUHardwareVersionNumberDataIdentifier[2] = "\2\1";
/* 0xF195 */ const BYTE SystemSupplierECUSoftwareVersionNumberDataIdentifier[2] = "\3\0";

/* 0xF18C */ DWORD ECUSerialNumberDataIdentifier[4]; //14 bytes
/* 0xF190 */ DWORD VINDataIdentifier[5]; // 17 bytes

void Can_App_Signal_Init (void)
{
	/* AVM_1 */
	AVM_St_sys = 0;
	AVM_St_ViewDisplay = 1;
//	Can_SendSignal(AVM_St_sys);
//	Can_SendSignal(AVM_St_ViewDisplay);
//	Can_SendSignal(AVM_St_Calibration);
}
void Can_App_RRM_060_OnChange(void)    	/* event, CAN-->AVM */
{
	/* Can bus data receive code */
	
	/* Update data */
	Frm_RRM060.Data[0] = (BYTE)((Calibrate_start & 0xFF000000) >> 24);	/* Calibrate_start */
	Frm_RRM060.Data[1] = (BYTE)((Calibrate_start & 0x00FF0000) >> 16);
	Frm_RRM060.Data[2] = (BYTE)((Calibrate_start & 0x0000FF00) >> 8);
	Frm_RRM060.Data[3] = (BYTE)((Calibrate_start & 0x000000FF));
	Frm_RRM060.Data[4] = (BYTE)((time_information & 0x00FF0000) >> 16);	/* time_information */
	Frm_RRM060.Data[5] = (BYTE)((time_information & 0x0000FF00) >> 8);
	Frm_RRM060.Data[6] = (BYTE)((time_information & 0x000000FF));
	Frm_RRM060.Data[7] = cali_info_req;					/* cali_info_req */
	SetTxFlag(FRM_AVM_CALI_FLAG);
}

void Can_App_AVM_070_OnWrite(void)	/* event, AVM-->CAN */
{

}

void Can_App_AVM_391_OnWrite (void)	/* Cycle, AVM-->CAN */
{

}