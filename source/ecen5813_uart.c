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
#include "LED.h"

void UART0_Tx_init( void )
{
	SIM->SCGC4 |= 0x0400; 		/* enable clock for UART0 */
	SIM->SOPT2 |= 0x04000000; /* use FLL output for UART Baud rate generator */
	UART0->C2 = 0;	/* turn off UART0 while changing configurations */
	UART0->BDH = 0x00;
	UART0->BDL = 0x17; 			/* 115200 Baud */
	UART0->C4 = 0x0F; 			/* Over Sampling Ratio 16 */
	UART0->C1 = 0x00; 			/* 8-bit data */
	UART0->C2 = 0x08; 			/* enable transmit */
	SIM->SCGC5 |= 0x0200; 	/* enable clock for PORTA */
	PORTA->PCR[2] = 0x0200; /* make PTA2 UART0_Tx pin */
	return;
}

void UART0_Rx_init( void )
{
	SIM->SCGC4 |= 0x0400;			/* enable clock for UART0 */
	SIM->SOPT2 |= 0x04000000;	/* use FLL output for UART Baud rate generator */
	UART0->C2 = 0;	/* turn off UART0 while changing configurations */
	UART0->BDH = 0x00;
	UART0->BDL = 0x17;			/* 115200 Baud */
	UART0->C4 = 0x0F;				/* Over Sampling Ratio 16 */
	UART0->C1 = 0x00;				/* 8-bit data */
	UART0->C2 = 0x04;				/* enable receive */
	SIM->SCGC5 |= 0x0200;		/* enable clock for PORTA */
	PORTA->PCR[1] = 0x0200;	/* make PTA1 UART0_Rx pin */
	return;
}

/* Blocking Transfer */
void UART0_Tx_blocking( ring_t* p_ring )
{
	char* data;
	/* Return value - default success */
	int retVal = 1;
	/* Keep going until ring buffer is emptied */
	while( !(p_ring->empty) && retVal )
	{
		/* Get first entry for ring pointer */
		retVal = ring_removeData( p_ring, data );
		if( 1 == retVal )		/* Success! */
		{
			/* Wait for transmit buffer to empty */
			while(!(UART0->S1 & 0x80));
			UART0->D = *data;		/* Send char stored in data */
		}
	}
	return;
}

/* Blocking Read */
void UART0_Rx_blocking( ring_t* p_ring )
{
	char c;
	/* Return value - default success */
	int retVal = 1;
	/* Keep going until ring buffer is full */
	while( !(p_ring->full) && retVal )
	{
		/* Wait for receive buffer full */
		while( !(UART0->S1 & 0x20) );
		c = UART0->D;		/* read char received */
		retVal = ring_insert( p_ring, c );		/* Store char read in ring buffer */
		LED_set(c);		/* Blink LED for fun */
	}
	return;
}
