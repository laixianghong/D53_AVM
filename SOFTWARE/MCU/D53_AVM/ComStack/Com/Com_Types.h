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
| 00.01.00    2015-08-04                           first version
|-------------------------------------------------------------------------------
*/

#ifndef _COM_TYPES_H_
#define _COM_TYPES_H_

/*******************************************************************************
*   Includes
*******************************************************************************/
#include"ComStack_Types.h"

/*******************************************************************************
*   define the data type for COM
*******************************************************************************/
#define Com_IpduGroupVector uint32

/*******************************************************************************
*   Macro define
*******************************************************************************/


#define COM_NULL    ((void*)0)
#define COM_YES                   1u
#define COM_NO                    0u
#define COM_RUNNING               COM_YES
#define COM_STOP                  COM_NO

#define COM_SERVICE_NOT_AVAILABLE    1u
#define COM_BUSY                    2u
#define COM_NONE_FUNCTION         3u
#define COM_OUT_OF_RANGE          4u
#define COM_ERROR                 5u

#define COM_DIRECTION_TX                0x01u
#define COM_DIRECTION_RX                0x02u
#define COM_IPDUCONTROLCOMMAND_START    0x01u
#define COM_IPDUCONTROLCOMMAND_STOP     0x02u

#define COM_RXTIMEOUTMONITOR_YES  1u
#define COM_RXTIMEOUTMONITOR_NO   0u

/* Message and Signal Send type */
#define COM_NOSENDTYPE               ((uint8)0x00) /*Ipdu and Signal*/
#define COM_SENDTYPECYCLIC           ((uint8)0x01) /*Ipdu*/
#define COM_SENDTYPEONWRITE          ((uint8)0x02) /*Signal*/
#define COM_SENDTYPEONCHANGE         ((uint8)0x04) /*Signal*/
#define COM_SENDTYPEIFACTIVE         ((uint8)0x08) /*Signal*/
#define COM_SENDTYPEREPETITION       ((uint8)0x10) /*Signal*/
#define COM_SENDTYPETIMEOUTMONITOR   ((uint8)0x20) /*Ipdu*/
#define COM_SENDTYPERESERVED         ((uint8)0x40)
#define COM_SENDTYPEONEVENT       ((uint8)0x06)
#define COM_TXREQUEST             ((uint8)0x80)
#define COM_TXNOREQUEST           ((uint8)0x7F)

/*******************************************************************************
*   data type definitions
*******************************************************************************/
typedef P2FUNC(void, TYPEDEF, Com_TOIndicationType) (void);
typedef P2FUNC(void, TYPEDEF, Com_RxIndicationType) (void);
typedef P2FUNC(void, TYPEDEF, Com_TxConfirmationType) (void);
typedef P2FUNC(void, TYPEDEF, Com_ErrIndicationType) (NotifResultType Result);
typedef P2FUNC(void, TYPEDEF, Com_LpduRxStartIndicationType)  
    (BufReq_ReturnType Result);

typedef P2FUNC(void, TYPEDEF, Com_SendSignalType) 
    (P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue);

typedef P2FUNC(void, TYPEDEF, Com_ReceiveSignalType) 
    (P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue);

typedef unsigned char  Com_IpduGroupIdType;
typedef unsigned short Com_SignalIdType;
typedef unsigned char  Com_SignalTxPropertyType;
typedef struct
{
    PduLengthType Length;
    P2VAR(uint8, TYPEDEF, COM_APPL_DATA) Data_p;
}Com_LpduType;

/*******************************************************************************
*   Type define
*******************************************************************************/
typedef void   Com_SigInActiveType ;

typedef struct{
    PduIdType  TxPduId;
    Com_SignalTxPropertyType  SigTxProperty;                                                                                 
    P2CONST(Com_SigInActiveType, TYPEDEF, COM_CONFIG_DATA) aubSigInActiveValue;
}Com_TxSigTableType;

typedef struct{
    PduIdType  RxPduId;
    Com_SignalTxPropertyType  SigTxProperty;
}Com_RxSigTableType;

/*******************************************************************************
*   receive timeout messages struct
*******************************************************************************/
typedef struct
{
    boollean TOMonitored;
    uint16  RxTOTimer;    
}Com_RxIpduTableType;

/* for signal gateway */
typedef struct 
{
    PduIdType RxPduId;
    uint16 OffsetInSignalGatewayInfo;
    uint16 SigGWNum; 
}Com_SignalGatewayIpduTableType;

typedef struct
{
    Com_SignalIdType RxSignalId;
    Com_SignalIdType TxSignalId; 
}Com_SignalGatewayTableType;

typedef struct
{
    PduIdType  IpduId;
    boollean IpduDirecttion;
}Com_GroupIpduTableType;
typedef struct
{
    PduIdType IpduGroupPosition;
    PduIdType IpduNumInGroup;
}Com_IpduGroupTableType;


#endif



