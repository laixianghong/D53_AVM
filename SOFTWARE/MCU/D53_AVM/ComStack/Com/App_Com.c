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
#include "NmCbk.h"
#include "DdmCfg.h"
#include "Ddm.h"

void Com_TxIpduCallout(PduIdType PduId, uint8 *DataPtr)
{
    (void)PduId;
}

void Com_RxIpduCallout(PduIdType PduId, uint8 *DataPtr)
{
    (void)PduId;
}

void AppIpduAVM_STATE_Conf(void)
{
}

void AppIpduAVM_STATE_TxTOIndication(void)
{
}

void AppIpduGW_CommAVailability_Ind(void)
{
}

void AppIpduIBCM4_Ind(void)
{
}

void AppIpduGW_TCU1_Ind(void)
{
}

void AppIpduGW_ESC2_Ind(void)
{
}

void AppIpduGW_SAS_inf_Ind(void)
{
}

void AppIpduIBCM2_Ind(void)
{
}

void AppIpduIBCM3_Ind(void)
{
}

void AppIpduGW_PSA2_VCU5_Ind(void)
{
}

void AppIpduMP5_2_Ind(void)
{
}

void AppIpduAPA2_Ind(void)
{
}

void AppIpduMP5_STATE_Ind(void)
{
}

void AppIpduMP5_3_Ind(void)
{
}

void AppRxIpduGW_CommAVailability_TimeOutInd(void)
{
}

void AppRxIpduIBCM4_TimeOutInd(void)
{
}

void AppRxIpduGW_TCU1_TimeOutInd(void)
{
}

void AppRxIpduGW_ESC2_TimeOutInd(void)
{
}

void AppRxIpduGW_SAS_inf_TimeOutInd(void)
{
}

void AppRxIpduIBCM2_TimeOutInd(void)
{
}

void AppRxIpduIBCM3_TimeOutInd(void)
    {
}

void AppRxIpduGW_PSA2_VCU5_TimeOutInd(void)
{
}

void AppRxIpduMP5_2_TimeOutInd(void)
{
}

void AppRxIpduAPA2_TimeOutInd(void)
{
}

void AppRxIpduMP5_STATE_TimeOutInd(void)
{
}

void AppRxIpduMP5_3_TimeOutInd(void)
{
}

