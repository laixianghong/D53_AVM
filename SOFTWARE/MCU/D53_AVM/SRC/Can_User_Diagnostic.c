#include 	"cpu.h"
#include	"Can_User_Diagnostic.h"
unsigned char tttest = 0;
void Reset_ECU (void);
void	Can_Diagnostic_HardwareReset (void)
{
	tttest ++;
	WDTE = 0x03;
	Reset_ECU();
	//__asm("BR FFFF0H");
}