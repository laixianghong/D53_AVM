/*================================================================================================*/
/* Project      = 78K0R EEPROM Emulation Library, MF2 single voltage flash                        */
/* Module       = eel_descriptor.c                                                                */
/* Device:      = 78K0R/Fx3                                                                       */
/* Version      = V1.0.6                                                                          */
/* Date         = 15.07.2010 15:33:02                                                             */
/*================================================================================================*/
/*                                  COPYRIGHT                                                     */
/*================================================================================================*/
/* Copyright (c) 2010 by Renesas Electronics Europe GmbH, a company of the Renesas Electronics    */
/* Corporation. All rights reserved.                                                              */
/*================================================================================================*/
/*                                                                                                */
/* Purpose:     contains the user defined EEL-variable descriptor                                 */
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



/*==============================================================================================*/
/* compiler settings                                                                            */
/*==============================================================================================*/
#pragma name EEL_DESCRIPTOR
#pragma sfr


#ifdef __K0R_LARGE__
  #pragma section @@DATAL EEL_UDAT
#else
  #pragma section @@DATA  EEL_UDAT
#endif

#pragma section @@CNSTL EEL_CNST



/*==============================================================================================*/
/* include files list                                                                           */
/*==============================================================================================*/
#define  __EEL_DESCRIPTOR_C
  #include  "eel_types.h"
  #include  "eel_descriptor.h"
#undef   __EEL_DESCRIPTOR_C

#if (EEL_STORAGE_TYPE == 'C')
  #include  "fcl_types.h"
#elif (EEL_STORAGE_TYPE=='D')
  #include  "fdl_types.h"
#else
  #error "EEL: wrong storage type defined !"
#endif


/* definition of variable types registered at EEL */
#include  "EEL_user_types.h"


/*==============================================================================================*/
/* import list                                                                                  */
/*==============================================================================================*/
/* empty */


/*==============================================================================================*/
/* data definition                                                                              */
/*==============================================================================================*/
#if (EEL_STORAGE_TYPE=='C')
  eel_u16   EEL_var_ref[EEL_VAR_NO];
#else
  eel_u16   EEL_var_ref[1];                                    /* dummy address for FDL variant */
#endif



/*********************************************************************************************************/
/*******                                                                                           *******/
/*******      B E G I N    O F    C U S T O M I Z A B L E    D E C L A R A T I O N    A R E A      *******/
/*******                                                                                           *******/
/*********************************************************************************************************/

__far const eel_u08 eel_descriptor[EEL_VAR_NO+1][4] =
            {
            /*  identifier        word-size (1...64)                  byte-size (1..255)         RAM-Ref. */
            /*  ----------------------------------------------------------------------------------------- */
                (eel_u08)'a',     (eel_u08)((sizeof(type_A)+3)/4),    (eel_u08)sizeof(type_A),   0x01,  \
                (eel_u08)'b',     (eel_u08)((sizeof(type_B)+3)/4),    (eel_u08)sizeof(type_B),   0x01,  \
                (eel_u08)'c',     (eel_u08)((sizeof(type_C)+3)/4),    (eel_u08)sizeof(type_C),   0x01,  \
                (eel_u08)'d',     (eel_u08)((sizeof(type_D)+3)/4),    (eel_u08)sizeof(type_D),   0x01,  \
                (eel_u08)'e',     (eel_u08)((sizeof(type_E)+3)/4),    (eel_u08)sizeof(type_E),   0x01,  \
                (eel_u08)'f',     (eel_u08)((sizeof(type_F)+3)/4),    (eel_u08)sizeof(type_F),   0x01,  \
                (eel_u08)'x',     (eel_u08)((sizeof(type_X)+3)/4),    (eel_u08)sizeof(type_X),   0x01,  \
                (eel_u08)'z',     (eel_u08)((sizeof(type_Z)+3)/4),    (eel_u08)sizeof(type_Z),   0x01,  \
                (eel_u08)0x00,    (eel_u08)(0x00),                    (eel_u08)(0x00),           0x00,  \
            };

/*********************************************************************************************************/
/*******                                                                                           *******/
/*******      E N D    O F    C U S T O M I Z A B L E    D E C L A R A T I O N    A R E A          *******/
/*******                                                                                           *******/
/*********************************************************************************************************/





/* ----------------------------------------------------------------------------------------------------- */
/* ------                                                                                          ----- */
/* ------     B E G I N    O F    U N T O U C H A B L E     D E C L A R A T I O N    A R E A       ----- */
/* ------                                                                                          ----- */
/* ----------------------------------------------------------------------------------------------------- */
__far const eel_u08   eel_refresh_bth_u08     = (eel_u08)EEL_REFRESH_BLOCK_THRESHOLD;
__far const eel_u08   eel_storage_type_u08    = (eel_u08)EEL_STORAGE_TYPE;
__far const eel_u08   eel_var_number_u08      = (eel_u08)EEL_VAR_NO;
/* ----------------------------------------------------------------------------------------------------- */
/* ------                                                                                          ----- */
/* ------     E N D    O F    U N T O U C H A B L E     D E C L A R A T I O N    A R E A           ----- */
/* ------                                                                                          ----- */
/* ----------------------------------------------------------------------------------------------------- */
