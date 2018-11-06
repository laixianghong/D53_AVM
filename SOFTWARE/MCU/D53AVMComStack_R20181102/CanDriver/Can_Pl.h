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

#ifndef _CAN_PL_H_
#define _CAN_PL_H_

/*******************************************************************************
*   Includes 
*******************************************************************************/
#include "ComStack_Types.h"
#include "Can_Cfg.h"

/*******************************************************************************
*   Macro  
*******************************************************************************/
#define CAN_HARDWARE_TIMEOUT_CHECK      STD_ON
#define CAN_ENTER_CRITICAL_SECTION()    Can_DisableGlobalInterrupts()
#define CAN_LEAVE_CRITICAL_SECTION()    Can_EnableGlobalInterrupts() 
#define CAN_NOT_MATCH                   ((uint8)0x0U)
#define CAN_MATCH                       ((uint8)0x1U)
#define CAN_CONTROLLER_NOT_HOH          (0xffU)
#define CAN_TOTAL_MB_NUM                ((Can_HwHandleType)0x10U)          
#define CAN_DATA_INIT_NULL              ((uint8)0x00U)
/*******************************************************************************
*   Can Controller Base Address
*******************************************************************************/
#define CAN_CONTROLLER0_BASE_ADDRESS    (0x000F05C0UL)

/*******************************************************************************
*   Typedef 
*******************************************************************************/
typedef struct
{
    uint8      Can_CGMCS; 
    uint8      Can_CBRP;
    uint16     Can_CBTR;
    uint16     Can_CIE;  
    uint16     Can_CMASK1L;
    uint16     Can_CMASK1H; 
    uint16     Can_CMASK2L;
    uint16     Can_CMASK2H;
    uint16     Can_CMASK3L;
    uint16     Can_CMASK3H;
    uint16     Can_CMASK4L;
    uint16     Can_CMASK4H;   

}Can_RegInitType;

/*******************************************************************************
*  Register definitions
*******************************************************************************/
#define CAN_PCKSEL     (*((__far volatile uint8 *)0x000F00F2UL))
#define CAN_MK2H       (*((__far volatile uint8 *)0x000FFFD5UL))
#define CAN_MK2L       (*((__far volatile uint8 *)0x000FFFD4UL))

#define CAN_CGMCTRL    (*((__far volatile uint16 *)0x000F05C0UL))
#define CAN_CGMABT     (*((__far volatile uint16 *)0x000F05C6UL))
#define CAN_CGMABTD    (*((__far volatile uint8 *)0x000F05C8UL))
#define CAN_CGMCS      (*((__far volatile uint8 *)0x000F05CEUL))
#define CAN_CMASK1L    (*((__far volatile uint16 *)0x000F05D0UL))
#define CAN_CMASK1H    (*((__far volatile uint16 *)0x000F05D2UL))
#define CAN_CMASK2L    (*((__far volatile uint16 *)0x000F05D4UL))
#define CAN_CMASK2H    (*((__far volatile uint16 *)0x000F05D6UL))
#define CAN_CMASK3L    (*((__far volatile uint16 *)0x000F05D8UL))
#define CAN_CMASK3H    (*((__far volatile uint16 *)0x000F05DAUL))
#define CAN_CMASK4L    (*((__far volatile uint16 *)0x000F05DCUL))
#define CAN_CMASK4H    (*((__far volatile uint16 *)0x000F05DEUL))
#define CAN_CCTRL      (*((__far volatile uint16 *)0x000F05E0UL))
#define CAN_CLEC       (*((__far volatile uint8 *)0x000F05E2UL))
#define CAN_CINFO      (*((__far volatile uint8 *)0x000F05E3UL))
#define CAN_CERC       (*((__far volatile uint16 *)0x000F05E4UL))
#define CAN_CIE        (*((__far volatile uint16 *)0x000F05E6UL))
#define CAN_CINTS      (*((__far volatile uint16 *)0x000F05E8UL))
#define CAN_CBRP       (*((__far volatile uint8 *)0x000F05EAUL))
#define CAN_CBTR       (*((__far volatile uint16 *)0x000F05ECUL))
#define CAN_CLIPT      (*((__far volatile uint8 *)0x000F05EEUL))
#define CAN_CRGPT      (*((__far volatile uint16 *)0x000F05F0UL))
#define CAN_CLOPT      (*((__far volatile uint8 *)0x000F05F2UL))
#define CAN_CTGPT      (*((__far volatile uint16 *)0x000F05F4UL))
#define CAN_CTS        (*((__far volatile uint16 *)0x000F05F6UL))
 
#define CAN_CMDB(MBNum,DATA)    (*((__far volatile uint8 *)(0x000F0600UL+DATA+(0x10*MBNum))))
#define CAN_CMDLC(MBNum)    (*((__far volatile uint8 *)(0x000F0608UL+(0x10*MBNum))))
#define CAN_CMCONF(MBNum)   (*((__far volatile uint8 *)(0x000F0609UL+(0x10*MBNum))))
#define CAN_CMIDL(MBNum)    (*((__far volatile uint16 *)(0x000F060AUL+(0x10*MBNum))))
#define CAN_CMIDH(MBNum)    (*((__far volatile uint16 *)(0x000F060CUL+(0x10*MBNum))))
#define CAN_CMCTRL(MBNum)   (*((__far volatile uint16 *)(0x000F060EUL+(0x10*MBNum))))


/*******************************************************************************
*  Register Mask Value define
*******************************************************************************/
#define CAN_DLC_MASK            ((uint8)0x0fU)
#define CAN_MCKE_MASK           0x12//((uint8)0x10U)  
#define CAN_GOM_MASK            ((uint16)0x0100U)                                                    
#define CAN_SET_CIE0            ((uint16)0x0100U)                                                   
#define CAN_SET_CIE1            ((uint16)0x0200U)                                                   
#define CAN_SET_CIE2            ((uint16)0x0400U)                                                   
#define CAN_SET_CIE3            ((uint16)0x0800U)                                                   
#define CAN_SET_CIE4            ((uint16)0x1000U)                                                   
#define CAN_SET_CIE5            ((uint16)0x2000U)                                                 
#define CAN_CLR_CIE5            ((uint16)0x0020U)
#define CAN_MA0_MASK            ((uint8)0x01U)
#define CAN_MS0_MASK            ((uint8)0x08U)
#define CAN_MS1_MASK            ((uint8)0x10U)
#define CAN_MS2_MASK            ((uint8)0x18U)
#define CAN_MS3_MASK            ((uint8)0x20U)
#define CAN_MS4_MASK            ((uint8)0x28U)
#define CAN_RTR_MASK            ((uint8)0x40U)
#define CAN_OWS_MASK            ((uint8)0x80U)
#define CAN_IDE_MASK            ((uint16)0x8000U)
#define CAN_IDH_MASK            ((uint16)0x1fffU)
#define CAN_IE_MASK             ((uint16)0x0800U)
#define CAN_SET_RDY             ((uint16)0x0100U)
#define CAN_CLR_RDY             ((uint16)0x0001U)
#define CAN_CLR_TRQ             ((uint16)0x0002U)
#define CAN_CLR_DN              ((uint16)0x0004U)
#define CAN_MUC_MASK            ((uint16)0x2000U)
#define CAN_CCERC_MASK          ((uint16)0x8000U)
#define CAN_AL_MASK             ((uint16)0x4000U)
#define CAN_CLR_TXINTS0         ((uint16)0x0001U)
#define CAN_CLR_RXINTS1         ((uint16)0x0002U)
#define CAN_CLR_ERINTS2         ((uint16)0x0004U)
#define CAN_CLR_ERINTS3         ((uint16)0x0008U)
#define CAN_CLR_ERINTS4         ((uint16)0x0010U)
#define CAN_CLR_WUINTS5         ((uint16)0x0020U)
#define CAN_SET_CCERC           ((uint16)0x8000U)
#define CAN_CLR_AL              ((uint16)0x0040U)
#define CAN_CLR_VALID           ((uint16)0x0020U)
#define CAN_CLR_PSMODE          ((uint16)0x0018U)
#define CAN_CLR_PSMODE0         ((uint16)0x0008U)
#define CAN_CLR_PSMODE1         ((uint16)0x0010U)
#define CAN_CLR_OPMODE          ((uint16)0x0007U)
#define CAN_SET_NORMAL          ((uint16)0x0106U)
#define CAN_NORMAL_MASK         ((uint16)0x0001U)
#define CAN_SET_SLEEP           ((uint16)0x0810U)
#define CAN_SET_STOP            ((uint16)0x1800U)
#define CAN_SLEEP_MASK          ((uint16)0x0008U)
#define CAN_STOP_MASK           ((uint16)0x0018U)
#define CAN_RHPM_MASK           ((uint16)0x0002U)
#define CAN_ROVF_MASK           ((uint16)0x0001U)
#define CAN_BOFF_MASK           ((uint8)0x10U)
#define CAN_TSTAT_MASK          ((uint16)0x0100U)

/*******************************************************************************
*  Controller related  
*******************************************************************************/
#if (CAN_USED_CONTROLLER_NUM >= 1)     
    #if (CAN0_RX_PROCESSING == CAN_INTERRUPT)
        #define CAN0_RX_INT_CFG  CAN_SET_CIE0
    #elif (CAN0_RX_PROCESSING == CAN_POLLING)
        #define CAN0_RX_INT_CFG  ((uint8)0x0U)
    #else
        #error "!!!ERROR FOR CAN0_RX_CFG!!!"
    #endif
  
    #if (CAN0_TX_PROCESSING == CAN_INTERRUPT)
        #define CAN0_TX_INT_CFG  CAN_SET_CIE1
    #elif (CAN0_TX_PROCESSING == CAN_POLLING)
        #define CAN0_TX_INT_CFG  ((uint8)0x0U)
    #else
        #error "!!!ERROR FOR CAN0_TX_CFG!!!"
    #endif

    #if (CAN0_BUSOFF_PROCESSING == CAN_INTERRUPT)
        #define CAN0_BUSOFF_INT_CFG  CAN_SET_CIE2
    #elif (CAN0_BUSOFF_PROCESSING == CAN_POLLING)
        #define CAN0_BUSOFF_INT_CFG  ((uint8)0x0U)
    #else
        #error "!!!ERROR FOR CAN0_BUSOFF_CFG!!!"
    #endif

    #if (CAN0_WAKEUP_PROCESSING == CAN_INTERRUPT)
        #define CAN0_WAKEUP_INT_CFG  CAN_SET_CIE5
    #elif (CAN0_WAKEUP_PROCESSING == CAN_POLLING)
        #define CAN0_WAKEUP_INT_CFG  ((uint8)0x0U)
    #else
         #error "!!!ERROR FOR CAN0_BUSOFF_CFG!!!"
    #endif
  
    #if (CAN0_BUSOFF_AUTOREC == STD_ON)
        #define CAN0_BUSOFF_RECCFG  ((uint8)0x0U)
    #elif (CAN0_BUSOFF_AUTOREC == STD_OFF)
        #define CAN0_BUSOFF_RECCFG  CAN_BOFF_REC_MASK
    #else
        #error "!!!ERROR FOR CAN0_CLKSRC_CFG!!!"
    #endif
 
#endif/* #if (CAN_USED_CONTROLLER_NUM>=1) */

/*******************************************************************************
*   Loop timer define 
*******************************************************************************/
#if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
    #define CAN_LOOP_BEGIN(i)      ApplTimerBegin(i)
    #define CAN_LOOP_TIMEOUT(i)    ApplTimerOutCheck(i)
    #define CAN_LOOP_END(i)        ApplTimerEnd(i) 
#else
    #define CAN_LOOP_TIMEOUT(i)    CAN_NOT_OK 
#endif/* #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) */
        
#define INIT_ENTER_TIMEOUT        (0x0U)
#define INIT_LEAVE_TIMEOUT        (0x1U)
#define SLEEP_ENTER_TIMEOUT       (0x2U)
#define SLEEP_LEAVE_TIMEOUT       (0x3U)
  
#endif/* _CAN_PL_H_*/
