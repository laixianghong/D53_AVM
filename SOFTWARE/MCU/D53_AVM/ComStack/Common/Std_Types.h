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

#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_

/*******************************************************************************
*   Includes 
*******************************************************************************/
#include "Platform_Types.h"
#include "Compiler.h"

/*******************************************************************************
*   Macro 
*******************************************************************************/
#define STD_HIGH     (1)  
#define STD_LOW      (0) 

#define STD_ACTIVE   (1)       
#define STD_IDLE     (0) 

#define STD_ON       (1)                                       
#define STD_OFF      (0)

/* This typedef has been addedf or OSEK compliance */                        
#ifndef STATUSTYPEDEFINED  
    #define STATUSTYPEDEFINED  
    #define E_OK    (0) 
    /* OSEK compliance */ 
    typedef unsigned char StatusType; 
#endif 
 
#define E_NOT_OK  (1) 
                                                
/*******************************************************************************
*   Typedef 
*******************************************************************************/                                                                   
typedef uint8 Std_ReturnType;

typedef struct                                          
{
    uint16 vendorID;                           
    uint16 moduleID;
    uint8  instanceID;
    uint8  sw_major_version;                         
    uint8  sw_minor_version;
    uint8  sw_patch_version;
}Std_VersionInfoType;

#endif  /* _STD_TYPES_H_ */
