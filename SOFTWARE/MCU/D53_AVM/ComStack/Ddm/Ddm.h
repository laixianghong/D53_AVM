/*  BEGIN_FILE_HDR
************************************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information contained in this
*   doc should not be reproduced, or used, or disclosed without the written authorization from
*   HiRain Technologies.
************************************************************************************************
*   File Name       : Ddm.h
************************************************************************************************
*   Project/Product : System module
*   Title           : 
*   Author          : rui.guo
************************************************************************************************
*   Description     : This module ...
*
************************************************************************************************
*   Limitations     : 
************************************************************************************************
*
************************************************************************************************
*   Revision History:
*
*    Version      Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------  ---------------
*     1.0        2015/03/15      rui.guo        N/A          Original
*     1.2        2015/09/28      rui.guo        N/A
************************************************************************************************
* END_FILE_HDR*/
#ifndef    _DDM_H_
#define    _DDM_H_

#include "DdmCfg.h"
#include "Can.h"


#define DDM_STARTCYCLE                        0x04U
#define DDM_STOPCYCLE                         0x08U

#define ISO15031FORMAT                            0x00U
#define ISO14229FORMAT                            0x01U
#define SAEJ1939FORMAT                            0x02U

#define DTC_SWITCH_DISABLE                        0U
#define DTC_SWITCH_ENABLE                        1U

#define DTC_TEST_PREFAILED                        0U
#define DTC_TEST_PREPASSED                        1U
#define DTC_TEST_FAILED                            2U
#define DTC_TEST_PASSED                            3U

#define DTC_STATUS_BIT0_TEST_FAILED                ((uint8)(0x01))
#define DTC_STATUS_BIT1_CYCLE_FAILED            ((uint8)(0x02))
#define DTC_STATUS_BIT2_PENDING_DTC                ((uint8)(0x04))
#define DTC_STATUS_BIT3_CONFIRMED_DTC            ((uint8)(0x08))
#define DTC_STATUS_BIT4_NO_TEST_CLEARED            ((uint8)(0x10))
#define DTC_STATUS_BIT5_TEST_FAILED_CLEARED        ((uint8)(0x20))
#define DTC_STATUS_BIT6_NO_TEST_THIS_CYCLE        ((uint8)(0x40))
#define DTC_STATUS_BIT7_WARNING_INDICATOR        ((uint8)(0x80))


#define DTC_TRUE                                0x01
#define DTC_FALSE                               0X02

//#define DDMCLR_OK       0
//#define DDMCLR_NOTOK    1


#define SetDtcMState(x)                         DtcMState = x
#define GetDtcMState(x)                         x = DtcMState

#define SetDDMStateBit(Mask)  DtcMState |= Mask    
#define ClrDDMStateBit(Mask)  DtcMState &= (~Mask)


#define DTCM_UNINIT                            0x0000U
#define DTCM_INITED                            0x0001U
#define DTCM_PROCESSING                        0x0002U
#define DTCM_STARTCYCLE                        0x0004U
#define DTCM_STOPCYCLE                         0x0008U
//#define DTCM_CLEARALL                          0x0010U /*Clear ALL DTC*/
//#define DTCM_CLEARSIG                          0x0020U /*Clear one DTC*/
//#define DTCM_CLEARDONE                         0x0040U /*Clear over*/

#define DTCM_CLEARING                         0x8000U /*add*/
#define DTCM_CYCLESAVING                         0x4000U /*add*/



typedef uint8 DTCSwitchType;

typedef enum
{
    DDM_OK = 0,
    DDM_OUTOFRANGE = 1,
    DDM_CBKRETERROR = 2,
    DDM_CLRDTCBUSY = 3,
    DDM_CLRERROR  = 4,
    DDM_NOT_OK  = 5,
} DTCStdReturnType;


typedef struct
{
    //sint16 ssFCounterSequential;
    //sint16 ssFCounterIntermit;
    uint8  ucDTCCurStatus;/*current operation cycle*/
    uint8  ucDTCLastStatus;/*last operation cycle*/
    uint8  ucAgingCounter;
    //uint8  ucSwitchInter;//dele
#ifdef DDM_FIRST_STORE_FREEZEFRAME_INDI    
    uint8  ucFirstRecord;
#endif    
#ifdef DDM_FAULT_OCCURCOUNTER_RECORD
    uint8  ucFaultOccurCounter;
#endif   
#ifdef DDM_FAULT_PENDINGCOUNTER_SUPPORT
    uint8  ucFaultPendingCounter;
#endif
#ifdef DDM_AGAED_COUNTER_RECORD
    uint8  ucAgedCounter;
#endif
    /*uint8  ucFirstPowerF;*/
    uint8  ucValidFlag;

}DTCStatusInfoType;

typedef struct
{
    uint16  uiDTCIdx;
    uint16  uiRecdNum;
    uint16  uiDIDNum;
    uint16  uiDIDIdx;
    uint16  uiDIDLen;
    uint8*  ucDatPtr;
}DTCRecdNumInfoType;

extern void DDM_MainTask(void);

extern void DDMTestPreResultProcess
(
    uint16 usDTCIndex, 
    uint8  ucCurrentStatus
);
extern DTCStdReturnType DDMClearDTC
(
    uint32 uiDTCNumber
);
extern void DDMReportNumberOfDTCByMask
(
    uint8 ucMaskByte, 
    uint8 *pData
);
extern uint16 DDMReportDTCByStatusMask
(
    uint8  ucMaskByte, 
    uint8* pData
);
extern DTCStdReturnType DDMReportSnapshotByDTCNumber
(    
    uint32   uiDTCNumber, 
    uint8    ucSnapshotNumber, 
    uint8*   pData,
    uint32*  pResLen/*out*/
);
extern DTCStdReturnType DDMReportExtenDataByDTCNumber
(   
    uint32   uiDTCNumber, 
    uint8    ucExtendedRecordNumber, 
    uint8*   pData,
    uint32*  pResLen/*out*/
);
extern Std_ReturnType DDMInit
(
    void
);
extern uint16 DDMReportSupportedDTC
(
    uint8* pData
);                                             
extern uint8 DDMSetDTCSwitch
(
    uint16        DtcIndex,
    DTCSwitchType type
);
extern void  DDMSetAllDTCSwitch
(
    DTCSwitchType type
);
extern uint8 DDMSetDtcStatuBit
(
    uint16 usDtcIndex,
    uint8  ucBitMask
);
extern uint8 DDMClearDtcStatuBit
(
    uint16 usDtcIndex,
    uint8  ucBitMask
);
extern uint8 DDMSetOperationMode
(
    uint8 mode
);
extern uint8 DDMGetCurrentStatusByMask
(
    uint16 usDtcIndex,
    uint8 ucBitMask
);
/********************************CBK********************************************/
#if 0
extern Std_ReturnType Cbk_DDMDTCInfoValid
(
    uint16 dtcindex
);
#endif
extern Std_ReturnType Cbk_DDMRestoreDTCStatus
(
    uint16 dtcindex,
    DTCStatusInfoType* buff,
    uint16 cnt
);
extern void Cbk_DTCM_StoreFreezeFrame
(
#ifdef DDM_FIRST_STORE_FREEZEFRAME_INDI 
    uint8 firstFlag,
#endif    
    uint16 dtcIndex
);

extern Std_ReturnType Cbk_DDMSaveAllDTCStatusRequest
(
    uint8* dat,uint16 len
);
extern Std_ReturnType Cbk_DDMRequireDTCSaveReault(void);
extern Std_ReturnType Cbk_DDMSaveDTCStatus
(
    uint16 DTCIndex,
    DTCStatusInfoType* StPtr,
    uint16 cnt
);
/*
Std_ReturnType Cbk_DDMReqSnapshotByDID
(
    uint16 did,
    uint8* data,
    uint16 len
);
*/
extern Std_ReturnType Cbk_DDMReqSnapshotByDID(DTCRecdNumInfoType* pDtcRecd);

extern Std_ReturnType Cbk_DDMReqExtendedDataByRecdNum
(
    uint16 dtcidx,
    uint8  recd,
    uint8* data,
    uint16 len
);
extern Std_ReturnType Cbk_DDMTestReseultFailPre
(
    uint16 usDtcIndex
);
extern Std_ReturnType Cbk_DDMTestReseultPassPre
(
    uint16 usDtcIndex
);
extern void Cbk_DDMEventFiltered
(
    uint16 usDTCIndex, 
    uint8 ucCurrentState
);

extern DTCStatusInfoType  DtcStatusInfo[NUMBER_OF_DTC];
#ifdef DDM_FAULT_OCCURCOUNTER_RECORD
extern uint8 DDMGetFaultOccurCounter(uint16 usDtcIndex);
#endif
#ifdef DDM_FAULT_PENDINGCOUNTER_SUPPORT
extern uint8 DDMGetFaultPendingCounter(uint16 usDtcIndex);
#endif
#ifdef DDM_AGAED_COUNTER_RECORD
extern uint8 DDMGetAgedCounter(uint16 usDtcIndex);
#endif
extern uint8 DDMGetAgingCounter(uint16 usDtcIndex);

#endif
/********************************End*******************************************/

