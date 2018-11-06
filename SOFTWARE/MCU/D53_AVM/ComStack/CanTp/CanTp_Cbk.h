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

#ifndef _CANTP_CBK_H_
#define _CANTP_CBK_H_


/*******************************************************************************
* Prototypes of export functions
*******************************************************************************/
#define CANTP_START_SEC_PUBLIC_CODE
#include "MemMap.h"
#include "ComStack_Types.h"

extern FUNC(void,CANTP_PUBLIC_CODE) CanTp_RxIndication
(
    PduIdType RxPduId, 
    P2CONST(PduInfoType,AUTOMATIC,CANTP_APPL_DATA)PduInfoPtr
);

extern FUNC(void,CANTP_PUBLIC_CODE) CanTp_TxConfirmation
(
    PduIdType CanTpTxPduId
);
#define CANTP_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"


#endif
/* ifndef _CANTP_CBK_H_ */

/*******************************************************************************
 *  END OF FILE: CanTp_Cbk.
 ******************************************************************************/ 

