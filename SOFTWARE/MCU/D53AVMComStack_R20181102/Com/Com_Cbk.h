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

#ifndef _COM_CBK_H_
#define _COM_CBK_H_
/*******************************************************************************
*   Includes
*******************************************************************************/
 #include "Com.h"


/*******************************************************************************
*   Function Declaration 
*******************************************************************************/
#define COM_START_SEC_PUBLIC_CODE
#include "MemMap.h"

#if (COM_TXIPDUNUM >= 1u) 

extern FUNC(void, COM_PUBLIC_CODE) Com_TxConfirmation
(
    PduIdType TxPduId
);

extern FUNC(BufReq_ReturnType, COM_PUBLIC_CODE) Com_CopyTxData
(
    PduIdType PduId, 
    P2CONST(PduInfoType, COM_APPL_DATA, COM_AUTOMOTIVE) PduInfoPtr,
    P2VAR(RetryInfoType, COM_APPL_DATA, COM_AUTOMOTIVE) RetryInfoPtr,
    P2VAR(PduLengthType, COM_APPL_DATA, COM_AUTOMOTIVE) TxDataCntPtr
);

extern FUNC(void, COM_PUBLIC_CODE) Com_TpTxConfirmation
(
    PduIdType PduId,
    NotifResultType Result
);

/*#if (COM_TXIPDUNUM >= 1u)*/
#endif

#if (COM_RXIPDUNUM >= 1u)

extern FUNC(void, COM_PUBLIC_CODE) Com_RxIndication
(
    PduIdType RxPduId,
    P2CONST(PduInfoType, COM_APPL_DATA, COM_AUTOMOTIVE) PduInfoPtr
);

extern FUNC(BufReq_ReturnType, COM_PUBLIC_CODE) Com_StartOfReception
(
    PduIdType ComRxPduId,
    PduLengthType TpSduLength,
    P2VAR(PduLengthType, COM_APPL_DATA, COM_AUTOMOTIVE) RxBufferSizePtr
);

extern FUNC(BufReq_ReturnType, COM_PUBLIC_CODE) Com_CopyRxData
(
    PduIdType PduId,
    P2CONST(PduInfoType, COM_APPL_DATA, COM_AUTOMOTIVE) PduInfoPointer,
    P2VAR(PduLengthType, COM_APPL_DATA, COM_AUTOMOTIVE) RxBufferSizePtr
);

extern FUNC(void, COM_PUBLIC_CODE) Com_TpRxIndication
(
    PduIdType PduId,
    NotifResultType Result
);

/*#if (COM_RXIPDUNUM >= 1u)*/
#endif

#define COM_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"

#endif



