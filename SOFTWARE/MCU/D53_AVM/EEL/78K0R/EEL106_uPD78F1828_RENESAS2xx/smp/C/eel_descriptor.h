/*================================================================================================*/
/* Project      = 78K0R EEPROM Emulation Library, MF2 single voltage flash                        */
/* Module       = eel_descriptor.h                                                                */
/* Device:      = 78K0R/Fx3                                                                       */
/* Version      = V1.0.6                                                                          */
/* Date         = 15.07.2010 15:33:10                                                             */
/*================================================================================================*/
/*                                  COPYRIGHT                                                     */
/*================================================================================================*/
/* Copyright (c) 2010 by Renesas Electronics Europe GmbH, a company of the Renesas Electronics    */
/* Corporation. All rights reserved.                                                              */
/*================================================================================================*/
/*                                                                                                */
/* Purpose:     contains user configurable parameter of the EEPROM emulation                      */
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

#ifndef __EEL_DESCRIPTOR_H_INCLUDED
#define __EEL_DESCRIPTOR_H_INCLUDED


/*==============================================================================================*/
/* include files list                                                                           */
/*==============================================================================================*/
/* empty */


/*==============================================================================================*/
/* constant definitions   (USER CONFIGURABLE PART)                                                                      */
/*==============================================================================================*/


/* specifies the flash access library used for EEPROM emulation               */
/* Use 'D' for data-flash, 'C' for code-flash. Other values are invalid       */
#define   EEL_STORAGE_TYPE              'D'


/* specifies the number of abstract variables the EEL should handle           */
#define   EEL_VAR_NO                    8


/* Maximum size of the active area expressed in blocks  */
/* Overrunning this threshold triggers automatically the refresh process effecting the last active block */
#define   EEL_REFRESH_BLOCK_THRESHOLD   1


#endif
