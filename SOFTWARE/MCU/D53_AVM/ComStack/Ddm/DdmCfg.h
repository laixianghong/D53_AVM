/*  BEGIN_FILE_HDR
************************************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information contained in this
*   doc should not be reproduced, or used, or disclosed without the written authorization from
*   HiRain Technologies.
************************************************************************************************
*   File Name       : DDMCfg.h
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
************************************************************************************************
* END_FILE_HDR*/
#ifndef    _DDMCFG_H_
#define    _DDMCFG_H_

//#include "Ddm.h"
#include "ComStack_Types.h"

/*#define DDM_FIRST_STORE_FREEZEFRAME_INDI */
/*#define DDM_FAULT_OCCURCOUNTER_RECORD*/
/*#define DDM_AGAED_COUNTER_RECORD*/
/*#define DDM_FAULT_PENDINGCOUNTER_SUPPORT*/


//#define COUNTER_SEQ                             2U/*Sequential only*/
//#define COUNTER_INT                             1U/*Intermit only*/
/*#define COUNTER_ALL                             2U*/ /*Sequential or Intermit*/ /*Do NOT SUPPORT!!*/
//#define DDM_DEBOUNCE_ALGORITH         COUNTER_SEQ

#define DDMGlobalIntDisable() Can_DisableGlobalInterrupts()
#define DDMGlobalIntEnable()  Can_DisableGlobalInterrupts()

#define DDM_MAINCYCLE         10
#define DDM_SAVEDATACYCLE     500

typedef struct 
{
    const uint16 usSnapDidNum;
    const uint8  ucSnapDidLen;
}DTCSnapShotDIDInfoCfgType;


typedef struct 
{
    uint8                              DTCSnapshotRecordNumber;
    uint8                              DTCSnapshotRecordNumberOfIdentifiers;/*当前RecordNumber下的DID数量*/
    const DTCSnapShotDIDInfoCfgType*   SnapShotDIDPtr;
}DTCSnapShotCfgType;

typedef struct 
{
    uint8                         DTCExtendedRecordNumber;
    uint8                       ucExtendRecordLen;/*当前RecordNumber下的DID数量*/
}DTCExtendedCfgType;


typedef struct
{
    uint32                        uiDTCNumber;
    uint8                        NumOfDTCSnapshotRecordNumber;/*当前DTC包含的SnapshotRecordNumber的数量*/
    uint8                        NumOfDTCExtendedRecordNumber;/*当前DTC包含的ExtendedRecordNumber的数量*/
    const DTCSnapShotCfgType*       DTCSnapShotInfoPtr;
    const DTCExtendedCfgType*     DTCExtendedInfoPtr;
}DTCFreezeFrameInfoCfgType;

typedef struct
{
    //uint8    ucFaultCounterType;    /* 错误计数器累加方式：1,consecutive可用 2,intermittently间歇可用 3,都可用，默认为1*/
    
    //sint16   ssFThresholdSequential;/*failed Threshold Sequential;*/
    sint16   ssFThresholdIntermit;  /*failed Threshold Intermit;*/
    //sint16   ssPThresholdSequential;/*Passed Threshold Sequential;*/
    sint16   ssPThresholdIntermit;  /*Passed Threshold Intermit;*/
    sint16   ucIncreaseStepSize;    /* Step size for incrementation of FDC (PREFAILED). */
    sint16   ucDecreaseStepSize;    /* Step size for decrementation of FDC (PREPASSED). */
    
    uint8    ucAgingThreshold;
    uint8    ucPendingThreshold;    /*after reaching,BIT3_CONFIRMED set to 1*/ /*相当于Tripcounter*/
    //uint8    ucStatusByteSwitch;
    uint8    ucAgingAllowed;
    //uint8    ucTripCounter;         /*reserved*/
    uint8    ucDownToZero;          /* Enable / disable ;when passed accur FailCounter down to Zero ,after reaching failed level. */
    uint8    ucJumpToZero;          /* Enable / disable ;when failed accur FailCounter jump to Zero ,after reaching passed level. */
}DTCStatusByteCfgType;

#define DTC_BUSOFF                               0xC01988U
#define DTC_BUSOFF_INDEX                 	 	0U

#define DTC_FRONT_SENSOR_FAULT                   0x990013U
#define DTC_FRONT_SENSOR_FAULT_INDEX               	1U

#define DTC_REAR_SENSOR_FAULT                    0x990313U
#define DTC_REAR_SENSOR_FAULT_INDEX               	2U

#define DTC_LEFT_SENSOR_FAULT                    0x990413U
#define DTC_LEFT_SENSOR_FAULT_INDEX                	3U

#define DTC_RIGHT_SENSOR_FAULT                   0x990713U
#define DTC_RIGHT_SENSOR_FAULT_INDEX                	4U

#define DTC_LOST_COMMUNICATION_WITH_SAS          0xC12600U
#define DTC_LOST_COMMUNICATION_WITH_SAS_INDEX           5U

#define DTC_LOST_COMMUNICATION_WITH_ABS          0xC12100U
#define DTC_LOST_COMMUNICATION_WITH_ABS_INDEX           6U

#define DTC_LOST_COMMUNICATION_WITH_BCM          0xC14000U
#define DTC_LOST_COMMUNICATION_WITH_BCM_INDEX           7U

#define DTC_LOST_COMMUNICATION_WITH_MP5          0xC15600U
#define DTC_LOST_COMMUNICATION_WITH_MP5_INDEX           8U

#define NUMBER_OF_DTC                            9U

#define DTCSTATUSAVAILABLEMASK                   0x09
/*#define DTCSTATUSRESTORERESPECTIVELY*/    
extern const DTCStatusByteCfgType DTCStatusByteInfoCfg[NUMBER_OF_DTC];
extern const DTCFreezeFrameInfoCfgType DTCFFInfoCfg[NUMBER_OF_DTC]; /*DTC number must be in order,Begin with the smallest one*/


#endif
/********************************End*******************************************/

