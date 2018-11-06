/*
|NOTICE
|-------------------------------------------------------------------------------
|                              
|   This software is the property of GUANGDA Technologies. 
|
|END----------------------------------------------------------------------------
|FILE INFORMATION START
|-------------------------------------------------------------------------------
|     File Name: Can.c
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
| 00.01.01    2015-08-05                             
|-------------------------------------------------------------------------------
*/

#pragma DI
#pragma EI
#pragma NOP
#pragma HALT
#pragma STOP
#if(CAN_INTERRUPT == CAN_PHY0_TX_PROCESSING)
#pragma interrupt INTC0TRX CAN_PHY0_Tx_ISR
#endif
#if(CAN_INTERRUPT == CAN_PHY0_RX_PROCESSING)
#pragma interrupt INTC0REC CAN_PHY0_Rx_ISR
#endif
#if(CAN_INTERRUPT == CAN_PHY0_BUSOFF_PROCESSING)
#pragma interrupt INTC0ERR CAN_PHY0_Error_ISR
#endif
#if(CAN_INTERRUPT == CAN_PHY0_WAKEUP_PROCESSING)
#pragma interrupt INTC0WUP CAN_PHY0_Wakeup_ISR
#endif

/*******************************************************************************
*   Includes 
*******************************************************************************/ 
#include "Can.h"
#include "CanIf_Cbk.h"

/*******************************************************************************
*   Macro 
*******************************************************************************/

/*******************************************************************************
*   Local Data Declaration 
*******************************************************************************/
STATIC uint8 CanGlobalInterruptCount;
STATIC uint8 CanControllerInterruptCount;
STATIC uint16 CanControllerOldInterrupReg;
STATIC uint8 EmptyFlagForHth[CAN_USED_HOH_NUM];
STATIC PduIdType PduIdForHth[CAN_USED_HOH_NUM];
STATIC Can_StateTransitionType Can_ModeMonitor;

/*******************************************************************************
*   Local Functions declare
*******************************************************************************/

STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_Controller_Tx_handler
(
    const uint8 Controller
);
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_Controller_Rx_handler
(
    const uint8 Controller
);
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_Controller_Error_handler
(
    const uint8 Controller
);
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_Controller_Wakeup_handler
(
    const uint8 Controller
);

STATIC FUNC(void, CAN_PRIVATE_CODE) Can_Transmit_Abort
(
    const uint8 phyController
);

/*******************************************************************************
*   Local Functions define
*******************************************************************************/

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CAN_Controller_Tx_handler
*                
* Description:   This function is used for handle the success TX confirmation 
*                             
* Inputs:        Controller
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_Controller_Tx_handler
(
    const uint8 Controller
)
{
    uint8 HthIndex;
    uint16 RegShadow;
    uint8 nloop;

    nloop = 255u;
    RegShadow = CAN_CTGPT;
    
    while( (0==(RegShadow & CAN_RHPM_MASK))&&(nloop))
    {
        //for(nloop = 0; nloop < CAN_USED_HTH_NUM; nloop++)
        {
            //RegShadow = CAN_CTGPT;
            HthIndex = (RegShadow >> 8);
            if(0 != (RegShadow & CAN_ROVF_MASK))
            {
                CAN_CRGPT = CAN_ROVF_MASK;
            }
            CAN_CMCTRL(HthIndex) = 0x0001; 
        
            if((0 == (RegShadow & CAN_RHPM_MASK))&&(TRUE != EmptyFlagForHth[HthIndex]))
            {      
                EmptyFlagForHth[HthIndex] = (uint8)TRUE;
                CanIf_TxConfirmation(PduIdForHth[HthIndex]);
            }
        }

        RegShadow = CAN_CTGPT;
        nloop--;
    }
    
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CAN_Controller_Rx_handler
*                
* Description:   This function is used for handle the success TX confirmation 
*                             
* Inputs:        Controller
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_Controller_Rx_handler
(
    const uint8 Controller 
)
{
    uint8 HrhIndex;
    uint8 temprxbuffer[CAN_DATA_DLC];
    uint8 i;
    uint32 canID;
    uint8 dlc ;
    uint16 RegShadow;
    uint8 nloop;

    nloop = 255u;
    RegShadow = CAN_CRGPT;

    while((0==(RegShadow & CAN_RHPM_MASK))&&(nloop))
    {
        //for(nloop = 0; nloop < CAN_USED_HRH_NUM; nloop++)
        {
            //RegShadow = CAN_CRGPT;
            HrhIndex = (RegShadow >> 8);
            if(0 != (RegShadow & CAN_ROVF_MASK))
            {
                CAN_CRGPT = CAN_ROVF_MASK;
            }
    
            if(0 == (RegShadow & CAN_RHPM_MASK))
            {
                CAN_CMCTRL(HrhIndex) = CAN_CLR_DN;
                
                dlc = (CAN_CMDLC(HrhIndex) & CAN_DLC_MASK);
                for(i = 0; i < CAN_DATA_DLC; i++)
                {
                    temprxbuffer[i] = CAN_CMDB(HrhIndex,i);
                }
                if(0 == (CAN_CMIDH(HrhIndex) & CAN_IDE_MASK))
                {
                    canID = (CAN_CMIDH(HrhIndex) >> 2);
                }
                else
                {
                    canID = (CAN_CMIDH(HrhIndex)& CAN_IDH_MASK);
                    canID = ((canID << 16)| CAN_CMIDL(HrhIndex));
                }
                if(0 != (CAN_CMCTRL(HrhIndex) & (CAN_MUC_MASK|CAN_CLR_DN)))
                {
                    //CAN_CMCTRL(HthIndex) = CAN_CLR_DN;        
                }
                else
                {
                    CanIf_RxIndication(HrhIndex, canID, dlc, temprxbuffer);
                }
                
                /*Check MBON*/
            }
        }  
        RegShadow = CAN_CRGPT;
        nloop--;
    }
}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CAN_Controller_Error_handler
*                
* Description:   This function is used for handle the success TX confirmation 
*                             
* Inputs:        Controller
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_Controller_Error_handler(const uint8 Controller)
{
    if(0 != (CAN_CINTS & CAN_CLR_ERINTS2))
    {
        if(0 != (CAN_CINFO & CAN_BOFF_MASK))
        {
            /*BusOff*/
            Can_Transmit_Abort(Controller);    
            (void)Can_SetControllerMode(Controller, CAN_T_STOP);
            CanIf_ControllerBusOff(Controller);

            /**/Can_InitController(0, NULL_PTR);
            (void)Can_SetControllerMode(Controller, CAN_T_START);
        }
        CAN_CINTS = CAN_CLR_ERINTS2;
    }
    if(0 != (CAN_CINTS & CAN_CLR_ERINTS3))
    {
        CAN_CINTS = CAN_CLR_ERINTS3;
    }
    if(0 != (CAN_CINTS & CAN_CLR_ERINTS4))
    {
        CAN_CINTS = CAN_CLR_ERINTS4;
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CAN_Controller_Wakeup_handler
*                
* Description:   This function is used for handle the success TX confirmation 
*                             
* Inputs:        Controller
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_Controller_Wakeup_handler(const uint8 Controller)
{
    if(0 != (CAN_CINTS & CAN_CLR_WUINTS5))
    {
        CAN_CINTS = CAN_CLR_WUINTS5;
        (void)Can_SetControllerMode(Controller, CAN_T_WAKEUP);
        CanIf_ControllerWakeUp(Controller);
        /**/(void)Can_SetControllerMode(Controller, CAN_T_START);
    }
}
 


/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_Controller_Transmit_Abort
*                
* Description:   This function is used for abort all the message in the 
*                transmission buffer which is belong to one controller
*                             
* Inputs:        Controller
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CAN_PRIVATE_CODE) Can_Transmit_Abort
(
    const uint8 phyController
)
{
    uint8 nloop;
    uint8 HthIndex;

    for(nloop = 0; nloop < CAN_USED_HTH_NUM; nloop++)
    {
        HthIndex = nloop + CAN_USED_HRH_NUM;
        
        CAN_CMCTRL(HthIndex) = CAN_CLR_TRQ;
    }
}

/*******************************************************************************
*  PUBLIC Functions define 
*******************************************************************************/

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_Init
*                
* Description:   This function initializes the module. 
*                             
* Inputs:        None
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE) Can_Init(void)
{
    Can_HwHandleType hohIndex;

    for(hohIndex = 0; hohIndex < CAN_USED_HOH_NUM; hohIndex++)
    {
        EmptyFlagForHth[hohIndex] = (uint8)TRUE;
        PduIdForHth[hohIndex] = CAN_EMPTY_PDUID;
    }
    
    Can_ModeMonitor = CAN_T_NONE;
    CanGlobalInterruptCount = 0;
    CanControllerInterruptCount = 0;
    CanControllerOldInterrupReg = 0;

    Can_InitController(0, NULL_PTR);      
} 

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_InitController
*                
* Description:   Used to initialize the bit timing related settings 
                 of a CAN controller.
*                
* Inputs:        Controller:  CAN controller to be initialized 
                 Config
*                   
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/ 
FUNC(void, CAN_PUBLIC_CODE) Can_InitController
( 
    uint8 Controller, 
    P2CONST(Can_ControllerBaudrateConfigType, AUTOMATIC, CAN_CONFIG_CONST)Config
)
{
    uint16 MBIndex; 
    uint8 Dlccount;
    
    CAN_CCTRL = CAN_CLR_OPMODE;
    #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
    CAN_LOOP_BEGIN(INIT_ENTER_TIMEOUT);
    #endif
    while((0 != (CAN_CCTRL & CAN_CLR_OPMODE))
          && (CAN_OK != CAN_LOOP_TIMEOUT(INIT_ENTER_TIMEOUT)))
    {
        ;
    }
    #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
    CAN_LOOP_END(INIT_ENTER_TIMEOUT);
    #endif
    if(0 == (CAN_CCTRL & CAN_CLR_OPMODE))
    {
        (void)Config;
        CAN_PCKSEL |= CAN_MCKE_MASK;    
        CAN_CGMCS = CanRegInit[0].Can_CGMCS;
        CAN_CGMCTRL = CAN_GOM_MASK;
        CAN_CBRP = CanRegInit[0].Can_CBRP;
        CAN_CBTR = CanRegInit[0].Can_CBTR;
        CAN_CIE = CanRegInit[0].Can_CIE;
        CAN_CMASK1L = CanRegInit[0].Can_CMASK1L;
        CAN_CMASK1H = CanRegInit[0].Can_CMASK1H;
        CAN_CMASK2L = CanRegInit[0].Can_CMASK2L;
        CAN_CMASK2H = CanRegInit[0].Can_CMASK2H;
        CAN_CMASK3L = CanRegInit[0].Can_CMASK3L;
        CAN_CMASK3H = CanRegInit[0].Can_CMASK3H;
        CAN_CMASK4L = CanRegInit[0].Can_CMASK4L;
        CAN_CMASK4H = CanRegInit[0].Can_CMASK4H;

        for(MBIndex = 0; MBIndex < CAN_TOTAL_MB_NUM; MBIndex++)
        {
            #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
            CAN_LOOP_BEGIN(INIT_ENTER_TIMEOUT);
            #endif
            while(((CAN_CMCTRL(MBIndex) & 0x01) == 0x01)
                && (CAN_OK != CAN_LOOP_TIMEOUT(INIT_ENTER_TIMEOUT)))
            {
                CAN_CMCTRL(MBIndex) = 0x0001; 
            }
            #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
            CAN_LOOP_END(INIT_ENTER_TIMEOUT);
            #endif
            if(MBIndex < CAN_USED_HOH_NUM)
            {
                if(0 != (CanHardwareObjectConfig[MBIndex].hohType & CAN_HOH_TX_MASK))
                {
                    /*Tx MB*/
                    CAN_CMCONF(MBIndex) = CAN_MA0_MASK;
                    if(STANDARD_ID == CanHardwareObjectConfig[MBIndex].idtype)
                    {
                        CAN_CMIDH(MBIndex) = (CanHardwareObjectConfig[MBIndex].id << 2);
                        CAN_CMIDL(MBIndex) = 0x00;
                            
                    }
                    else
                    {
                            CAN_CMIDH(MBIndex) = (CAN_IDE_MASK|(CanHardwareObjectConfig[MBIndex].id >> 16));
                            CAN_CMIDL(MBIndex) = (uint16)CanHardwareObjectConfig[MBIndex].id;    
                    }
                    CAN_CMDLC(MBIndex) = 0x80;
                    for(Dlccount = 0; Dlccount < 8; Dlccount++)
                    {
                        CAN_CMDB(MBIndex,Dlccount) = 0x00;
                    }
                }
                else
                {
                    /*Rx MB*/
                    CAN_CMCONF(MBIndex) = (CAN_MA0_MASK|CAN_OWS_MASK|CanHardwareObjectConfig[MBIndex].mask);
                    if(STANDARD_ID == CanHardwareObjectConfig[MBIndex].idtype)
                    {
                        CAN_CMIDH(MBIndex) = (CanHardwareObjectConfig[MBIndex].id << 2);
                        CAN_CMIDL(MBIndex) = 0x00;
                            
                    }
                    else
                    {
                        CAN_CMIDH(MBIndex) = (CAN_IDE_MASK|(CanHardwareObjectConfig[MBIndex].id >> 16));
                        CAN_CMIDL(MBIndex) = (uint16)CanHardwareObjectConfig[MBIndex].id;    
                    }
                }
                CAN_CMCTRL(MBIndex) = CAN_IE_MASK;
                CAN_CMCTRL(MBIndex) = CAN_SET_RDY;
            }
            else
            {
                CAN_CMCONF(MBIndex) = 0x00;
            }
        }
        CAN_CCTRL = (CAN_SET_CCERC|CAN_CLR_OPMODE|CAN_CLR_PSMODE
                     |CAN_CLR_VALID|CAN_CLR_AL);
    }
    else
    {
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_SetControllerMode
*                
* Description:   This function performs software triggered state 
*                transitions of the CAN controller State machine.  
*                             
* Inputs:        Controller:CAN controller for which the status 
*                           shall be changed 
*                Transition:Transition value to request new 
*                           CAN controller state
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Can_ReturnType, CAN_PUBLIC_CODE) Can_SetControllerMode
(
    uint8 Controller,
    Can_StateTransitionType Transition
)
{
    Can_ReturnType ret = CAN_OK;
    uint8 hohIndex;

    switch(Transition)    
    {
        case CAN_T_START:
        {
            
            for(hohIndex = 0; hohIndex < CAN_USED_HOH_NUM; hohIndex++)
            {
                EmptyFlagForHth[hohIndex] = (uint8)TRUE;
                PduIdForHth[hohIndex] = CAN_EMPTY_PDUID;
            }
            /*Clear PSMode*/
            CAN_CCTRL = CAN_CLR_PSMODE1;
            CAN_CCTRL = CAN_CLR_PSMODE0;
            /*Set OPMode Normal*/
            CAN_CCTRL = CAN_SET_NORMAL;
            #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
            CAN_LOOP_BEGIN(INIT_ENTER_TIMEOUT);
            #endif
            while((CAN_NORMAL_MASK != (CAN_CCTRL & CAN_CLR_OPMODE))
                  && (CAN_OK != CAN_LOOP_TIMEOUT(INIT_LEAVE_TIMEOUT))) 
            {
                ;
            }
            #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
            CAN_LOOP_END(INIT_ENTER_TIMEOUT);
            #endif
            if(CAN_NORMAL_MASK == (CAN_CCTRL & CAN_CLR_OPMODE))
            {
                CanIf_ControllerModeIndication(Controller,CANIF_CS_STARTED);
            }
            else
            {
                Can_ModeMonitor = CAN_T_START;
            }
        } 
        break;
  
        case CAN_T_STOP:
        { 
            Can_Transmit_Abort(Controller);
            /*Init Mode*/
            CAN_CCTRL = CAN_CLR_OPMODE;
            #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
            CAN_LOOP_BEGIN(INIT_ENTER_TIMEOUT);
            #endif
            while((0 != (CAN_CCTRL & CAN_CLR_OPMODE))
                && (CAN_OK != CAN_LOOP_TIMEOUT(INIT_ENTER_TIMEOUT)))
            {
                ;
            }
            #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
            CAN_LOOP_END(INIT_ENTER_TIMEOUT);
            #endif
            if(0 == (CAN_CCTRL & CAN_CLR_OPMODE))
            {
                CanIf_ControllerModeIndication(Controller,CANIF_CS_STOPPED);
            }
            else
            {
                Can_ModeMonitor = CAN_T_STOP;
            }
        } 
        break;
  
        case CAN_T_SLEEP:
        {   
            #if(CAN0_WAKEUP_PROCESSING == CAN_INTERRUPT)
            CAN_CIE = CAN0_WAKEUP_INT_CFG;
            #endif
            /*Set OPMode Normal*/
            CAN_CCTRL = CAN_SET_NORMAL;
            #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
            CAN_LOOP_BEGIN(INIT_ENTER_TIMEOUT);
            #endif
            while((CAN_NORMAL_MASK != (CAN_CCTRL & CAN_CLR_OPMODE))
                && (CAN_OK != CAN_LOOP_TIMEOUT(INIT_ENTER_TIMEOUT)))
            {
                ;
            }
            #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
            CAN_LOOP_END(INIT_ENTER_TIMEOUT);
            #endif
            /*Set PSMode Sleep*/
            CAN_CCTRL = CAN_SET_SLEEP;
            #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
            CAN_LOOP_BEGIN(INIT_ENTER_TIMEOUT);
            #endif
            while((CAN_SLEEP_MASK != (CAN_CCTRL & CAN_CLR_PSMODE))
                && (CAN_OK != CAN_LOOP_TIMEOUT(INIT_ENTER_TIMEOUT)))
            {
                ;
            }
            #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
            CAN_LOOP_END(INIT_ENTER_TIMEOUT);
            #endif
            if(CAN_SLEEP_MASK == (CAN_CCTRL & CAN_CLR_PSMODE))
            {           
                CanIf_ControllerModeIndication(Controller,CANIF_CS_SLEEP);
            }
            else
            {
                Can_ModeMonitor = CAN_T_SLEEP;
            }
        } 
        break;
  
        case CAN_T_WAKEUP:
        {            
            #if(CAN0_WAKEUP_PROCESSING == CAN_INTERRUPT)
            CAN_CIE = CAN_CLR_CIE5;
            #endif
            /*Init Mode*/
            CAN_CCTRL = CAN_CLR_OPMODE;
            #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
            CAN_LOOP_BEGIN(INIT_ENTER_TIMEOUT);
            #endif
            while((0 != (CAN_CCTRL & CAN_CLR_OPMODE))
                && (CAN_OK != CAN_LOOP_TIMEOUT(INIT_ENTER_TIMEOUT)))
            {
                ;
            }
            #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
            CAN_LOOP_END(INIT_ENTER_TIMEOUT);
            #endif
            if(0 == (CAN_CCTRL & CAN_CLR_OPMODE))
            {
                CanIf_ControllerModeIndication(Controller,CANIF_CS_STOPPED);
            }
            else
            {
                Can_ModeMonitor = CAN_T_WAKEUP;
            }
        } 
        break;         
        
        default:
        ret = CAN_NOT_OK;
        break;
    }
    return ret;

}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_DisableControllerInterrupts
*                
* Description:   This function used to disable all can controller interrupts 
*                             
* Inputs:        Controller
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE) Can_DisableControllerInterrupts
( 
    uint8 Controller 
) 
{
    if(0 == (CanControllerInterruptCount))
    {
        CanControllerOldInterrupReg = CAN_CIE;
        CAN_CIE = 0x003f;
    }
    CanControllerInterruptCount++;
    if(CanControllerInterruptCount > CAN_INT_NEST_COUNT)
    {
        CanControllerInterruptCount = CAN_INT_NEST_COUNT;
    }

}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_EnableControllerInterrupts
*                
* Description:   This function enables all allowed interrupts. 
*                             
* Inputs:        Controller
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE)Can_EnableControllerInterrupts
( 
    uint8 Controller 
) 
{
    if(CanControllerInterruptCount > 0)
    {
        (CanControllerInterruptCount)--;
    }
    if(0 == (CanControllerInterruptCount))
    {
        CAN_CIE = ((CanControllerOldInterrupReg << 8) & 0x3f00);
    }

}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_DisableGlobalInterrupt
*                
* Description:   This function disables all maskable interrupts 
*                             
* Inputs:        None
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE)Can_DisableGlobalInterrupt(void) 
{
    if(CAN_DATA_INIT_NULL == CanGlobalInterruptCount)
    {
        DI();
    } 
    
    CanGlobalInterruptCount++;
    if(CanGlobalInterruptCount > CAN_INT_NEST_COUNT)
    {
        CanGlobalInterruptCount = CAN_INT_NEST_COUNT;
    }

}
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_EnableGlobalInterrupt
*                
* Description:   This function enables all maskable interrupts 
*                             
* Inputs:        None
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE) Can_EnableGlobalInterrupt(void) 
{
    if(CanGlobalInterruptCount > CAN_DATA_INIT_NULL)
    {
        CanGlobalInterruptCount--;
    }
    
    if(CAN_DATA_INIT_NULL == CanGlobalInterruptCount)
    {
        EI();
    }  
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_Write
*                
* Description:   This function used to send 1 can frame
*                             
* Inputs:        PduInfo:  Pointer to SDU user memory, DLC and Identifier.
*                Hth:  information which HW-transmit handle shall be used 
*                      for transmit. Implicitly this is also the information 
*                      about the controller to use because the Hth numbers 
*                      are unique inside one hardware unit.
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Can_ReturnType, CAN_PUBLIC_CODE) Can_Write
(
    Can_HwHandleType Hth,
    P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfo
)
{
    Can_ReturnType Ret;
    uint8 hthmatchflag = CAN_NOT_MATCH;
    uint8 Dlccount;
    
    CAN_ENTER_CRITICAL_SECTION();
    if(TRUE == EmptyFlagForHth[Hth])
    {
        hthmatchflag = CAN_MATCH;
    }
    if(CAN_MATCH == hthmatchflag)
    {
        #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
        CAN_LOOP_BEGIN(INIT_ENTER_TIMEOUT);
        #endif
        while(((CAN_CMCTRL(Hth) & 0x01) == 0x01)
            && (CAN_OK != CAN_LOOP_TIMEOUT(INIT_ENTER_TIMEOUT)))
        {
            CAN_CMCTRL(Hth) = 0x0001; 
        }
        #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
        CAN_LOOP_END(INIT_ENTER_TIMEOUT);
        #endif
        if((CAN_CMCTRL(Hth) & 0x01)==0)
        {
            for(Dlccount = 0; Dlccount < PduInfo->length; Dlccount++)
            {
                CAN_CMDB(Hth,Dlccount) = PduInfo->sdu[Dlccount];
            }            
            CAN_CMDLC(Hth) = PduInfo->length;
            if(STANDARD_ID == CanHardwareObjectConfig[Hth].idtype)
            {
                CAN_CMIDH(Hth) = (PduInfo->id << 2);
                CAN_CMIDL(Hth) = 0x00;
                    
            }
            else
            {
                CAN_CMIDH(Hth) = (CAN_IDE_MASK|(PduInfo->id >> 16));
                CAN_CMIDL(Hth) = (uint16)PduInfo->id; 
            }
            CAN_CMCONF(Hth) &= 0xBF;
                
            CAN_CMCTRL(Hth) = 0x0100; 
            CAN_CMCTRL(Hth) = 0x0200; 
                
            PduIdForHth[Hth] = PduInfo->swPduHandle;
            EmptyFlagForHth[Hth] = FALSE;        
            Ret = CAN_OK;            
        } 
    }               
    else
    {   
        Ret = CAN_BUSY;
    }     
    CAN_LEAVE_CRITICAL_SECTION(); 
    return(Ret);
}

/*******************************************************************************
*  Scheduled functions
*******************************************************************************/

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_MainFunction_Write
*                
* Description:   This function performs the polling of TX confirmation 
*                when CAN_TX_PROCESSING is set to CAN_POLLING. 
*                             
* Inputs:        None
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write(void)
{
    #if (CAN0_TX_PROCESSING == CAN_POLLING)
    if(0 != (CAN_CINTS & CAN_CLR_TXINTS0))
    {
        CAN_Controller_Tx_handler(0);
        CAN_CINTS = CAN_CLR_TXINTS0;
    }
    #endif
} 

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_MainFunction_Read
*                
* Description:   This function performs the polling of RX indications 
*                when CAN_RX_PROCESSING is set to CAN_POLLING. 
*                             
* Inputs:        None
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read(void)
{
    #if (CAN0_RX_PROCESSING == CAN_POLLING)
    if(0 != (CAN_CINTS & CAN_CLR_RXINTS1))
    {
        CAN_Controller_Rx_handler(0);
        CAN_CINTS = CAN_CLR_RXINTS1;
    }
    #endif
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_MainFunction_BusOff
*                
* Description:   This function performs the polling of bus-off events that 
*                are configured statically as 'to be polled'.
*                             
* Inputs:        None
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_BusOff(void)   
{
    #if (CAN0_BUSOFF_PROCESSING == CAN_POLLING)
    CAN_Controller_Error_handler(0);
    #endif
} 

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_MainFunction_Wakeup
*                
* Description:   This function performs the polling of wake-up events that 
*                are configured statically as 'to be polled'.
*                             
* Inputs:        None
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Wakeup(void)
{
    #if (CAN0_WAKEUP_PROCESSING == CAN_POLLING)
    CAN_Controller_Wakeup_handler(0);
    #endif
} 

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_MainFunction_Mode
*                
* Description:   This function performs the polling of CAN controller 
*                mode transitions. 
*                             
* Inputs:        None
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Mode(void)
{
    uint16 RegShadow;
    
    RegShadow = CAN_CCTRL;
    switch(Can_ModeMonitor)
    {
        case CAN_T_START:
        {
            if(CAN_NORMAL_MASK == (RegShadow & CAN_CLR_OPMODE))
            {
                CanIf_ControllerModeIndication(0, CANIF_CS_STARTED); 
                Can_ModeMonitor = CAN_T_NONE; 
            }
        }
        break;
    
        case CAN_T_STOP:
        {                     
            if(CAN_STOP_MASK == (RegShadow & CAN_CLR_PSMODE))
            {
                CanIf_ControllerModeIndication(0, CANIF_CS_STOPPED); 
                Can_ModeMonitor = CAN_T_NONE; 
            }
        }
        break;
    
        case CAN_T_SLEEP:
        {
            if(CAN_SLEEP_MASK == (RegShadow & CAN_CLR_PSMODE))
            {
                CanIf_ControllerModeIndication(0, CANIF_CS_SLEEP); 
                Can_ModeMonitor = CAN_T_NONE; 
            }
        }
        break;
    
        case CAN_T_WAKEUP:
        {
            if(CAN_STOP_MASK == (RegShadow & CAN_CLR_PSMODE))
            {
                CanIf_ControllerModeIndication(0, CANIF_CS_STOPPED); 
                Can_ModeMonitor = CAN_T_NONE; 
            }
        }
        break;
        default:
        break;
        
    }
} 

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CAN_PHYx_Tx_ISR \ CAN_PHYx_Rx_ISR
*                \CAN_PHYx_Busoff_ISR\CAN_PHYx_Wakeup_ISR
*                
* Description:   These functions are ISR for can event 
*                             
* Inputs:        None
*             
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if (STD_ON == CAN_PHY0_ACTIVATION)
    /* Tx_Interrupt */
    #if(CAN_INTERRUPT == CAN_PHY0_TX_PROCESSING)
    __interrupt void CAN_PHY0_Tx_ISR(void)
    {
        CAN_Controller_Tx_handler(CAN_PHY0_TO_LOGIC);
    }
    #endif
    
    /* Rx_Interrupt */
    #if(CAN_INTERRUPT == CAN_PHY0_RX_PROCESSING)
    __interrupt void CAN_PHY0_Rx_ISR(void)
    {
        CAN_Controller_Rx_handler(CAN_PHY0_TO_LOGIC);
    }
    #endif
    
    /* Error_Interrupt */
    #if(CAN_INTERRUPT == CAN_PHY0_BUSOFF_PROCESSING)
    __interrupt void CAN_PHY0_Error_ISR(void)
    {
        CAN_Controller_Error_handler(CAN_PHY0_TO_LOGIC);
    }
    #endif

     /* Wakeup_Interrupt */
    #if(CAN_INTERRUPT == CAN_PHY0_WAKEUP_PROCESSING)
    __interrupt void CAN_PHY0_Wakeup_ISR(void)
    {
        CAN_Controller_Wakeup_handler(CAN_PHY0_TO_LOGIC);
    }
    #endif

#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Service Name: Time out check
*                
* Description:   This service is used for testing whether timeout exists or not.
*                
* Inputs:        None
*                   
* Outputs:       None
* 
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if(STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)
uint16 CanLoopTimerCount = 0;
uint16 BeginTimerValue[CAN_TIMEOUT_STATE] =
{
    0,
    0,
    0,
    0
};
uint16 TimerOutValue[CAN_TIMEOUT_STATE] =
{
    CAN_TIMEOUT_DURATION,
    CAN_TIMEOUT_DURATION,
    CAN_TIMEOUT_DURATION,
    CAN_TIMEOUT_DURATION
};

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: ApplTimerBegin
*
* Description:   Used for timeout start.
*
* Inputs:        uint8 LoopReason
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_APPL_CODE) ApplTimerBegin
(
    uint8 LoopReason
)
{
    CanLoopTimerCount = 0; /* start timercount */
    BeginTimerValue[LoopReason] = CanLoopTimerCount;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: ApplTimerOutCheck
*
* Description:   Used for timeout check.
*
* Inputs:        uint8 LoopReason
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Can_ReturnType, CAN_APPL_CODE) ApplTimerOutCheck
(
    uint8 LoopReason
)
{
    Can_ReturnType ret = CAN_NOT_OK;

    CanLoopTimerCount++;

    if((CanLoopTimerCount - BeginTimerValue[LoopReason])
        > TimerOutValue[LoopReason])
    {
        ret = CAN_OK;
    }
    return ret;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: ApplTimerEnd
*
* Description:   Used for timeout.
*
* Inputs:        uint8 LoopReason
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_APPL_CODE) ApplTimerEnd
(
    uint8 LoopReason
)
{
    (void)LoopReason;

    CanLoopTimerCount = 0; /* release timercount */
}
#endif/* #if(STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) */


