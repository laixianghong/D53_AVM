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

#ifndef _DCM_CBK_H_
#define _DCM_CBK_H_

/*******************************************************************************
* Include files
********************************************************************************/
#include "ComStack_Types.h"
/*******************************************************************************
* Global Function Prototype
********************************************************************************/
#define DCM_START_SEC_PUBLIC_CODE
#include "MemMap.h"

extern FUNC(BufReq_ReturnType,DCM_PUBLIC_CODE) Dcm_StartOfReception
(
    const PduIdType     DcmRxPduId,
    const PduLengthType TpSduLength,
    CONSTP2VAR(PduLengthType,AUTOMATIC,DCM_APPL_DATA) Length
);

extern FUNC(BufReq_ReturnType,DCM_PUBLIC_CODE) Dcm_CopyRxData
(
    const PduIdType  DcmRxPduId,
    CONSTP2CONST(PduInfoType,AUTOMATIC,DCM_APPL_DATA)  PduInfoPointer,
    CONSTP2VAR(PduLengthType,AUTOMATIC,DCM_APPL_DATA)  RxBufferSizePtr
);

extern FUNC(void,DCM_PUBLIC_CODE) Dcm_RxIndication
(
    const PduIdType       DcmRxPduId,
    const NotifResultType Result
);

extern FUNC(BufReq_ReturnType,DCM_PUBLIC_CODE) Dcm_CopyTxData
(
    const PduIdType  DcmTxPduId,
    CONSTP2CONST(PduInfoType,AUTOMATIC,DCM_APPL_DATA)  PduInfoPtr,
    CONSTP2CONST(RetryInfoType,AUTOMATIC,DCM_APPL_DATA)  RetryInfoPtr,
    CONSTP2VAR(PduLengthType,AUTOMATIC,DCM_APPL_DATA)  TxDataCntPtr
);

extern FUNC(void,DCM_PUBLIC_CODE) Dcm_TxConfirmation
(
    const PduIdType       DcmTxPduId,
    const NotifResultType Result
);

#define DCM_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"

#endif
