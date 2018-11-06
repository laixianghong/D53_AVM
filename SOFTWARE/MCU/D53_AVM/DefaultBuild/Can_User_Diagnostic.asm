; 78K0R C Compiler V2.70 Assembler Source        Date: 6 Sep 2015 Time:10:57:06

; Command   : -cf182848 -yD:\Program Files\Renesas Electronics\CubeSuite+\Devic
;             e\78K0R\Devicefile SRC\Can_User_Diagnostic.c -oDefaultBuild -_msg
;             off -nq -iFDL -iSelfProgramming -iSRC -iComStack\CanDriver -iComS
;             tack\CanInterface -iComStack\CanTp -iComStack\Com -iComStack\Comm
;             on -iComStack\Dcm -iComStack\DTCSM -iComStack\Nm -zps -mm -mi0 -g
;             2
; In-file   : SRC\Can_User_Diagnostic.c
; Asm-file  : DefaultBuild\Can_User_Diagnostic.asm
; Para-file : 

$PROCESSOR(F182848)
$DEBUG
$NODEBUGA
$KANJICODE SJIS
$TOL_INF	03FH, 0270H, 02H, 04000H, 00H, 00H, 00H

$DGS	FIL_NAM, .file,		019H,	0FFFEH,	03FH,	067H,	01H,	00H
$DGS	AUX_FIL, Can_User_Diagnostic.c
$DGS	MOD_NAM, Can_User_Diagnostic,	00H,	0FFFEH,	00H,	077H,	00H,	00H
$DGS	SEC_NAM, @@BITS,	U,	U,	00H,	078H,	00H,	00H
$DGS	SEC_NAM, @@CNST,	U,	U,	00H,	078H,	00H,	00H
$DGS	SEC_NAM, @@R_INIT,	U,	U,	00H,	078H,	00H,	00H
$DGS	SEC_NAM, @@INIT,	U,	U,	00H,	078H,	00H,	00H
$DGS	SEC_NAM, @@DATA,	U,	U,	00H,	078H,	00H,	00H
$DGS	SEC_NAM, @@R_INIS,	U,	U,	00H,	078H,	00H,	00H
$DGS	SEC_NAM, @@INIS,	U,	U,	00H,	078H,	00H,	00H
$DGS	SEC_NAM, @@DATS,	U,	U,	00H,	078H,	00H,	00H
$DGS	SEC_NAM, @@CNSTL,	U,	U,	00H,	078H,	00H,	00H
$DGS	SEC_NAM, @@RLINIT,	U,	U,	00H,	078H,	00H,	00H
$DGS	SEC_NAM, @@INITL,	U,	U,	00H,	078H,	00H,	00H
$DGS	SEC_NAM, @@DATAL,	U,	U,	00H,	078H,	00H,	00H
$DGS	SEC_NAM, @@CALT,	U,	U,	00H,	078H,	00H,	00H
$DGS	SEC_NAM, @@CODE,	U,	U,	00H,	078H,	00H,	00H
$DGS	SEC_NAM, @@CODEL,	U,	U,	00H,	078H,	00H,	00H
$DGS	SEC_NAM, @@BASE,	U,	U,	00H,	078H,	00H,	00H
$DGS	GLV_SYM, _Can_Diagnostic_HardwareReset,	U,	U,	01H,	026H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	019H,	01H,	00H
$DGS	BEG_FUN, ??bf_Can_Diagnostic_HardwareReset,	U,	U,	00H,	065H,	01H,	00H
$DGS	AUX_BEG, 05H,		00H,	019H
$DGS	END_FUN, ??ef_Can_Diagnostic_HardwareReset,	U,	U,	00H,	065H,	01H,	00H
$DGS	AUX_END, 04H
$DGS	GLV_SYM, _tttest,	U,	U,	0CH,	026H,	00H,	00H

	PUBLIC	_tttest
	PUBLIC	_Can_Diagnostic_HardwareReset

@@BITS	BSEG

@@CNST	CSEG	MIRRORP

@@R_INIT	CSEG	UNIT64KP
	DB	00H	; 0
	DB	(1)

@@INIT	DSEG	BASEP
_tttest:	DS	(1)
	DS	(1)

@@DATA	DSEG	BASEP

@@R_INIS	CSEG	UNIT64KP

@@INIS	DSEG	SADDRP

@@DATS	DSEG	SADDRP

@@CNSTL	CSEG	PAGE64KP

@@RLINIT	CSEG	UNIT64KP

@@INITL	DSEG	UNIT64KP

@@DATAL	DSEG	UNIT64KP

@@CALT	CSEG	CALLT0

; line    11
; line    12
; line    13
; line    21
; line     3
; line     5

@@CODEL	CSEG
_Can_Diagnostic_HardwareReset:
$DGL	1,19
??bf_Can_Diagnostic_HardwareReset:
; line     6
$DGL	0,2
	inc	!_tttest					;[INF] 3, 2
; line     7
$DGL	0,3
BR FFFF0H
; line     8
$DGL	0,4
??ef_Can_Diagnostic_HardwareReset:
	ret							;[INF] 1, 6
??ee_Can_Diagnostic_HardwareReset:

@@CODE	CSEG	BASE

@@BASE	CSEG	BASE
	END


; *** Code Information ***
;
; $FILE E:\lxh\Work\06_DFSK Motor\F507\BirdView Camera\360View\SRC\Can_User_Dia
;	gnostic.c
;
; $FUNC Can_Diagnostic_HardwareReset(5)
;	void=(void)
;	CODE SIZE= 4 bytes, CLOCK_SIZE= 8 clocks, STACK_SIZE= 0 bytes

; Target chip : uPD78F1828_48
; Device file : V1.01 
