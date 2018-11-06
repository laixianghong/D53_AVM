; 78K0R C Compiler V2.70 Assembler Source        Date: 6 Sep 2015 Time:17:15:28

; Command   : -cf182848 -yD:\Program Files\Renesas Electronics\CubeSuite+\Devic
;             e\78K0R\Devicefile SRC\main.c -oDefaultBuild -_msgoff -qx2 -iFDL 
;             -iSelfProgramming -iSRC -iComStack\CanDriver -iComStack\CanInterf
;             ace -iComStack\CanTp -iComStack\Com -iComStack\Common -iComStack\
;             Dcm -iComStack\DTCSM -iComStack\Nm -zps -mm -mi0 -g2
; In-file   : SRC\main.c
; Asm-file  : DefaultBuild\main.asm
; Para-file : 

$PROCESSOR(F182848)
$DEBUG
$NODEBUGA
$KANJICODE SJIS
$TOL_INF	03FH, 0270H, 02H, 04000H, 00H, 00H, 00H

$DGS	FIL_NAM, .file,		0A7H,	0FFFEH,	03FH,	067H,	01H,	00H
$DGS	AUX_FIL, main.c
$DGS	MOD_NAM, main,		00H,	0FFFEH,	00H,	077H,	00H,	00H
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
$DGS	STR_STR, __TXSTATUS,	00H,	0FFFEH,	08H,	0AH,	01H,	00H
$DGS	AUX_TAG, 04H,		01BH
$DGS	MEB_STR, _Indicator,	00H,	0FFFFH,	0CH,	08H,	00H,	00H
$DGS	MEB_STR, _CurByteFlag,	01H,	0FFFFH,	0CH,	08H,	00H,	00H
$DGS	MEB_STR, _CurTransmitPos,	02H,	0FFFFH,	0CH,	08H,	00H,	00H
$DGS	MEB_STR, _bTxTimeFlag,	03H,	0FFFFH,	0CH,	08H,	00H,	00H
$DGS	END_STR, .eos,		04H,	0FFFFH,	00H,	066H,	01H,	00H
$DGS	AUX_EOS, 013H,		04H
$DGS	ENM_TAG, .1fake,	00H,	0FFFEH,	0AH,	0FH,	01H,	00H
$DGS	AUX_TAG, 01H,		02BH
$DGS	MEB_ENM, _FAL_OK,	00H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	MEB_ENM, _FAL_BUSY,	01H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	MEB_ENM, _FAL_ERR_PROTECTION,	010H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	MEB_ENM, _FAL_ERR_BLANKCHECK,	011H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	MEB_ENM, _FAL_ERR_VERIFY,	012H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	MEB_ENM, _FAL_ERR_WRITE,	013H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	MEB_ENM, _FAL_ERR_ERASE,	014H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	MEB_ENM, _FAL_ERR_PARAMETER,	020H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	MEB_ENM, _FAL_ERR_CONFIGURATION,	021H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	MEB_ENM, _FAL_ERR_INITIALIZATION,	022H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	MEB_ENM, _FAL_ERR_COMMAND,	023H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	MEB_ENM, _FAL_ERR_REJECTED,	024H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	END_STR, .eos,		01H,	0FFFFH,	00H,	066H,	01H,	00H
$DGS	AUX_EOS, 01BH,		01H
$DGS	STR_STR, .3fake,	00H,	0FFFEH,	08H,	0AH,	01H,	00H
$DGS	AUX_TAG, 03EH,		04AH
$DGS	MEB_STR, _fal_pool_first_addr_u32,	00H,	0FFFFH,	0FH,	08H,	00H,	00H
$DGS	MEB_STR, _eel_pool_first_addr_u32,	04H,	0FFFFH,	0FH,	08H,	00H,	00H
$DGS	MEB_STR, _user_pool_first_addr_u32,	08H,	0FFFFH,	0FH,	08H,	00H,	00H
$DGS	MEB_STR, _fal_pool_last_addr_u32,	0CH,	0FFFFH,	0FH,	08H,	00H,	00H
$DGS	MEB_STR, _eel_pool_last_addr_u32,	010H,	0FFFFH,	0FH,	08H,	00H,	00H
$DGS	MEB_STR, _user_pool_last_addr_u32,	014H,	0FFFFH,	0FH,	08H,	00H,	00H
$DGS	MEB_STR, _fal_pool_first_block_u16,	018H,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _eel_pool_first_block_u16,	01AH,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _user_pool_first_block_u16,	01CH,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _fal_pool_last_block_u16,	01EH,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _eel_pool_last_block_u16,	020H,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _user_pool_last_block_u16,	022H,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _fal_first_widx_u16,	024H,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _eel_first_widx_u16,	026H,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _user_first_widx_u16,	028H,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _fal_last_widx_u16,	02AH,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _eel_last_widx_u16,	02CH,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _user_last_widx_u16,	02EH,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _fal_pool_wsize_u16,	030H,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _eel_pool_wsize_u16,	032H,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _user_pool_wsize_u16,	034H,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _block_size_u16,	036H,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _block_wsize_u16,	038H,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _fal_pool_size_u08,	03AH,	0FFFFH,	0CH,	08H,	00H,	00H
$DGS	MEB_STR, _eel_pool_size_u08,	03BH,	0FFFFH,	0CH,	08H,	00H,	00H
$DGS	MEB_STR, _user_pool_size_u08,	03CH,	0FFFFH,	0CH,	08H,	00H,	00H
$DGS	MEB_STR, _fx_MHz_u08,	03DH,	0FFFFH,	0CH,	08H,	00H,	00H
$DGS	END_STR, .eos,		03EH,	0FFFFH,	00H,	066H,	01H,	00H
$DGS	AUX_EOS, 02BH,		03EH
$DGS	ENM_TAG, .0fake,	00H,	0FFFEH,	0AH,	0FH,	01H,	00H
$DGS	AUX_TAG, 01H,		054H
$DGS	MEB_ENM, _FAL_CMD_UNDEFINED,	00H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	MEB_ENM, _FAL_CMD_BLANKCHECK_WORD,	01H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	MEB_ENM, _FAL_CMD_IVERIFY_WORD,	02H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	MEB_ENM, _FAL_CMD_READ_WORD,	03H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	MEB_ENM, _FAL_CMD_WRITE_WORD,	04H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	MEB_ENM, _FAL_CMD_ERASE_BLOCK,	05H,	0FFFFH,	04H,	010H,	00H,	00H
$DGS	END_STR, .eos,		01H,	0FFFFH,	00H,	066H,	01H,	00H
$DGS	AUX_EOS, 04AH,		01H
$DGS	STR_STR, .2fake,	00H,	0FFFEH,	08H,	0AH,	01H,	00H
$DGS	AUX_TAG, 08H,		05EH
$DGS	MEB_STR, _data_u32,	00H,	0FFFFH,	0FH,	08H,	00H,	00H
$DGS	MEB_STR, _index_u16,	04H,	0FFFFH,	0EH,	08H,	00H,	00H
$DGS	MEB_STR, _command_enu,	06H,	0FFFFH,	0AH,	08H,	01H,	00H
$DGS	AUX_STR, 04AH,		00H,	01H,	00H,	00H,	00H,	00H,	00H
$DGS	MEB_STR, _status_enu,	07H,	0FFFFH,	0AH,	08H,	01H,	00H
$DGS	AUX_STR, 01BH,		00H,	01H,	00H,	00H,	00H,	00H,	00H
$DGS	END_STR, .eos,		08H,	0FFFFH,	00H,	066H,	01H,	00H
$DGS	AUX_EOS, 054H,		08H
$DGS	GLV_SYM, _delay,	U,	U,	01H,	026H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	065H,	01H,	00H
$DGS	BEG_FUN, ??bf_delay,	U,	U,	00H,	065H,	01H,	00H
$DGS	AUX_BEG, 013H,		02H,	065H
$DGS	REG_VAR, _i,		0103H,	0FFFFH,	010DH,	04H,	00H,	00H
$DGS	END_FUN, ??ef_delay,	U,	U,	00H,	065H,	01H,	00H
$DGS	AUX_END, 04H
$DGS	GLV_SYM, _Can_PortInit,	U,	U,	01H,	026H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	06BH,	01H,	00H
$DGS	BEG_FUN, ??bf_Can_PortInit,	U,	U,	00H,	065H,	01H,	00H
$DGS	AUX_BEG, 021H,		00H,	06BH
$DGS	END_FUN, ??ef_Can_PortInit,	U,	U,	00H,	065H,	01H,	00H
$DGS	AUX_END, 09H
$DGS	GLV_SYM, _R_MAIN_UserInit,	U,	U,	01H,	026H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	071H,	01H,	00H
$DGS	BEG_FUN, ??bf_R_MAIN_UserInit,	U,	U,	00H,	065H,	01H,	00H
$DGS	AUX_BEG, 02CH,		00H,	071H
$DGS	END_FUN, ??ef_R_MAIN_UserInit,	U,	U,	00H,	065H,	01H,	00H
$DGS	AUX_END, 05H
$DGS	GLV_SYM, _Can_HardwareInit,	U,	U,	01H,	026H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	077H,	01H,	00H
$DGS	BEG_FUN, ??bf_Can_HardwareInit,	U,	U,	00H,	065H,	01H,	00H
$DGS	AUX_BEG, 033H,		00H,	077H
$DGS	END_FUN, ??ef_Can_HardwareInit,	U,	U,	00H,	065H,	01H,	00H
$DGS	AUX_END, 0BH
$DGS	GLV_SYM, _main,		U,	U,	01H,	026H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	0A7H,	01H,	00H
$DGS	BEG_FUN, ??bf_main,	U,	U,	00H,	065H,	01H,	00H
$DGS	AUX_BEG, 03FH,		00H,	07BH
$DGS	BEG_BLK, ??bb00_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_BEG, 0CH,		00H,	07DH
$DGS	BEG_BLK, ??bb01_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_BEG, 017H,		00H,	081H
$DGS	END_BLK, ??eb01_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_END, 019H
$DGS	BEG_BLK, ??bb02_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_BEG, 01BH,		00H,	085H
$DGS	END_BLK, ??eb02_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_END, 01DH
$DGS	BEG_BLK, ??bb03_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_BEG, 026H,		00H,	089H
$DGS	END_BLK, ??eb03_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_END, 028H
$DGS	BEG_BLK, ??bb04_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_BEG, 02AH,		00H,	08DH
$DGS	END_BLK, ??eb04_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_END, 02CH
$DGS	BEG_BLK, ??bb05_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_BEG, 031H,		00H,	093H
$DGS	END_BLK, ??eb05_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_END, 033H
$DGS	END_BLK, ??eb00_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_END, 034H
$DGS	BEG_BLK, ??bb06_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_BEG, 036H,		00H,	095H
$DGS	BEG_BLK, ??bb07_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_BEG, 038H,		00H,	099H
$DGS	STA_SYM, _cnt,		?L0014,	U,	0CH,	03H,	01H,	00H
$DGS	AUX_STR, 00H,		039H,	01H,	00H,	00H,	00H,	00H,	00H
$DGS	BEG_BLK, ??bb08_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_BEG, 03EH,		00H,	09DH
$DGS	END_BLK, ??eb08_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_END, 040H
$DGS	BEG_BLK, ??bb09_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_BEG, 042H,		00H,	00H
$DGS	END_BLK, ??eb09_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_END, 045H
$DGS	END_BLK, ??eb07_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_END, 047H
$DGS	END_BLK, ??eb06_main,	U,	U,	00H,	064H,	01H,	00H
$DGS	AUX_END, 04AH
$DGS	END_FUN, ??ef_main,	U,	U,	00H,	065H,	01H,	00H
$DGS	AUX_END, 04BH
$DGS	GLV_SYM, _my_fal_status_enu,	U,	U,	0AH,	026H,	01H,	00H
$DGS	AUX_STR, 01BH,		00H,	01H,	00H,	00H,	00H,	00H,	00H
$DGS	GLV_SYM, _my_version_string,	U,	U,	0CH,	026H,	01H,	01H
$DGS	AUX_STR, 00H,		00H,	04H,	00H,	00H,	00H,	00H,	02H
$DGS	GLV_SYM, _request_pstr,	U,	U,	08H,	026H,	01H,	00H
$DGS	AUX_STR, 054H,		00H,	08H,	00H,	00H,	00H,	00H,	00H
$DGS	GLV_SYM, _IndirNm_Init,	U,	U,	01H,	02H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	00H,	01H,	00H
$DGS	GLV_SYM, _IndirNm_StartUp,	U,	U,	0CH,	02H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	00H,	01H,	00H
$DGS	GLV_SYM, _Cpu_InitTheSystemClock,	U,	U,	01H,	02H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	00H,	01H,	00H
$DGS	GLV_SYM, _Uart_Init,	U,	U,	01H,	02H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	00H,	01H,	00H
$DGS	GLV_SYM, _Stack_Init,	U,	U,	01H,	02H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	00H,	01H,	00H
$DGS	GLV_SYM, _Timer00_10ms_Init,	U,	U,	01H,	02H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	00H,	01H,	00H
$DGS	GLV_SYM, _fal_descriptor_str,	U,	U,	0D008H,	02H,	01H,	00H
$DGS	AUX_STR, 02BH,		00H,	03EH,	00H,	00H,	00H,	00H,	00H
$DGS	GLV_SYM, _FAL_Init,	U,	U,	0AH,	02H,	01H,	02H
$DGS	AUX_FUN, 01BH,		U,	U,	00H,	01H,	00H
$DGS	GLV_SYM, _FAL_GetVersionString,	U,	U,	0CH,	02H,	01H,	06H
$DGS	AUX_FUN, 00H,		U,	U,	00H,	01H,	08H
$DGS	GLV_SYM, _FAL_Open,	U,	U,	01H,	02H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	00H,	01H,	00H
$DGS	GLV_SYM, _FAL_Execute,	U,	U,	01H,	02H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	00H,	01H,	00H
$DGS	GLV_SYM, _FAL_Handler,	U,	U,	01H,	02H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	00H,	01H,	00H
$DGS	GLV_SYM, _FAL_Close,	U,	U,	01H,	02H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	00H,	01H,	00H
$DGS	GLV_SYM, _b10msFlag,	U,	U,	0CH,	02H,	00H,	00H
$DGS	GLV_SYM, _TxStat,	U,	U,	01008H,	02H,	01H,	00H
$DGS	AUX_STR, 013H,		00H,	04H,	00H,	00H,	00H,	00H,	00H
$DGS	GLV_SYM, _Stack_Can_Task,	U,	U,	01H,	02H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	00H,	01H,	00H
$DGS	GLV_SYM, _Stack_Uart_Task,	U,	U,	01H,	02H,	01H,	02H
$DGS	AUX_FUN, 00H,		U,	U,	00H,	01H,	00H

	EXTRN	_IndirNm_Init
	EXTRN	_IndirNm_StartUp
	EXTRN	_Cpu_InitTheSystemClock
	EXTRN	_Uart_Init
	EXTRN	_Stack_Init
	EXTRN	_Timer00_10ms_Init
	EXTRN	_fal_descriptor_str
	EXTRN	_FAL_Init
	EXTRN	_FAL_GetVersionString
	EXTRN	_FAL_Open
	EXTRN	_FAL_Execute
	EXTRN	_FAL_Handler
	EXTRN	_FAL_Close
	EXTRN	_b10msFlag
	EXTRN	_TxStat
	EXTRN	_Stack_Can_Task
	EXTRN	_Stack_Uart_Task
	PUBLIC	_delay
	PUBLIC	_my_fal_status_enu
	PUBLIC	_my_version_string
	PUBLIC	_request_pstr
	PUBLIC	_Can_PortInit
	PUBLIC	_R_MAIN_UserInit
	PUBLIC	_Can_HardwareInit
	PUBLIC	_main

@@BITS	BSEG

@@CNST	CSEG	MIRRORP

@@R_INIT	CSEG	UNIT64KP
	DB	00H	; 0
	DB	(1)

@@INIT	DSEG	BASEP
?L0014:	DS	(1)
	DS	(1)

@@DATA	DSEG	BASEP
_my_fal_status_enu:	DS	(1)
	DS	(1)
_my_version_string:	DS	(4)
_request_pstr:	DS	(8)

@@R_INIS	CSEG	UNIT64KP

@@INIS	DSEG	SADDRP

@@DATS	DSEG	SADDRP

@@CNSTL	CSEG	PAGE64KP

@@RLINIT	CSEG	UNIT64KP

@@INITL	DSEG	UNIT64KP

@@DATAL	DSEG	UNIT64KP

@@CALT	CSEG	CALLT0

; line    12
; line    13
; line    14
; line    22
; line   177
; line   342
; line   344
; line   345
; line   346
; line   347
; line   348
; line    55
; line    61
; line    69
; line    72
; line    73
; line    74
; line    75
; line    76
; line    77
; line    78
; line    79
; line    80
; line    81
; line    83
; line    84
; line    85
; line    86
; line    87
; line    88
; line    89
; line    91
; line    92
; line    94
; line    95
; line    96
; line    97
; line    98
; line    99
; line   100
; line   101
; line     7
; line     8
; line    10
; line    58
; line    59
; line    60
; line    82
; line   103
; line   112
; line   155
; line    67
; line    79
; line    98
; line   124
; line   137
; line   150
; line    68
; line    70
; line    71
; line    72
; line    73
; line    74
; line    75
; line    77
; line    78
; line    79
; line    80
; line    81
; line    82
; line    84
; line    85
; line    58
; line    66
; line    76
; line   129
; line   132
; line   134
; line   139
; line   150
; line   165
; line   171
; line   173
; line   174
; line   175
; line    55
; line    70
; line    89
; line   111
; line   117
; line   132
; line   147
; line   162
; line   172
; line   175
; line   181
; line    75
; line    65
; line    66
; line    68
; line    73
; line    75
; line    82
; line    88
; line    93
; line    98
; line   100
; line   102
; line   109
; line   111
; line   113
; line   115
; line   117
; line   123
; line   124
; line   125
; line   131
; line   132
; line    54
; line    80
; line   107
; line   116
; line    50
; line    53
; line    54
; line    70
; line    76
; line    79
; line    86
; line    96
; line    99
; line   104
; line   108
; line   113
; line   118
; line   125
; line   132
; line   136
; line   140
; line   145
; line   149
; line   154
; line   159
; line   163
; line   169
; line   173
; line   179
; line   183
; line   187
; line   193
; line   199
; line   205
; line   209
; line    48
; line    49
; line    52
; line    53
; line    56
; line    57
; line    38
; line    39
; line   157
; line   163
; line   169
; line   173
; line   179
; line   186
; line   210
; line   222
; line   257
; line   269
; line   285
; line   286
; line   287
; line   316
; line   317
; line   318
; line   324
; line   331
; line   332
; line   343
; line   345
; line   350
; line   358
; line   365
; line   372
; line   378
; line   427
; line    86
; line    87
; line    88
; line    89
; line    90
; line    93
; line    96
; line    99
; line   100
; line   101
; line   106
; line   111
; line   117
; line   122
; line   131
; line   139
; line   145
; line   151
; line   156
; line    96
; line   109
; line   118
; line   123
; line   131
; line   132
; line   141
; line   142
; line   151
; line   152
; line   159
; line   160
; line   238
; line   249
; line   261
; line   275
; line   288
; line   301
; line   313
; line   326
; line   339
; line   355
; line   364
; line   369
; line   374
; line   379
; line   384
; line   389
; line   394
; line   399
; line   404
; line   409
; line   417
; line   418
; line   419
; line   420
; line   421
; line   422
; line   423
; line   424
; line   425
; line   426
; line   435
; line   436
; line   437
; line   438
; line   439
; line   440
; line   441
; line   442
; line   443
; line   444
; line   454
; line   455
; line   456
; line   457
; line   458
; line   459
; line   460
; line   461
; line   462
; line   463
; line   470
; line   471
; line   472
; line   473
; line   474
; line   475
; line   476
; line   477
; line   478
; line   479
; line   503
; line   504
; line   510
; line   518
; line   519
; line   520
; line   523
; line   527
; line   534
; line   556
; line   557
; line   558
; line   561
; line   562
; line   563
; line   575
; line   576
; line   577
; line   578
; line   581
; line   585
; line   601
; line   608
; line   613
; line   627
; line   628
; line   632
; line    66
; line    71
; line    80
; line    85
; line    90
; line    95
; line   101
; line   107
; line   112
; line   117
; line   122
; line   133
; line   138
; line   143
; line   148
; line   153
; line   158
; line   163
; line   168
; line    46
; line    53
; line    60
; line    66
; line    74
; line    79
; line    85
; line    93
; line    99
; line   105
; line   132
; line   149
; line   156
; line   166
; line   202
; line   225
; line   239
; line   252
; line   269
; line   274
; line   275
; line   276
; line   287
; line   291
; line   306
; line   329
; line   330
; line   331
; line   332
; line   333
; line   334
; line   338
; line   339
; line   340
; line   341
; line   342
; line   343
; line   344
; line   352
; line   353
; line   354
; line   355
; line   356
; line   357
; line   358
; line   359
; line   360
; line   361
; line   362
; line   368
; line   380
; line   381
; line   387
; line   262
; line   263
; line   268
; line   269
; line   278
; line   286
; line   298
; line   310
; line   315
; line   322
; line   329
; line   347
; line   357
; line   359
; line   360
; line   378
; line   392
; line   402
; line   418
; line   426
; line   441
; line   449
; line   454
; line   463
; line   474
; line   484
; line   506
; line   507
; line   508
; line   510
; line   516
; line   517
; line   520
; line   524
; line   549
; line   553
; line   557
; line   581
; line   582
; line   583
; line   584
; line   586
; line   587
; line   588
; line   589
; line   591
; line   593
; line   594
; line   595
; line   596
; line   597
; line   599
; line   600
; line   601
; line   602
; line   603
; line   604
; line   605
; line   606
; line   607
; line   608
; line   609
; line   610
; line   611
; line   612
; line   617
; line   618
; line   619
; line   620
; line   621
; line   623
; line   624
; line   625
; line   626
; line   628
; line   629
; line   631
; line   632
; line   633
; line   634
; line   636
; line   637
; line   638
; line   639
; line   640
; line   641
; line   642
; line   643
; line   644
; line   645
; line   646
; line   647
; line   648
; line   649
; line   651
; line   652
; line    79
; line   138
; line   139
; line   146
; line   149
; line   150
; line   160
; line   163
; line   166
; line   167
; line   168
; line   169
; line   170
; line   171
; line   172
; line   173
; line   174
; line   175
; line   176
; line   177
; line   178
; line   181
; line   182
; line   184
; line   237
; line   241
; line   251
; line   255
; line   259
; line   263
; line   269
; line   275
; line   279
; line   291
; line   298
; line   304
; line   310
; line   317
; line   324
; line   331
; line   352
; line   356
; line   364
; line   385
; line   392
; line   399
; line   403
; line   407
; line   411
; line   426
; line   433
; line    39
; line    40
; line    41
; line    42
; line    43
; line    44
; line    45
; line    48
; line    49
; line    50
; line    51
; line    52
; line    53
; line    19

@@CODEL	CSEG
_delay:
$DGL	1,94
	push	hl						;[INF] 1, 1
??bf_delay:
; line    21
$DGL	0,3
	clrw	ax						;[INF] 1, 1
	movw	hl,ax						;[INF] 1, 1
?L0003:
	movw	ax,hl						;[INF] 1, 1
	cmpw	ax,#02710H	; 10000 			;[INF] 3, 1
	bnc	$?L0004						;[INF] 2, 4
	incw	hl						;[INF] 1, 1
	br	$?L0003						;[INF] 2, 3
?L0004:
; line    22
$DGL	0,4
??ef_delay:
	pop	hl						;[INF] 1, 1
	ret							;[INF] 1, 6
??ee_delay:
; line    24
; line    25
; line    28
; line    30
; line    33
_Can_PortInit:
$DGL	1,101
??bf_Can_PortInit:
; line    34
$DGL	0,2
	mov	a,STSEL						;[INF] 2, 1
	or	a,#080H	; 128 					;[INF] 2, 1
	mov	STSEL,a						;[INF] 2, 1
; line    35
$DGL	0,3
	or	P1,#01H	; 1 					;[INF] 3, 2
; line    36
$DGL	0,4
	mov	a,PM1						;[INF] 2, 1
	and	a,#0FEH	; 254 					;[INF] 2, 1
	mov	PM1,a						;[INF] 2, 1
; line    39
$DGL	0,7
	clr1	P1.2						;[INF] 3, 2
; line    40
$DGL	0,8
	clr1	PM1.2						;[INF] 3, 2
; line    41
$DGL	0,9
??ef_Can_PortInit:
	ret							;[INF] 1, 6
??ee_Can_PortInit:
; line    44
_R_MAIN_UserInit:
$DGL	1,107
??bf_R_MAIN_UserInit:
; line    48
$DGL	0,5
??ef_R_MAIN_UserInit:
	ei							;[INF] 3, 4
	ret							;[INF] 1, 6
??ee_R_MAIN_UserInit:
; line    51
_Can_HardwareInit:
$DGL	1,113
??bf_Can_HardwareInit:
; line    52
$DGL	0,2
	clr1	MK2H.0						;[INF] 3, 2
; line    53
$DGL	0,3
	clr1	MK2L.7						;[INF] 3, 2
; line    54
$DGL	0,4
	clr1	MK2L.6						;[INF] 3, 2
; line    55
$DGL	0,5
	clr1	MK2L.5						;[INF] 3, 2
; line    57
$DGL	0,7
	call	!!_IndirNm_Init					;[INF] 4, 3
; line    58
$DGL	0,8
	call	!!_IndirNm_StartUp				;[INF] 4, 3
; line    60
$DGL	0,10
	br	!!_R_MAIN_UserInit				;[INF] 4, 3
??ef_Can_HardwareInit:
??ee_Can_HardwareInit:
; line    63
_main:
$DGL	1,119
??bf_main:
; line    64
$DGL	0,2
	call	!!_Cpu_InitTheSystemClock			;[INF] 4, 3
; line    65
$DGL	0,3
	call	!!_Uart_Init					;[INF] 4, 3
; line    66
$DGL	0,4
nop
; line    67
$DGL	0,5
	call	!!_Stack_Init					;[INF] 4, 3
; line    68
$DGL	0,6
	call	!!_Can_HardwareInit				;[INF] 4, 3
; line    69
$DGL	0,7
	call	!!_Timer00_10ms_Init				;[INF] 4, 3
; line    71
$DGL	0,9
	movw	ax,#loww (_fal_descriptor_str)			;[INF] 3, 1
	mov	c,#highw (_fal_descriptor_str)			;[INF] 2, 1
	clrb	b						;[INF] 1, 1
	call	!!_FAL_Init					;[INF] 4, 3
	mov	a,c						;[INF] 1, 1
	mov	!_my_fal_status_enu,a				;[INF] 3, 1
; line    73
$DGL	0,11
	cmp0	!_my_fal_status_enu				;[INF] 3, 1
	skz							;[INF] 2, 1
	br	$!?L0015					;[INF] 3, 3
; line    74
??bb00_main:
; line    75
$DGL	0,13
	call	!!_FAL_GetVersionString				;[INF] 4, 3
	movw	ax,bc						;[INF] 1, 1
	movw	!_my_version_string,ax				;[INF] 3, 1
	mov	a,e						;[INF] 1, 1
	mov	!_my_version_string+2,a				;[INF] 3, 1
; line    76
$DGL	0,14
	call	!!_FAL_Open					;[INF] 4, 3
; line    77
$DGL	0,15
	clrw	ax						;[INF] 1, 1
	movw	!_request_pstr,ax				;[INF] 3, 1
	movw	!_request_pstr+2,ax				;[INF] 3, 1
; line    78
$DGL	0,16
	movw	!_request_pstr+4,ax				;[INF] 3, 1
; line    79
$DGL	0,17
	mov	!_request_pstr+6,#03H	; 3 			;[INF] 4, 1
; line    81
$DGL	0,19
	movw	ax,#loww (_request_pstr)			;[INF] 3, 1
	call	!!_FAL_Execute					;[INF] 4, 3
; line    82
$DGL	0,20
	call	!!_FAL_Handler					;[INF] 4, 3
; line    84
$DGL	0,22
?L0017:
	cmp	!_request_pstr+7,#01H	; 1 			;[INF] 4, 1
	bnz	$?L0018						;[INF] 2, 4
; line    85
??bb01_main:
; line    86
$DGL	0,24
	call	!!_FAL_Handler					;[INF] 4, 3
??eb01_main:
; line    87
$DGL	0,25
	br	$?L0017						;[INF] 2, 3
?L0018:
; line    88
$DGL	0,26
	cmp0	!_request_pstr+7				;[INF] 3, 1
	skz							;[INF] 2, 1
; line    89
??bb02_main:
; line    90
$DGL	0,28
	call	!!_FAL_Handler					;[INF] 4, 3
??eb02_main:
; line    91
?L0019:
?L0020:
; line    93
$DGL	0,31
	movw	ax,#05678H	; 22136 			;[INF] 3, 1
	movw	!_request_pstr,ax				;[INF] 3, 1
	movw	ax,#01234H	; 4660 				;[INF] 3, 1
	movw	!_request_pstr+2,ax				;[INF] 3, 1
; line    94
$DGL	0,32
	clrw	ax						;[INF] 1, 1
	movw	!_request_pstr+4,ax				;[INF] 3, 1
; line    95
$DGL	0,33
	mov	!_request_pstr+6,#04H	; 4 			;[INF] 4, 1
; line    97
$DGL	0,35
	movw	ax,#loww (_request_pstr)			;[INF] 3, 1
	call	!!_FAL_Execute					;[INF] 4, 3
; line    98
$DGL	0,36
	call	!!_FAL_Handler					;[INF] 4, 3
; line    99
$DGL	0,37
?L0021:
	cmp	!_request_pstr+7,#01H	; 1 			;[INF] 4, 1
	bnz	$?L0022						;[INF] 2, 4
; line   100
??bb03_main:
; line   101
$DGL	0,39
	call	!!_FAL_Handler					;[INF] 4, 3
??eb03_main:
; line   102
$DGL	0,40
	br	$?L0021						;[INF] 2, 3
?L0022:
; line   103
$DGL	0,41
	cmp0	!_request_pstr+7				;[INF] 3, 1
	skz							;[INF] 2, 1
; line   104
??bb04_main:
; line   105
$DGL	0,43
	call	!!_FAL_Handler					;[INF] 4, 3
??eb04_main:
; line   106
?L0023:
?L0024:
; line   108
$DGL	0,46
	mov	!_request_pstr+6,#03H	; 3 			;[INF] 4, 1
; line   110
$DGL	0,48
	cmp0	!_request_pstr+7				;[INF] 3, 1
	sknz							;[INF] 2, 1
; line   111
??bb05_main:
; line   112
$DGL	0,50
	call	!!_FAL_Close					;[INF] 4, 3
??eb05_main:
; line   113
?L0025:
?L0026:
??eb00_main:
; line   114
?L0015:
?L0016:
; line   115
?L0027:
; line   116
??bb06_main:
; line   117
$DGL	0,55
	cmp0	!_b10msFlag					;[INF] 3, 1
	bz	$?L0029						;[INF] 2, 4
; line   118
??bb07_main:
; line   119
; line   121
$DGL	0,59
	clrb	!_b10msFlag					;[INF] 3, 1
; line   122
$DGL	0,60
	inc	!?L0014	; cnt 					;[INF] 3, 2
; line   123
$DGL	0,61
	mov	a,!?L0014	; cnt 				;[INF] 3, 1
	and	a,#03H	; 3 					;[INF] 2, 1
	cmp0	a						;[INF] 1, 1
	bnz	$?L0031						;[INF] 2, 4
; line   124
??bb08_main:
; line   125
$DGL	0,63
	mov	a,!_TxStat+3					;[INF] 3, 1
	or	a,#020H	; 32 					;[INF] 2, 1
	mov	!_TxStat+3,a					;[INF] 3, 1
??eb08_main:
; line   126
?L0031:
?L0032:
; line   127
$DGL	0,65
	cmp	!?L0014,#014H	; cnt,20 			;[INF] 4, 1
	bc	$?L0033						;[INF] 2, 4
; line   128
??bb09_main:
; line   129
$DGL	0,67
	clrb	!?L0014	; cnt 					;[INF] 3, 1
; line   130
$DGL	0,68
	mov	a,!_TxStat+3					;[INF] 3, 1
	or	a,#08H	; 8 					;[INF] 2, 1
	mov	!_TxStat+3,a					;[INF] 3, 1
??eb09_main:
; line   131
?L0033:
?L0034:
; line   132
$DGL	0,70
	call	!!_Stack_Can_Task				;[INF] 4, 3
??eb07_main:
; line   133
?L0029:
?L0030:
; line   135
$DGL	0,73
	call	!!_Stack_Uart_Task				;[INF] 4, 3
??eb06_main:
; line   136
$DGL	0,74
	br	$?L0027						;[INF] 2, 3
?L0028:
; line   137
$DGL	0,75
??ef_main:
	ret							;[INF] 1, 6
??ee_main:

@@CODE	CSEG	BASE

@@BASE	CSEG	BASE
	END


; *** Code Information ***
;
; $FILE E:\lxh\Work\06_DFSK Motor\F507\BirdView Camera\360View\SRC\main.c
;
; $FUNC delay(19)
;	void=(void)
;	CODE SIZE= 14 bytes, CLOCK_SIZE= 20 clocks, STACK_SIZE= 2 bytes
;
; $FUNC Can_PortInit(33)
;	void=(void)
;	CODE SIZE= 22 bytes, CLOCK_SIZE= 18 clocks, STACK_SIZE= 0 bytes
;
; $FUNC R_MAIN_UserInit(44)
;	void=(void)
;	CODE SIZE= 4 bytes, CLOCK_SIZE= 10 clocks, STACK_SIZE= 0 bytes
;
; $FUNC Can_HardwareInit(51)
;	void=(void)
;	CODE SIZE= 24 bytes, CLOCK_SIZE= 17 clocks, STACK_SIZE= 4 bytes
;
; $CALL IndirNm_Init(57)
;	void=(void)
;
; $CALL IndirNm_StartUp(58)
;	bc=(void)
;
; $CALL R_MAIN_UserInit(60)
;	void=(void)
;
; $FUNC main(63)
;	void=(void)
;	CODE SIZE= 224 bytes, CLOCK_SIZE= 144 clocks, STACK_SIZE= 4 bytes
;
; $CALL Cpu_InitTheSystemClock(64)
;	void=(void)
;
; $CALL Uart_Init(65)
;	void=(void)
;
; $CALL Stack_Init(67)
;	void=(void)
;
; $CALL Can_HardwareInit(68)
;	void=(void)
;
; $CALL Timer00_10ms_Init(69)
;	void=(void)
;
; $CALL FAL_Init(71)
;	bc=(pointer:ax,bc)
;
; $CALL FAL_GetVersionString(75)
;	bc,de=(void)
;
; $CALL FAL_Open(76)
;	void=(void)
;
; $CALL FAL_Execute(81)
;	void=(pointer:ax)
;
; $CALL FAL_Handler(82)
;	void=(void)
;
; $CALL FAL_Handler(86)
;	void=(void)
;
; $CALL FAL_Handler(90)
;	void=(void)
;
; $CALL FAL_Execute(97)
;	void=(pointer:ax)
;
; $CALL FAL_Handler(98)
;	void=(void)
;
; $CALL FAL_Handler(101)
;	void=(void)
;
; $CALL FAL_Handler(105)
;	void=(void)
;
; $CALL FAL_Close(112)
;	void=(void)
;
; $CALL Stack_Can_Task(132)
;	void=(void)
;
; $CALL Stack_Uart_Task(135)
;	void=(void)

; Target chip : uPD78F1828_48
; Device file : V1.01 
