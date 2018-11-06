;==============================================================================================
; Project      = 78K0R EEPROM Emulation Library, MF2 single voltage flash
; Module       = eel_types.inc
; Device:      = 78K0R
; Version      = V1.0.6
; Date         = 15.07.2010 17:46:13
;==============================================================================================
;                                  COPYRIGHT
;==============================================================================================
; Copyright (c) 2010 by Renesas Electronics Europe GmbH, a company of the Renesas Electronics) GmbH,
; Corporation. All rights reserved.
;==============================================================================================
;
; Purpose:     API definition of the EEPROM Emulation Library (EEL)
;
;==============================================================================================
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
;==============================================================================================
;
; Environment  = Assembler:    RA78K0R V1.20
;                C-Compiler:   CC78K0R V2.00
;                Linker:       LK78K0R V1.20
;                Debugger:     ID78K0R-QB V3.60
;
;==============================================================================================


$IF (__EEL_TYPES_INC_INCLUDED)

$ELSE
$SET (__EEL_TYPES_INC_INCLUDED)




;==============================================================================================
; constant definitions
;==============================================================================================


; EEL command code definitions
; -----------------------------------------------------
EEL_CMD_UNDEFINED                 EQU     (00H)
EEL_CMD_STARTUP                   EQU     (00H OR 01H)
EEL_CMD_WRITE                     EQU     (00H OR 02H)
EEL_CMD_READ                      EQU     (00H OR 03H)
EEL_CMD_CLEANUP                   EQU     (00H OR 04H)
EEL_CMD_FORMAT                    EQU     (00H OR 05H)
EEL_CMD_SHUTDOWN                  EQU     (00H OR 06H)


; EEL driver operation status code definition
; -----------------------------------------------------
EEL_OPERATION_PASSIVE             EQU     (000H OR 000H)
EEL_OPERATION_IDLE                EQU     (030H OR 001H)
EEL_OPERATION_BUSY                EQU     (030H OR 002H)


; EEL driver access status code definition
; -----------------------------------------------------
EEL_ACCESS_LOCKED                 EQU     (000H OR 000H)
EEL_ACCESS_UNLOCKED               EQU     (040H OR 001H)


; EEL error code definitions
; -----------------------------------------------------
EEL_OK                            EQU     (000H OR 000H)
EEL_BUSY                          EQU     (000H OR 001H)
EEL_ERR_CONFIGURATION             EQU     (080H OR 002H)
EEL_ERR_INITIALIZATION            EQU     (080H OR 003H)
EEL_ERR_ACCESS_LOCKED             EQU     (080H OR 004H)
EEL_ERR_COMMAND                   EQU     (080H OR 005H)
EEL_ERR_PARAMETER                 EQU     (080H OR 006H)
EEL_ERR_REJECTED                  EQU     (080H OR 007H)
EEL_ERR_NO_INSTANCE               EQU     (080H OR 008H)
EEL_ERR_POOL_FULL                 EQU     (080H OR 009H)
EEL_ERR_POOL_INCONSISTENT         EQU     (080H OR 00AH)
EEL_ERR_POOL_EXHAUSTED            EQU     (080H OR 00BH)
EEL_ERR_INTERNAL                  EQU     (080H OR 00CH)


; byte index within EEL-request structure
; -----------------------------------------------------
EEL_REQUEST_ADDR                  EQU     (000H)
EEL_REQUEST_IDENTIFIER            EQU     (002H)
EEL_REQUEST_TIMEOUT               EQU     (003H)
EEL_REQUEST_COMMAND               EQU     (004H)
EEL_REQUEST_ERROR                 EQU     (005H)


$ENDIF
