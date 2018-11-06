;=================================================================================================
; Project      = 78K0R EEPROM Emulation Library, MF2 single voltage flash
; Module       = eel_descriptor.asm
; Device:      = 78K0R/Fx3
; Version      = V1.0.6
; Date         = 15.07.2010 17:39:02
;=================================================================================================
;                                  COPYRIGHT
;=================================================================================================
; Copyright (c) 2010 by Renesas Electronics Europe GmbH, a company of the Renesas Electronics) GmbH,
; Corporation. All rights reserved.
;=================================================================================================
; Purpose:      contains the user defined EEL-variable descriptor
;=================================================================================================
;
; Warranty Disclaimer
;
; Because the Product(s) is licensed free of charge, there is no warranty of any kind whatsoever
; and expressly disclaimed and excluded by Renesas, either expressed or implied, including but
; not limited to those for non-infringement of intellectual property, merchantability and/or
; fitness for the particular purpose.
; Renesas shall not have any obligation to maintain, service or provide bug fixes for the
; supplied Product(s) and/or the Application.
;
; Each User is solely responsible for determining the appropriateness of using the Product(s)
; and assumes all risks associated with its exercise of rights under this Agreement, including,
; but not limited to the risks and costs of program errors, compliance with applicable laws,
; damage to or loss of data, programs or equipment, and unavailability or interruption of
; operations.
;
; Limitation of Liability
;
; In no event shall Renesas be liable to the User for any incidental, consequential, indirect,
; or punitive damage (including but not limited to lost profits) regardless of whether such
; liability is based on breach of contract, tort, strict liability, breach of warranties,
; failure of essential purpose or otherwise and even if advised of the possibility of such
; damages. Renesas shall not be liable for any services or products provided by third party
; vendors, developers or consultants identified or referred to the User by Renesas in
; connection with the Product(s) and/or the Application.
;
;=================================================================================================
;
; Environment  = PM plus(V6.30)
;                RA78K0R(V1.20)
;                CC78K0R(V2.00)
;
;=================================================================================================

 NAME           EEL_DESCRIPTOR                        ; module name


                                                      ;===========================================
                                                      ; INCLUDE LIST
                                                      ;===========================================
$include    (eel_descriptor.inc)
                                                      ;===========================================
                                                      ; EXPORT LIST
                                                      ;===========================================
 PUBLIC     _eel_descriptor                           ;
 PUBLIC     _eel_refresh_bth_u08                      ;
 PUBLIC     _eel_storage_type_u08                     ;
 PUBLIC     _eel_var_number_u08                       ;
 PUBLIC     _EEL_var_ref                              ;





; ==============================================================================================
;  data definition
; ==============================================================================================
EEL_UDAT	DSEG	BASEP

$_IF ( EEL_STORAGE_TYPE = 'C' )
  _EEL_var_ref:	DS	(EEL_VAR_NO * 2)
$ELSE
  _EEL_var_ref:	DS	(2)
$ENDIF


;=================================================================================================
; Segment name:  EEL_CNST
; Segment type:  CONST, location of the descriptor
;=================================================================================================
EEL_CNST	CSEG	PAGE64KP
;=================================================================================================

;*******************************************************************************************************
;******                                                                                           ******
;******      B E G I N    O F    C U S T O M I Z A B L E    D E C L A R A T I O N    A R E A      ******
;******                                                                                           ******
;*******************************************************************************************************

; size definition of variables
  VAR_SIZE_A              EQU               2
  VAR_SIZE_B              EQU               9
  VAR_SIZE_C              EQU               13
  VAR_SIZE_D              EQU               27
  VAR_SIZE_E              EQU               33
  VAR_SIZE_F              EQU               47
  VAR_SIZE_X              EQU               77
  VAR_SIZE_Z              EQU               255



; eel descriptor
eel_descriptor:
_eel_descriptor:


;     identifier(1...255),  word-size (1...64),   byte-size (1..255),   RAM-Ref.
; -----------------------------------------------------------------------------------------
  DB  'a',                  (VAR_SIZE_A + 3)/4,   VAR_SIZE_A,           01H
  DB  'b',                  (VAR_SIZE_B + 3)/4,   VAR_SIZE_B,           01H
  DB  'c',                  (VAR_SIZE_C + 3)/4,   VAR_SIZE_C,           01H
  DB  'd',                  (VAR_SIZE_D + 3)/4,   VAR_SIZE_D,           01H
  DB  'e',                  (VAR_SIZE_E + 3)/4,   VAR_SIZE_E,           01H
  DB  'f',                  (VAR_SIZE_F + 3)/4,   VAR_SIZE_F,           01H
  DB  'x',                  (VAR_SIZE_X + 3)/4,   VAR_SIZE_X,           01H
  DB  'z',                  (VAR_SIZE_Z + 3)/4,   VAR_SIZE_Z,           01H
  DB  00H,                                 00H,          00H,           00H

;*******************************************************************************************************
;******                                                                                           ******
;******      E N D    O F    C U S T O M I Z A B L E    D E C L A R A T I O N    A R E A          ******
;******                                                                                           ******
;*******************************************************************************************************





; -----------------------------------------------------------------------------------------------------
; ------                                                                                          -----
; ------     B E G I N    O F    U N T O U C H A B L E     D E C L A R A T I O N    A R E A       -----
; ------                                                                                          -----
; -----------------------------------------------------------------------------------------------------
 _eel_refresh_bth_u08:                    DB  EEL_REFRESH_BLOCK_THRESHOLD
 _eel_storage_type_u08:                   DB  EEL_STORAGE_TYPE
 _eel_var_number_u08:                     DB  EEL_VAR_NO
; -----------------------------------------------------------------------------------------------------
; ------                                                                                          -----
; ------     E N D    O F    U N T O U C H A B L E     D E C L A R A T I O N    A R E A           -----
; ------                                                                                          -----
; -----------------------------------------------------------------------------------------------------


  END


