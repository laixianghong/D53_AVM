/*  BEGIN_FILE_HDR
************************************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information contained in this
*   doc should not be reproduced, or used, or disclosed without the written authorization from
*   HiRain Technologies.
************************************************************************************************
*   File Name       : Ddm.c
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
*     1.1        2015/09/08      rui.guo        N/A     
*     1.2        2015/09/28      rui.guo        N/A      
************************************************************************************************
* END_FILE_HDR*/


#include "Ddm.h"



STATIC sint16 FaultDetectionCounter[NUMBER_OF_DTC];

STATIC DTCStatusInfoType  DtcStatusInfo[NUMBER_OF_DTC];
STATIC uint16             DtcMState;
STATIC uint8    DtcStatusByteChangeFlag[(NUMBER_OF_DTC/8)+1]={0};//no use
STATIC uint8    DtcSwitchInterFlag[(NUMBER_OF_DTC/8)+1]={0};
STATIC uint8    DtcStatusToBeSavedFlag = 0;
//STATIC uint8    DtcClearDTCFlag = 0;

STATIC uint16   EventIndex = 0;
//STATIC uint16   ClearDTCResult = DDMCLR_OK;/*0::OK 1:Not OK*/

#define DEM_BIT0 1u
/*#define DEM_FIRST_POWERON_FLAG 0x57*/


void DDMTestPreResultProcess
(
    uint16 usDTCIndex, 
    uint8  ucCurrentStatus
);
DTCStdReturnType DDMClearDTC
(
    uint32 uiDTCNumber
);
void DDMReportNumberOfDTCByMask
(
    uint8  ucMaskByte, 
    uint8* pData
);
uint16 DDMReportDTCByStatusMask
(
    uint8  ucMaskByte, 
    uint8* pData
);
DTCStdReturnType DDMReportSnapshotByDTCNumber
(    
    uint32   uiDTCNumber, 
    uint8    ucSnapshotNumber, 
    uint8*   pData,
    uint32*  pResLen/*out*/
);

DTCStdReturnType DDMReportExtenDataByDTCNumber
(   
    uint32   uiDTCNumber, 
    uint8    ucExtendedRecordNumber, 
    uint8*   pData,
    uint32*  pResLen/*out*/
);
uint16 DDMReportSupportedDTC
(
    uint8 *pData
);     
uint8 DDMSetDTCSwitch
(
    uint16        DtcIndex,
    DTCSwitchType type
);
void DDMSetAllDTCSwitch
(
    DTCSwitchType type
);

uint8 DDMSetOperationMode
(
    uint8 mode
);
#if 0
uint8 DDMSetDtcStatuBit
(
    uint16 usDtcIndex,
    uint8  ucBitMask
);
uint8 DDMClearDtcStatuBit
(
    uint16 usDtcIndex,
    uint8  ucBitMask
);
#endif
STATIC uint16 DDMGetDTCIndex
(
    uint32 usDIDNumber
);
STATIC uint8 DDMTestReseultProcess
(
    uint16 usDTCIndex, 
    uint8  ucCurrentState
);
STATIC void DDMDtcClrReqProcess
(
    uint16 usDTCIndex
);
STATIC uint8 DDMGetDTCSwitch
(
    uint16 DtcIndex
);

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
STATIC uint16 DdmMainTickCouncter = 0;

void DDM_MainTask(void)
{
//    uint8 byteidx;
//    uint8 bitidx;
//    uint8 bytenum;
    uint16 i;
    uint16 j;
    uint8 flagBitMask = 0;
    uint8 ucRet;

//    uint16 eventId;

    /*Disable INT*/
   
    if(DdmMainTickCouncter == 65535)
    {
        DdmMainTickCouncter = 65534;
    }

    DdmMainTickCouncter++;
    
    if((DdmMainTickCouncter >= (DDM_SAVEDATACYCLE/DDM_MAINCYCLE)) && (DtcStatusToBeSavedFlag))
    {   
        
        DDMGlobalIntDisable();
        if(DtcMState == DTCM_STARTCYCLE)
        {
            
            ucRet = Cbk_DDMSaveAllDTCStatusRequest((uint8*)(&DtcStatusInfo[0]),sizeof(DtcStatusInfo));
            if(E_OK == ucRet)
            {
                SetDDMStateBit(DTCM_CYCLESAVING);
            }
            else
            {
                DdmMainTickCouncter = 0;
            }
        } 
        else if((DtcMState & DTCM_CYCLESAVING )!=0)
        {
            uint8 rt;

            rt = Cbk_DDMRequireDTCSaveReault();
            if(DDM_CLRDTCBUSY != rt)
            {   /*OK or NOT OK*/
                DdmMainTickCouncter = 0;
                DtcStatusToBeSavedFlag = 0;
                ClrDDMStateBit(DTCM_CYCLESAVING);
            }
        }
        DDMGlobalIntEnable();
    }

    
#if 0  

    Std_ReturnType ucRet = E_OK;
    
    for (i = EventIndex/8; i <((uint8)(NUMBER_OF_DTC/8)+1); i++)
    {
        if(DtcStatusByteChangeFlag[i] != 0) /*Check event status change flag*/
        {
            for (j=0; j<8; j++)
            {
                EventIndex=(uint16)(i*8+j);/*current checking DTC*/

                flagBitMask=(uint8)(DEM_BIT0<<j);
                if((uint8)(DtcStatusByteChangeFlag[i] & flagBitMask)== flagBitMask)
                {
                    ucRet = Cbk_DDMSaveDTCStatus(EventIndex,&DtcStatusInfo[EventIndex],sizeof(DTCStatusInfoType));
                    if(ucRet == E_OK)
                    {
                        /*Clear event status change flag*/
                        DtcStatusByteChangeFlag[i] &=(uint8) (~flagBitMask);
                    }
                    if((DtcMState & DTCM_CLEARSIG) == DTCM_CLEARSIG)
                    {
                        ClrDDMStateBit(DTCM_CLEARSIG);
                        SetDDMStateBit(DTCM_CLEARDONE);
                        if(ucRet == E_OK)
                        {/*清除成功*/
                            //ClearDTCResult = DDMCLR_OK;//not use
                        }
                        else
                        {/*清除失败*/
                            ClearDTCResult = DDMCLR_NOTOK;
                        }
                    }
                }

                if((ucRet != E_OK)&&((DtcMState & DTCM_CLEARALL) == DTCM_CLEARALL))
                {
                    ClrDDMStateBit(DTCM_CLEARALL);
                    SetDDMStateBit(DTCM_CLEARDONE);
                    /*清除失败*/
                    ClearDTCResult = DDMCLR_NOTOK;
                }
                if(EventIndex >= (NUMBER_OF_DTC-1))
                {   /*the last EventId*/
                    EventIndex =  0; 
                    /*add 20151102*/
                    if((DtcMState & DTCM_CLEARALL) == DTCM_CLEARALL)
                    {
                        ClrDDMStateBit(DTCM_CLEARALL);
                        SetDDMStateBit(DTCM_CLEARDONE);
                    }
                    break;
                }
                else
                {
                    EventIndex++;//next 
                }
            }
            //EventIndex++;
            break;
        }   
        else if(i == ((uint8)(NUMBER_OF_DTC/8)+1)-1)
        {
            EventIndex =  0;
        }
    }

#endif


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
Std_ReturnType DDMInit(void)
{
    Std_ReturnType ret = E_OK;
    uint16 usDTCIndex;

    uint16 byteidx;
    uint16 bitidx;
    

    SetDtcMState(DTCM_UNINIT);

    /*从Flash中读取数据 */
#ifdef DTCSTATUSRESTORERESPECTIVELY
    for(usDTCIndex = 0; usDTCIndex < NUMBER_OF_DTC; usDTCIndex++)
    {
        ret = Cbk_DDMRestoreDTCStatus(usDTCIndex,&DtcStatusInfo[usDTCIndex],sizeof(DTCStatusInfoType));

        /*if((E_OK != ret)||\
            (DtcStatusInfo[usDTCIndex].ucFirstPowerF != DEM_FIRST_POWERON_FLAG))*/
        if(E_OK != ret)
        {
            DtcStatusInfo[usDTCIndex].ucDTCCurStatus = 0x50;/*bit4 and 6 set */
            DtcStatusInfo[usDTCIndex].ucDTCLastStatus = 0x50;
            DtcStatusInfo[usDTCIndex].ucAgingCounter = 0;
            //DtcStatusInfo[usDTCIndex].ssFCounterSequential = 0;
            FaultDetectionCounter[usDTCIndex] = 0;
#ifdef DDM_FIRST_STORE_FREEZEFRAME_INDI 
            DtcStatusInfo[usDTCIndex].ucFirstRecord = 1;
#endif
            /*DtcStatusInfo[usDTCIndex].ucFirstPowerF = DEM_FIRST_POWERON_FLAG;*/
#ifdef DDM_FAULT_OCCURCOUNTER_RECORD
            DtcStatusInfo[usDTCIndex].ucFaultOccurCounter = 0;
#endif
#ifdef DDM_FAULT_PENDINGCOUNTER_SUPPORT
            DtcStatusInfo[usDTCIndex].ucFaultPendingCounter = 0;
#endif
#ifdef DDM_AGAED_COUNTER_RECORD
            DtcStatusInfo[usDTCIndex].ucAgedCounter = 0;
#endif
            byteidx = usDTCIndex/8;
            bitidx = usDTCIndex%8;
            DtcStatusByteChangeFlag[byteidx]|=(uint8)(1u<<bitidx);
            DtcStatusToBeSavedFlag = 1;        
        }
    }
#else
    ret = Cbk_DDMRestoreDTCStatus(0xFFFF,&DtcStatusInfo[0],sizeof(DtcStatusInfo));
    if(E_OK != ret)
    {
        for(usDTCIndex = 0; usDTCIndex < NUMBER_OF_DTC; usDTCIndex++)
        {
            DtcStatusInfo[usDTCIndex].ucDTCCurStatus = 0x50;/*bit4 and 6 set */
            DtcStatusInfo[usDTCIndex].ucDTCLastStatus = 0x50;
            DtcStatusInfo[usDTCIndex].ucAgingCounter = 0;
            //DtcStatusInfo[usDTCIndex].ssFCounterSequential = 0;
            FaultDetectionCounter[usDTCIndex] = 0;
#ifdef DDM_FIRST_STORE_FREEZEFRAME_INDI 
            DtcStatusInfo[usDTCIndex].ucFirstRecord = 1;
#endif
            /*DtcStatusInfo[usDTCIndex].ucFirstPowerF = DEM_FIRST_POWERON_FLAG;*/
#ifdef DDM_FAULT_OCCURCOUNTER_RECORD
            DtcStatusInfo[usDTCIndex].ucFaultOccurCounter = 0;
#endif
#ifdef DDM_FAULT_PENDINGCOUNTER_SUPPORT
            DtcStatusInfo[usDTCIndex].ucFaultPendingCounter = 0;
#endif
#ifdef DDM_AGAED_COUNTER_RECORD
            DtcStatusInfo[usDTCIndex].ucAgedCounter = 0;
#endif
            byteidx = usDTCIndex/8;
            bitidx = usDTCIndex%8;
            DtcStatusByteChangeFlag[byteidx]|=(uint8)(1u<<bitidx);
            
        }
        DtcStatusToBeSavedFlag = 1;
    }
#endif


    DDMSetAllDTCSwitch(DTC_SWITCH_ENABLE);
    SetDtcMState(DTCM_INITED);

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
Std_ReturnType DDMSetOperationMode(uint8 mode)
{

    Std_ReturnType ucRet = E_OK;
    uint16 byteidx;
    uint16 bitidx;
/*
    if(DtcMState != DTCM_INITED)
    {
        return E_NOT_OK;
    }*/
    DDMGlobalIntDisable();
    switch(mode)
    { 
        case DDM_STARTCYCLE:

            if((DtcMState == DTCM_INITED)||(DtcMState == DTCM_STOPCYCLE))   
            {    
                uint16 usDTCIndex;
                for(usDTCIndex = 0; usDTCIndex < NUMBER_OF_DTC; usDTCIndex++)
                {
                    uint8 ucCurrentStat=0;

                    /*save the current dtc status*/
                    ucCurrentStat = DtcStatusInfo[usDTCIndex].ucDTCCurStatus;

                    //DtcStatusInfo[usDTCIndex].ssFCounterSequential = 0;
                    FaultDetectionCounter[usDTCIndex] = 0;


                    /*BIT3_CONFIRMED_DTC*/
                    if((DtcStatusInfo[usDTCIndex].ucDTCCurStatus & DTC_STATUS_BIT3_CONFIRMED_DTC)&&\
                    (DTCStatusByteInfoCfg[usDTCIndex].ucAgingAllowed == TRUE))
                    {
                        if((0 == (DtcStatusInfo[usDTCIndex].ucDTCCurStatus & DTC_STATUS_BIT1_CYCLE_FAILED))&&\
                        (0 == (DtcStatusInfo[usDTCIndex].ucDTCCurStatus & DTC_STATUS_BIT4_NO_TEST_CLEARED)))
                        {   /*当前周期的Bit4与Bit1可表示当前周期测试完成且测试通过（没有发生任何Fail）*/
                            DtcStatusInfo[usDTCIndex].ucAgingCounter++;
                        }
                        else
                        {   
                            DtcStatusInfo[usDTCIndex].ucAgingCounter = 0;
                        }
                                
                        if(DtcStatusInfo[usDTCIndex].ucAgingCounter >= DTCStatusByteInfoCfg[usDTCIndex].ucAgingThreshold)
                        {   
                            DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT3_CONFIRMED_DTC;
                            DtcStatusInfo[usDTCIndex].ucAgingCounter = 0;
#ifdef DDM_AGAED_COUNTER_RECORD
                            if(DtcStatusInfo[usDTCIndex].ucAgedCounter < 0xFF)
                            {
                                DtcStatusInfo[usDTCIndex].ucAgedCounter++;
                            }
#endif
                        }

                    }

                    /*BIT2_Pending_DTC*/
                    if((DtcStatusInfo[usDTCIndex].ucDTCLastStatus & DTC_STATUS_BIT2_PENDING_DTC)&&\
                    (DtcStatusInfo[usDTCIndex].ucDTCCurStatus & DTC_STATUS_BIT2_PENDING_DTC))
                    {
                        if((0 == (DtcStatusInfo[usDTCIndex].ucDTCLastStatus & DTC_STATUS_BIT1_CYCLE_FAILED))&&\
                        (0 == (DtcStatusInfo[usDTCIndex].ucDTCLastStatus & DTC_STATUS_BIT4_NO_TEST_CLEARED))&&\
                        (0 == (DtcStatusInfo[usDTCIndex].ucDTCCurStatus & DTC_STATUS_BIT1_CYCLE_FAILED))&&\
                        (0 == (DtcStatusInfo[usDTCIndex].ucDTCCurStatus & DTC_STATUS_BIT4_NO_TEST_CLEARED)))
                        /*当前周期的Bit4与Bit1可表示当前周期测试完成且测试通过（没有发生任何Fail）*/
                        /*上次周期的Bit4与Bit1可表示上次周期测试完成且测试通过（没有发生任何Fail）*/
                        {
                            DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT2_PENDING_DTC;
#ifdef DDM_FAULT_PENDINGCOUNTER_SUPPORT
                            DtcStatusInfo[usDTCIndex].ucFaultPendingCounter = 0;
#endif
                        }
                    }
                    /*clear bit0*/
                    /*
                    if(DTCStatusByteInfoCfg[usDTCIndex].ucStatusByteSwitch & DTC_STATUS_BIT0_TEST_FAILED)
                    {
                        DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT0_TEST_FAILED;
                    }
                    else
                    {
                    } 
                    */
                    /*clear bit1*/
                    DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT1_CYCLE_FAILED;
                    /*if(DTCStatusByteInfoCfg[usDTCIndex].ucStatusByteSwitch & DTC_STATUS_BIT1_CYCLE_FAILED)
                    {
                        DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT1_CYCLE_FAILED;
                    }
                    else
                    {
                    }*/
                    /*set bit6*/
                    DtcStatusInfo[usDTCIndex].ucDTCCurStatus |= DTC_STATUS_BIT6_NO_TEST_THIS_CYCLE;
                    /*if(DTCStatusByteInfoCfg[usDTCIndex].ucStatusByteSwitch & DTC_STATUS_BIT6_NO_TEST_THIS_CYCLE)
                    {
                        DtcStatusInfo[usDTCIndex].ucDTCCurStatus |= DTC_STATUS_BIT6_NO_TEST_THIS_CYCLE;
                    }
                    else
                    {
                    }*/
                    /*save the current DTC as the last operation cycle status*/
                    DtcStatusInfo[usDTCIndex].ucDTCLastStatus = ucCurrentStat;

                    byteidx = usDTCIndex/8;
                    bitidx = usDTCIndex%8;
                    DtcStatusByteChangeFlag[byteidx]|=(uint8)(1u<<bitidx);
            
                }

                SetDtcMState(DTCM_STARTCYCLE);
                DtcStatusToBeSavedFlag = 1;

            }
            else
            {
                ucRet = E_NOT_OK;
            }

        break;       
        case DDM_STOPCYCLE:
         
            if(DtcMState == DTCM_STARTCYCLE)
            {
                ucRet = Cbk_DDMSaveAllDTCStatusRequest((uint8*)(&DtcStatusInfo[0]),sizeof(DtcStatusInfo));
                if(E_OK == ucRet)
                {   
                    DtcStatusToBeSavedFlag = 1;
                    SetDtcMState(DTCM_STOPCYCLE);
                }
                else
                {
                    ucRet = E_NOT_OK;
                }
            }
            else
            {
                ucRet = E_NOT_OK;    
            }
        break;   
        
        default:
            ucRet = E_NOT_OK;
        break;    

    }
    /*开中断*/
    DDMGlobalIntEnable();

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


DTCStdReturnType DDMClearDTC(uint32 uiDTCNumber)
{
    uint16 usDTCIndex = 0;
    //uint16 byteidx;
    //uint16 bitidx;
    //uint16 ucrrentst;
    DTCStdReturnType ucRet = DDM_OK;
    
    DDMGlobalIntDisable();

    //GetDtcMState(ucrrentst);


    if(DtcMState == DTCM_STARTCYCLE)
    {
        usDTCIndex = DDMGetDTCIndex(uiDTCNumber);
        if(uiDTCNumber == 0xFFFFFFU)
        {  
            uint16 usIndex=0;
            for(usIndex = 0; usIndex < NUMBER_OF_DTC; usIndex++)
            {
                DDMDtcClrReqProcess(usIndex);
                //byteidx = usIndex/8;
                //bitidx = usIndex%8;
                //DtcStatusByteChangeFlag[byteidx]|=(uint8)(1u<<bitidx);
            }
            //ucRet = Cbk_DDMSaveAllDTCStatusRequest(DtcStatusInfo);
            //SetDDMStateBit(DTCM_CLEARALL);
            ucRet = Cbk_DDMSaveAllDTCStatusRequest((uint8*)(&DtcStatusInfo[0]),sizeof(DtcStatusInfo));
            if(ucRet == DDM_OK)
            {
                SetDDMStateBit(DTCM_CLEARING);
                ucRet = DDM_CLRDTCBUSY;
            }
        }
        else
        {
            ucRet = DDM_OUTOFRANGE;
        }
    }
    else if((DtcMState & DTCM_CLEARING) != 0)
    {
        ucRet = Cbk_DDMRequireDTCSaveReault();
        if(ucRet != DDM_CLRDTCBUSY)
        {   /*Clear OK or NOT OK*/
            ClrDDMStateBit(DTCM_CLEARING);
        }
    }
    else if(DtcMState & (DTCM_PROCESSING|DTCM_CYCLESAVING) != 0)
    {
        ucRet = DDM_CLRDTCBUSY;
    }
    else 
    {
        ucRet = DDM_NOT_OK;
    }
    
    DDMGlobalIntEnable();

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
Std_ReturnType DDMSetDtcStatuBit(uint16 usDtcIndex,uint8 ucBitMask)
{
    Std_ReturnType ucRet = E_OK;
    if(DtcMState != DTCM_PROCESSING)
    {
        DtcStatusInfo[usDtcIndex].ucDTCCurStatus |= ucBitMask;    
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
Std_ReturnType DDMClearDtcStatuBit(uint16 usDtcIndex,uint8 ucBitMask)
{
    Std_ReturnType ucRet = E_OK;
    if(DtcMState != DTCM_PROCESSING)
    {
        DtcStatusInfo[usDtcIndex].ucDTCCurStatus &= (uint8)(~ucBitMask);//DTC_STATUS_BIT2_PENDING_DTC;    
    }
    else
    {
        ucRet = E_NOT_OK;
    }
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
void DDMTestPreResultProcess(uint16 usDTCIndex, uint8 ucCurrentStatus)
{
    uint16 ucrrentst;
    /*Disable INT*/
    DDMGlobalIntDisable();

    GetDtcMState(ucrrentst);

    SetDDMStateBit(DTCM_PROCESSING);

    ucrrentst &= (~(DTCM_CYCLESAVING|DTCM_CLEARING));

    DDMGlobalIntEnable();
    

    if((usDTCIndex < NUMBER_OF_DTC)&&(ucrrentst == DTCM_STARTCYCLE)&&\
        (DTC_SWITCH_ENABLE == DDMGetDTCSwitch(usDTCIndex))/*&&\
        ((DtcMState & DTCM_CLEARALL) != DTCM_CLEARALL)*/)
    {
        switch(ucCurrentStatus)
        {
            case DTC_TEST_PREFAILED:
            case DTC_TEST_FAILED:

                /*clear  counter*/
                if(DTCStatusByteInfoCfg[usDTCIndex].ucJumpToZero == DTC_TRUE)
                {
                    /*reach the pass level*/
                    if(FaultDetectionCounter[usDTCIndex] <= DTCStatusByteInfoCfg[usDTCIndex].ssPThresholdIntermit)
                    {
                        //DtcStatusInfo[usDTCIndex].ssFCounterSequential = 0;
                        FaultDetectionCounter[usDTCIndex] = 0;
                    } 
                }
                
                /* increase  Intermit failed counter*/
                if(FaultDetectionCounter[usDTCIndex] < DTCStatusByteInfoCfg[usDTCIndex].ssFThresholdIntermit)
                {
                    sint16 tempFcont = 0;
                    tempFcont = FaultDetectionCounter[usDTCIndex];//Save the current Counter
                    FaultDetectionCounter[usDTCIndex] += DTCStatusByteInfoCfg[usDTCIndex].ucIncreaseStepSize;
                    
                    if(FaultDetectionCounter[usDTCIndex] < tempFcont)
                    {/*over*/
                        FaultDetectionCounter[usDTCIndex] = DTCStatusByteInfoCfg[usDTCIndex].ssFThresholdIntermit;        
                    }
                }
                else
                {
                    FaultDetectionCounter[usDTCIndex] = DTCStatusByteInfoCfg[usDTCIndex].ssFThresholdIntermit;    
                }
                
                if(DTC_TEST_FAILED == ucCurrentStatus)
                {
                    FaultDetectionCounter[usDTCIndex] = DTCStatusByteInfoCfg[usDTCIndex].ssFThresholdIntermit;        
                }
                
                /*Intermit only*/
                if(FaultDetectionCounter[usDTCIndex] >= DTCStatusByteInfoCfg[usDTCIndex].ssFThresholdIntermit)
                {
                    if(E_OK == Cbk_DDMTestReseultFailPre(usDTCIndex))
                    {
                        DDMTestReseultProcess(usDTCIndex, DTC_TEST_FAILED); 
                        Cbk_DDMEventFiltered(usDTCIndex,DTC_TEST_FAILED);
                    }
                }
                 

                break;
            case DTC_TEST_PREPASSED:
            case DTC_TEST_PASSED:
                    /*clear  counter*/
                if(DTCStatusByteInfoCfg[usDTCIndex].ucDownToZero == DTC_TRUE)
                {
                    if(FaultDetectionCounter[usDTCIndex] >= DTCStatusByteInfoCfg[usDTCIndex].ssFThresholdIntermit)
                    {
                        //DtcStatusInfo[usDTCIndex].ssFCounterSequential = 0;
                        FaultDetectionCounter[usDTCIndex]   = 0;
                    }                    
                }

                /* decrease  Intermit failed counter*/
                if(FaultDetectionCounter[usDTCIndex] > DTCStatusByteInfoCfg[usDTCIndex].ssPThresholdIntermit)
                {
                    sint16 tempFcont = 0;
                    tempFcont = FaultDetectionCounter[usDTCIndex];//Save the current Counter
                    
                    FaultDetectionCounter[usDTCIndex] -= DTCStatusByteInfoCfg[usDTCIndex].ucDecreaseStepSize;
                    
                    if(FaultDetectionCounter[usDTCIndex] > tempFcont)
                    {/*over*/
                        FaultDetectionCounter[usDTCIndex] = DTCStatusByteInfoCfg[usDTCIndex].ssPThresholdIntermit;
                    }
                }
                else
                {
                    FaultDetectionCounter[usDTCIndex] = DTCStatusByteInfoCfg[usDTCIndex].ssPThresholdIntermit;
                }               
                            
                if(DTC_TEST_PASSED == ucCurrentStatus)
                {
                    FaultDetectionCounter[usDTCIndex] = DTCStatusByteInfoCfg[usDTCIndex].ssPThresholdIntermit;        
                }            
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                if(FaultDetectionCounter[usDTCIndex] <= DTCStatusByteInfoCfg[usDTCIndex].ssPThresholdIntermit)
                {       
                    if(E_OK == Cbk_DDMTestReseultPassPre(usDTCIndex))
                    {
                        DDMTestReseultProcess(usDTCIndex, DTC_TEST_PASSED);
                        Cbk_DDMEventFiltered(usDTCIndex,DTC_TEST_PASSED);
                    }
                }

                break;
            default:
                break;
        }
    }

    DDMGlobalIntDisable();
    ClrDDMStateBit(DTCM_PROCESSING);
    DDMGlobalIntEnable();

    /*Enable INT*/
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
void DDMReportNumberOfDTCByMask(uint8 ucMaskByte, uint8 *pData)
{
    uint16 usCounter = 0;
    uint16 usLoop = 0;
    Std_ReturnType ret = E_OK;
    uint8  mask;

    mask = DTCSTATUSAVAILABLEMASK&ucMaskByte;
    if(mask !=0 )
    {
        for(usLoop = 0;usLoop < NUMBER_OF_DTC;usLoop++)
        {
            if(mask & DtcStatusInfo[usLoop].ucDTCCurStatus)
            {
                usCounter++;
            }
        }
    }
    //pData[0] = 0x59;
    //pData[1] = 0x01;
    pData[2] = DTCSTATUSAVAILABLEMASK;
    pData[3] = ISO15031FORMAT;
    pData[4] = (uint8)(usCounter >> 8U);
    pData[5] = (uint8)(usCounter);

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
uint16 DDMReportDTCByStatusMask(uint8 ucMaskByte, uint8 *pData)
{
    uint16 usoffset = 0;
    uint16 usLoop = 0;
    uint16 usResLen = 0;
    uint16 usCounter=0;
    uint8  mask;
    
    mask = DTCSTATUSAVAILABLEMASK&ucMaskByte;
    
    //pData[0] = 0x59;
    //pData[1] = 0x02;
    pData[2] = DTCSTATUSAVAILABLEMASK;
    usResLen = 3u;
    
    if(mask !=0 )
    {
        for(usLoop = 0;usLoop < NUMBER_OF_DTC;usLoop++)
        {
            if(mask & DtcStatusInfo[usLoop].ucDTCCurStatus)
            {
                usCounter++;
            }
        }
        if(usCounter != 0)
        {
            usResLen = 3u + (usCounter << 2);//usResLen = 3u + 4*usCounter;
            usoffset = 3u;
        
            for(usLoop = 0;usLoop < NUMBER_OF_DTC;usLoop++)
            {
                if(mask & DtcStatusInfo[usLoop].ucDTCCurStatus)
                {
                    pData[usoffset] = (uint8)(DTCFFInfoCfg[usLoop].uiDTCNumber>>16u);//high
                    usoffset++;
                    pData[usoffset] = (uint8)(DTCFFInfoCfg[usLoop].uiDTCNumber>>8U);
                    usoffset++;
                    pData[usoffset] = (uint8)(DTCFFInfoCfg[usLoop].uiDTCNumber);
                    usoffset++;
                    pData[usoffset] = mask&DtcStatusInfo[usLoop].ucDTCCurStatus; 
                    usoffset++;
                }
            }       
        }
    }
    else
    {
        
    }
    return usResLen;
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
DTCStdReturnType DDMReportSnapshotByDTCNumber
(    
    uint32   uiDTCNumber, 
    uint8    ucSnapshotNumber, 
    uint8*   pData,
    uint32*  pResLen/*out*/
)
{
    uint16 RespIndex;
    uint16 usResLen = 0;
    uint16 DtcIndex;
    uint16 i,k;
    DTCStdReturnType ucRet = DDM_OK;

    DTCRecdNumInfoType DTCRecdNumInfo;
    
    DtcIndex = DDMGetDTCIndex(uiDTCNumber); 
    if(DtcIndex < NUMBER_OF_DTC)
    {
        if(ucSnapshotNumber == 0xFF)
        {   
            //pData[0] = 0x59;
            //pData[1] = 0x4;
            //pData[2] = uiDTCNumber>>16u;
            //pData[3] = uiDTCNumber>>8u;
            //pData[4] = uiDTCNumber>>0u;
            pData[5] = DtcStatusInfo[DtcIndex].ucDTCCurStatus;
            /*********************/
            RespIndex = 6u;
            usResLen = 6u;

            /*当前DTC的快照标示符数量*/
            for(k = 0;k<DTCFFInfoCfg[DtcIndex].NumOfDTCSnapshotRecordNumber; k++)
            {
                pData[RespIndex] = DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].DTCSnapshotRecordNumber;/*fiex DTCSnapshotRecordNumber #2*/
                RespIndex++;
                pData[RespIndex] = DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].DTCSnapshotRecordNumberOfIdentifiers;/*fiex DTCSnapshotRecordNumberOfIdentifiers #2*/
                RespIndex++;

                usResLen += 2u;/*DTCSnapshotRecordNumber and DTCSnapshotRecordNumberOfIdentifiers*/
                /*当前DTC的当前SnapshotRecordNumber数量*/
                for(i = 0;i<DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].DTCSnapshotRecordNumberOfIdentifiers;i++)
                {
                    Std_ReturnType ret;

                    pData[RespIndex] = (uint8)((DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].SnapShotDIDPtr[i].usSnapDidNum) >> 8u);
                    RespIndex++;
                    pData[RespIndex] = (uint8)((DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].SnapShotDIDPtr[i].usSnapDidNum) >> 0);
                    RespIndex++;
#if 0
                    ret = Cbk_DDMReqSnapshotByDID(\
                            DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].SnapShotDIDPtr[i].usSnapDidNum,\
                            &pData[RespIndex],\
                            DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].SnapShotDIDPtr[i].ucSnapDidLen);
#endif
                    DTCRecdNumInfo.uiDTCIdx  = DtcIndex;
                    DTCRecdNumInfo.uiRecdNum = DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].DTCSnapshotRecordNumber;
                    DTCRecdNumInfo.uiDIDNum = DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].SnapShotDIDPtr[i].usSnapDidNum;
                    DTCRecdNumInfo.uiDIDIdx = i;
                    DTCRecdNumInfo.uiDIDLen  = DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].SnapShotDIDPtr[i].ucSnapDidLen;
                    DTCRecdNumInfo.ucDatPtr  = &pData[RespIndex];

                    ret = Cbk_DDMReqSnapshotByDID(&DTCRecdNumInfo);

                    if(ret == E_OK)
                    {
                        RespIndex += DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].SnapShotDIDPtr[i].ucSnapDidLen;
                    }
                    else
                    {
                        ucRet = DDM_CBKRETERROR;
                        break;
                    }

                    usResLen += (2u+DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].SnapShotDIDPtr[i].ucSnapDidLen);
                }

                *pResLen = usResLen;
            }
        /**************************************************************/
        //////////////////////////////////////////
        /**************************************************************/    
        }
        else
        {
            for(k = 0;k<DTCFFInfoCfg[DtcIndex].NumOfDTCSnapshotRecordNumber; k++)
            {
                if(ucSnapshotNumber == DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].DTCSnapshotRecordNumber)
                {
                    break;
                }
            }

            if(k < DTCFFInfoCfg[DtcIndex].NumOfDTCSnapshotRecordNumber)
            {
                //pData[0] = 0x59;
                //pData[1] = 0x4;
                //pData[2] = uiDTCNumber>>16u;
                //pData[3] = uiDTCNumber>>8u;
                //pData[4] = uiDTCNumber>>0u;
                pData[5] = DtcStatusInfo[DtcIndex].ucDTCCurStatus;
                /*********************/
                RespIndex = 6u;
                usResLen = 6u;

                pData[RespIndex] = DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].DTCSnapshotRecordNumber;/*fiex DTCSnapshotRecordNumber #2*/
                RespIndex++;
                pData[RespIndex] = DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].DTCSnapshotRecordNumberOfIdentifiers;/*fiex DTCSnapshotRecordNumberOfIdentifiers #2*/
                RespIndex++;
                usResLen += 2u;/*DTCSnapshotRecordNumber and DTCSnapshotRecordNumberOfIdentifiers*/
                /*当前DTC的当前SnapshotRecordNumber数量*/
                for(i = 0;i<DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].DTCSnapshotRecordNumberOfIdentifiers;i++)
                {
                    Std_ReturnType ret;
                    
                    pData[RespIndex] = (uint8)((DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].SnapShotDIDPtr[i].usSnapDidNum) >> 8u);
                    RespIndex++;
                    pData[RespIndex] = (uint8)((DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].SnapShotDIDPtr[i].usSnapDidNum) >> 0);
                    RespIndex++;
#if 0
                    ret = Cbk_DDMReqSnapshotByDID(\
                        DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].SnapShotDIDPtr[i].usSnapDidNum,\
                        &pData[RespIndex],\
                        DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].SnapShotDIDPtr[i].ucSnapDidLen);

#endif
                    DTCRecdNumInfo.uiDTCIdx  = DtcIndex;
                    DTCRecdNumInfo.uiRecdNum = DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].DTCSnapshotRecordNumber;
                    DTCRecdNumInfo.uiDIDNum = DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].SnapShotDIDPtr[i].usSnapDidNum;
                    DTCRecdNumInfo.uiDIDIdx = i;
                    DTCRecdNumInfo.uiDIDLen  = DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].SnapShotDIDPtr[i].ucSnapDidLen;
                    DTCRecdNumInfo.ucDatPtr  = &pData[RespIndex];

                    ret = Cbk_DDMReqSnapshotByDID(&DTCRecdNumInfo);

                    if(ret == E_OK)
                    {
                        RespIndex += DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].SnapShotDIDPtr[i].ucSnapDidLen;
                    }
                    else
                    {
                        ucRet = DDM_CBKRETERROR;
                        break;
                    }
     
                    usResLen += (2u+DTCFFInfoCfg[DtcIndex].DTCSnapShotInfoPtr[k].SnapShotDIDPtr[i].ucSnapDidLen);
                }

                *pResLen = usResLen;
            }
            else
            {/*没有找到RecordNumber*/
                ucRet = DDM_OUTOFRANGE;
            }
        }

    }
    else
    {
        ucRet = DDM_OUTOFRANGE;
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
DTCStdReturnType DDMReportExtenDataByDTCNumber
(    
    uint32   uiDTCNumber, 
    uint8    ucExtendedRecordNumber, 
    uint8*   pData,
    uint32*  pResLen/*out*/
)
{
    uint16 k;
    uint16 RespIndex;
    uint8* ExtendedPtr;
    uint16 usResLen = 0;
    uint16 DtcIndex=NUMBER_OF_DTC;
    DTCStdReturnType ucRet = DDM_OK;

    DtcIndex = DDMGetDTCIndex(uiDTCNumber); 

       if(DtcIndex < NUMBER_OF_DTC)
    {

        if(ucExtendedRecordNumber == 0xFF)
        {
            //pData[0] = 0x59;
            //pData[1] = 0x6;
            //pData[2] = uiDTCNumber>>16u;
            //pData[3] = uiDTCNumber>>8u;
            //pData[4] = uiDTCNumber>>0u;
            pData[5] = DtcStatusInfo[DtcIndex].ucDTCCurStatus;
            RespIndex = 6u;
            usResLen = 6u;

            for(k = 0;k<DTCFFInfoCfg[DtcIndex].NumOfDTCExtendedRecordNumber; k++)
            {
                Std_ReturnType ret;
                pData[RespIndex] =  DTCFFInfoCfg[DtcIndex].DTCExtendedInfoPtr[k].DTCExtendedRecordNumber;
                RespIndex++;

                ret = Cbk_DDMReqExtendedDataByRecdNum(\
                    DtcIndex,\
                    DTCFFInfoCfg[DtcIndex].DTCExtendedInfoPtr[k].DTCExtendedRecordNumber,\
                    &pData[RespIndex],\
                    DTCFFInfoCfg[DtcIndex].DTCExtendedInfoPtr[k].ucExtendRecordLen);
                if(ret == E_OK)
                {
                    RespIndex += DTCFFInfoCfg[DtcIndex].DTCExtendedInfoPtr[k].ucExtendRecordLen;
                }
                else
                {
                    ucRet = DDM_CBKRETERROR;
                    break;
                }
                 usResLen += (1+DTCFFInfoCfg[DtcIndex].DTCExtendedInfoPtr[k].ucExtendRecordLen);
            }
            *pResLen = usResLen;
        }
        else
        {
            for(k = 0;k<DTCFFInfoCfg[DtcIndex].NumOfDTCExtendedRecordNumber; k++)
            {
                if(ucExtendedRecordNumber == DTCFFInfoCfg[DtcIndex].DTCExtendedInfoPtr[k].DTCExtendedRecordNumber)
                {
                    break;
                }
            }

            if(k < DTCFFInfoCfg[DtcIndex].NumOfDTCExtendedRecordNumber)
            {
                Std_ReturnType ret;
                //pData[0] = 0x59;
                //pData[1] = 0x6;
                //pData[2] = uiDTCNumber>>16u;
                //pData[3] = uiDTCNumber>>8u;
                //pData[4] = uiDTCNumber>>0u;
                pData[5] = DtcStatusInfo[DtcIndex].ucDTCCurStatus;
                RespIndex = 6u;
                usResLen = 6u;

                pData[RespIndex] =  DTCFFInfoCfg[DtcIndex].DTCExtendedInfoPtr[k].DTCExtendedRecordNumber;
                RespIndex++;

                ret = Cbk_DDMReqExtendedDataByRecdNum(\
                    DtcIndex,\
                    DTCFFInfoCfg[DtcIndex].DTCExtendedInfoPtr[k].DTCExtendedRecordNumber,\
                    &pData[RespIndex],\
                    DTCFFInfoCfg[DtcIndex].DTCExtendedInfoPtr[k].ucExtendRecordLen);
                if(ret == E_OK)
                {
                    RespIndex += DTCFFInfoCfg[DtcIndex].DTCExtendedInfoPtr[k].ucExtendRecordLen;
                    usResLen += (1+DTCFFInfoCfg[DtcIndex].DTCExtendedInfoPtr[k].ucExtendRecordLen);
                    *pResLen = usResLen;
                }
                else
                {
                    ucRet = DDM_CBKRETERROR;
                }

            }
            else
            {/*没有找到extended Number*/
                ucRet = DDM_OUTOFRANGE;
            }
        }

    }
    else
    {
        ucRet = DDM_OUTOFRANGE;
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
uint16 DDMReportSupportedDTC(uint8 *pData)
{
    uint16 usLoop = 0;
    uint16 usCounter = 0;
    uint16 usResLen = 0;
    usResLen = 3u+(NUMBER_OF_DTC*4u);
    
    //pData[0] = 0x59;
    //pData[1] = 0x0A;
    pData[2] = DTCSTATUSAVAILABLEMASK;
    usCounter = 3u;
    for(usLoop = 0;usLoop < NUMBER_OF_DTC;usLoop++)
    {
        pData[usCounter] = (uint8)(DTCFFInfoCfg[usLoop].uiDTCNumber>>16U);  /*high*/
        usCounter++;
        pData[usCounter] = (uint8)(DTCFFInfoCfg[usLoop].uiDTCNumber>>8U);
        usCounter++;
        pData[usCounter] = (uint8)(DTCFFInfoCfg[usLoop].uiDTCNumber);
        usCounter++;
        pData[usCounter] = DtcStatusInfo[usLoop].ucDTCCurStatus&DTCSTATUSAVAILABLEMASK;
        usCounter++;
    }
    return usResLen;
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
STATIC uint8 DDMGetDTCSwitch(uint16 DtcIndex)
{    
    uint8  ucRet;
    uint8  Mask; 

    uint16 byteId;
    uint16 bitId;   
    

    byteId = DtcIndex/8;
    bitId  = DtcIndex%8;

    ucRet = DTC_SWITCH_DISABLE;
    
    if(DtcIndex < NUMBER_OF_DTC)
    {
        Mask = (1<<bitId);

        if((DtcSwitchInterFlag[byteId] & Mask) != 0)
        {
            ucRet = DTC_SWITCH_ENABLE;
        }
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
uint8 DDMSetDTCSwitch(uint16 DtcIndex,DTCSwitchType type)
{    
    DTCStdReturnType ucRet = DDM_OK;
    uint8  Mask; 
    uint16 byteId;
    uint16 bitId;

    byteId = DtcIndex/8;
    bitId  = DtcIndex%8;
    
    if(DtcIndex < NUMBER_OF_DTC)
    {
        Mask = (1<<bitId);
        
        if(type == DTC_SWITCH_ENABLE)
        {
            DtcSwitchInterFlag[byteId] |= Mask;
        }
        else if(type == DTC_SWITCH_DISABLE)
        {
            DtcSwitchInterFlag[byteId] &= (~Mask);
        }
        else
        {
            ucRet = DDM_OUTOFRANGE;
        }
    }
    else
    {
        ucRet = DDM_OUTOFRANGE; 
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
void DDMSetAllDTCSwitch(DTCSwitchType type)
{    
    /*关中断*/
    uint16 DtcIndex;

    for(DtcIndex = 0;DtcIndex < ((NUMBER_OF_DTC/8)+1); DtcIndex++)
    {
        if(DTC_SWITCH_ENABLE == type)
        {DtcSwitchInterFlag[DtcIndex] = 0xFF;}  
        else
        {DtcSwitchInterFlag[DtcIndex] = 0;} 
    }
    /*开中断*/
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
uint8 DDMGetCurrentStatusByMask(uint16 usDtcIndex,uint8 ucBitMask)
{

    return (DtcStatusInfo[usDtcIndex].ucDTCCurStatus & ucBitMask);
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
uint8 DDMGetCurrentStatusByte(uint16 usDtcIndex)
{
    return (DtcStatusInfo[usDtcIndex].ucDTCCurStatus);
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
#ifdef DDM_FAULT_OCCURCOUNTER_RECORD
uint8 DDMGetFaultOccurCounter(uint16 usDtcIndex)
{
    return (DtcStatusInfo[usDtcIndex].ucFaultOccurCounter);
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
#ifdef DDM_FAULT_PENDINGCOUNTER_SUPPORT
uint8 DDMGetFaultPendingCounter(uint16 usDtcIndex)
{
    return (DtcStatusInfo[usDtcIndex].ucFaultPendingCounter);
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
#ifdef DDM_AGAED_COUNTER_RECORD
uint8 DDMGetAgedCounter(uint16 usDtcIndex)
{
    return (DtcStatusInfo[usDtcIndex].ucAgedCounter);
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
uint8 DDMGetAgingCounter(uint16 usDtcIndex)
{
    return (DtcStatusInfo[usDtcIndex].ucAgingCounter);
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
STATIC uint16 DDMGetDTCIndex(uint32 usDIDNumber)
{
    uint16 idx = 0;
    
    for(idx = 0; idx < NUMBER_OF_DTC; idx++)
    {
        if(usDIDNumber == DTCFFInfoCfg[idx].uiDTCNumber)
        {
            break;
        }
        else
        {
        }
    }

    return idx;
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
STATIC uint8 DDMTestReseultProcess(uint16 usDTCIndex, uint8 ucCurrentState)
{
    DTCStdReturnType ucRet = DDM_OK;
    //uint16 ucrrentst;
    uint16 byteidx = 0;
    uint16 bitidx = 0;
    DTCStatusInfoType tempstinfo;
    uint16 i;
    //GetDtcMState(ucrrentst);
    //SetDtcMState(DTCM_PROCESSING);

    tempstinfo = DtcStatusInfo[usDTCIndex];
    
    if(usDTCIndex < NUMBER_OF_DTC)
    {
        if(DTC_SWITCH_ENABLE == DDMGetDTCSwitch(usDTCIndex))
        {
            switch(ucCurrentState)
            {    
                case DTC_TEST_FAILED:

#ifdef DDM_FAULT_OCCURCOUNTER_RECORD
                    if(DtcStatusInfo[usDTCIndex].ucFaultOccurCounter < 0xFF)
                    {
                        DtcStatusInfo[usDTCIndex].ucFaultOccurCounter++;
                    }
#endif

                    DtcStatusInfo[usDTCIndex].ucAgingCounter = 0;
                    /*snapshot and extended data*/
                    Cbk_DTCM_StoreFreezeFrame(
#ifdef DDM_FIRST_STORE_FREEZEFRAME_INDI 
                    DtcStatusInfo[usDTCIndex].ucFirstRecord,
#endif
                    usDTCIndex);
#ifdef DDM_FIRST_STORE_FREEZEFRAME_INDI 
                    DtcStatusInfo[usDTCIndex].ucFirstRecord = 0;
#endif
                      
                    DtcStatusInfo[usDTCIndex].ucDTCCurStatus |= DTC_STATUS_BIT0_TEST_FAILED;
                    
                    if((DtcStatusInfo[usDTCIndex].ucDTCCurStatus & DTC_STATUS_BIT1_CYCLE_FAILED) == 0)
                    {
                        DtcStatusInfo[usDTCIndex].ucDTCCurStatus |= DTC_STATUS_BIT1_CYCLE_FAILED;
#ifdef DDM_FAULT_PENDINGCOUNTER_SUPPORT
                        if(DtcStatusInfo[usDTCIndex].ucFaultPendingCounter < DTCStatusByteInfoCfg[usDTCIndex].ucPendingThreshold)
                        {
                            DtcStatusInfo[usDTCIndex].ucFaultPendingCounter++;
                            if(DtcStatusInfo[usDTCIndex].ucFaultPendingCounter == DTCStatusByteInfoCfg[usDTCIndex].ucPendingThreshold)
                            {
                                DtcStatusInfo[usDTCIndex].ucDTCCurStatus |= DTC_STATUS_BIT3_CONFIRMED_DTC;
                                /*DtcStatusInfo[usDTCIndex].ucAgingCounter = 0;*/ /*move up*/
                            }
                        }
                        else
#endif  
                        {
                            DtcStatusInfo[usDTCIndex].ucDTCCurStatus |= DTC_STATUS_BIT3_CONFIRMED_DTC;
                        }
                    }

                    DtcStatusInfo[usDTCIndex].ucDTCCurStatus |= DTC_STATUS_BIT2_PENDING_DTC;

/*
                    if(DTCStatusByteInfoCfg[usDTCIndex].ucStatusByteSwitch & DTC_STATUS_BIT3_CONFIRMED_DTC)
                    {
                        DtcStatusInfo[usDTCIndex].ucDTCCurStatus |= DTC_STATUS_BIT3_CONFIRMED_DTC;
                        DtcStatusInfo[usDTCIndex].usAgingCounter = 0;
                    }
                    else
                    {
                    }
*/
                    
                    DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT4_NO_TEST_CLEARED;
                    DtcStatusInfo[usDTCIndex].ucDTCCurStatus |= DTC_STATUS_BIT5_TEST_FAILED_CLEARED;
                    DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT6_NO_TEST_THIS_CYCLE;    
                     
                    break;
                case DTC_TEST_PASSED:
                    
                    DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT0_TEST_FAILED;
                    DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT4_NO_TEST_CLEARED;
                    DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT6_NO_TEST_THIS_CYCLE;
                    
                    break;
        
                default:
                    break;
            }
        }
        else    /*DTC switch is Disabled do nothing*/
        {
        }
    }
    else
    {
        ucRet = DDM_OUTOFRANGE;
    }
    
    byteidx = usDTCIndex/8;
    bitidx = usDTCIndex%8;
    DtcStatusByteChangeFlag[byteidx]|=(uint8)(1u<<bitidx);


    if((tempstinfo.ucAgingCounter != DtcStatusInfo[usDTCIndex].ucAgingCounter)||\
        ((tempstinfo.ucDTCCurStatus & (~DTC_STATUS_BIT0_TEST_FAILED) ) != (DtcStatusInfo[usDTCIndex].ucDTCCurStatus & (~DTC_STATUS_BIT0_TEST_FAILED) )))
    {DtcStatusToBeSavedFlag = 1;}
    //SetDtcMState(ucrrentst);
    
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
STATIC void DDMDtcClrReqProcess(uint16 usDTCIndex)
{
    //if(usDTCIndex < NUMBER_OF_DTC) 内部函数没有必要判断此条件
    { 
#if 0
        DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT0_TEST_FAILED;
        DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT1_CYCLE_FAILED;
        DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT2_PENDING_DTC;
        DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT3_CONFIRMED_DTC;
        DtcStatusInfo[usDTCIndex].ucDTCCurStatus |= DTC_STATUS_BIT4_NO_TEST_CLEARED;
        DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ~DTC_STATUS_BIT5_TEST_FAILED_CLEARED;
        DtcStatusInfo[usDTCIndex].ucDTCCurStatus |= DTC_STATUS_BIT6_NO_TEST_THIS_CYCLE;  
        DtcStatusInfo[usDTCIndex].ucDTCCurStatus &= ((uint8)(~DTC_STATUS_BIT7_WARNING_INDICATOR));
#endif
        DtcStatusInfo[usDTCIndex].ucDTCCurStatus = 0x50;/*bit4 and 6 set */
        DtcStatusInfo[usDTCIndex].ucDTCLastStatus = 0x50;
        DtcStatusInfo[usDTCIndex].ucAgingCounter = 0;
        //DtcStatusInfo[usDTCIndex].ssFCounterSequential = 0;
        FaultDetectionCounter[usDTCIndex] = 0;
#ifdef DDM_FIRST_STORE_FREEZEFRAME_INDI 
        DtcStatusInfo[usDTCIndex].ucFirstRecord = 1;
#endif
#ifdef DDM_FAULT_OCCURCOUNTER_RECORD
        DtcStatusInfo[usDTCIndex].ucFaultOccurCounter = 0;
#endif
#ifdef DDM_FAULT_PENDINGCOUNTER_SUPPORT
        DtcStatusInfo[usDTCIndex].ucFaultPendingCounter = 0;
#endif
#ifdef DDM_AGAED_COUNTER_RECORD
        DtcStatusInfo[usDTCIndex].ucAgedCounter = 0;
#endif
    }
    //else
    //{
    //    ucRet = DDM_OUTOFRANGE;
    //}
    //return ucRet;
}

/********************************End*******************************************/
