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

#ifndef _CAN_CFG_H_
#define _CAN_CFG_H_
/*******************************************************************************
*   Includes
*******************************************************************************/
#include "ComStack_Types.h"
/*******************************************************************************
*   Config Parameters
*******************************************************************************/

#define CAN_INTERRUPT                        (0x1U)
#define CAN_POLLING                          (0x0U)
#define CAN_STANDARD_ID_ONLY                 (0x1U)
#define CAN_EXTERNED_ID_ONLY                 (0x2U)
#define CAN_MIXED_ID                         (0x3U)
                                             
#define CAN_HOH_TX_MASK                      ((uint8)0x01U)
#define CAN_HOH_RX_MASK                      ((uint8)0x00U)
#define CAN_HOH_FULL_MASK                    ((uint8)0x02U)
#define CAN_HOH_BASIC_MASK                   ((uint8)0x00U)

#define CAN_TIMEOUT_DURATION                2000U
#define CAN_USED_CONTROLLER_NUM             1
#define CAN_TIMEOUT_STATE                   4

#define CAN0_CONTROLLER_ACTIVATION          STD_ON 
#define CAN0_BUSOFF_PROCESSING              CAN_INTERRUPT
#define CAN0_WAKEUP_PROCESSING              CAN_INTERRUPT
#define CAN0_RX_PROCESSING                  CAN_INTERRUPT
#define CAN0_TX_PROCESSING                  CAN_INTERRUPT

#define CAN_PHY0_ACTIVATION          CAN0_CONTROLLER_ACTIVATION
#define CAN_PHY0_RX_PROCESSING       CAN0_RX_PROCESSING
#define CAN_PHY0_TX_PROCESSING       CAN0_TX_PROCESSING
#define CAN_PHY0_BUSOFF_PROCESSING   CAN0_BUSOFF_PROCESSING
#define CAN_PHY0_WAKEUP_PROCESSING   CAN0_WAKEUP_PROCESSING

#define CAN_PHY0_TO_LOGIC               0

#define CAN_ID_TYPE_SUPPORT      CAN_STANDARD_ID_ONLY
#define CAN_USED_HOH_NUM               16
#define CAN_USED_HRH_NUM               4 
#define CAN_USED_HTH_NUM               2

#if (CAN_ID_TYPE_SUPPORT == CAN_STANDARD_ID_ONLY)
   #define CAN_ENABLE_EXTERNED_ID       STD_OFF
#else
    #define CAN_ENABLE_EXTERNED_ID      STD_ON
#endif/* #if (CAN_ID_TYPE_SUPPORT ==STANDARD_ID_ONLY) */

#define Can_EnableGlobalInterrupts()    Can_EnableGlobalInterrupt
#define Can_DisableGlobalInterrupts()   Can_DisableGlobalInterrupt


#endif/* _CAN_CFG_H_ */

