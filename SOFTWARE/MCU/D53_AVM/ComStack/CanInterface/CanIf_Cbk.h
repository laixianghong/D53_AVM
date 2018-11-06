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
| 00.01.00    2015-08-04                             first version
|-------------------------------------------------------------------------------
*/


#ifndef _CANIF_CBK_H_
#define _CANIF_CBK_H_

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "CanIf_Cfg.h"
#include "CanIf_Type.h"

/*******************************************************************************
*   Callback Function Declaration 
*******************************************************************************/
#define CANIF_START_SEC_PUBLIC_CODE
#include "MemMap.h"

extern FUNC(void, CANIF_PUBLIC_CODE) CanIf_TxConfirmation
( 
    PduIdType CanTxPduId
);

extern FUNC(void, CANIF_PUBLIC_CODE) CanIf_RxIndication
( 
    Can_HwHandleType Hrh, 
    Can_IdType CanId,
    uint8 CanDlc,
    P2CONST(uint8, AUTOMATIC, CANIF_APPL_DATA) CanSduPtr
);
#if(CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT == STD_ON) 
extern FUNC(void, CANIF_PUBLIC_CODE) CanIf_CancelTxConfirmation
( 
    P2CONST(Can_PduType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
);
#endif

extern FUNC(void, CANIF_PUBLIC_CODE) CanIf_ControllerBusOff
( 
    uint8 Controller 
);

extern FUNC(void, CANIF_PUBLIC_CODE) CanIf_ControllerWakeUp
( 
    uint8 Controller 
); 

extern FUNC(void, CANIF_PUBLIC_CODE) CanIf_ControllerModeIndication
( 
    uint8 Controller,
    CanIf_ControllerModeType ControllerMode
);

#define CANIF_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"
                           
#endif/* _CANIF_CBK_H_ */

