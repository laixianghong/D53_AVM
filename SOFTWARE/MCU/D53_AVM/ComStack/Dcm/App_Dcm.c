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
#include "Dcm.h"
#if(DCM_SERVICE_28_ENABLED == STD_ON)
#include "Com.h"
//#include "OsekNm.h"
#endif
#include "Ddm.h"
#include "Nm.h"

/*******************************************************************************
* Macros and Typedef
********************************************************************************/



/* For 0x28 */
#define Dcm_EnRx_EnTx                (0U)
#define Dcm_DisRx_EnTx               (1U)
#define Dcm_EnRx_DisTx               (2U)
#define Dcm_DisRx_DisTx              (3U)



/* For 0x2F*/
#define IOcontrolHandle_0x3001    (0U)

/* For 0x31*/
#define RoutineHandle_0xB301    (0U)
#define RoutineHandle_0xC000    (1U)
#define RoutineHandle_0xC001    (2U)
#define RoutineHandle_0xC002    (3U)


#if(DCM_SERVICE_28_ENABLED == STD_ON)
/* if Hirain Com& Nm are used, don't change below codes */
static uint8 Dcm_NmMessage_Status = Dcm_EnRx_EnTx;
static uint8 Dcm_ComMessage_Status = Dcm_EnRx_EnTx;
#endif

/***************************************************************************
* Global Function Implementation
****************************************************************************/
#if(DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL == STD_ON)
/****************************************************************************
* Name         :App_DiagnosticActive 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :N/A  
* Return code  :N/A  
* Description  :Check is it possible to enable Dcm module.  
*                
******************************************************************************/
FUNC(Std_ReturnType,DCM_CODE) App_DiagnosticActive(void)
{
    Std_ReturnType ret;
    ret = IndirNm_IsStartDelayExpired();
    return ret;
}
#endif 

/* 0x10 */
#if(DCM_SERVICE_10_ENABLED == STD_ON)

/******************************************************************************
* Name         :App_Default 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Default session callback function  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Default(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 tempP2Star;
    /* Step 1:Transmit positive response*/
    if(GetSuppressPosResponseBit() == 0U)/* If positive response is supressed, dont' need make it */
    {
        #if(RESPONSE_WITH_P2TIMER == STD_ON)
        pMsgContext->resData[DCM_INDEX_2] = (uint8)(gDcmDspSessionRow[DCM_INDEX_0].DcmDspSessionP2ServerMax >> 8U);
        pMsgContext->resData[DCM_INDEX_3] = (uint8)(gDcmDspSessionRow[DCM_INDEX_0].DcmDspSessionP2ServerMax); 
        tempP2Star = gDcmDspSessionRow[DCM_INDEX_0].DcmDspSessionP2StarServerMax/10U;
        pMsgContext->resData[DCM_INDEX_4] = (uint8)(tempP2Star >> 8U);
        pMsgContext->resData[DCM_INDEX_5] = (uint8)(tempP2Star);
        pMsgContext->resDataLen = 6U;
        #else
        pMsgContext->resDataLen = 2U;
        #endif
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_ProcessingDoneNoResponse();
    }  
}


/******************************************************************************
* Name         :App_DefaultPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Jump to default session once positive response is transmitted. 
*               Otherwise, do not change session type. 
******************************************************************************/
FUNC(void,DCM_CODE) App_DefaultPost(Std_ReturnType Result)
{
    uint8 i;
    
    if(Result == E_OK)
    {
        Set_SesCtrl(DCM_SESSION_DEFAULT); 
        gS3ServerTimerStartFlag = DCM_FLAG_DISACTIVE;
        Clr_S3_Server_Timer();
        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType = DCM_SEC_LEV_LOCK;
        
        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;    /* Reset */ 
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
        /* add your code here*/
        /* Restart Communication */
        #if(DCM_SERVICE_28_ENABLED == STD_ON)
                 Com_TxStart();
                 Com_RxStart();
        #endif
#if(DCM_SERVICE_85_ENABLED == STD_ON)
        DDMSetAllDTCSwitch(DTC_SWITCH_ENABLE);
#endif
    }
    else
    {
    }
}
/******************************************************************************
* Name         :App_Programming 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Default session callback function  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Programming(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DslInternal_RCRResponsePending(FORCERCR_RP);
    Clr_DiagState(DIAG_UDS_PROCESSING);
}

/******************************************************************************
* Name         :App_ProgrammingPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Jump to default session once positive response is transmitted.  
*               Otherwise, do not change session type. 
******************************************************************************/
FUNC(void,DCM_CODE) App_ProgrammingPost(Std_ReturnType Result)
{
    /* add your code here*/
    *((uint32*)0xFFE10) = 0xA5A5A5A5;
    /*reset*/
 }
/******************************************************************************
* Name         :App_Extended_Diagnostic 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Default session callback function  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Extended_Diagnostic(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 tempP2Star;
    /* Step 1:Transmit positive response*/
    if(GetSuppressPosResponseBit() == 0U)/* If positive response is supressed, dont' need make it */
    {
        #if(RESPONSE_WITH_P2TIMER == STD_ON)
        pMsgContext->resData[DCM_INDEX_2] = (uint8)(gDcmDspSessionRow[DCM_INDEX_2].DcmDspSessionP2ServerMax >> 8U);
        pMsgContext->resData[DCM_INDEX_3] = (uint8)(gDcmDspSessionRow[DCM_INDEX_2].DcmDspSessionP2ServerMax); 
        tempP2Star = gDcmDspSessionRow[DCM_INDEX_2].DcmDspSessionP2StarServerMax/10U;
        pMsgContext->resData[DCM_INDEX_4] = (uint8)(tempP2Star >> 8U);
        pMsgContext->resData[DCM_INDEX_5] = (uint8)(tempP2Star);
        pMsgContext->resDataLen = 6U;
        #else
        pMsgContext->resDataLen = 2U;
        #endif
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_ProcessingDoneNoResponse();
    }  
}


/******************************************************************************
* Name         :App_Extended_DiagnosticPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Jump to default session once positive response is transmitted. 
*               Otherwise, do not change session type. 
******************************************************************************/
FUNC(void,DCM_CODE) App_Extended_DiagnosticPost(Std_ReturnType Result)
{
    uint8 i;
    
    if(Result == E_OK)
    {
        /* Reset MCU and go to bootloader at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_EXTENDED_DIAGNOSTIC);  
        gS3ServerTimerStartFlag = DCM_FLAG_ACTIVE;
        Set_S3_Server_Timer(gDcmDspNonDefaultSessionS3Server);
        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType = DCM_SEC_LEV_LOCK;
        
        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;    /* Reset */ 
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
        
        /* add your code here*/
    }
    else
    {
    }
}
#endif

/* 0x11 */
#if(DCM_SERVICE_11_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_hardReset_Reset 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A   
* Description  :hardReset_Reset.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Hard_Reset_Reset(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);   
}

/******************************************************************************
* Name         :App_hardReset_ResetPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Std_ReturnType Result  
* Return code  :N/A  
* Description  : 
******************************************************************************/
FUNC(void,DCM_CODE) App_Hard_Reset_ResetPost(Std_ReturnType Result)
{
    uint8 i;

    if(Result == E_OK)
    {
        /* Reset MCU at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_DEFAULT);
        gS3ServerTimerStartFlag = DCM_FLAG_DISACTIVE;
        Clr_S3_Server_Timer();

        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType=DCM_SEC_LEV_LOCK;

        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;   /* Reset */           
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
    }
    else
    {
    }
}
/******************************************************************************
* Name         :App_keyOffOnReset_Reset 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A   
* Description  :keyOffOnReset_Reset.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_SoftReset_Reset(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);   
}

/******************************************************************************
* Name         :App_keyOffOnReset_ResetPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Std_ReturnType Result  
* Return code  :N/A  
* Description  : 
******************************************************************************/
FUNC(void,DCM_CODE) App_SoftReset_ResetPost(Std_ReturnType Result)
{
    uint8 i;

    if(Result == E_OK)
    {
        /* Reset MCU at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_DEFAULT);
        gS3ServerTimerStartFlag = DCM_FLAG_DISACTIVE;
        Clr_S3_Server_Timer();

        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType=DCM_SEC_LEV_LOCK;

        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;   /* Reset */           
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
    }
    else
    {
    }
}
#endif

/* 0x14 */
#if(DCM_SERVICE_14_ENABLED == STD_ON)
/************************************************************************
* Name         :App_ClearDiagnosticInformation 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A 
* Description  :Clear single DTC or group of DTC.  
*                
******************************************************************************/
static uint16 App_ClearFlag = 0;
FUNC(void,DCM_CODE) App_ClearDiagnosticInformation(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DTCStdReturnType error=DDM_OK;
    uint32 Dtc;


    if(0 == App_ClearFlag)
    {   
        App_ClearFlag = 1;
        DslInternal_RCRResponsePending(FORCERCR_RP);
    }

        Dtc=Make32Bit(pMsgContext->reqData[1],pMsgContext->reqData[2],pMsgContext->reqData[3]);
        error = DDMClearDTC(Dtc);
    if(error == DDM_CLRDTCBUSY)
        {
        /*do nothing*/
        return;
        }
    else if(error == DDM_OK)
        {
        pMsgContext->resDataLen=1; 
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else if(error == DDM_OUTOFRANGE)
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else if(error ==DDM_CLRERROR)
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_GENERALPROGRAMMINGFAILURE);
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_CONDITIONSNOTCORRECT);
        DsdInternal_ProcessingDone(pMsgContext);
    }
    App_ClearFlag = 0;
}
#endif

/* 0x22 */
#if(DCM_SERVICE_22_ENABLED == STD_ON)
/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF187(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint8 i;
    /*Demo for filling data*/
    for(i = 0U; i < RDBI_DIDLEN_0xF187; i++)
    {
        pMsgContext->resData[2U + i] = 0;
    }
    /*Demo end */
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resDataLen += (RDBI_DIDLEN_0xF187 + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF18A(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint8 i;
    /*Demo for filling data*/
    for(i = 0U; i < RDBI_DIDLEN_0xF18A; i++)
    {
        pMsgContext->resData[2U + i] = 0;
    }
    /*Demo end */
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resDataLen += (RDBI_DIDLEN_0xF18A + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF18C(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint8 i;
    /*Demo for filling data*/
    for(i = 0U; i < RDBI_DIDLEN_0xF18C; i++)
    {
        pMsgContext->resData[2U + i] = 0;
    }
    /*Demo end */
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resDataLen += (RDBI_DIDLEN_0xF18C + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF190(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint8 i;
    /*Demo for filling data*/
    for(i = 0U; i < RDBI_DIDLEN_0xF190; i++)
    {
        pMsgContext->resData[2U + i] = 0;
    }
    /*Demo end */
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resDataLen += (RDBI_DIDLEN_0xF190 + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xFD96(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint8 i;
    /*Demo for filling data*/
    for(i = 0U; i < RDBI_DIDLEN_0xFD96; i++)
    {
        pMsgContext->resData[2U + i] = 0;
    }
    /*Demo end */
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resDataLen += (RDBI_DIDLEN_0xFD96 + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF084(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint8 i;
    /*Demo for filling data*/
    for(i = 0U; i < RDBI_DIDLEN_0xF084; i++)
    {
        pMsgContext->resData[2U + i] = 0;
    }
    /*Demo end */
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resDataLen += (RDBI_DIDLEN_0xF084 + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF1FA(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint8 i;
    /*Demo for filling data*/
    for(i = 0U; i < RDBI_DIDLEN_0xF1FA; i++)
    {
        pMsgContext->resData[2U + i] = 0;
    }
    /*Demo end */
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resDataLen += (RDBI_DIDLEN_0xF1FA + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF120(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint8 i;
    /*Demo for filling data*/
    for(i = 0U; i < RDBI_DIDLEN_0xF120; i++)
    {
        pMsgContext->resData[2U + i] = 0;
    }
    /*Demo end */
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resDataLen += (RDBI_DIDLEN_0xF120 + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF121(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint8 i;
    /*Demo for filling data*/
    for(i = 0U; i < RDBI_DIDLEN_0xF121; i++)
    {
        pMsgContext->resData[2U + i] = 0;
    }
    /*Demo end */
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resDataLen += (RDBI_DIDLEN_0xF121 + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF122(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint8 i;
    /*Demo for filling data*/
    for(i = 0U; i < RDBI_DIDLEN_0xF122; i++)
    {
        pMsgContext->resData[2U + i] = 0;
    }
    /*Demo end */
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resDataLen += (RDBI_DIDLEN_0xF122 + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF184(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint8 i;
    /*Demo for filling data*/
    for(i = 0U; i < RDBI_DIDLEN_0xF184; i++)
    {
        pMsgContext->resData[2U + i] = 0;
    }
    /*Demo end */
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resDataLen += (RDBI_DIDLEN_0xF184 + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF089(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint8 i;
    /*Demo for filling data*/
    for(i = 0U; i < RDBI_DIDLEN_0xF089; i++)
    {
        pMsgContext->resData[2U + i] = 0;
    }
    /*Demo end */
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resDataLen += (RDBI_DIDLEN_0xF089 + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF189(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint8 i;
    /*Demo for filling data*/
    for(i = 0U; i < RDBI_DIDLEN_0xF189; i++)
    {
        pMsgContext->resData[2U + i] = 0;
    }
    /*Demo end */
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resDataLen += (RDBI_DIDLEN_0xF189 + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF1A2(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
 
    uint8 i;
    /*Demo for filling data*/
    for(i = 0U; i < RDBI_DIDLEN_0xF1A2; i++)
    {
        pMsgContext->resData[2U + i] = 0;
    }
    /*Demo end */
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resDataLen += (RDBI_DIDLEN_0xF1A2 + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
#if(DCM_SERVICE_2A_ENABLED == STD_ON)
#if(DCM_SERVICE_2C_ENABLED == STD_ON)
#endif
#endif
#endif

/* 0x2A */
#if(DCM_SERVICE_2A_ENABLED == STD_ON)
#endif

/* 0x24 */
#if(DCM_SERVICE_24_ENABLED == STD_ON)
#endif

/* 0x2E */
#if(DCM_SERVICE_2E_ENABLED == STD_ON)
/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF190(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    /*Demo for Getting data*/
    for(i = 0U; i < WDBI_DIDLEN_0xF190; i++)
    {
        /* *addr = pMsgContext->resData[2U + i];*/
    }
    /*Demo end*/
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xFD96(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    /*Demo for Getting data*/
    for(i = 0U; i < WDBI_DIDLEN_0xFD96; i++)
    {
        /* *addr = pMsgContext->resData[2U + i];*/
    }
    /*Demo end*/
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF1FA(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    /*Demo for Getting data*/
    for(i = 0U; i < WDBI_DIDLEN_0xF1FA; i++)
    {
        /* *addr = pMsgContext->resData[2U + i];*/
    }
    /*Demo end*/
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF18C(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    /*Demo for Getting data*/
    for(i = 0U; i < WDBI_DIDLEN_0xF18C; i++)
    {
        /* *addr = pMsgContext->resData[2U + i];*/
    }
    /*Demo end*/
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(pMsgContext);
}

#endif

/* 0x2F */
#if(DCM_SERVICE_2F_ENABLED == STD_ON)
#if 0
/******************************************************************************
* Name         :App_ReturnControlToEcuF060 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0x3001 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ResetToDefault0xF060 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_FreezeCurrentState0x3001 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_FreezeCurrentState0xF060 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ResetToDefault0x3001 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustmentF060 
* Called by    :Dcm   
* Preconditions:N/A 
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*          
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0x3001 (Dcm_MsgContextType* pMsgContext)
{
    /* Add your code here */
    /* If response data needed, set response data */
    pMsgContext->resData[DCM_INDEX_4] = TEST[DCM_INDEX_6];
    /* Set response legnth */
    pMsgContext->resDataLen = 5U;
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif
/******************************************************************************
* Name         :App_ReturnControlToEcu0x0100 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0x0100(Dcm_MsgContextType* pMsgContext)
{
    //pMsgContext->resData[4]=TEST[6];
    pMsgContext->resDataLen=4;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustment0x0100 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0x0100(Dcm_MsgContextType* pMsgContext)
{
    /*if(pMsgContext->reqData[5]>TEST[3])
    {
        pMsgContext->resData[4]=TEST[4];
    }
    else
    {
        pMsgContext->resData[4]=TEST[2];
    }*/
    pMsgContext->resDataLen=6;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcu0x0101 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0x0101(Dcm_MsgContextType* pMsgContext)
{
    //pMsgContext->resData[4]=TEST[6];
    pMsgContext->resDataLen=4;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustment0x0101 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0x0101(Dcm_MsgContextType* pMsgContext)
{
    /*if(pMsgContext->reqData[5]>TEST[3])
    {
        pMsgContext->resData[4]=TEST[4];
    }
    else
    {
        pMsgContext->resData[4]=TEST[2];
    }*/
    pMsgContext->resDataLen=6;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcu0x0102 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0x0102(Dcm_MsgContextType* pMsgContext)
{
    //pMsgContext->resData[4]=TEST[6];
    pMsgContext->resDataLen=4;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustment0x0102 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0x0102(Dcm_MsgContextType* pMsgContext)
{
    /*if(pMsgContext->reqData[5]>TEST[3])
    {
        pMsgContext->resData[4]=TEST[4];
    }
    else
    {
        pMsgContext->resData[4]=TEST[2];
    }*/
    pMsgContext->resDataLen=6;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcu0x0103 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0x0103(Dcm_MsgContextType* pMsgContext)
{
    //pMsgContext->resData[4]=TEST[6];
    pMsgContext->resDataLen=4;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustment0x0103 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0x0103(Dcm_MsgContextType* pMsgContext)
{
    /*if(pMsgContext->reqData[5]>TEST[3])
    {
        pMsgContext->resData[4]=TEST[4];
    }
    else
    {
        pMsgContext->resData[4]=TEST[2];
    }*/
    pMsgContext->resDataLen=6;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcu0x0104 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0x0104(Dcm_MsgContextType* pMsgContext)
{
    //pMsgContext->resData[4]=TEST[6];
    pMsgContext->resDataLen=4;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustment0x0104 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0x0104(Dcm_MsgContextType* pMsgContext)
{
    /*if(pMsgContext->reqData[5]>TEST[3])
    {
        pMsgContext->resData[4]=TEST[4];
    }
    else
    {
        pMsgContext->resData[4]=TEST[2];
    }*/
    pMsgContext->resDataLen=6;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcu0x0105 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0x0105(Dcm_MsgContextType* pMsgContext)
{
    //pMsgContext->resData[4]=TEST[6];
    pMsgContext->resDataLen=4;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustment0x0105 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0x0105(Dcm_MsgContextType* pMsgContext)
{
    /*if(pMsgContext->reqData[5]>TEST[3])
    {
        pMsgContext->resData[4]=TEST[4];
    }
    else
    {
        pMsgContext->resData[4]=TEST[2];
    }*/
    pMsgContext->resDataLen=6;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcu0x0106 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0x0106(Dcm_MsgContextType* pMsgContext)
{
    //pMsgContext->resData[4]=TEST[6];
    pMsgContext->resDataLen=4;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustment0x0106 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0x0106(Dcm_MsgContextType* pMsgContext)
{
    /*if(pMsgContext->reqData[5]>TEST[3])
    {
        pMsgContext->resData[4]=TEST[4];
    }
    else
    {
        pMsgContext->resData[4]=TEST[2];
    }*/
    pMsgContext->resDataLen=6;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcu0x0107 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0x0107(Dcm_MsgContextType* pMsgContext)
{
    //pMsgContext->resData[4]=TEST[6];
    pMsgContext->resDataLen=4;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustment0x0107 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0x0107(Dcm_MsgContextType* pMsgContext)
{
    /*if(pMsgContext->reqData[5]>TEST[3])
    {
        pMsgContext->resData[4]=TEST[4];
    }
    else
    {
        pMsgContext->resData[4]=TEST[2];
    }*/
    pMsgContext->resDataLen=6;
    DsdInternal_ProcessingDone(pMsgContext);
}

#endif

/* 0x19 */
#if(DCM_SERVICE_19_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_ReportNumberOfDTCByStatusMask 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A 
* Description  :Report number of DTC by status mask.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReportNumberOfDTCByStatusMask(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint8  DtcStatus;

    DtcStatus=pMsgContext->reqData[2];

    DDMReportNumberOfDTCByMask(DtcStatus,&pMsgContext->resData[0]);
    pMsgContext->resDataLen=6;/* Always equals 6 */

    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReportDTCByStatusMask 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Report DTC by status mask.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReportDTCByStatusMask(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint8  DtcStatus;
    uint32  DataLen;

    DtcStatus=pMsgContext->reqData[2];

    DataLen = DDMReportDTCByStatusMask(DtcStatus,&pMsgContext->resData[0]);
    pMsgContext->resDataLen = DataLen;

    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_ReportDTCSnapshortRecordByDTCNumber 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
 FUNC(void,DCM_CODE) App_ReportDTCSnapshotRecordByDTCNumber(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DTCStdReturnType error=DDM_OK;
    uint32 Dtc;
    uint8 DTCSnapshotRecordNumber;

    DTCSnapshotRecordNumber = pMsgContext->reqData[5];
    Dtc=Make32Bit(pMsgContext->reqData[2],pMsgContext->reqData[3],pMsgContext->reqData[4]);

    error = DDMReportSnapshotByDTCNumber(Dtc,DTCSnapshotRecordNumber,&pMsgContext->resData[0],&pMsgContext->resDataLen);
    if(error==DDM_OK)
    {
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
    }

}
/******************************************************************************
* Name         :App_ReportDTCExtendedDataRecordByDTCNumber 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReportDTCExtendedDataRecordByDTCNumber(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DTCStdReturnType error=DDM_OK;
    uint32 Dtc;
    uint8 DTCExtenNumber;

    DTCExtenNumber = pMsgContext->reqData[5];
    Dtc=Make32Bit(pMsgContext->reqData[2],pMsgContext->reqData[3],pMsgContext->reqData[4]);

    error = DDMReportExtenDataByDTCNumber(Dtc,DTCExtenNumber,&pMsgContext->resData[0],&pMsgContext->resDataLen);

    if(error==DDM_OK)
    {
        DsdInternal_ProcessingDone(pMsgContext);
    }   
    else
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
    }

}

/******************************************************************************
* Name         :App_ReportSupportedDTC 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReportSupportedDTC(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 DataLen;

    DataLen = DDMReportSupportedDTC(&pMsgContext->resData[0]);
    pMsgContext->resDataLen = DataLen;

    DsdInternal_ProcessingDone(pMsgContext);
}

#endif

/* 0x23 */
#if(DCM_SERVICE_23_ENABLED == STD_ON)
#endif

/* 0x27 */
#if(DCM_SERVICE_27_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_Request_Seed_L1 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Request_Seed_L1(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;

    for(i = 0U; i < 4; i++)
    {
        /* add your code here, generate App Seed */
        gMsgContextType.resData[2U + i] = 0x0C;
    }
    pMsgContext->resDataLen = 6; 
    DsdInternal_ProcessingDone(pMsgContext); 
}
/******************************************************************************
* Name         :App_Send_Key_L1 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Send_Key_L1(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint16 cunt = 0;
    
    /*compare Key here*/

    /*compare demo*/
    for(i=0;i<gDcmDspSecurityRow[0].DcmDspSecurityKeySize;i++)
    {
        cunt += pMsgContext->reqData[2+i];
    }

    if(cunt != 0)
    {   /*Key valid*/
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L1,KEY_IS_VALID);
        pMsgContext->resDataLen=2;
        
    }
    else
    {   /*Key invalid*/
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L1,KEY_IS_NOT_VALID);
    }
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif

/* 0x28 */
#if(DCM_SERVICE_28_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_enableRxAndTx_Control
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_EnableRxAndEnableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */
    uint8 CommunicationType;
    
    CommunicationType = pMsgContext->reqData[2];
    if((1u == CommunicationType)||(3u == CommunicationType))
    {
        Com_TxStart();
        Com_RxStart();
    pMsgContext->resDataLen = 2U;
    }
    else
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
    }
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_enableRxAnddisableTx_Control
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_EnableRxAndDisableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */
    uint8 CommunicationType;
    
    CommunicationType = pMsgContext->reqData[2];
    if((1u == CommunicationType)||(3u == CommunicationType))
    {
        Com_TxStop();
        Com_RxStart();
    pMsgContext->resDataLen = 2U;
    }
    else
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
    }
    DsdInternal_ProcessingDone(pMsgContext);

}
/******************************************************************************
* Name         :App_disableRxAndenableTx_Control
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_DisableRxAndEnableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */
    uint8 CommunicationType;
    
    CommunicationType = pMsgContext->reqData[2];
    if((1u == CommunicationType)||(3u == CommunicationType))
    {
        Com_TxStart();
        Com_RxStop();
    pMsgContext->resDataLen = 2U;
    }
    else
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
    }
    DsdInternal_ProcessingDone(pMsgContext);

}
/******************************************************************************
* Name         :App_disableRxAndTx_Control
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_DisableRxAndDisableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */
    uint8 CommunicationType;
    
    CommunicationType = pMsgContext->reqData[2];
    if((1u == CommunicationType)||(3u == CommunicationType))
    {
        Com_TxStop();
        Com_RxStop();
    pMsgContext->resDataLen = 2U;
    }
    else
    {
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
    }
    DsdInternal_ProcessingDone(pMsgContext);

}
#endif

/* 0x31 */
#if(DCM_SERVICE_31_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_StartRoutine0xB301
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0xB301(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DsdInternal_RoutineStarted();
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xB301].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_StopRoutine0xB301 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StopRoutine0xB301(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DsdInternal_RoutineStopped();
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xB301].DcmDspRoutineInfoRef.DcmDspRoutineStopOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_RequestRoutineResults0xB301 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_RequestRoutineResults0xB301(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xB301].DcmDspRoutineInfoRef.DcmDspRoutineRequestResOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_StartRoutine0xC000 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0xC000(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DsdInternal_RoutineStarted();
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xC000].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_StopRoutine0xC000 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StopRoutine0xC000(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DsdInternal_RoutineStopped();
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xC000].DcmDspRoutineInfoRef.DcmDspRoutineStopOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_RequestRoutineResults0xC000 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_RequestRoutineResults0xC000(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xC000].DcmDspRoutineInfoRef.DcmDspRoutineRequestResOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_StartRoutine0xC001 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0xC001(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DsdInternal_RoutineStarted();
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xC001].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_StopRoutine0xC001 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StopRoutine0xC001(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DsdInternal_RoutineStopped();
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xC001].DcmDspRoutineInfoRef.DcmDspRoutineStopOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_RequestRoutineResults0xC001 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_RequestRoutineResults0xC001(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xC001].DcmDspRoutineInfoRef.DcmDspRoutineRequestResOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_StartRoutine0xC002 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0xC002(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DsdInternal_RoutineStarted();
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xC002].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_StopRoutine0xC002 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StopRoutine0xC002(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DsdInternal_RoutineStopped();
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xC002].DcmDspRoutineInfoRef.DcmDspRoutineStopOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
/******************************************************************************
* Name         :App_RequestRoutineResults0xC002 
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_RequestRoutineResults0xC002(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xC002].DcmDspRoutineInfoRef.DcmDspRoutineRequestResOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);  
}
#endif

/* 0x3D */
#if(DCM_SERVICE_3D_ENABLED == STD_ON)
#endif

/* 0x85 */
#if(DCM_SERVICE_85_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_Control_DTC_Setting_Control_DTC_Setting_on
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Control_DTC_Setting_ON(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    (void)pMsgContext;
    /* Add your code here */
    DDMSetAllDTCSwitch(DTC_SWITCH_ENABLE);

    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_Control_DTC_Setting_Control_DTC_Setting_off
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Control_DTC_Setting_OFF(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    (void)pMsgContext;
    /* Add your code here */
    DDMSetAllDTCSwitch(DTC_SWITCH_DISABLE);

    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif

/* 0x86 */
#if(DCM_SERVICE_86_ENABLED == STD_ON)
#endif
