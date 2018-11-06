/*
|NOTICE
|-------------------------------------------------------------------------------
|                              
|   This software is the property of GUANGDA Technologies. 
|
|END----------------------------------------------------------------------------
|FILE INFORMATION START
|-------------------------------------------------------------------------------
|     File Name: 
|   Description: Implementation of the CAN driver
|Target systems: RRS
|    Target CPU: upd78F1828
|           IDE: CS+ V20200                           
|      Compiler: CC78k0r
|END----------------------------------------------------------------------------
|PROJECT INFORMATION START 
|-------------------------------------------------------------------------------
| Project Name: 
|
|  Description: 
|
|END----------------------------------------------------------------------------
|REVISION HISTORY
|-------------------------------------------------------------------------------
| Version        Date          Author              Description
| --------   -----------      ---------     ------------------------------------
| 00.01.00    2015-09-30                           first version
|-------------------------------------------------------------------------------
*/
#ifndef _COM_CFG_H_
#define _COM_CFG_H_

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Com_Types.h"
/*adding underlying layer's head files here if necessary*/ 
#include "CanIf.h" 
/*******************************************************************************
*   Macro define
*******************************************************************************/
#define COM_VERSION_INFO_API                         STD_OFF
#define COM_ENABLE_NONSENDTYPEONLY
#define COM_ENABLE_TXCONFIRMATIONFUN
#define COM_ENABLE_TXTOINDFUN
#define COM_ENABLE_RXINDICATIONFUN
#define COM_ENABLE_RXTOINDFUN
#define COM_TXMAIN_FUNCTION_PERIOD                   (10U)
#define COM_RXMAIN_FUNCTION_PERIOD                   (10U)
#define COM_SIGNALROUTINEMAIN_FUNCTION_PERIOD        (10U)

/******************************************************************************
*    number of Tx object                                                       
******************************************************************************/
#define COM_TXIPDUNUM    (1U)
/******************************************************************************
*    Handles of send messages                                                  
******************************************************************************/
#define COM_TXIPDUAVM_STATE    (0U)
/******************************************************************************
*    number of Tx object Signal                                                
******************************************************************************/
#define COM_TXSIGNUM    (2U)
/******************************************************************************
*    Handles of send signals                                                  
******************************************************************************/
/*AVM_STATE D53_AVM*/
#define COM_TXSIGAVM_360_DisplayViewStatus    (0U)
#define COM_TXSIGAVM_360_AlarmStatus    (1U)

/******************************************************************************
*    Send Signal structures                                                    
******************************************************************************/
typedef struct {
    uint8 AVM_360_DisplayViewStatus : 5;
    uint8 AVM_360_AlarmStatus : 3;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduAVM_STATE_Type;


/******************************************************************************
*    Send Message unions                                                       
******************************************************************************/
typedef union {
    IpduAVM_STATE_Type  Ipdu;
    uint8  _c[8];
}IpduAVM_STATE_bufType;


/******************************************************************************
*    Databuffer for sended objects                                             
******************************************************************************/
#define COM_START_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"
extern VAR(IpduAVM_STATE_bufType, COM_PRIVATE_DATA) TxIpduAVM_STATE;
#define COM_STOP_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"

/******************************************************************************
*    Databuffer for Sended Message default Value                               
******************************************************************************/
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"
extern CONST(IpduAVM_STATE_bufType, COM_CONFIG_CONST)  TxIpduAVM_STATEDefaultValue;
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"

#if (COM_TXIPDUNUM >= 1u)
/******************************************************************************
*    used for application:message tx timeout indication Function               
******************************************************************************/
#ifdef COM_ENABLE_TXTOINDFUN 
extern void AppIpduAVM_STATE_TxTOIndication(void);
#endif

/******************************************************************************
*    Ipdu Tx Confirmation function declare                                     
******************************************************************************/
#ifdef COM_ENABLE_TXCONFIRMATIONFUN 
extern void AppIpduAVM_STATE_Conf(void);
#endif

#endif /*#if (COM_TXIPDUNUM>=1)*/ 

/******************************************************************************
*    number of Rx object                                                       
******************************************************************************/
#define COM_RXIPDUNUM    (12U)
/******************************************************************************
*    Handles of receive messages                                                  
******************************************************************************/
#define COM_RXIPDUGW_CommAVailability    (0U)
#define COM_RXIPDUIBCM4    (1U)
#define COM_RXIPDUGW_TCU1    (2U)
#define COM_RXIPDUGW_ESC2    (3U)
#define COM_RXIPDUGW_SAS_inf    (4U)
#define COM_RXIPDUIBCM2    (5U)
#define COM_RXIPDUIBCM3    (6U)
#define COM_RXIPDUGW_PSA2_VCU5    (7U)
#define COM_RXIPDUMP5_2    (8U)
#define COM_RXIPDUAPA2    (9U)
#define COM_RXIPDUMP5_STATE    (10U)
#define COM_RXIPDUMP5_3    (11U)
/******************************************************************************
*    the buffer size of Message received                                       
******************************************************************************/
#define COM_RXIPDUGW_CommAVailability_BUFFER_SIZE    (8U)
#define COM_RXIPDUIBCM4_BUFFER_SIZE    (8U)
#define COM_RXIPDUGW_TCU1_BUFFER_SIZE    (8U)
#define COM_RXIPDUGW_ESC2_BUFFER_SIZE    (8U)
#define COM_RXIPDUGW_SAS_inf_BUFFER_SIZE    (8U)
#define COM_RXIPDUIBCM2_BUFFER_SIZE    (8U)
#define COM_RXIPDUIBCM3_BUFFER_SIZE    (8U)
#define COM_RXIPDUGW_PSA2_VCU5_BUFFER_SIZE    (8U)
#define COM_RXIPDUMP5_2_BUFFER_SIZE    (8U)
#define COM_RXIPDUAPA2_BUFFER_SIZE    (8U)
#define COM_RXIPDUMP5_STATE_BUFFER_SIZE    (8U)
#define COM_RXIPDUMP5_3_BUFFER_SIZE    (8U)
/******************************************************************************
*    number of Rx object Signal                                                
******************************************************************************/
#define COM_RXSIGNUM    (31U)
/******************************************************************************
*    Handles of receive signals                                                  
******************************************************************************/
/*GW_CommAVailability D53_AVM*/
#define COM_RXSIGGW_LostToESC    (0U)
#define COM_RXSIGGW_LostToTCU    (1U)
#define COM_RXSIGGW_LostToVCU    (2U)
/*IBCM4 D53_AVM*/
#define COM_RXSIGReverseGearInMaualTransValidity    (3U)
#define COM_RXSIGReverseGearInMaualTrans    (4U)
/*GW_TCU1 D53_AVM*/
#define COM_RXSIGGW_TCU_ShiftLeverPosValidFlag    (5U)
#define COM_RXSIGGW_TCU_PRNDLSt    (6U)
/*GW_ESC2 D53_AVM*/
#define COM_RXSIGGW_ESC_VehSpd    (7U)
/*GW_SAS_inf D53_AVM*/
#define COM_RXSIGGW_ESC_EPS_SAS_SteeriAngle    (8U)
/*IBCM2 D53_AVM*/
#define COM_RXSIGBCM_LowBeamStatus    (9U)
#define COM_RXSIGBCM_LFDoorSwitchSt    (10U)
#define COM_RXSIGBCM_RFDoorSwitchSt    (11U)
#define COM_RXSIGBCM_RRDoorSwitchSt    (12U)
#define COM_RXSIGBCM_LRDoorSwitchSt    (13U)
/*IBCM3 D53_AVM*/
#define COM_RXSIGBCM_IgnitionSt    (14U)
/*GW_PSA2_VCU5 D53_AVM*/
#define COM_RXSIGGW_VCU_Gear    (15U)
/*MP5_2 D53_AVM*/
#define COM_RXSIGMP5_Language_Set    (16U)
/*APA2 D53_AVM*/
#define COM_RXSIGAPAParkAssistantRearRegion2ObjSt    (17U)
#define COM_RXSIGAPAParkAssistantRearRegion1ObjSt    (18U)
#define COM_RXSIGAPAParkingAssisRearExtenedDist    (19U)
#define COM_RXSIGAPAParkAssistantRearRegion4ObjSt    (20U)
#define COM_RXSIGAPAParkAssistantRearRegion3ObjSt    (21U)
/*MP5_STATE D53_AVM*/
#define COM_RXSIGMP5_Active_commnd    (22U)
#define COM_RXSIGMP5_Pupose_Key    (23U)
#define COM_RXSIGMP5_Da_screen_state    (24U)
#define COM_RXSIGMP5_Sideview_Control    (25U)
#define COM_RXSIGMP5_Touch_X_Coordinate    (26U)
#define COM_RXSIGMP5_Touch_Y_Coordinate    (27U)
#define COM_RXSIGMP5_AVMLineSetSwitch    (28U)
#define COM_RXSIGMP5_Touch_ButtonPress    (29U)
/*MP5_3 D53_AVM*/
#define COM_RXSIGMP5_AVM_CalibrateStart    (30U)

/******************************************************************************
*    Receive Signal structures                                                    
******************************************************************************/
typedef struct {
    uint8 unused0 : 2;
    uint8 GW_LostToESC : 2;
    uint8 GW_LostToTCU : 2;
    uint8 unused1_Byte0 : 2;
    uint8 unused1_Byte1 : 8;
    uint8 unused1_Byte2 : 8;
    uint8 unused1_Byte3 : 6;
    uint8 GW_LostToVCU : 2;
    uint8 unused2_Byte0 : 8;
    uint8 unused2_Byte1 : 8;
    uint8 unused2_Byte2 : 8;
    uint8 unused2_Byte3 : 8;
}IpduGW_CommAVailability_Type;

typedef struct {
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 ReverseGearInMaualTransValidity : 1;
    uint8 ReverseGearInMaualTrans : 2;
    uint8 unused1_Byte0 : 5;
    uint8 unused1_Byte1 : 8;
    uint8 unused1_Byte2 : 8;
    uint8 unused1_Byte3 : 8;
    uint8 unused1_Byte4 : 8;
    uint8 unused1_Byte5 : 8;
}IpduIBCM4_Type;

typedef struct {
    uint8 unused0 : 7;
    uint8 GW_TCU_ShiftLeverPosValidFlag : 1;
    uint8 unused1_Byte0 : 8;
    uint8 unused1_Byte1 : 8;
    uint8 unused1_Byte2 : 8;
    uint8 unused1_Byte3 : 8;
    uint8 unused1_Byte4 : 8;
    uint8 GW_TCU_PRNDLSt : 8;
    uint8 unused2 : 8;
}IpduGW_TCU1_Type;

typedef struct {
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 GW_ESC_VehSpd_Byte1 : 8;
    uint8 GW_ESC_VehSpd_Byte0 : 8;
}IpduGW_ESC2_Type;

typedef struct {
    uint8 GW_ESC_EPS_SAS_SteeriAngle_Byte1 : 8;
    uint8 GW_ESC_EPS_SAS_SteeriAngle_Byte0 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
}IpduGW_SAS_inf_Type;

typedef struct {
    uint8 unused0 : 8;
    uint8 BCM_LowBeamStatus : 1;
    uint8 unused1 : 2;
    uint8 BCM_LFDoorSwitchSt : 1;
    uint8 BCM_RFDoorSwitchSt : 1;
    uint8 BCM_RRDoorSwitchSt : 1;
    uint8 BCM_LRDoorSwitchSt : 1;
    uint8 unused2_Byte0 : 1;
    uint8 unused2_Byte1 : 8;
    uint8 unused2_Byte2 : 8;
    uint8 unused2_Byte3 : 8;
    uint8 unused2_Byte4 : 8;
    uint8 unused2_Byte5 : 8;
    uint8 unused2_Byte6 : 8;
}IpduIBCM2_Type;

typedef struct {
    uint8 BCM_IgnitionSt : 2;
    uint8 unused0_Byte0 : 6;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
    uint8 unused0_Byte7 : 8;
}IpduIBCM3_Type;

typedef struct {
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 2;
    uint8 GW_VCU_Gear : 3;
    uint8 unused1_Byte0 : 3;
    uint8 unused1_Byte1 : 8;
    uint8 unused1_Byte2 : 8;
    uint8 unused1_Byte3 : 8;
    uint8 unused1_Byte4 : 8;
    uint8 unused1_Byte5 : 8;
    uint8 unused1_Byte6 : 8;
}IpduGW_PSA2_VCU5_Type;

typedef struct {
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 MP5_Language_Set : 3;
    uint8 unused1_Byte0 : 5;
    uint8 unused1_Byte1 : 8;
    uint8 unused1_Byte2 : 8;
    uint8 unused1_Byte3 : 8;
    uint8 unused1_Byte4 : 8;
    uint8 unused1_Byte5 : 8;
}IpduMP5_2_Type;

typedef struct {
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 APAParkingAssisRearExtenedDist_Byte1 : 2;
    uint8 APAParkAssistantRearRegion2ObjSt : 3;
    uint8 APAParkAssistantRearRegion1ObjSt : 3;
    uint8 APAParkingAssisRearExtenedDist_Byte0 : 8;
    uint8 unused1 : 2;
    uint8 APAParkAssistantRearRegion4ObjSt : 3;
    uint8 APAParkAssistantRearRegion3ObjSt : 3;
    uint8 unused2 : 8;
}IpduAPA2_Type;

typedef struct {
    uint8 MP5_Active_commnd : 2;
    uint8 MP5_Pupose_Key : 2;
    uint8 MP5_Da_screen_state : 2;
    uint8 MP5_Sideview_Control : 2;
    uint8 MP5_Touch_X_Coordinate_Byte1 : 8;
    uint8 MP5_Touch_X_Coordinate_Byte0 : 8;
    uint8 MP5_Touch_Y_Coordinate_Byte1 : 8;
    uint8 MP5_Touch_Y_Coordinate_Byte0 : 8;
    uint8 unused0 : 3;
    uint8 MP5_AVMLineSetSwitch : 1;
    uint8 unused1 : 3;
    uint8 MP5_Touch_ButtonPress : 1;
    uint8 unused2_Byte0 : 8;
    uint8 unused2_Byte1 : 8;
}IpduMP5_STATE_Type;

typedef struct {
    uint8 MP5_AVM_CalibrateStart : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
    uint8 unused0_Byte4 : 8;
    uint8 unused0_Byte5 : 8;
    uint8 unused0_Byte6 : 8;
}IpduMP5_3_Type;


/******************************************************************************
*    Receive Message unions                                                       
******************************************************************************/
typedef union {
    IpduGW_CommAVailability_Type  Ipdu;
    uint8  _c[8];
}IpduGW_CommAVailability_bufType;

typedef union {
    IpduIBCM4_Type  Ipdu;
    uint8  _c[8];
}IpduIBCM4_bufType;

typedef union {
    IpduGW_TCU1_Type  Ipdu;
    uint8  _c[8];
}IpduGW_TCU1_bufType;

typedef union {
    IpduGW_ESC2_Type  Ipdu;
    uint8  _c[8];
}IpduGW_ESC2_bufType;

typedef union {
    IpduGW_SAS_inf_Type  Ipdu;
    uint8  _c[8];
}IpduGW_SAS_inf_bufType;

typedef union {
    IpduIBCM2_Type  Ipdu;
    uint8  _c[8];
}IpduIBCM2_bufType;

typedef union {
    IpduIBCM3_Type  Ipdu;
    uint8  _c[8];
}IpduIBCM3_bufType;

typedef union {
    IpduGW_PSA2_VCU5_Type  Ipdu;
    uint8  _c[8];
}IpduGW_PSA2_VCU5_bufType;

typedef union {
    IpduMP5_2_Type  Ipdu;
    uint8  _c[8];
}IpduMP5_2_bufType;

typedef union {
    IpduAPA2_Type  Ipdu;
    uint8  _c[8];
}IpduAPA2_bufType;

typedef union {
    IpduMP5_STATE_Type  Ipdu;
    uint8  _c[8];
}IpduMP5_STATE_bufType;

typedef union {
    IpduMP5_3_Type  Ipdu;
    uint8  _c[8];
}IpduMP5_3_bufType;


/******************************************************************************
*    Databuffer for Receive objects                                             
******************************************************************************/
#define COM_START_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"
extern VAR(IpduGW_CommAVailability_bufType, COM_PRIVATE_DATA)  RxIpduGW_CommAVailability;
extern VAR(IpduIBCM4_bufType, COM_PRIVATE_DATA)  RxIpduIBCM4;
extern VAR(IpduGW_TCU1_bufType, COM_PRIVATE_DATA)  RxIpduGW_TCU1;
extern VAR(IpduGW_ESC2_bufType, COM_PRIVATE_DATA)  RxIpduGW_ESC2;
extern VAR(IpduGW_SAS_inf_bufType, COM_PRIVATE_DATA)  RxIpduGW_SAS_inf;
extern VAR(IpduIBCM2_bufType, COM_PRIVATE_DATA)  RxIpduIBCM2;
extern VAR(IpduIBCM3_bufType, COM_PRIVATE_DATA)  RxIpduIBCM3;
extern VAR(IpduGW_PSA2_VCU5_bufType, COM_PRIVATE_DATA)  RxIpduGW_PSA2_VCU5;
extern VAR(IpduMP5_2_bufType, COM_PRIVATE_DATA)  RxIpduMP5_2;
extern VAR(IpduAPA2_bufType, COM_PRIVATE_DATA)  RxIpduAPA2;
extern VAR(IpduMP5_STATE_bufType, COM_PRIVATE_DATA)  RxIpduMP5_STATE;
extern VAR(IpduMP5_3_bufType, COM_PRIVATE_DATA)  RxIpduMP5_3;
#define COM_STOP_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"

/******************************************************************************
*    Databuffer for Receive Message default Value                               
******************************************************************************/
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"
extern CONST(IpduGW_CommAVailability_bufType, COM_CONFIG_CONST)  RxIpduGW_CommAVailabilityDefaultValue;
extern CONST(IpduIBCM4_bufType, COM_CONFIG_CONST)  RxIpduIBCM4DefaultValue;
extern CONST(IpduGW_TCU1_bufType, COM_CONFIG_CONST)  RxIpduGW_TCU1DefaultValue;
extern CONST(IpduGW_ESC2_bufType, COM_CONFIG_CONST)  RxIpduGW_ESC2DefaultValue;
extern CONST(IpduGW_SAS_inf_bufType, COM_CONFIG_CONST)  RxIpduGW_SAS_infDefaultValue;
extern CONST(IpduIBCM2_bufType, COM_CONFIG_CONST)  RxIpduIBCM2DefaultValue;
extern CONST(IpduIBCM3_bufType, COM_CONFIG_CONST)  RxIpduIBCM3DefaultValue;
extern CONST(IpduGW_PSA2_VCU5_bufType, COM_CONFIG_CONST)  RxIpduGW_PSA2_VCU5DefaultValue;
extern CONST(IpduMP5_2_bufType, COM_CONFIG_CONST)  RxIpduMP5_2DefaultValue;
extern CONST(IpduAPA2_bufType, COM_CONFIG_CONST)  RxIpduAPA2DefaultValue;
extern CONST(IpduMP5_STATE_bufType, COM_CONFIG_CONST)  RxIpduMP5_STATEDefaultValue;
extern CONST(IpduMP5_3_bufType, COM_CONFIG_CONST)  RxIpduMP5_3DefaultValue;
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"

#if (COM_RXIPDUNUM >= 1u)

/******************************************************************************
*    rx Ipdu timeout indication function Declare                               
******************************************************************************/
#ifdef COM_ENABLE_RXTOINDFUN 
extern void AppRxIpduGW_CommAVailability_TimeOutInd(void);
extern void AppRxIpduIBCM4_TimeOutInd(void);
extern void AppRxIpduGW_TCU1_TimeOutInd(void);
extern void AppRxIpduGW_ESC2_TimeOutInd(void);
extern void AppRxIpduGW_SAS_inf_TimeOutInd(void);
extern void AppRxIpduIBCM2_TimeOutInd(void);
extern void AppRxIpduIBCM3_TimeOutInd(void);
extern void AppRxIpduGW_PSA2_VCU5_TimeOutInd(void);
extern void AppRxIpduMP5_2_TimeOutInd(void);
extern void AppRxIpduAPA2_TimeOutInd(void);
extern void AppRxIpduMP5_STATE_TimeOutInd(void);
extern void AppRxIpduMP5_3_TimeOutInd(void);
#endif

/******************************************************************************
*    Rx indication function Declare                                            
******************************************************************************/
#ifdef COM_ENABLE_RXINDICATIONFUN 
extern void AppIpduGW_CommAVailability_Ind(void);
extern void AppIpduIBCM4_Ind(void);
extern void AppIpduGW_TCU1_Ind(void);
extern void AppIpduGW_ESC2_Ind(void);
extern void AppIpduGW_SAS_inf_Ind(void);
extern void AppIpduIBCM2_Ind(void);
extern void AppIpduIBCM3_Ind(void);
extern void AppIpduGW_PSA2_VCU5_Ind(void);
extern void AppIpduMP5_2_Ind(void);
extern void AppIpduAPA2_Ind(void);
extern void AppIpduMP5_STATE_Ind(void);
extern void AppIpduMP5_3_Ind(void);
#endif

#endif /*#if (COM_RXIPDUNUM>=1)*/ 

/******************************************************************************
*    Signal Gateway                                                            
******************************************************************************/
#ifdef COM_ENABLE_ROUTESIGNAL
#define COM_GWIPDUNUM    (0U)
#define COM_GWSIGNUM     (0U)
#endif

/******************************************************************************
*    Ipdu Group                                                                
******************************************************************************/
#if((COM_TXIPDUNUM >= 1u) || (COM_RXIPDUNUM >= 1u))
#define COM_IPDUGROUPNUM    (2U)
#define COM_IPDUGROUP0    (0x1U)
#define COM_IPDUGROUP1    (0x2U)
#define COM_GROUPIPDUNUM    (13U)
#endif

/******************************************************************************
*    data declaration                                                          
******************************************************************************/
extern void Com_TxIpduCallout(PduIdType PduId, uint8 *DataPtr);
extern void Com_RxIpduCallout(PduIdType PduId, uint8 *DataPtr);

#if(COM_TXIPDUNUM >= 1u)
#define COM_START_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"

extern VAR(PduInfoType, COM_APPL_DATA) Com_TxIpdu[COM_TXIPDUNUM];

#define COM_STOP_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"

#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"

extern CONST(PduInfoType, COM_CONFIG_CONST)  Com_TxIpduInitTable[COM_TXIPDUNUM]; 
extern CONST(Com_TxSigTableType, COM_CONFIG_CONST)  Com_TxSigTable[COM_TXSIGNUM];
extern CONSTP2CONST(uint8,COM_CONFIG_CONST,COM_CONFIG_CONST) Com_TxIpduDefaultValue[COM_TXIPDUNUM];

#ifdef COM_ENABLE_TXCONFIRMATIONFUN
extern CONST(Com_TxConfirmationType, COM_CONFIG_CONST)  Com_TxIpduConfirmTable[COM_TXIPDUNUM];
#endif

#ifdef COM_ENABLE_TXTOINDFUN
extern CONST(Com_TOIndicationType, COM_CONFIG_CONST)  Com_TxIpduTOIndicationTable[COM_TXIPDUNUM];
#endif

#ifdef COM_ENABLE_LPDUTXERRINDFUN
extern CONST(Com_ErrIndicationType, COM_CONFIG_CONST)  Com_LpduTxErrIndicationTable[COM_TXIPDUNUM];
#endif

extern CONST(uint8, COM_CONFIG_CONST)  Com_TxIpduTable[COM_TXIPDUNUM];

#ifndef COM_ENABLE_NONSENDTYPEONLY

#ifdef COM_ENABLE_ACTIVEPORPERTY 
extern CONST(uint16, COM_CONFIG_CONST) Com_TxIpduFastCycleTable[COM_TXIPDUNUM];
extern CONST(uint8, COM_CONFIG_CONST) Com_TxIpduSigNum[COM_TXIPDUNUM];

extern FUNC(void, COM_PUBLIC_CODE) Com_ActiveSig
(
    Com_SignalIdType SignalId
);

extern FUNC(void, COM_PUBLIC_CODE) Com_DisactiveSig
(
    Com_SignalIdType SignalId
);

extern CONST(Com_SignalIdType, COM_CONFIG_CONST)  Com_TxSigOffsetTable[COM_TXIPDUNUM];

#endif

extern CONST(uint16, COM_CONFIG_CONST) Com_TxIpduTdelayTable[COM_TXIPDUNUM];
extern CONST(uint8, COM_CONFIG_CONST) Com_TxIpduRepNumTable[COM_TXIPDUNUM];
#endif /*#ifndef COM_ENABLE_NONSENDTYPEONLY*/

extern CONST(uint16, COM_CONFIG_CONST) Com_TxIpduCycleTable[COM_TXIPDUNUM]; 
extern CONST(uint16, COM_CONFIG_CONST) Com_TxIpduTimeOutTable[COM_TXIPDUNUM]; 
extern CONST(uint16, COM_CONFIG_CONST) Com_TxIpduOffsetTable[COM_TXIPDUNUM];

#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

#endif /*#if(COM_TXIPDUNUM>=1)*/

#if(COM_RXIPDUNUM >= 1u)

#ifdef COM_ENABLE_RXEXTEND
extern CONST(uint8, COM_CONFIG_CONST) Com_RxIpduSigNum[COM_RXIPDUNUM];
extern CONST(Com_SignalIdType, COM_CONFIG_CONST) Com_RxSigOffsetTable[COM_RXIPDUNUM];
#endif

extern CONST(PduInfoType, COM_CONFIG_CONST) Com_RxIpduInitTable[COM_RXIPDUNUM];
extern CONST(Com_RxSigTableType, COM_CONFIG_CONST) Com_RxSigTable[COM_RXSIGNUM];
extern CONST(Com_RxIpduTableType, COM_CONFIG_CONST) Com_RxIpduTable[COM_RXIPDUNUM];
extern CONSTP2CONST(uint8,COM_CONFIG_CONST,COM_CONFIG_CONST) Com_RxIpduDefaultValue[COM_RXIPDUNUM];

#ifdef COM_ENABLE_RXINDICATIONFUN
extern CONST(Com_RxIndicationType, COM_CONFIG_CONST) Com_RxIpduIndicationTable[COM_RXIPDUNUM]; 
#endif

#ifdef COM_ENABLE_RXTOINDFUN 
extern CONST(Com_TOIndicationType, COM_CONFIG_CONST) Com_RxIpduTOIndicationTable[COM_RXIPDUNUM];
#endif

#ifdef COM_ENABLE_LPDURXERRINDFUN
extern CONST(Com_ErrIndicationType, COM_CONFIG_CONST) Com_LpduRxErrIndicationTable[COM_RXIPDUNUM];
#endif

#ifdef COM_ENABLE_LPDURXSTARTINDIFUN
extern CONST(Com_LpduRxStartIndicationType, COM_CONFIG_CONST)  
             Com_LpduRxStartIndicationTable[COM_RXIPDUNUM];
#endif

#ifdef COM_ENABLE_RXTIMEOUTVALUE
extern  CONSTP2CONST(uint8,COM_CONFIG_CONST,COM_CONFIG_CONST) Com_RxIpduTimeoutValue[COM_RXIPDUNUM];
#endif

extern CONST(PduLengthType, COM_CONFIG_CONST)  Com_RxIpduBufferSize[COM_RXIPDUNUM];


#endif /*#if(COM_RXIPDUNUM>=1)*/


#if(COM_TXIPDUNUM >= 1u)
extern CONST(Com_SendSignalType, COM_CONFIG_CONST)  Com_SendSignalTable[COM_TXSIGNUM];
#endif


#if(COM_RXIPDUNUM >= 1u)
extern  CONST(Com_ReceiveSignalType, COM_CONFIG_CONST)   Com_ReceiveSignalTable[COM_RXSIGNUM];
#endif

#ifdef COM_ENABLE_ROUTESIGNAL
#if(COM_GWSIGNUM >= 1u)
extern CONST(Com_SignalGatewayIpduTableType, COM_CONFIG_CONST)  
             Com_SignalGatewayIpduTable[COM_GWIPDUNUM];
             
extern CONST(Com_SignalGatewayTableType, COM_CONFIG_CONST)  Com_SignalGatewayTable[COM_GWSIGNUM];
#endif /*#if(COM_GWSIGNUM>=1)*/
#endif /*#ifdef COM_ENABLE_ROUTESIGNAL*/


#if(COM_IPDUGROUPNUM >= 1u)
extern CONST(Com_GroupIpduTableType, COM_CONFIG_CONST)  Com_GroupIpduTable[COM_GROUPIPDUNUM];
extern CONST(Com_IpduGroupTableType, COM_CONFIG_CONST)  Com_IpduGroupTable[COM_IPDUGROUPNUM];
#endif

#if(COM_TXIPDUNUM >= 1u)
extern CONST(PduIdType, COM_CONFIG_CONST) Com_TxIpduIdMapTable[COM_TXIPDUNUM];
#define Com_TransmitLPDU(ComTxPduId,PduInfoPtr)     CanIf_Transmit(Com_TxIpduIdMapTable[ComTxPduId],PduInfoPtr) 
#define Com_Transmit(ComTxPduId,PduInfoPtr)	        CanIf_Transmit(Com_TxIpduIdMapTable[ComTxPduId],PduInfoPtr)
#endif

#endif



