/*================================================================================================*/
/* Project      = EEPROM emulation library for 78k0r Single Voltage SST (MF2) Flash               */
/* Module       = eel.h                                                                           */
/* Device:      = 78K0R/Fx3                                                                       */
/* Version      = V1.0.6                                                                          */
/* Date         = 15.07.2010 15:27:59                                                             */
/*================================================================================================*/
/*                                  COPYRIGHT                                                     */
/*================================================================================================*/
/* Copyright (c) 2010 by Renesas Electronics Europe GmbH, a company of the Renesas Electronics    */
/* Corporation. All rights reserved.                                                              */
/*================================================================================================*/
/* Purpose:     API definition of the EEPROM Emulation Library (EEL)                              */
/*================================================================================================*/
/*                                                                                                */
/* Warranty Disclaimer                                                                            */
/*                                                                                                */
/* Because the Product(s) is licensed free of charge, there is no warranty of any kind            */
/* whatsoever and expressly disclaimed and excluded by NEC, either expressed or implied,          */
/* including but not limited to those for non-infringement of intellectual property,              */
/* merchantability and/or fitness for the particular purpose. NEC shall not have any obligation   */
/* to maintain, service or provide bug fixes for the supplied Product(s) and/or the Application.  */
/*                                                                                                */
/* Each User is solely responsible for determining the appropriateness of using the Product(s)    */
/* and assumes all risks associated with its exercise of rights under this Agreement,             */
/* including, but not limited to the risks and costs of program errors, compliance with           */
/* applicable laws, damage to or loss of data, programs or equipment, and unavailability or       */
/* interruption of operations.                                                                    */
/*                                                                                                */
/* Limitation of Liability                                                                        */
/*                                                                                                */
/* In no event shall NEC be liable to the User for any incidental, consequential, indirect,       */
/* or punitive damage (including but not limited to lost profits) regardless of whether           */
/* such liability is based on breach of contract, tort, strict liability, breach of warranties,   */
/* failure of essential purpose or otherwise and even if advised of the possibility of            */
/* such damages. NEC shall not be liable for any services or products provided by third party     */
/* vendors, developers or consultants identified or referred to the User by NEC in connection     */
/* with the Product(s) and/or the Application.                                                    */
/*                                                                                                */
/*================================================================================================*/
/*                                                                                                */
/* Environment  = Assembler:    RA78K0R V1.20                                                     */
/*                C-Compiler:   CC78K0R V2.00                                                     */
/*                Linker:       LK78K0R V1.20                                                     */
/*                Debugger:     ID78K0R-QB V3.60                                                  */
/*                                                                                                */
/*================================================================================================*/

#ifndef __EEL_H_INCLUDED
#define __EEL_H_INCLUDED

/*==============================================================================================*/
/* include files list                                                                           */
/*==============================================================================================*/
#include  "eel_types.h"


/*================================================================================================================*/
/* global function prototypes                                                                                     */
/*================================================================================================================*/



/* ---------------------------------------------------------------------------------------------------------------*/
/*  Block type:   standard function                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
/*  Purpose:      Initialization of the EEPROM Emulation Library (EEL).                                           */
/*                Internal variables are initialized.                                                             */
/*  Input:        -                                                                                               */
/*  Output:       -                                                                                               */
/*  Return:       status: configuration related status code                                                       */
/*                - EEL_OK:                 initialization done without problems                                  */
/*                - EEL_ERR_CONFIGURATION:  pool configuration error                                              */
/* ---------------------------------------------------------------------------------------------------------------*/
extern  eel_status_t __far EEL_Init(void);



/* ---------------------------------------------------------------------------------------------------------------*/
/*  Block type:   standard function                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
/*  Purpose:      Activates/Deactivates the access to the used flash medium.                                      */
/*                If data-flash (FDL) is used, the data-flash clock is switched ON/OFF.                           */
/*                In case of code-flash (FCL) is used, the FLMD0 pin is controlled herewith.                      */
/*  Input:        -                                                                                               */
/*  Output:       -                                                                                               */
/*  Return:       -                                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
extern  void  __far EEL_Open(void);
extern  void  __far EEL_Close(void);



/* ---------------------------------------------------------------------------------------------------------------*/
/*  Block type:   standard function                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
/*  Purpose:      Starting of execution of the corresponding EEL request.                                         */
/*                The value of the time-out within the request variable determines the command execution mode.    */
/*                Time-Out=0x00  -> polling mode, returns immediately to the application.                         */
/*                Time-Out=0xFF  -> enforced mode, returns to the application after the command is completed.     */
/*                other values   -> counting mode, returns to the application after Time-Out was counted          */
/*                                  down to 0x00 or the command is completed before that.                         */
/*  Input:        request_pstr - pointer to the EEL request variable                                              */
/*  Output:       error: command related status code                                                              */
/*                - EEL_OK:             command completed without problems                                        */
/*                - EEL_BUSY:           command accepted and                                                      */
/*                - EEL_ERR_REJECTED:   specified command couldn't be accepted (driver busy with other comamnd)   */
/*                - other:              refer to the documentation.                                               */
/*  Return:       -                                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
extern  void  __far  EEL_Execute(eel_request_t* request_pstr);



/* ---------------------------------------------------------------------------------------------------------------*/
/*  Block type:   standard function                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
/*  Purpose:      Normally, this function takes care for the execution of the background process (maintenance).   */
/*                When any command is started in "polling" mode, this function executes it state-by-state         */
/*                When any command is started in "counting" mode, this function executes it time-slice-wise.      */
/*                When starting commands in "enforced" mode, the EEL_Handler is not needed for command execution. */
/*                Just maintenance on EEL pool and data is realized by it in the idle-time of the application.    */
/*                                                                                                                */
/*  Input:        timeout - time-slice for the command execution expressed in time-out ticks                      */
/*                          0x00,  polling execution mode without TO supervision, execution state-by-state        */
/*                          other, allocates a time-slice for the EEL command execution                           */
/*  Output:       -                                                                                               */
/*  Return:       -                                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
extern  void  __far  EEL_Handler(eel_u08 timeout_u08);



/* ---------------------------------------------------------------------------------------------------------------*/
/*  Block type:   standard functions                                                                              */
/* ---------------------------------------------------------------------------------------------------------------*/
/*  Purpose:      This function decrements an internal 8-bit software counter used for timeout supervision.       */
/*                The time out period (time-slice) is determined by EEL_Execute(....) or EEL_Handler(...)         */
/*                EEL_TimeOut_CountDown() should be called in any periodical ISR creating the counting time-base. */
/*                Each time this function is called time-count register is decremented down to zero.              */
/*                When timeout-counter becomes 0x00 an internal timeout-event is generated, the counting          */
/*                process is stopped and progam counter (PC) is reterning from EEL to the user application.       */
/*                Preferable place for EEL_TimeOut_Count() the operating system timer is used for such purpose.   */
/*  Input:        -                                                                                               */
/*  Output:       -                                                                                               */
/*  Return:       -                                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
extern  void      __far  EEL_TimeOut_CountDown(void);



/* ---------------------------------------------------------------------------------------------------------------*/
/*  Block type:   standard function                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
/*  Purpose:      Provides the internal status of the EEL.                                                        */
/*                The information is only valid if the returned status is EEL_OK.                                 */
/*  Input:        &eel_driver_pstr - address of the status variable used by the application                       */
/*  Output:       driverStatus_pstr->operationStatus_enu:   operation status of the EEL driver                    */
/*                  EEL_OPERATION_PASSIVE:  STARTUP command not yet executed succesfuly                           */
/*                  EEL_OPERATION_IDLE:     no command and no background process is being executed                */
/*                  EEL_OPERATION_BUSY:     a command or any background process is being executed                 */
/*                driverStatus_pstr->accessStatus_enu:      access status of the EEL driver                       */
/*                  EEL_ACCESS_LOCKED:      any access to the EEL is disabled                                     */
/*                  EEL_ACCESS_UNLOCKED:    any access to the EEL is possibe (after successful startup)           */
/*                driverStatus_pstr->backgroundStatus_enu:  internal status of the background process             */
/*  Return:       -                                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
extern  void      __far  EEL_GetDriverStatus(__near eel_driver_status_t* driverStatus_pstr);



/* ---------------------------------------------------------------------------------------------------------------*/
/*  Block type:   standard function                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
/*  Purpose:      Provides the currently available space inside the EEL pool.                                     */
/*                It consists of the space inside the active heading block and all "prepared" blocks in pool.     */
/*  Input:        &space_pu16 - address of the space variable used by the application                             */
/*  Output:       space_pu16  - available space expressed in flash words (here 1 word = 4 bytes)                  */
/*  Return:       status: returns the execution status of this function                                           */
/*                EEL_OK - space value is correct                                                                 */
/*                EEL_ERR_REJECTED - not able to calculate available space (space_pu16* remains unchanged)        */
/*                EEL_ERR_ACCESS_LOCKED - STARTUP not yet executed successfully                                   */
/* ---------------------------------------------------------------------------------------------------------------*/
extern  eel_status_t  __far  EEL_GetSpace(__near eel_u16* space_pu16);



/* ---------------------------------------------------------------------------------------------------------------*/
/*  Block type:   standard function                                                                               */
/* ---------------------------------------------------------------------------------------------------------------*/
/*  Purpose:      This function returns the pointer to the "zero-terminated" version string of the library.       */
/*  Input:        -                                                                                               */
/*  Output:       -                                                                                               */
/*  Return:       address of the version string (pointer to the first character)                                  */
/* ---------------------------------------------------------------------------------------------------------------*/
extern  __far  eel_u08*  __far  EEL_GetVersionString(void);


#endif
