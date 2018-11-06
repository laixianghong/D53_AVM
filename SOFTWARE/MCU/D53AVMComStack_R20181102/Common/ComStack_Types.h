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
#ifndef _COMSTACK_TYPES_H_
#define _COMSTACK_TYPES_H_

/*******************************************************************************
*   Includes 
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
*   Macro 
*******************************************************************************/
/*General return codes for NotifResultType*/ 

/*Action has been successfully finished:
- message sent out (in case of confirmation),
- message received (in case of indication) */
#define NTFRSLT_OK                       (0x00U) 
 /*Error notification:
- message not successfully sent out (in case of confirmation),
- message not successfully received (in case of indication) */ 
#define NTFRSLT_E_NOT_OK                 (0x01U)
/*Error notification:
- timer N_Ar/N_As (according to ISO specification [ISONM]) has passed its 
time-out value N_Asmax/N_Armax.This value can be issued to service user on 
both the sender and receiver side. */
#define NTFRSLT_E_TIMEOUT_A              (0x02U) 
/*Error notification:
- timer N_Bs has passed its time-out value N_Bsmax (according to ISO 
specification [ISONM]).This value can be issued to the service user on the 
sender side only. */ 
#define NTFRSLT_E_TIMEOUT_BS             (0x03U) 
/*Error notification:
- timer N_Cr has passed its time-out value N_Crmax.
This value can be issued to the service user on the receiver side only. */ 
#define NTFRSLT_E_TIMEOUT_CR             (0x04U)
/*Error notification:
- unexpected sequence number (PCI.SN) value received.
This value can be issued to the service user on the receiver side only. */  
#define NTFRSLT_E_WRONG_SN               (0x05U)  
/*Error notification:
- invalid or unknown FlowStatus value has been received in a flow control 
(FC) N_PDU.
This value can be issued to the service user on the sender side only. */
#define NTFRSLT_E_INVALID_FS             (0x06U) 
/*Error notification:
- unexpected protocol data unit received.
This value can be issued to the service user on both the sender and 
receiver side. */
#define NTFRSLT_E_UNEXP_PDU              (0x07U)
/*Error notification:
- flow control WAIT frame that exceeds the maximum counter N_WFTmax received.
This value can be issued to the service user on the receiver side. */  
#define NTFRSLT_E_WFT_OVRN               (0x08U)
/*Error notification:
Flow control (FC) N_PDU with FlowStatus = ABORT received. It indicates an abort 
of a transmission. A possible reason for this is that the receiver is currently 
busy and can not take the request at that point in time.*/
#define NTFRSLT_E_ABORT                  (0x09U)
/*Error notification:
- flow control (FC) N_PDU with FlowStatus = OVFLW received. 
  It indicates that the buffer on the receiver side of a segmented message 
  transmission cannot store the number of bytes specified by the FirstFrame 
  DataLength (FF_DL) parameter in the FirstFrame and therefore the transmission 
  of the 19 of 23 AUTOSAR_SWS_ComStackTypes segmented message was aborted.
- no buffer within the TP available to transmit the segmented I-PDU.
This value can be issued to the service user on both the sender and receiver 
side. */
#define NTFRSLT_E_NO_BUFFER              (0x0AU)  
/*Action has been successfully finished:
- Requested cancellation has been executed.*/
#define NTFRSLT_E_CANCELATION_OK         (0x0BU)
/*Error notification:
- Due to an internal error the requested cancelation has not been executed. 
This will happen e.g., if the to be canceled transmission has been executed
already.*/
#define NTFRSLT_E_CANCELATION_NOT_OK     (0x0CU)  
/*The parameter change request has been successfully executed */
#define NTFRSLT_PARAMETER_OK             (0x0DU)  
/*The request for the change of the parameter did not complete successfully*/
#define NTFRSLT_E_PARAMETER_NOT_OK       (0x0EU)  
/*The parameter change request not executed successfully due to an ongoing 
reception*/
#define NTFRSLT_E_RX_ON                  (0x0FU)
/*The parameter change request not executed successfully due to a wrong value*/
#define NTFRSLT_E_VALUE_NOT_OK           (0x10U)
  
#define NTFRSLT_E_CAN_WRONG_CFDL         (0x11U)
/* 0x12-0x1E Reserved values for  future usage. */

/*General return codes for BusTrcvErrorType*/
#define BUSTRCV_OK         (0x00U)                              
#define BUSTRCV_E_OK       (0x01U)                                                                                                                                                          
                                                                                
/*******************************************************************************
*   Typedef 
*******************************************************************************/
/*The size of this global type depends on the maximum number of PDUs used 
within one software module.*/
typedef uint16       PduIdType; 
/*The size of this global type depends on the maximum length of PDUs to be 
sent by an ECU.*/             
typedef uint16       PduLengthType;       

typedef P2VAR(uint8, TYPEDEF, TYPEDEF) SduDataPtrType;
typedef struct
{ 
    SduDataPtrType SduDataPtr; 
    PduLengthType   SduLength; 
}PduInfoType; 
 

typedef enum                          
{
    BUFREQ_OK,           /*Buffer request accomplished successful.*/
    BUFREQ_E_NOT_OK,     /*Buffer request not successful. Buffer cannot be 
                         accessed.*/
    BUFREQ_E_BUSY,       /*Temporarily no buffer available. It's up the 
                         requestor to retry request for a certain time.*/
    BUFREQ_E_OVFL        /*No Buffer of the required length can be provided.*/
}BufReq_ReturnType;


typedef enum                          
{
    TP_DATACONF,     /*indicates that all data, that have been copied so far, 
                     are confirmed and can be removed from the TP buffer. 
                     Data copied by this API call are excluded and will be 
                     confirmed later.*/
    TP_DATARETRY,    /*indicates that this API call shall copy already copied 
                     data in order to recover from an error. In this case 
                     TxTpDataCnt specifies the offset of the first byte to be 
                     copied by the API call.*/
    TP_CONFPENDING   /*indicates that the previously copied data must remain 
                     in the TP*/
}TpDataStateType;

typedef struct
{
    TpDataStateType TpDataState;
    PduLengthType TxTpDataCnt;
}RetryInfoType;

typedef uint8    NotifResultType;
typedef uint8    BusTrcvErrorType;
typedef uint8    NetworkHandleType;
                                                                                                                                                                
#endif  /* _COMSTACK_TYPES_H_ */                                                                                                                                  

