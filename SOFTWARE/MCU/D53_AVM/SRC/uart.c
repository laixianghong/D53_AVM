#pragma interrupt INTLR0 Uart_Isp_Rxd
#pragma interrupt INTLT0 Uart_Isp_Txd
#pragma interrupt INTLS0 Uart_Isp_Err

#include "uart.h"
#include "Stack.h"
UART Uart;
void Uart_Init(void)
{
	LIN0EN = 1U;   	// Enable Lin1 module
	// UF1CTL0
	UF0TXE = 0U;   	// Disable Rx and Tx operation
	UF0RXE = 0U;
	UF0CTL0 |= _10_UARTF_TRANSFDIR_LSB; // LSB first default
	UF0CTL0 |= _00_UARTF_PARITY_NONE;   // No parity
	UF0CTL0 |= _02_UARTF_DATALENGTH_8BIT;	// Char length
	UF0CTL0 |= _00_UARTF_STOPLENGTH_1BIT;   // One stop bit
	// Pin select
	//STSEL |= 0x80;  // Selecet pin P72 and P73 as LTxD1 and LRxD1

	// UF1CTL1
	//UF1CTL1 |= _0000_UARTF_BASECLK_1;  // Prescale frequency divided not used
	UF0CTL1 = /*70*/417;/* 16,000,000 / 417/2 = 19184.65*/		           // Dedicated baudrate generator divided by 70, 16,000,000/70/2 = 114285.7	
	// UF1OPT0
	UF0OPT0 |= (0x03);  // Normal Txd level output and normal rxd level input
	// UF1OPT1
	UF0OPT1 |= _00_UARTF_EXPANSIONBIT_UNUSE;
	UF0OPT1 |= _00_UARTF_NORMAL_MODE;
	// UF1OPT2
	UF0OPT2 = 0x03;   //Do not use noise filter,Outputs transmission interrupt request upon transmission completion
	// Set LTXD1 pin 
	PM1.3 = 0;   // LTxD1 output
	P1.3 = 1;    // Output '1'
	// Set LRXD1 pin 
	PM1.4 = 1;   // LRxD1 input
	P1.4 = 1;    // May be '0' or '1'
	// Interrupt
	LTMK0 = 0U;	/* disable INTLT1 interrupt */
	LTIF0 = 0U;	/* clear INTLT1 interrupt flag */
	LRMK0 = 0U;	/* disable INTLR1 interrupt */
	LRIF0 = 0U;	/* clear INTLR1 interrupt flag */
	LSMK0= 0U;	/* disable INTLS1 interrupt */
	LSIF0 = 0U;	/* clear INTLS1 interrupt flag */
	/* Set INTLT0 low priority */
	//LTPR10 = 1U;
	//LTPR00 = 1U;
	/* Set INTLR0 low priority */
	//LRPR10 = 1U;
	//LRPR00 = 1U;
	/* Set INTLS0 low priority */
	//LSPR10 = 1U;
	//LSPR00 = 1U;
	//  Enable operation
	UF0TXE = 1;   	// Disable Rx and Tx operation
	UF0RXE = 1;
	
	Uart.TxIndicator = FALSE;
}

__interrupt void  Uart_Isp_Txd (void)
{
	TxStat.CurByteFlag = TRUE;
}

__interrupt void  Uart_Isp_Rxd (void)
{

	static BYTE RxCnt = 0;
	Buffer[RxCnt] = (BYTE)UF0RX;
	RxCnt ++;
	if(RxCnt > (BUFFER_SIZE - 1))
	{
		RxCnt = 0;
	}
}
BYTE DataNouse;
__interrupt void  Uart_Isp_Err (void)
{
	DataNouse = (BYTE)UF0RX;
	UF0STC = UF0STR;//0x7F1F;//
	
	UF0RXE = 0;
	UF0TXE = 0;
	
	PM1.3 = 0;   // LTxD1 output
	P1.3 = 1;    // Output '1'
	// Set LRXD1 pin 
	PM1.4 = 1;   // LRxD1 input
	P1.4 = 1;    // May be '0' or '1'
	UF0RXE = 1;
	UF0TXE = 1;
	TxStat.CurByteFlag = TRUE;
}