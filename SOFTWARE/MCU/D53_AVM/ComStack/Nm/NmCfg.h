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

#ifndef _NMCFG_H_
#define _NMCFG_H_

#include "ComStack_Types.h"

#define INDIRNM_LOSTCOMM_CHECK  STD_OFF
#if(INDIRNM_LOSTCOMM_CHECK == STD_ON)
#define INDIRNM_TOTALNUMOFNODES      2 
#endif
#define INDIRNM_TASK_PERIOD          10
//#define INDIRNM_TURE         1
//#define INDIRNM_FASLE        0
#define INDIRNM_SET            1
#define INDIRNM_CLR            0


#define IndirNmGlobalIntDisable() Can_DisableGlobalInterrupts()
#define IndirNmGlobalIntEnable()  Can_DisableGlobalInterrupts()

#if(INDIRNM_LOSTCOMM_CHECK == STD_ON)
extern const IndirNMNodeLostCheckConfigType IndirNMNodeLostCheckCfgArry[INDIRNM_TOTALNUMOFNODES];
#endif
extern const IndirNmDelayCfgType IndirNmDelayCfgItem;

/*Fast Recover times*/
extern const uint16 nmBusOffQuickRecAttemp;
extern const uint16 nmBusOffQuickRecTime;

/*Slow Recover times*/ 
/*extern const uint16 nmBusOffSlowRecAttemp;*/
extern const uint16 nmBusOffSlowkRecTime;

#if(INDIRNM_LOSTCOMM_CHECK == STD_ON)
#define NM_LOSTCOMM_0x218_INDEX  0
#define NM_LOSTCOMM_0x270_INDEX  1
#endif

#endif

