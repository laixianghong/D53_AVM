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


#ifndef _NMCBK_H_
#define _NMCBK_H_

#include "NmTypes.h"
#include "NmCfg.h"
extern void IndirNm_BusOffIndication(void);
extern void IndirNm_MsgTxSucceed(void);
#if(INDIRNM_LOSTCOMM_CHECK == STD_ON)
extern void IndirNm_MsgRxIndication(uint16 idx);
#endif

#endif

