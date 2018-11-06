#include "cpu.h"

void Cpu_InitTheSystemClock (void)
{
  //CMC = 0x41;           //先配置X1震荡引脚，X1震荡模式，频率2M~Fx~20M
  //OSTS = 0x07;          //等待时间11.31ms
  //GDCSC = 1;            // 允许设置CSC寄存器
  //CKC = 0x10;
  //CSC = 0x41;           //X1起振，禁止外部时钟，停止内部高速振荡器
  //while(OSTC != 0xFF); 	//等待稳定下来
  	unsigned char temp_stabset, temp_stabwait;

	/* Set fMX */
	CMC = _40_CG_HISYS_OSC | _01_CG_SYSOSC_OVER10M | _00_CG_SUB_PORT;
	OSTS = _07_CG_OSCSTAB_SEL18;
	GUARD |= _01_CG_CSC_ENWR;
	MSTOP = 0U;
	temp_stabset = _FF_CG_OSCSTAB_STA18;
	do
	{
		temp_stabwait = OSTC;
		temp_stabwait &= temp_stabset;
	}
	while (temp_stabwait != temp_stabset);
	/* Set fMAIN */
	DI();
	OSMC = _00_CG_FCLK_UNDER20M | _01_CG_FCLK_OVER10M;
	NOP();
	NOP();
	EI();
	MCM0 = 1U;
	/* Set fSUB */
	XTSTOP = 1U;
	/* Set fCLK */
	CSS = 0U;
	CKC &= (UCHAR)~_07_CG_CPUCLK;
	CKC |= _00_CG_CPUCLK_MAIN0;
	/* Set fIH */
	HIOSTOP = 1U;
	GUARD &= (UCHAR)~_01_CG_CSC_ENWR;
}

 void 	  Cpu_FeedDog	(void)
{
	WDTE = 0xAC;
}

void 	Cpu_Reset (void)
{
    WDTE = 0xAA;
    for(;;)
    {
    }
}