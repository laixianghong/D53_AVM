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

#ifndef _NM_H_
#define _NM_H_

#include "NmTypes.h"
#include "NmCfg.h"


extern Std_ReturnType IndirNM_GetCurrentNmState(IndirNMStateType * curst);
extern void IndirNm_Init(void);
extern Std_ReturnType IndirNm_VoltageNormal(void);
extern Std_ReturnType IndirNm_VoltageAbnormal(void);
extern Std_ReturnType IndirNm_StartUp(void);
extern void IndirNm_ShutDown(void);
extern void IndirNm_MainTask(void);
extern Std_ReturnType IndirNm_IsStartDelayExpired(void);

extern void App_IndirNmStartUp(void);
extern void App_IndirNmShutDownSyn(void);
extern void App_IndirNmShutDownPost(void);

extern void Appl_IndirNmRecoverSuccess(void);
extern void Appl_IndirNmReachMaxTimes(void);
extern void Appl_IndirNmBusOffStart(void);
extern void Appl_IndirNmBusOffEnd(void);
#endif

