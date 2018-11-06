;=================================================================================================
; Project      = 78K0R Flash Data access Library, MF2 single voltage flash
; Module       = fdl_descriptor.inc
; Device:      = 78K0R/Fx3
; Version      = V1.0.2
; Date         = 07.01.2010 13:59:06
;=================================================================================================
;                                  COPYRIGHT
;=================================================================================================
; Copyright (c) 2009 by NEC Electronics (Europe) GmbH,
;               a company of the NEC Electronics Corporation
;=================================================================================================
; Purpose:       contains user configuration of the FAL pool
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


$IF (__FDL_DESCRIPTOR_INC_INCLUDED)

$ELSE
$SET (__FDL_DESCRIPTOR_INC_INCLUDED)


;==============================================================================================
; constant definitions
;==============================================================================================

; specify the size of the FAL pool expressed in number of blocks
FAL_POOL_SIZE           EQU               8

; specify the size of the EEL pool inside the FAL pool expressed in blocks
EEL_POOL_SIZE           EQU               6


$ENDIF
