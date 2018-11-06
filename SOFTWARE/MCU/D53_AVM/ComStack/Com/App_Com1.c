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
| 00.01.00    2015-09-30                           first version
|-------------------------------------------------------------------------------
*/
#include "Com.h"

void Com_TxIpduCallout(PduIdType PduId, uint8 *DataPtr)
{
    (void)PduId;
}

void Com_RxIpduCallout(PduIdType PduId, uint8 *DataPtr)
{
    (void)PduId;
}

void AppIpduAVM_0x341_Conf(void)
{
}

void AppIpduAVM_0x341_TxTOIndication(void)
{
}

void AppIpduSAS_0x224_Ind(void)
{
}

void AppIpduABS_0x330_Ind(void)
{
}

void AppIpduBCM_0x350_Ind(void)
{
}

void AppIpduMP5_0x361_Ind(void)
{
}

void AppIpduMP5_0x366_Ind(void)
    {
}

void AppIpduMp5_0x367_Ind(void)
{
}

void AppRxIpduSAS_0x224_TimeOutInd(void)
{
}

void AppRxIpduABS_0x330_TimeOutInd(void)
{
}

void AppRxIpduBCM_0x350_TimeOutInd(void)
{
}

void AppRxIpduMP5_0x361_TimeOutInd(void)
{
}

void AppRxIpduMP5_0x366_TimeOutInd(void)
{
}

void AppRxIpduMp5_0x367_TimeOutInd(void)
{
}

