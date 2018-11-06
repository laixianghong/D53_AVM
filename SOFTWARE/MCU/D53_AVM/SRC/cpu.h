#ifndef	_CPU_H_
#define _CPU_H_

#pragma sfr
#pragma DI
#pragma EI
#pragma NOP
#pragma HALT
#pragma STOP



typedef	unsigned char 	BYTE;
typedef	unsigned short 	WORD;
typedef	unsigned long 	DWORD;

#define 	TRUE		1
#define 	FALSE   	0
#define 	UCHAR		BYTE
#define 	BOOL		BYTE
#define		ENABLE		1
#define 	DISABLE		0
void Cpu_InitTheSystemClock (void);

/* High-speed system clock pin operation mode (EXCLK, OSCSEL) */
#define	_C0_CG_HISYS_PIN		0xC0U
#define	_00_CG_HISYS_PORT		0x00U	/* X1, X2 as I/O port */
#define	_40_CG_HISYS_OSC		0x40U	/* X1, X2 as crystal/ceramic resonator connection */
#define	_80_CG_HISYS_PORT1		0x80U	/* X1, X2 as I/O port */
#define	_C0_CG_HISYS_EXT		0xC0U	/* X1 as external clock input, X2 as I/O port */
/* Subsystem clock pin operation mode (EXCLKS, OSCSELS) */
#define	_30_CG_SUB_PIN			0x30U
#define	_00_CG_SUB_PORT			0x00U	/* EXCLKS as I/O port	*/
#define	_30_CG_SUB_EXT			0x30U	/* EXCLKS as external clock input */
/* Control of high-speed system clock oscillation frequency (AMPH) */
#define	_00_CG_SYSOSC_UNDER10M		0x00U	/* 2MHz <= fMX <= 10MHz */
#define	_01_CG_SYSOSC_OVER10M		0x01U	/* 10MHz < fMX <= 20MHz */

/*
	Clock operation status control register (CSC)
*/
/* Control of high-speed system clock operation (MSTOP) */
#define	_00_CG_HISYS_OPER		0x00U	/* X1 oscillator/external clock operating */
#define	_80_CG_HISYS_STOP		0x80U	/* X1 oscillator/external clock stopped */
/* Subsystem clock operation (XTSTOP) */
#define	_00_CG_SUB_OPER			0x00U	/* external clock from EXCLK pin is valid */
#define	_40_CG_SUB_STOP			0x40U	/* external clock from EXCLK pin is invalid */
/* Internal high-speed oscillator operation (HIOSTOP) */
#define	_00_CG_HIO_OPER			0x00U	/* internal high-speed oscillator operating */
#define	_01_CG_HIO_STOP			0x01U	/* internal high-speed oscillator stopped */

/*
	Oscillation stabilization time counter status register (OSTC)
*/
/* Oscillation stabilization time status (MOST8 - MOST18) */
#define	_FF_CG_OSCSTAB_STATUS		0xFFU
#define	_00_CG_OSCSTAB_STA0		0x00U	/* < 2^8/fx */
#define	_80_CG_OSCSTAB_STA8		0x80U	/* 2^8/fx */
#define	_C0_CG_OSCSTAB_STA9		0xC0U	/* 2^9/fx */
#define	_E0_CG_OSCSTAB_STA10		0xE0U	/* 2^10/fx */
#define	_F0_CG_OSCSTAB_STA11		0xF0U	/* 2^11/fx */
#define	_F8_CG_OSCSTAB_STA13		0xF8U	/* 2^13/fx */
#define	_FC_CG_OSCSTAB_STA15		0xFCU	/* 2^15/fx */
#define	_FE_CG_OSCSTAB_STA17		0xFEU	/* 2^17/fx */
#define	_FF_CG_OSCSTAB_STA18		0xFFU	/* 2^18/fx */

/*
	Oscillation stabilization time select register (OSTS)
*/
/* Oscillation stabilization time selection (OSTS2 - OSTS0) */
#define	_07_CG_OSCSTAB_SEL		0x07U
#define	_00_CG_OSCSTAB_SEL8		0x00U	/* 2^8/fx */
#define	_01_CG_OSCSTAB_SEL9		0x01U	/* 2^9/fx */
#define	_02_CG_OSCSTAB_SEL10		0x02U	/* 2^10/fx */
#define	_03_CG_OSCSTAB_SEL11		0x03U	/* 2^11/fx */
#define	_04_CG_OSCSTAB_SEL13		0x04U	/* 2^13/fx */
#define	_05_CG_OSCSTAB_SEL15		0x05U	/* 2^15/fx */
#define	_06_CG_OSCSTAB_SEL17		0x06U	/* 2^17/fx */
#define	_07_CG_OSCSTAB_SEL18		0x07U	/* 2^18/fx */

/*
	System clock control register (CKC)
*/
/* Status of CPU/peripheral hardware clock fCLK (CLS) */
#define	_00_CG_CPUCLK_FPLL		0x00U	/* PLL clock (fPLL) being selected */
#define	_80_CG_CPUCLK_FIL		0x80U	/* internal low-speed oscillation clock (fIL) being selected */
/* Selection of CPU/peripheral hardware clock fCLK (CSS) */
#define	_00_CG_CPUCLK_SELFPLL		0x00U	/* PLL clock (fPLL) */
#define	_40_CG_CPUCLK_SELFIL		0x40U	/* internal low-speed oscillation clock (fIL) */
/* Status of Main system clock fMAIN (MCS) */
#define	_00_CG_MAINCLK_HIO		0x00U	/* internal high-speed oscillation clock (fIH) */
#define	_20_CG_MAINCLK_HISYS		0x20U	/* high-speed system clock (fMX) */
/* Selection of Main system clock fMAIN (MCM0) */
#define	_00_CG_MAINCLK_SELHIO		0x00U	/* internal high-speed oscillation clock (fIH) */
#define	_10_CG_MAINCLK_SELHISYS		0x10U	/* high-speed system clock (fMX) */
/* CPU clock (fCPU) selection (MDIV2 - MDIV0) */
#define	_07_CG_CPUCLK			0x07U
#define	_00_CG_CPUCLK_MAIN0		0x00U	/* fCLK = fPLL */
#define	_01_CG_CPUCLK_MAIN1		0x01U	/* fCLK = fPLL/2 (default) */
#define	_02_CG_CPUCLK_MAIN2		0x02U	/* fCLK = fPLL/2^2 */
#define	_03_CG_CPUCLK_MAIN3		0x03U	/* fCLK = fPLL/2^3 */
#define	_04_CG_CPUCLK_MAIN4		0x04U	/* fCLK = fPLL/2^4 */
#define	_05_CG_CPUCLK_MAIN5		0x05U	/* fCLK = fPLL/2^5 */

/*
	Operation speed mode control register (OSMC)
*/
/* Selection the clock frequency (fCLK) of data flash (DMSTP) */
#define	_00_CG_FCLK_UNDER20M		0x00U	/* fCLK <= 20 MHz */
#define	_04_CG_FCLK_OVER20M		0x04U	/* fCLK > 20 MHz */
/* Selection the clock frequency (fCLK) of code flash (FSEL) */
#define	_00_CG_FCLK_UNDER10M		0x00U	/* fCLK <= 10 MHz */
#define	_01_CG_FCLK_OVER10M		0x01U	/* fCLK > 10 MHz */

/*
	PLL clock control register (PLLCTL)
*/
/* Lockup wait counter setting value (LCKSEL1, LCKSEL0) */
#define	_C0_CG_PLL_LCK			0xC0U
#define	_00_CG_PLLLOCKUP_SEL0		0x00U	/* 2^8/fPLLI */
#define	_40_CG_PLLLOCKUP_SEL1		0x40U	/* 2^9/fPLLI */
#define	_80_CG_PLLLOCKUP_SEL2		0x80U	/* 2^10/fPLLI */
/* PLL output clock (fPLLO) selection (PLLDIV1) */
#define	_00_CG_FPLLO_DIV1		0x00U	/* does not operate PLL output divider */
#define	_20_CG_FPLLO_DIV2		0x20U	/* operates PLL output half divider */
/* PLL input clock (fPLLI) selection (PLLDIV0) */
#define	_00_CG_FPLLI_DIV1		0x00U	/* does not operate PLL output divider */
#define	_10_CG_FPLLI_DIV2		0x10U	/* operates PLL output half divider */
/* Clock mode selection (SELPLL) */
#define	_00_CG_PLL_FMAIN		0x00U	/* clock through mode (fMAIN) */
#define	_04_CG_PLL_FPLL			0x04U	/* PLL clock select mode (fPLL) */
/* PLL operation control (PLLON) */
#define	_00_CG_PLL_OFF			0x00U	/* stops PLL */
#define	_01_CG_PLL_ON			0x01U	/* operates PLL */

/*
	PLL Clock Status Register (PLLSTS)
*/
/* PLL lock state (LOCK) */
#define	_00_CG_PLLSTATUS_LOCK		0x00U	/* unlocked state */
#define	_80_CG_PLLSTATUS_UNLOCK		0x80U	/* locked state */
/* State of the clock mode (SELPLLS) */
#define	_00_CG_CPUCLK_CLKTHROUGH	0x00U	/* clock through mode (fMAIN) */
#define	_08_CG_CPUCLK_PLL		0x08U	/* PLL clock select mode (fPLL) */

/*
	Specific-register manipulation protection register (GUARD)
*/
/* Protection against manipulation of PLL clock control register (GDPLL) */
#define	_00_CG_PLLCTL_DIWR		0x00U	/* disables manipulation of PLLCTL register */
#define	_02_CG_PLLCTL_ENWR		0x02U	/* enables manipulation of PLLCTL register */
/* Protection against manipulation of clock operation status control register (GDCSC) */
#define	_00_CG_CSC_DIWR			0x00U	/* disables manipulation of CSC register */
#define	_01_CG_CSC_ENWR			0x01U	/* enables manipulation of CSC register */
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
#define CG_SUBWAITTIME			120U	/* change the waiting time according to the system */
enum ClockMode
{
	HIOCLK, SYSX1CLK, SYSEXTCLK, FILCLK
};
enum CPUClock
{
	SYSTEMCLOCK, SYSONEHALF, SYSONEFOURTH, SYSONEEIGHTH, SYSONESIXTEENTH, SYSONETHIRTYSECOND
};
enum PSLevel
{
	PSSTOP, PSHALT
};
enum StabTime
{
	STLEVEL0, STLEVEL1, STLEVEL2, STLEVEL3, STLEVEL4, STLEVEL5, STLEVEL6, STLEVEL7
};

void 	 Cpu_FeedDog	(void);
void 	Cpu_Reset (void);
#define		Can_SendSignal(x)	Com_SendSignal(COM_TXSIG##x,&x)
#define		Can_ReceSignal(x)	Com_ReceiveSignal(COM_RXSIG##x,&x)
#endif