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
#include "Can.h"
/*******************************************************************************
*   Config Parameters   
*******************************************************************************/
CONST(Can_RegInitType, CAN_CONFIG_CONST) CanRegInit[CAN_USED_CONTROLLER_NUM] =    
{
/*
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
*/
    #if (CAN_USED_CONTROLLER_NUM >= 1)
    { 
        ((uint8)0x00U), 
        ((uint8)0x01U), 
        ((uint16)0x120BU), 
        (CAN0_RX_INT_CFG|CAN0_TX_INT_CFG|CAN0_BUSOFF_INT_CFG),
        ((uint16)0x0000U), 
        ((uint16)0x0000U), 
        ((uint16)0x0000U),
        ((uint16)0x03FCU),  
        ((uint16)0x0000U), 
        ((uint16)0x0000U), 
        ((uint16)0x0000U), 
        ((uint16)0x0000U), 
        
    }
    #endif/* #if (CAN_USED_CONTROLLER_NUM >= 1U) */
  
};

CONST(Can_HardwareObjectConfigType, CAN_CONFIG_CONST) 
                                     CanHardwareObjectConfig[CAN_USED_HOH_NUM] =  
{   
 
  /* CAN0 RX MB */ 
    /*0*/   
    {    
        0x50,       
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK, 
        STANDARD_ID,
        CAN_MS1_MASK    
    },
    /*1*/   
    {    
        0x8A,       
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK, 
        STANDARD_ID,    
        CAN_MS1_MASK    
    },
    /*2*/   
    {    
        0x93,       
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK, 
        STANDARD_ID,    
        CAN_MS1_MASK    
    },
    /*3*/   
    {    
        0xA0,       
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK, 
        STANDARD_ID,    
        CAN_MS1_MASK    
    },
    /*4*/   
    {    
        0xA5,       
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK, 
        STANDARD_ID,    
        CAN_MS1_MASK    
    },
    /*5*/   
    {  
        0x23A,       
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK,   
        STANDARD_ID,  
        CAN_MS1_MASK    
    },
    /*6*/   
    {  
        0x33C,       
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK,  
        STANDARD_ID,   
        CAN_MS1_MASK    
    },
    /*7*/   
    {  
        0x355U,        
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK, 
        STANDARD_ID,  
        CAN_MS1_MASK    
    },
    /*8*/   
    {    
        0x366U,        
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK, 
        STANDARD_ID,  
        CAN_MS1_MASK    
    },
    /*9*/   
    {    
        0x376U,        
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK, 
        STANDARD_ID,  
        CAN_MS1_MASK    
    },
    /*10*/   
    {    
        0x393U,        
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK, 
        STANDARD_ID,  
        CAN_MS1_MASK    
    },
    /*11*/   
    {    
        0x395U,        
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK, 
        STANDARD_ID,  
        CAN_MS1_MASK    
    },
    /*12*/   
    {    
        0x765U,        
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK, 
        STANDARD_ID,  
        CAN_MS1_MASK    
    },
    /*13*/   
    {    
        0x7DF,         
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK, 
        STANDARD_ID,   
        CAN_MS1_MASK    
    },
    /*14*/   
    {   
        0x394U,         
        CAN_HOH_TX_MASK, 
        STANDARD_ID,    
        CAN_MS0_MASK    
    },
    /*15*/   
    {  
        0x76D,       
        CAN_HOH_TX_MASK, 
        STANDARD_ID,    
        CAN_MS0_MASK    
    }
}; 


