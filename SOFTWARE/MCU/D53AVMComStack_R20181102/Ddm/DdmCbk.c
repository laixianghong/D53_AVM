/*  BEGIN_FILE_HDR
************************************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information contained in this
*   doc should not be reproduced, or used, or disclosed without the written authorization from
*   HiRain Technologies.
************************************************************************************************
*   File Name       : DDMCbk.c
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
*     1.1        2015/09/29      rui.guo        N/A          
************************************************************************************************
* END_FILE_HDR*/

/*******************************************************************

1、每个DTC都对应一个结构体数据，这个结构体包含了DTC状态信息,如下，
typedef struct
{
    uint8  ucDTCCurStatus;
    uint8  ucDTCLastStatus;
    uint16 usAgingCounter;
    sint16 ssFCounterSequential;
    sint16 ssFCounterIntermit;
    uint8  ucSwitchInter;
}DTCStatusInfoType;
当DTC状态改变时，例如发生错误，DDM就会调用Cbk_DDMSaveDTCStatus函数触发一次存储这个结构体的操作,
在Cbk_DDMSaveDTCStatus函数中调用EEP相关的函数将数据写入EEP.
详细请看Cbk_DDMSaveDTCStatus中的注释。

2、函数Cbk_DDMRestoreDTCStatus用于初始化阶段从EEP中读取DTC状态信息。
详细请看Cbk_DDMRestoreDTCStatus中的注释。

3、应用程序需为每个DTC开辟一块空间用于存储DTC状态信息。地址空间分配由应用程序决定。
************************************************************************/
#include "Ddm.h"

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : NONE
*
* Description   : NONE
*
* Arguments     : NONE
* 
* Returns       : NONE
*
* Limitations   : NONE
*                 
************************************************************************************************
END_FUNCTION_HDR */

Std_ReturnType Cbk_DDMRestoreDTCStatus(uint16 dtcindex,DTCStatusInfoType* buff,uint16 cnt)
{
    Std_ReturnType ret = E_OK;
    /*当dtcindex 0xffff时，表示一次性恢复所有dtc状态*/
    
    /*首次上电认为数据无效 ，判断数据是否有效的方法需应用程序自己决定，
      例如EEP数据全FF、单独设有有效标志(也需存在EEP)*/
    /*if(DTC数据无效)*/  
    {
        ret = E_NOT_OK;
    }
    //else 
    {
        /*开始 拷贝数据，如果拷贝过程出现错误返回 E_NOT_OK*/
        ret = E_NOT_OK;
    }


    return ret;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : NONE
*
* Description   : NONE
*
* Arguments     : NONE
* 
* Returns       : NONE
*
* Limitations   : NONE
*                 
************************************************************************************************
END_FUNCTION_HDR */

void Cbk_DTCM_StoreFreezeFrame
(
#ifdef DDM_FIRST_STORE_FREEZEFRAME_INDI 
uint8 firstFlag,
#endif
uint16 dtcIndex
)
{
/*存储快照或扩展数据*/

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : NONE
*
* Description   : NONE
*
* Arguments     : NONE
* 
* Returns       : NONE
*
* Limitations   : NONE
*                 
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Cbk_DDMSaveAllDTCStatusRequest(uint8* dat,uint16 len)
{
    /*Tip: 在此函数中调用写入Dflash的写入接口End*/

     
    /*!!!!!!!必须将数据拷贝到其他全局buffer中!!!!!*/
    
    Std_ReturnType ucRet = DDM_OK;
    
    /*
    返回值说明:
    DDM_OK:        接受清除请求
    DDM_NOT_OK:清除请求被拒，且不需要再次请求
    DDM_CLRDTCBUSY:清除请求暂时不能接受，可再次请求
     */

    return ucRet;
}
Std_ReturnType Cbk_DDMRequireDTCSaveReault(void)
{
    /*Tip: 在此函数中调用查询Dflash的写入结果的函数End*/


    Std_ReturnType ucRet = DDM_OK;

    /*
    DDM_OK:        清除完成
    DDM_CLRDTCBUSY:清除未完成，且需要再次查询
    其他: 清除失败
     */

    return ucRet;
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : NONE
*
* Description   : NONE
*
* Arguments     : NONE
* 
* Returns       : NONE
*
* Limitations   : NONE
*                 
************************************************************************************************
END_FUNCTION_HDR */
#if 0

Std_ReturnType Cbk_DDMSaveDTCStatus(uint16 DTCIndex,DTCStatusInfoType* StPtr,uint16 cnt)
{
/*
    此函数用于存储当前DTC的状态信息。
    index是当前需要DTC索引号，StPtr是所要存储的数据指针，cnt是需要存储的数据长度

    应用程序依据index找到对应的EEP地址，将StPtr指向的数据存储到EEP，存储成功返回E_OK.否则返回E_NOT_OK

*/
    Std_ReturnType ucRet = E_OK;

    return ucRet;

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : NONE
*
* Description   : NONE
*
* Arguments     : NONE
* 
* Returns       : NONE
*
* Limitations   : NONE
*                 
************************************************************************************************
END_FUNCTION_HDR */

Std_ReturnType Cbk_DDMClrDTCDataSaveStatus(uint8* buff,uint16 cnt)
{
    Std_ReturnType ucRet = E_OK;

    return ucRet;
}
#endif
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : NONE
*
* Description   : NONE
*
* Arguments     : NONE
* 
* Returns       : NONE
*
* Limitations   : NONE
*                 
************************************************************************************************
END_FUNCTION_HDR */

Std_ReturnType Cbk_DDMReqSnapshotByDID(DTCRecdNumInfoType* pDtcRecd)
{
    Std_ReturnType ucRet = E_OK;

    return ucRet;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : NONE
*
* Description   : NONE
*
* Arguments     : NONE
* 
* Returns       : NONE
*
* Limitations   : NONE
*                 
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Cbk_DDMReqExtendedDataByRecdNum(uint16 dtcidx,uint8 recd,uint8* data,uint16 len)
{
    Std_ReturnType ucRet = E_OK;
#ifdef DDM_FAULT_OCCURCOUNTER_RECORD
    *data = DDMGetFaultOccurCounter(dtcidx);
#endif
#ifdef DDM_FAULT_PENDINGCOUNTER_SUPPORT
    *(data+1) = DDMGetFaultPendingCounter(dtcidx);
#endif
#ifdef DDM_AGAED_COUNTER_RECORD
    *(data+2) = DDMGetAgedCounter(dtcidx);
#endif
    *(data+3) = DDMGetAgingCounter(dtcidx);
    
    return ucRet;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : NONE
*
* Description   : NONE
*
* Arguments     : NONE
* 
* Returns       : NONE
*
* Limitations   : NONE
*                 
************************************************************************************************
END_FUNCTION_HDR */

Std_ReturnType Cbk_DDMTestReseultFailPre(uint16 usDtcIndex)
{
    /*实现DTC设置之间的其他应用逻辑*/
    /*返回 0 表示可以完成设置，否则禁止设置（由于其他逻辑限制，虽然满足设置条件但是也不能设置*/
    Std_ReturnType ucRet = E_OK;
    uint8 BitMask = 0;

    if(usDtcIndex<NUMBER_OF_DTC)
    {
        BitMask = DDMGetCurrentStatusByMask(usDtcIndex,DTC_STATUS_BIT0_TEST_FAILED);
        if(0 != BitMask)
        {  /*当前Bit0==1，错误已经被记录，不需要再记录了*/
            ucRet = E_NOT_OK;
        }
        else
        {/*当前Bit0==0，所以需要记录DTC*/
            
        }
    }
    else
    {
        ucRet = E_NOT_OK;
    }
    return ucRet;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : NONE
*
* Description   : NONE
*
* Arguments     : NONE
* 
* Returns       : NONE
*
* Limitations   : NONE
*                 
************************************************************************************************
END_FUNCTION_HDR */

Std_ReturnType Cbk_DDMTestReseultPassPre(uint16 usDtcIndex)
{
    /*实现DTC设置之间的其他应用逻辑*/
    /*返回 0 表示可以完成设置，否则禁止设置（由于其他逻辑限制，虽然满足设置条件但是也不能设置*/
    Std_ReturnType ucRet = E_OK;
    uint8 BitMask = 0;
       
    if(usDtcIndex < NUMBER_OF_DTC)
    {
    
        BitMask = DDMGetCurrentStatusByMask(usDtcIndex,(DTC_STATUS_BIT0_TEST_FAILED|DTC_STATUS_BIT4_NO_TEST_CLEARED|DTC_STATUS_BIT6_NO_TEST_THIS_CYCLE));
        if(0 == BitMask)
        {   /*上一次测试通过，且已经被记录，不需要再记录了*/
            ucRet = E_NOT_OK;
        }
        else
        {/*当前Bit0==0，所以需要记录DTC*/
            
        }
    }
    else
    {
        ucRet = E_NOT_OK;
    }

    return ucRet;
}


void Cbk_DDMEventFiltered(uint16 usDTCIndex, uint8 ucCurrentState)
{

}

/********************************End*******************************************/

