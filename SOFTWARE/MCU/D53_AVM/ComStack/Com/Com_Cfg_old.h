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
#define COM_TXIPDUAVM_0x341    (0U)
/******************************************************************************
*    number of Tx object Signal                                                
******************************************************************************/
#define COM_TXSIGNUM    (7U)
/******************************************************************************
*    Handles of send signals                                                  
******************************************************************************/
/*AVM_0x341 N3V2_BCAN_AVM*/
#define COM_TXSIGAVM_St_sys    (0U)
#define COM_TXSIGAVM_St_ViewDisplay    (1U)
#define COM_TXSIGAVM_St_Calibration    (2U)
#define COM_TXSIGAVM_L_FrontCamCaliFault    (3U)
#define COM_TXSIGAVM_L_RearCamCaliFault    (4U)
#define COM_TXSIGAVM_R_FrontCamCaliFault    (5U)
#define COM_TXSIGAVM_R_RearCamCaliFault    (6U)

/******************************************************************************
*    Send Signal structures                                                    
******************************************************************************/
typedef struct {
    uint8 AVM_St_sys : 1;
    uint8 unused0 : 7;
    uint8 AVM_St_ViewDisplay : 4;
    uint8 AVM_St_Calibration : 4;
    uint8 AVM_L_FrontCamCaliFault : 1;
    uint8 AVM_L_RearCamCaliFault : 1;
    uint8 AVM_R_FrontCamCaliFault : 1;
    uint8 AVM_R_RearCamCaliFault : 1;
    uint8 unused1_Byte0 : 4;
    uint8 unused1_Byte1 : 8;
}IpduAVM_0x341_Type;


/******************************************************************************
*    Send Message unions                                                       
******************************************************************************/
typedef union {
    IpduAVM_0x341_Type  Ipdu;
    uint8  _c[4];
}IpduAVM_0x341_bufType;


/******************************************************************************
*    Databuffer for sended objects                                             
******************************************************************************/
#define COM_START_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"
extern VAR(IpduAVM_0x341_bufType, COM_PRIVATE_DATA) TxIpduAVM_0x341;
#define COM_STOP_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"

/******************************************************************************
*    Databuffer for Sended Message default Value                               
******************************************************************************/
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"
extern CONST(IpduAVM_0x341_bufType, COM_CONFIG_CONST)  TxIpduAVM_0x341DefaultValue;
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"

#if (COM_TXIPDUNUM >= 1u)
/******************************************************************************
*    used for application:message tx timeout indication Function               
******************************************************************************/
#ifdef COM_ENABLE_TXTOINDFUN 
extern void AppIpduAVM_0x341_TxTOIndication(void);
#endif

/******************************************************************************
*    Ipdu Tx Confirmation function declare                                     
******************************************************************************/
#ifdef COM_ENABLE_TXCONFIRMATIONFUN 
extern void AppIpduAVM_0x341_Conf(void);
#endif

#endif /*#if (COM_TXIPDUNUM>=1)*/ 

/******************************************************************************
*    number of Rx object                                                       
******************************************************************************/
#define COM_RXIPDUNUM    (6U)
/******************************************************************************
*    Handles of receive messages                                                  
******************************************************************************/
#define COM_RXIPDUSAS_0x224    (0U)
#define COM_RXIPDUABS_0x330    (1U)
#define COM_RXIPDUBCM_0x350    (2U)
#define COM_RXIPDUMP5_0x361    (3U)
#define COM_RXIPDUMP5_0x366    (4U)
#define COM_RXIPDUMp5_0x367    (5U)
/******************************************************************************
*    the buffer size of Message received                                       
******************************************************************************/
#define COM_RXIPDUSAS_0x224_BUFFER_SIZE    (8U)
#define COM_RXIPDUABS_0x330_BUFFER_SIZE    (8U)
#define COM_RXIPDUBCM_0x350_BUFFER_SIZE    (8U)
#define COM_RXIPDUMP5_0x361_BUFFER_SIZE    (4U)
#define COM_RXIPDUMP5_0x366_BUFFER_SIZE    (8U)
#define COM_RXIPDUMp5_0x367_BUFFER_SIZE    (5U)
/******************************************************************************
*    number of Rx object Signal                                                
******************************************************************************/
#define COM_RXSIGNUM    (18U)
/******************************************************************************
*    Handles of receive signals                                                  
******************************************************************************/
/*SAS_0x224 N3V2_BCAN_AVM*/
#define COM_RXSIGSteeringAngle    (0U)
#define COM_RXSIGAngleFailure    (1U)
#define COM_RXSIGMessageCounter    (2U)
#define COM_RXSIGCRCCheck    (3U)
/*ABS_0x330 N3V2_BCAN_AVM*/
#define COM_RXSIGABS_Vehicle_speed_valid    (4U)
#define COM_RXSIGvehicle_speed    (5U)
#define COM_RXSIGABS2_RollingCounter    (6U)
#define COM_RXSIGABS2_CheckSum    (7U)
/*BCM_0x350 N3V2_BCAN_AVM*/
#define COM_RXSIGBCM_TurnIndicatorLeft    (8U)
#define COM_RXSIGBCM_TurnIndicatorRight    (9U)
#define COM_RXSIGBCM_ReverseGearSwitchStatus    (10U)
/*MP5_0x361 N3V2_BCAN_AVM*/
#define COM_RXSIGMP5_AVM_SwitchRequest    (11U)
/*MP5_0x366 N3V2_BCAN_AVM*/
#define COM_RXSIGCalibrate_start    (12U)
#define COM_RXSIGcali_info_req    (13U)
#define COM_RXSIGtime_information    (14U)
/*Mp5_0x367 N3V2_BCAN_AVM*/
#define COM_RXSIGx_coordinate    (15U)
#define COM_RXSIGy_coordinate    (16U)
#define COM_RXSIGtouch_state    (17U)

/******************************************************************************
*    Receive Signal structures                                                    
******************************************************************************/
typedef struct {
    uint8 SteeringAngle_Byte1 : 8;
    uint8 SteeringAngle_Byte0 : 8;
    uint8 unused0_Byte0 : 8;
    uint8 unused0_Byte1 : 7;
    uint8 AngleFailure : 1;
    uint8 unused1_Byte0 : 8;
    uint8 unused1_Byte1 : 4;
    uint8 MessageCounter : 4;
    uint8 unused2 : 8;
    uint8 CRCCheck : 8;
}IpduSAS_0x224_Type;

typedef struct {
    uint8 unused0 : 7;
    uint8 ABS_Vehicle_speed_valid : 1;
    uint8 vehicle_speed_Byte1 : 8;
    uint8 vehicle_speed_Byte0 : 8;
    uint8 unused1_Byte0 : 8;
    uint8 unused1_Byte1 : 8;
    uint8 unused1_Byte2 : 8;
    uint8 unused1_Byte3 : 4;
    uint8 ABS2_RollingCounter : 4;
    uint8 ABS2_CheckSum : 8;
}IpduABS_0x330_Type;

typedef struct {
    uint8 unused0 : 8;
    uint8 BCM_TurnIndicatorLeft : 2;
    uint8 BCM_TurnIndicatorRight : 2;
    uint8 unused1_Byte0 : 4;
    uint8 unused1_Byte1 : 8;
    uint8 unused1_Byte2 : 5;
    uint8 BCM_ReverseGearSwitchStatus : 1;
    uint8 unused2_Byte0 : 2;
    uint8 unused2_Byte1 : 8;
    uint8 unused2_Byte2 : 8;
    uint8 unused2_Byte3 : 8;
    uint8 unused2_Byte4 : 8;
}IpduBCM_0x350_Type;

typedef struct {
    uint8 MP5_AVM_SwitchRequest : 4;
    uint8 unused0_Byte0 : 4;
    uint8 unused0_Byte1 : 8;
    uint8 unused0_Byte2 : 8;
    uint8 unused0_Byte3 : 8;
}IpduMP5_0x361_Type;

typedef struct {
    uint8 Calibrate_start_Byte3 : 8;
    uint8 Calibrate_start_Byte2 : 8;
    uint8 Calibrate_start_Byte1 : 8;
    uint8 Calibrate_start_Byte0 : 8;
    uint8 cali_info_req : 1;
    uint8 unused0 : 7;
    uint8 time_information_Byte2 : 8;
    uint8 time_information_Byte1 : 8;
    uint8 time_information_Byte0 : 8;
}IpduMP5_0x366_Type;

typedef struct {
    uint8 x_coordinate_Byte1 : 8;
    uint8 x_coordinate_Byte0 : 8;
    uint8 y_coordinate_Byte1 : 8;
    uint8 y_coordinate_Byte0 : 8;
    uint8 touch_state : 8;
}IpduMp5_0x367_Type;


/******************************************************************************
*    Receive Message unions                                                       
******************************************************************************/
typedef union {
    IpduSAS_0x224_Type  Ipdu;
    uint8  _c[8];
}IpduSAS_0x224_bufType;

typedef union {
    IpduABS_0x330_Type  Ipdu;
    uint8  _c[8];
}IpduABS_0x330_bufType;

typedef union {
    IpduBCM_0x350_Type  Ipdu;
    uint8  _c[8];
}IpduBCM_0x350_bufType;

typedef union {
    IpduMP5_0x361_Type  Ipdu;
    uint8  _c[4];
}IpduMP5_0x361_bufType;

typedef union {
    IpduMP5_0x366_Type  Ipdu;
    uint8  _c[8];
}IpduMP5_0x366_bufType;

typedef union {
    IpduMp5_0x367_Type  Ipdu;
    uint8  _c[5];
}IpduMp5_0x367_bufType;


/******************************************************************************
*    Databuffer for Receive objects                                             
******************************************************************************/
#define COM_START_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"
extern VAR(IpduSAS_0x224_bufType, COM_PRIVATE_DATA)  RxIpduSAS_0x224;
extern VAR(IpduABS_0x330_bufType, COM_PRIVATE_DATA)  RxIpduABS_0x330;
extern VAR(IpduBCM_0x350_bufType, COM_PRIVATE_DATA)  RxIpduBCM_0x350;
extern VAR(IpduMP5_0x361_bufType, COM_PRIVATE_DATA)  RxIpduMP5_0x361;
extern VAR(IpduMP5_0x366_bufType, COM_PRIVATE_DATA)  RxIpduMP5_0x366;
extern VAR(IpduMp5_0x367_bufType, COM_PRIVATE_DATA)  RxIpduMp5_0x367;
#define COM_STOP_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"

/******************************************************************************
*    Databuffer for Receive Message default Value                               
******************************************************************************/
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"
extern CONST(IpduSAS_0x224_bufType, COM_CONFIG_CONST)  RxIpduSAS_0x224DefaultValue;
extern CONST(IpduABS_0x330_bufType, COM_CONFIG_CONST)  RxIpduABS_0x330DefaultValue;
extern CONST(IpduBCM_0x350_bufType, COM_CONFIG_CONST)  RxIpduBCM_0x350DefaultValue;
extern CONST(IpduMP5_0x361_bufType, COM_CONFIG_CONST)  RxIpduMP5_0x361DefaultValue;
extern CONST(IpduMP5_0x366_bufType, COM_CONFIG_CONST)  RxIpduMP5_0x366DefaultValue;
extern CONST(IpduMp5_0x367_bufType, COM_CONFIG_CONST)  RxIpduMp5_0x367DefaultValue;
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"

#if (COM_RXIPDUNUM >= 1u)

/******************************************************************************
*    rx Ipdu timeout indication function Declare                               
******************************************************************************/
#ifdef COM_ENABLE_RXTOINDFUN 
extern void AppRxIpduSAS_0x224_TimeOutInd(void);
extern void AppRxIpduABS_0x330_TimeOutInd(void);
extern void AppRxIpduBCM_0x350_TimeOutInd(void);
extern void AppRxIpduMP5_0x361_TimeOutInd(void);
extern void AppRxIpduMP5_0x366_TimeOutInd(void);
extern void AppRxIpduMp5_0x367_TimeOutInd(void);
#endif

/******************************************************************************
*    Rx indication function Declare                                            
******************************************************************************/
#ifdef COM_ENABLE_RXINDICATIONFUN 
extern void AppIpduSAS_0x224_Ind(void);
extern void AppIpduABS_0x330_Ind(void);
extern void AppIpduBCM_0x350_Ind(void);
extern void AppIpduMP5_0x361_Ind(void);
extern void AppIpduMP5_0x366_Ind(void);
extern void AppIpduMp5_0x367_Ind(void);
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
#define COM_GROUPIPDUNUM    (7U)
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



