;=================================================================================================
; Project      = 78K0R Flash Data access Library, MF2 single voltage flash
; Module       = fdl_descriptor.asm
; Device:      = 78K0R/Fx3
; Version      = V1.0.2
; Date         = 07.01.2010 13:59:25
;=================================================================================================
;                                  COPYRIGHT
;=================================================================================================
; Copyright (c) 2009 by NEC Electronics (Europe) GmbH,
;               a company of the NEC Electronics Corporation
;=================================================================================================
; Purpose:      Contains FAL pool descriptor. Please don't change this file!!!!
;=================================================================================================
;
; Warranty Disclaimer
;
; Because the Product(s) is licensed free of charge, there is no warranty of any kind
; whatsoever and expressly disclaimed and excluded by NEC, either expressed or implied,
; including but not limited to those for non-infringement of intellectual property,
; merchantability and/or fitness for the particular purpose. NEC shall not have any obligation
; to maintain, service or provide bug fixes for the supplied Product(s) and/or the Application.
;
; Each User is solely responsible for determining the appropriateness of using the Product(s)
; and assumes all risks associated with its exercise of rights under this Agreement,
; including, but not limited to the risks and costs of program errors, compliance with
; applicable laws, damage to or loss of data, programs or equipment, and unavailability or
; interruption of operations.
;
; Limitation of Liability
;
; In no event shall NEC be liable to the User for any incidental, consequential, indirect,
; or punitive damage (including but not limited to lost profits) regardless of whether
; such liability is based on breach of contract, tort, strict liability, breach of warranties,
; failure of essential purpose or otherwise and even if advised of the possibility of
; such damages. NEC shall not be liable for any services or products provided by third party
; vendors, developers or consultants identified or referred to the User by NEC in connection
; with the Product(s) and/or the Application.
;
;=================================================================================================
;
; Environment  = PM plus(V6.30)
;                RA78K0R(V1.20)
;                CC78K0R(V2.00)
;
;=================================================================================================

 NAME           fdl_descriptor                        ; module name


                                                      ;===========================================
                                                      ; INCLUDE LIST
                                                      ;===========================================
$include    (fdl_descriptor.inc)
                                                      ;===========================================
                                                      ; EXPORT LIST
                                                      ;===========================================
 PUBLIC     fal_descriptor_str                        ; FDL descriptor
 PUBLIC     _fal_descriptor_str                       ;



;=================================================================================================
; Segment name:  FAL_CNST
; Segment type:  CONST, location of the descriptor
;=================================================================================================
FAL_CNST  CSEG  PAGE64KP
;=================================================================================================



; -----------------------------------------------------------------------------------------------------
; ------                                                                                          -----
; ------     B E G I N    O F    U N T O U C H A B L E     D E C L A R A T I O N    A R E A       -----
; ------                                                                                          -----
; -----------------------------------------------------------------------------------------------------

; specify the flash block size expressed in bytes
FAL_BLOCK_SIZE              EQU               (2*1024)


; data flash start and end address
FAL_DATA_FLASH_START_ADDR   EQU               000E9800H
FAL_DATA_FLASH_END_ADDR     EQU               000ED7FFH



; FAL pool configuration

FAL_POOL_FIRST_BLOCK        EQU               0

$_IF ( FAL_POOL_SIZE > 0 )
  FAL_POOL_LAST_BLOCK       EQU               (FAL_POOL_SIZE - 1)
  FAL_POOL_FIRST_ADDRESS    EQU               FAL_DATA_FLASH_START_ADDR
  FAL_POOL_LAST_ADDRESS     EQU               ( FAL_POOL_FIRST_ADDRESS + (FAL_BLOCK_SIZE*FAL_POOL_LAST_BLOCK) + (FAL_BLOCK_SIZE-1) )
  FAL_POOL_WSIZE            EQU               (FAL_POOL_SIZE*FAL_BLOCK_SIZE/4)
  FAL_POOL_FIRST_WIDX       EQU               0
  FAL_POOL_LAST_WIDX        EQU               (FAL_POOL_WSIZE - 1)
  FAL_BLOCK_WSIZE           EQU               (FAL_BLOCK_SIZE/4)
$ELSE
  FAL_POOL_LAST_BLOCK       EQU               0
  FAL_POOL_FIRST_ADDRESS    EQU               0
  FAL_POOL_LAST_ADDRESS     EQU               0
  FAL_POOL_WSIZE            EQU               0
  FAL_POOL_FIRST_WIDX       EQU               0
  FAL_POOL_LAST_WIDX        EQU               0
  FAL_BLOCK_WSIZE           EQU               0
$ENDIF


; EEL pool configuration

  EEL_POOL_FIRST_BLOCK      EQU               0

$_IF ( EEL_POOL_SIZE > 0 )
  EEL_POOL_LAST_BLOCK       EQU               (EEL_POOL_FIRST_BLOCK + EEL_POOL_SIZE - 1)
  EEL_POOL_FIRST_ADDRESS    EQU               FAL_POOL_FIRST_ADDRESS
  EEL_POOL_LAST_ADDRESS     EQU               ( FAL_POOL_FIRST_ADDRESS + ( FAL_BLOCK_SIZE*EEL_POOL_LAST_BLOCK ) + (FAL_BLOCK_SIZE-1) )
  EEL_POOL_WSIZE            EQU               (EEL_POOL_SIZE*FAL_BLOCK_SIZE/4)
  EEL_POOL_FIRST_WIDX       EQU               0
  EEL_POOL_LAST_WIDX        EQU               (EEL_POOL_WSIZE - 1)
$ELSE
  EEL_POOL_LAST_BLOCK       EQU               0
  EEL_POOL_FIRST_ADDRESS    EQU               0
  EEL_POOL_LAST_ADDRESS     EQU               0
  EEL_POOL_WSIZE            EQU               0
  EEL_POOL_FIRST_WIDX       EQU               0
  EEL_POOL_LAST_WIDX        EQU               0
$ENDIF


; USER pool configuration

  USER_POOL_SIZE            EQU               (FAL_POOL_SIZE - EEL_POOL_SIZE)

$_IF ( USER_POOL_SIZE > 0 )
  USER_POOL_FIRST_BLOCK     EQU               0
  USER_POOL_LAST_BLOCK      EQU               (USER_POOL_FIRST_BLOCK + USER_POOL_SIZE - 1)

  $_IF ( EEL_POOL_SIZE > 0 )
    USER_POOL_FIRST_ADDRESS     EQU           (EEL_POOL_LAST_ADDRESS + 1)
  $ELSE
    USER_POOL_FIRST_ADDRESS     EQU           FAL_POOL_FIRST_ADDRESS
  $ENDIF

  USER_POOL_LAST_ADDRESS    EQU               ( USER_POOL_FIRST_ADDRESS + ( FAL_BLOCK_SIZE*USER_POOL_LAST_BLOCK ) + (FAL_BLOCK_SIZE-1) )
  USER_POOL_WSIZE           EQU               (USER_POOL_SIZE*FAL_BLOCK_SIZE/4)
  USER_POOL_FIRST_WIDX      EQU               0
  USER_POOL_LAST_WIDX       EQU               (USER_POOL_WSIZE - 1)
$ELSE
  USER_POOL_FIRST_BLOCK     EQU               0
  USER_POOL_LAST_BLOCK      EQU               0
  USER_POOL_FIRST_ADDRESS   EQU               0
  USER_POOL_LAST_ADDRESS    EQU               0
  USER_POOL_WSIZE           EQU               0
  USER_POOL_FIRST_WIDX      EQU               0
  USER_POOL_LAST_WIDX       EQU               0
$ENDIF








;-------------------------------------------------------------------------------------------------
; descriptor
;-------------------------------------------------------------------------------------------------
fal_descriptor_str:
_fal_descriptor_str:
  DW  LOWW(FAL_POOL_FIRST_ADDRESS),HIGHW(FAL_POOL_FIRST_ADDRESS)
  DW  LOWW(EEL_POOL_FIRST_ADDRESS),HIGHW(EEL_POOL_FIRST_ADDRESS)
  DW  LOWW(USER_POOL_FIRST_ADDRESS),HIGHW(USER_POOL_FIRST_ADDRESS)

  DW  LOWW(FAL_POOL_LAST_ADDRESS),HIGHW(FAL_POOL_LAST_ADDRESS)
  DW  LOWW(EEL_POOL_LAST_ADDRESS),HIGHW(EEL_POOL_LAST_ADDRESS)
  DW  LOWW(USER_POOL_LAST_ADDRESS),HIGHW(USER_POOL_LAST_ADDRESS)

  DW  FAL_POOL_FIRST_BLOCK
  DW  EEL_POOL_FIRST_BLOCK
  DW  USER_POOL_FIRST_BLOCK

  DW  FAL_POOL_LAST_BLOCK
  DW  EEL_POOL_LAST_BLOCK
  DW  USER_POOL_LAST_BLOCK

  DW  FAL_POOL_FIRST_WIDX
  DW  EEL_POOL_FIRST_WIDX
  DW  USER_POOL_FIRST_WIDX

  DW  FAL_POOL_LAST_WIDX
  DW  EEL_POOL_LAST_WIDX
  DW  USER_POOL_LAST_WIDX

  DW  FAL_POOL_WSIZE
  DW  EEL_POOL_WSIZE
  DW  USER_POOL_WSIZE

  DW  FAL_BLOCK_SIZE
  DW  FAL_BLOCK_WSIZE

  DB  FAL_POOL_SIZE
  DB  EEL_POOL_SIZE
  DB  USER_POOL_SIZE

  DB  00H

; -----------------------------------------------------------------------------------------------------
; ------                                                                                          -----
; ------     E N D    O F    U N T O U C H A B L E     D E C L A R A T I O N    A R E A           -----
; ------                                                                                          -----
; -----------------------------------------------------------------------------------------------------

  END


