/*
 *
 *
 *
 *
 *
 * REF: http://www.simplyembedded.org/tutorials/msp430-uart/
 *
 *
 *
 * pins 27,28
 *
 *
 * Notes from class
 * examination of block diagrams reveal that we will use UART0 pins, 27(Rx) and 28(Tx)
 * PortA bit 1, PortA bit 2
 * function "alternative 2" ALT2
 *
 * ch. 11
 * setting port pins
 * pg 177
 * pg. 183 contains value to set regs to
 * PORTx_PRCn
 * field 19-16 0000 disable interrupt
 * field 10-8 010 Alternative 2
 * ch 39
 *
 *
 */
#include <stdio.h>
#include "ecen5813_uart.h"

void UART0_init( void )
{
	SIM->SCGC4 |= 0x0400; /* enable clock for UART0 */
	SIM->SOPT2 |= 0x04000000; /* use FLL output for UART Baud rate generator
	*/
	UART0->C2 = 0; /* turn off UART0 while changing configurations */
	UART0->BDH = 0x00;
	UART0->BDL = 0x17; /* 115200 Baud */
	UART0->C4 = 0x0F; /* Over Sampling Ratio 16 */
	UART0->C1 = 0x00; /* 8-bit data */
	UART0->C2 = 0x08; /* enable transmit */
	SIM->SCGC5 |= 0x0200; /* enable clock for PORTA */
	PORTA->PCR[2] = 0x0200; /* make PTA2 UART0_Tx pin */
}


/*init fxn for polling method
 * passes in uart struct object
 */
void uartInit_blocking(uart_t *uart0)
{
	//configure
}

/*read fxn for polling method
 * passes in uart struct object
 */
void uartRead_blocking(uart_t *uart0)
{

}

/*write fxn for polling method
 * passes in uart struct object
 */
void uartWrite_blocking(uart_t *uart0)
{

}
