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
#ifndef _CAN_TYPE_H_
#define _CAN_TYPE_H_

/*******************************************************************************
*   Includes   
*******************************************************************************/
#include "Can_Cfg.h"
#include "ComStack_Types.h"

/*******************************************************************************
*   Typedef 
*******************************************************************************/
/*CAN429:
Name: Can_HwHandleType
Type: uint8, uint16
Range: Standard 0..0x0FF
       Extended 0..0xFFFF
Description:    
Represents the hardware object handles of a CAN hardware unit. 
For CAN hardware units with more than 255 HW objects use extended range.
*/
#if(CAN_USED_HOH_NUM > 255U)
typedef uint16 Can_HwHandleType;
#else
typedef uint8 Can_HwHandleType;
#endif

 /*CAN416:
Name:   Can_IdType
Type:   uint16, uint32
Range:  Standard 0..0x7FF
        Extended 0..0xFFFFFFFF
Description:    
Represents the Identifier of an L-PDU. For extended IDs the most significant 
bit is set.
*/
#if (STD_ON == CAN_ENABLE_EXTERNED_ID)  
typedef uint32 Can_IdType;
#else
typedef uint16 Can_IdType;
#endif/* #if (STD_ON == CAN_ENABLE_EXTERNED_ID)  */

/*CAN039:
Name:       Can_ReturnType 
Type:       Enumeration 
Range: 
CAN_OK      success 
CAN_NOT_OK  error occurred or wakeup event occurred during sleep transition 
CAN_BUSY    transmit request could not be processed because no transmit object 
            was available 
Description:  
Return values of CAN driver API . 
*/
typedef enum
{
    CAN_OK = 0,                   
    CAN_NOT_OK = 1,     
    CAN_BUSY = 2        
}Can_ReturnType;


/* CAN417:  
Name:  Can_StateTransitionType 
Type:  Enumeration 
Range: 
CAN_T_START   CAN controller transition value to request state STARTED. 
CAN_T_STOP    CAN controller transition value to request state STOPPED. 
CAN_T_SLEEP   CAN controller transition value to request state SLEEP. 
CAN_T_WAKEUP  CAN controller transition value to request state STOPPED 
              from state SLEEP. 
Description:  
State transitions that are used by the function CAN_SetControllerMode 
*/
typedef enum
{
    CAN_T_START  = 0,    
    CAN_T_STOP   = 1,     
    CAN_T_SLEEP  = 2,    
    CAN_T_WAKEUP = 3, 
    CAN_T_NONE   = 4  
}Can_StateTransitionType;

typedef enum
{
    STANDARD_ID  = 0, 
    EXTENDED_ID  = 1,     
}Can_CanIdType;
 /* CAN413: 
Name:  Can_ConfigType 
Type:  Structure 
Range: Implementation specific.  
Description:
This is the type of the external data structure containing the overall 
initialization data for the CAN driver and SFR settings affecting all 
controllers. Furthermore it contains pointers to controller configuration 
structures. The contents of the initialization data structure are CAN 
hardware specific. 
*/ 
typedef struct
{
    uint8 CanControllerNum;   
}Can_ConfigType;

/*CAN414:
Name:     Can_ControllerBaudrateConfigType
Type:     Structure
Range:    Implementation specific.
Description: 
This is the type of the external data structure containing 
the bit timing related initialization data for one CAN controller. 
The contents of the initialization data structure are CAN hardware specific.
*/
typedef struct
{
    uint8   CanCtrl0;
    uint8   CanCtrl1;
}Can_ControllerBaudrateConfigType;

/*CAN415:
Name: Can_PduType
Type: Structure
Description: 
This type is used to provide ID, DLC and SDU from CAN interface 
to CAN driver.
*/
typedef struct
{
    PduIdType   swPduHandle;
    uint8       length ;
    Can_IdType  id ;
    P2VAR(uint8, TYPEDEF, CAN_APPL_DATA)   sdu ;  
}Can_PduType;

/* hoh config type */
typedef struct
{                   
    Can_IdType     id;             /*CAN ID*/
    uint8          hohType;        /*hohType  bit0:0-receive,1-transmit;                                                          bit1:0-basic ,1-full*/
    Can_CanIdType  idtype;             /*CAN ID*/
    uint8          mask;      /*value of Rx Individual Mask Registers,
                                                                        1-full*/
}Can_HardwareObjectConfigType;

/* Can Internal buffer length type */
typedef uint32 Can_LenTyp;

typedef enum
{
    CAN_UNINITIALIZED = 0,
    CAN_INITIALIZED   = 1  
}Can_InitType;

#endif/* _CAN_TYPE_H_*/
