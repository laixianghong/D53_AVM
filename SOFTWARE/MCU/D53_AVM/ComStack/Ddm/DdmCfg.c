/*  BEGIN_FILE_HDR
************************************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information contained in this
*   doc should not be reproduced, or used, or disclosed without the written authorization from
*   HiRain Technologies.
************************************************************************************************
*   File Name       : DDMCfg.c
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
#include "Ddm.h"

const DTCStatusByteCfgType DTCStatusByteInfoCfg[NUMBER_OF_DTC] = 
{
    /*0*/
    {
        20,     /*failed Threshold Intermit;*/    
        -20,     /*Passed Threshold Intermit;*/
        1,
        1,
        40U,
        1U,
        TRUE,
        DTC_TRUE,
        DTC_TRUE
    },

    /*1*/
    {
        20,     /*failed Threshold Intermit;*/    
        -20,     /*Passed Threshold Intermit;*/
        1,
        1,
        40U,
        1U,
        TRUE,
        DTC_TRUE,
        DTC_TRUE
    },

    /*2*/
    {
        2,     /*failed Threshold Intermit;*/    
        -50,     /*Passed Threshold Intermit;*/
        1,
        1,
        40U,
        1U,
        TRUE,
        DTC_TRUE,
        DTC_TRUE
    },
    /*3*/
    {
        30,     /*failed Threshold Intermit;*/    
        -30,     /*Passed Threshold Intermit;*/
        5,
        3,
        40U,
        1U,
        FALSE,
        DTC_TRUE,
        DTC_TRUE
    },
    /*4*/
    {
        30,     /*failed Threshold Intermit;*/    
        -30,     /*Passed Threshold Intermit;*/
        5,
        3,
        40U,
        1U,
        FALSE,
        DTC_TRUE,
        DTC_TRUE
    },
    /*5*/
    {
        30,     /*failed Threshold Intermit;*/    
        -30,     /*Passed Threshold Intermit;*/
        5,
        3,
        40U,
        1U,
        FALSE,
        DTC_TRUE,
        DTC_TRUE
    },

    /*6*/
    {
        30,     /*failed Threshold Intermit;*/    
        -30,     /*Passed Threshold Intermit;*/
        5,
        3,
        40U,
        1U,
        FALSE,
        DTC_TRUE,
        DTC_TRUE
    },

    /*7*/
    {
        30,     /*failed Threshold Intermit;*/    
        -30,     /*Passed Threshold Intermit;*/
        5,
        3,
        40U,
        1U,
        FALSE,
        DTC_TRUE,
        DTC_TRUE
    },

    /*8*/
    {
        30,     /*failed Threshold Intermit;*/    
        -30,     /*Passed Threshold Intermit;*/
        5,
        3,
        40U,
        1U,
        FALSE,
        DTC_TRUE,
        DTC_TRUE
    },
};

static const DTCSnapShotDIDInfoCfgType SnapshopRecord[] =
{
    /*global snapshot ,fixed order*/
    {0x1112,1}, 
    {0x1101,3}, 
    {0x1001,1},
    {0x1102,1},
    /*local snapshot*/
    {0xD1DD,2}
};

static const DTCSnapShotCfgType DTCSnapShotInfo[]=
{
    {
        1u,
        5u,
        SnapshopRecord,        
    }
};


static const DTCExtendedCfgType DTCExtendedInfo[1]=
{
    {
        1u,
        4u,        
    }    
};


const DTCFreezeFrameInfoCfgType DTCFFInfoCfg[NUMBER_OF_DTC] = /*DTC number must be in order,Begin with the smallest one*/
{
    /* 0 */
    {
        DTC_BUSOFF/*uiDTCNumber*/,
        1,//NumOfDTCSnapshotRecordNumber;/*当前DTC包含的SnapshotRecordNumber的数量*/
        1,//NumOfDTCExtendedRecordNumber;/*当前DTC包含的ExtendedRecordNumber的数量*/
        &DTCSnapShotInfo[0],
        &DTCExtendedInfo[0],
    },
    /* 1 */
    {
        DTC_FRONT_SENSOR_FAULT/*uiDTCNumber*/,
        1,/*NumOfDTCSnapshotRecordNumber;*/
        1,/*NumOfDTCExtendedRecordNumber;*/
        &DTCSnapShotInfo[0],
        &DTCExtendedInfo[0],
    },
    /* 2 */
    {
        DTC_REAR_SENSOR_FAULT/*uiDTCNumber*/,
        1,/*NumOfDTCSnapshotRecordNumber;*/
        1,/*NumOfDTCExtendedRecordNumber;*/
        &DTCSnapShotInfo[0],
        &DTCExtendedInfo[0],
    },
    /* 3 */
    {
        DTC_LEFT_SENSOR_FAULT/*uiDTCNumber*/,
        1,/*NumOfDTCSnapshotRecordNumber;*/
        1,/*NumOfDTCExtendedRecordNumber;*/
        &DTCSnapShotInfo[0],
        &DTCExtendedInfo[0],
    },
    /* 4 */
    {
        DTC_RIGHT_SENSOR_FAULT/*uiDTCNumber*/,
        1,/*NumOfDTCSnapshotRecordNumber;*/
        1,/*NumOfDTCExtendedRecordNumber;*/
        &DTCSnapShotInfo[0],
        &DTCExtendedInfo[0],
    },
    /* 5 */
    {
        DTC_LOST_COMMUNICATION_WITH_SAS/*uiDTCNumber*/,
        1,/*NumOfDTCSnapshotRecordNumber;*/
        1,/*NumOfDTCExtendedRecordNumber;*/
        &DTCSnapShotInfo[0],
        &DTCExtendedInfo[0],
    },
    /* 6 */
    {
        DTC_LOST_COMMUNICATION_WITH_ABS/*uiDTCNumber*/,
        1,/*NumOfDTCSnapshotRecordNumber;*/
        1,/*NumOfDTCExtendedRecordNumber;*/
        &DTCSnapShotInfo[0],
        &DTCExtendedInfo[0],
    },
    /* 7 */
    {
        DTC_LOST_COMMUNICATION_WITH_BCM/*uiDTCNumber*/,
        1,/*NumOfDTCSnapshotRecordNumber;*/
        1,/*NumOfDTCExtendedRecordNumber;*/
        &DTCSnapShotInfo[0],
        &DTCExtendedInfo[0],
    },
    /* 8 */
    {
        DTC_LOST_COMMUNICATION_WITH_MP5/*uiDTCNumber*/,
        1,/*NumOfDTCSnapshotRecordNumber;*/
        1,/*NumOfDTCExtendedRecordNumber;*/
        &DTCSnapShotInfo[0],
        &DTCExtendedInfo[0],
    },
};
/********************************End*******************************************/

