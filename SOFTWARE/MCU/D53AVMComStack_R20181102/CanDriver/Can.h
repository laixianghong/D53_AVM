/*
|NOTICE
|-------------------------------------------------------------------------------
|                              
|   This software is the property of GUANGDA Technologies. 
|
|END----------------------------------------------------------------------------
|FILE INFORMATION START
|-------------------------------------------------------------------------------
|     File Name: Can.h
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

#ifndef _CAN_H_
#define _CAN_H_

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Can_Type.h"
#include "Can_Pl.h"

/*******************************************************************************
*   Macro 
*******************************************************************************/
#define CAN_EMPTY_PDUID            ((PduIdType)(~(0x0U)))
#define CAN_NO_INT_MB              ((Can_HwHandleType)(~(0x0U)))
#define CAN_DATA_DLC               ((uint8)0x08U)
#define CAN_INT_NEST_COUNT         ((uint8)250U)
#define CAN_STD_EXT_BOUNDS         (0x800UL)

/*******************************************************************************
*   CanController 
*******************************************************************************/
/*CAN316_Conf    :This parameter rovides the controller ID which is unique in a 
                  given CAN Driver. The value for this parameter starts with 0 
                  and continue without any gaps*/
#if (CAN_USED_CONTROLLER_NUM >= 1)
    #define CAN_DRIVER_CONTROLLER_ID_0  (0U)
#endif


/*******************************************************************************
*   Global Data Declaration 
*******************************************************************************/

extern CONST(uint8, CAN_CONFIG_CONST) CanControllerIDtoPhys[];
extern CONST(Can_RegInitType, CAN_CONFIG_CONST) CanRegInit[];
extern CONST(Can_HardwareObjectConfigType, CAN_CONFIG_CONST) CanHardwareObjectConfig[];
/*******************************************************************************
*   Global Function Declaration 
*******************************************************************************/

extern FUNC(void, CAN_PUBLIC_CODE) Can_Init(void);

extern FUNC(void, CAN_PUBLIC_CODE)Can_InitController
( 
    uint8 Controller, 
    P2CONST(Can_ControllerBaudrateConfigType, AUTOMATIC, CAN_CONFIG_CONST) 
                                                                          Config
);
                       
extern FUNC(Can_ReturnType, CAN_PUBLIC_CODE) Can_SetControllerMode
(
    uint8 Controller,
    Can_StateTransitionType Transition
);
                                    
extern FUNC(void, CAN_PUBLIC_CODE) Can_DisableControllerInterrupts
( 
    uint8 Controller 
); 
                                    
extern FUNC(void, CAN_PUBLIC_CODE)Can_EnableControllerInterrupts
( 
    uint8 Controller 
);
                                    
extern FUNC(void, CAN_PUBLIC_CODE)Can_DisableGlobalInterrupt(void); 

extern FUNC(void, CAN_PUBLIC_CODE) Can_EnableGlobalInterrupt(void);
                            
extern FUNC(Can_ReturnType, CAN_PUBLIC_CODE) Can_Write
(
    Can_HwHandleType Hth,
    P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfo
);

/* Scheduled functions */                        
extern FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write(void);
                                                     
extern FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read(void);

extern FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_BusOff(void);

extern FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Wakeup(void);  

extern FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Mode(void);


/* Application Call back function */

#if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) 
extern FUNC(void, CAN_APPL_CODE) ApplTimerBegin(uint8 LoopReason);
extern FUNC(Can_ReturnType, CAN_APPL_CODE) ApplTimerOutCheck(uint8 LoopReason);
extern FUNC(void, CAN_APPL_CODE) ApplTimerEnd(uint8 LoopReason);
#endif/* #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)  */ 


/* ISR */

extern FUNC(void, CAN_PUBLIC_CODE) CAN_PHY0_MB_ISR(void);
extern FUNC(void, CAN_PUBLIC_CODE) CAN_PHY0_Busoff_ISR(void);


#endif /* _CAN_H_ */

