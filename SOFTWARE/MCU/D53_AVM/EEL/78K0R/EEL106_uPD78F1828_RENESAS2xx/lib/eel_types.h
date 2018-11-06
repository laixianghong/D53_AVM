/*================================================================================================*/
/* Project      = 78K0R EEPROM Emulation Library, MF2 single voltage flash                        */
/* Module       = eel_types.h                                                                     */
/* Device:      = 78K0R/Fx3                                                                       */
/* Version      = V1.0.6                                                                          */
/* Date         = 15.07.2010 15:35:03                                                             */
/*================================================================================================*/
/*                                  COPYRIGHT                                                     */
/*================================================================================================*/
/* Copyright (c) 2010 by Renesas Electronics Europe GmbH, a company of the Renesas Electronics    */
/* Corporation. All rights reserved.                                                              */
/*================================================================================================*/
/*                                                                                                */
/* Purpose:     contains type definitions of the EEPROM Emulation Library (EEL)                   */
/*                                                                                                */
/*================================================================================================*/
/*                                                                                                */
/* Warranty Disclaimer                                                                            */
/*                                                                                                */
/* Because the Product(s) is licensed free of charge, there is no warranty of any kind whatsoever */
/* and expressly disclaimed and excluded by Renesas, either expressed or implied, including but   */
/* not limited to those for non-infringement of intellectual property, merchantability and/or     */
/* fitness for the particular purpose.                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the        */
/* supplied Product(s) and/or the Application.                                                    */
/*                                                                                                */
/* Each User is solely responsible for determining the appropriateness of using the Product(s)    */
/* and assumes all risks associated with its exercise of rights under this Agreement, including,  */
/* but not limited to the risks and costs of program errors, compliance with applicable laws,     */
/* damage to or loss of data, programs or equipment, and unavailability or interruption of        */
/* operations.                                                                                    */
/*                                                                                                */
/* Limitation of Liability                                                                        */
/*                                                                                                */
/* In no event shall Renesas be liable to the User for any incidental, consequential, indirect,   */
/* or punitive damage (including but not limited to lost profits) regardless of whether such      */
/* liability is based on breach of contract, tort, strict liability, breach of warranties,        */
/* failure of essential purpose or otherwise and even if advised of the possibility of such       */
/* damages. Renesas shall not be liable for any services or products provided by third party      */
/* vendors, developers or consultants identified or referred to the User by Renesas in            */
/* connection with the Product(s) and/or the Application.                                         */
/*                                                                                                */
/*================================================================================================*/
/*                                                                                                */
/* Environment  = Assembler:    RA78K0R V1.20                                                     */
/*                C-Compiler:   CC78K0R V2.00                                                     */
/*                Linker:       LK78K0R V1.20                                                     */
/*                Debugger:     ID78K0R-QB V3.60                                                  */
/*                                                                                                */
/*================================================================================================*/

#ifndef __EEL_TYPES_H_INCLUDED
#define __EEL_TYPES_H_INCLUDED


/*==============================================================================================*/
/* unsigned type definitions                                                                    */
/*==============================================================================================*/
typedef unsigned char                       eel_u08;
typedef unsigned int                        eel_u16;
typedef unsigned long int                   eel_u32;


/*==============================================================================================*/
/* global constant definitions                                                                  */
/*==============================================================================================*/
/* empty */


/*==============================================================================================*/
/* global type definitions                                                                      */
/*==============================================================================================*/



/* EEL command set  */
typedef enum  {                                             /* ---------------------------------------------------- */
                EEL_CMD_UNDEFINED         = (0x00 | 0x00),  /* 0x00, undefined command (initial value)              */
                EEL_CMD_STARTUP           = (0x00 | 0x01),  /* 0x01, plausibility check of the EEL data and driver  */
                EEL_CMD_WRITE             = (0x00 | 0x02),  /* 0x02, creates a new instance of EEL variable         */
                EEL_CMD_READ              = (0x00 | 0x03),  /* 0x03, reads last instance of the EEL variable        */
                EEL_CMD_CLEANUP           = (0x00 | 0x04),  /* 0x04, refreshs all variables (minimize active zone)  */
                EEL_CMD_FORMAT            = (0x00 | 0x05),  /* 0x05, format the EEL pool, all instances are lost    */
                EEL_CMD_SHUTDOWN          = (0x00 | 0x06)   /* 0x06, deactivates the EEL in secure state            */
              } eel_command_t;                              /* ---------------------------------------------------- */


/* type of the EEL driver operation status */
typedef enum  {                                             /* ---------------------------------------------------- */
                EEL_OPERATION_PASSIVE     = (0x00 | 0x00),  /* 0x00, when library is not yet started                */
                EEL_OPERATION_IDLE        = (0x30 | 0x01),  /* 0x31, only background supervision process is active  */
                EEL_OPERATION_BUSY        = (0x30 | 0x02)   /* 0x32, foreground command is being executed           */
              } eel_operation_status_t;                     /* ---------------------------------------------------- */


/* type of the access status */
typedef enum  {                                             /* ---------------------------------------------------- */
                EEL_ACCESS_LOCKED         = (0x00 | 0x00),  /* 0x00, nighter read nor write access possible         */
                EEL_ACCESS_UNLOCKED       = (0x40 | 0x01)   /* 0x41, full access to the EEL is possible             */
              } eel_access_status_t;                        /* ---------------------------------------------------- */


/* EEL status set  */
typedef enum  {                                             /* ---------------------------------------------------- */
                EEL_OK                    = (0x00 | 0x00),  /* 0x00, no error occurred                              */
                EEL_BUSY                  = (0x00 | 0x01),  /* 0x01, request is under processing                    */
                EEL_ERR_CONFIGURATION     = (0x80 | 0x02),  /* 0x82, bad FAL or EEL configuration                   */
                EEL_ERR_INITIALIZATION    = (0x80 | 0x03),  /* 0x83, EEL_Init(), EEL_Open missed                    */
                EEL_ERR_ACCESS_LOCKED     = (0x80 | 0x04),  /* 0x84, STARTUP missing or fatal operation error       */
                EEL_ERR_COMMAND           = (0x80 | 0x05),  /* 0x85, wrong command code                             */
                EEL_ERR_PARAMETER         = (0x80 | 0x06),  /* 0x86, wrong parameter (wrong identifier in request)  */
                EEL_ERR_REJECTED          = (0x80 | 0x07),  /* 0x87, another request already under processing       */
                EEL_ERR_NO_INSTANCE       = (0x80 | 0x08),  /* 0x88, no instance found (variable never written)     */
                EEL_ERR_POOL_FULL         = (0x80 | 0x09),  /* 0x89, no space for writing data                      */
                EEL_ERR_POOL_INCONSISTENT = (0x80 | 0x0A),  /* 0x8A, no active block found within EEL-pool          */
                EEL_ERR_POOL_EXHAUSTED    = (0x80 | 0x0B),  /* 0x8B, EEL pool to small for correct operation        */
                EEL_ERR_INTERNAL          = (0x80 | 0x0C)   /* 0x8C, internal error (should never occur)            */
              } eel_status_t;                               /* ---------------------------------------------------- */


/* EEL request type */
typedef __near struct {                                     /* ---------------------------------------------------- */
                  __near eel_u08*       address_pu08;       /* 2, r/w, source/destination RAM-address               */
                  __near eel_u08        identifier_u08;     /* 1, w,   variable identifier                          */
                  __near eel_u08        timeout_u08;        /* 1, w,   number of timeout ticks for execution        */
                  __near eel_command_t  command_enu;        /* 1, w,   command has to be processed                  */
                  __near eel_status_t   status_enu;         /* 1, r,   error code after command execution           */
                } eel_request_t;                            /* ---------------------------------------------------- */
                                                            /* 6 bytes in total                                     */


/* type of the internal EEL driver status */
typedef struct {                                              /* -------------------------------------------------- */
                 eel_operation_status_t operationStatus_enu;  /* 1, operation status of the EEL driver              */
                 eel_access_status_t    accessStatus_enu;     /* 1, access rights indicator                         */
                 eel_status_t           backgroundStatus_enu; /* 1, error status of the background process          */
               } eel_driver_status_t;                         /* -------------------------------------------------- */
                                                              /* 3 bytes in total                                   */

#endif
