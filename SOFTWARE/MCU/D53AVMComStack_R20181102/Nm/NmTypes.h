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

#ifndef _NMTYPES_H_
#define _NMTYPES_H_

#include "ComStack_Types.h"


/*******************************************************************************
*   Typedef 
*******************************************************************************/ 

typedef enum
{
    INDIRNM_UNINIT = 0,
    INDIRNM_OFF,
    INDIRNM_STARTUP,
    INDIRNM_SHUTDOWN,
    INDIRNM_NORMAL,
    INDIRNM_BUSERROR,
    INDIRNM_BUSERRORRECOVER
} IndirNMStateType;


typedef  uint16 IndirNmTimerType;
typedef  uint16 IndirFlagType;


typedef struct
{	
	//uint8  usMessageId;
	uint16  usDtcId;//for information DDM
	//GACINT16U  usDTCIndex;
	uint16  usMsgStartDelay; // ms
	uint16  usLostCommTime; // ms
	//GACINT8U ucMsgFThreshold;//Intermit;
	//GACINT8U ucRxSequentialThresholdPass;//;Sequential	
	
 	//GACINT8U   ucStepSizeUp;           /* Step size for decrementation of FDC (PREPASSED). */
    //GACINT8U   ucStepSizeDown;
	//GACINT8U  ucReserved;
}IndirNMNodeLostCheckConfigType;

typedef struct
{
    IndirNmTimerType  StartDelay;
    /*IndirNmTimerType  RecoverStartDelay;*/
    IndirNmTimerType  ShutDownDelay;
}IndirNmDelayCfgType;



#endif

