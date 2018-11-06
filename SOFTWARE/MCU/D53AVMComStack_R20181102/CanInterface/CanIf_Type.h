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

#ifndef _CANIF_TYPE_H_
#define _CANIF_TYPE_H_


/*Operating modes of the CAN Controller and CAN Driver*/
typedef enum  
{
    /*UNINIT mode. Default mode of the CAN Driver and all CAN controllers 
    connected to one CAN network after power on. */
    CANIF_CS_UNINIT = 0,
    /*SLEEP mode. At least one of all CAN controllers connected to one CAN 
    network are set into the SLEEP mode and can be woken up by request of the 
    CAN Driver or by a network event (must be supported by CAN hardware) */
    CANIF_CS_SLEEP = 1,     
    /*STARTED mode. All CAN controllers connected to one CAN network are started

    by the CAN Driver and in full-operational mode. */
    CANIF_CS_STARTED = 2,   
    /*STOPPED mode. At least one of all CAN controllers connected to one CAN 
    network is halted and does not operate on the network. */
    CANIF_CS_STOPPED = 3                       

}CanIf_ControllerModeType;  


/*Request for PDU channel group. The request type of the channel defines it's 
transmit or receive activity. Communication direction (transmission and/or 
reception) of the channel can be controlled separately or together
by upper layers.*/
typedef enum
{
    /*0000,Channel shall be set to the offline mode => no transmission and 
    reception */
    CANIF_SET_OFFLINE           = 0,      
    /*0111,Channel shall be set to online mode => full operation mode */
    CANIF_SET_ONLINE            = 1, 
    /*0110,Receive path of the corresponding channel shall be disabled*/
    CANIF_SET_RX_OFFLINE        = 2,  
    /*1001,Receive path of the corresponding channel shall be enabled*/
    CANIF_SET_RX_ONLINE         = 3,    
    /*0001,Transmit path of the corresponding channel shall be disabled*/
    CANIF_SET_TX_OFFLINE        = 4,  
    /*0100,Transmit path of the corresponding channel shall be set to the 
    offline active mode => notifications are processed but transmit
    requests are blocked.*/
    CANIF_SET_TX_OFFLINE_ACTIVE = 5,
     /*1110,Transmit path of the corresponding channel shall be enabled*/
    CANIF_SET_TX_ONLINE         = 6             
}CanIf_PduSetModeType ;                  


 /*Status of the PDU channel group. Current mode of the channel defines
 its transmit or receive activity. Communication direction (transmission and
 /or reception) of the channel can be controlled separately or together
 by upper layers*/
typedef enum
{
    /*000,Channel is in the offline mode => no transmission and reception*/
    CANIF_GET_OFFLINE                  = 0,
    /*100,Transmit path of the corresponding channel is in the offline active 
    mode => transmit notifications are processed but transmit requests are 
    blocked.The receive path is disabled.*/
    CANIF_GET_OFFLINE_ACTIVE           = 4,
    /*101,Transmit path of the corresponding channel is in the offline active 
    mode => transmit notifications are processed but transmit requests are 
    blocked.The receive path is enabled.*/
    CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE = 5,  
    /*111,Channel is in the online mode => full operation mode*/
    CANIF_GET_ONLINE                   = 7, 
    /*001,Receive path of the corresponding channel is enabled and transmit path
    is disabled.*/
    CANIF_GET_RX_ONLINE                = 1, 
    /*110,Transmit path of the corresponding channel is enabled and receive path
    is disabled.*/
    CANIF_GET_TX_ONLINE                = 6                  
}CanIf_PduGetModeType ;                 

/*Return value of CAN L-PDU notification status.*/  
typedef enum
{
    /*No transmit or receive event occurred for the requested L-PDU.*/
    CANIF_NO_NOTIFICATION    = 0,   
    /*The requested Rx/Tx CAN L-PDU was successfully transmitted or received.*/
    CANIF_TX_RX_NOTIFICATION = 1             
}CanIf_NotifStatusType ;                 
 
#endif/* _CANIF_TYPE_H_  */
