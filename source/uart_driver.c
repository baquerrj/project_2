#include "uart_driver.h"
#include <stdio.h>
#include <string.h>

#ifdef _NON_BLOCKING_
/* Functions used for non-blocking implementation of application */

/* Function to check whether the transmitter is available to accept a new character for transmission
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_TX_available( uart_handle_t* uart )
{
	if( uart->Instance->S1 & TDRE )
	{
		uart->state = UART_STATE_READY;
	}
	else
	{
		uart->state = UART_STATE_BUSY_TX;
	}
	return;
}

/* Function to transmit a character assuming transmitter is available
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_TX_transmit_char( uart_handle_t* uart )
{
	char c = '0';
	if( !(uart->myRing->empty) )
	{
		ring_removeData( uart->myRing, &c );
		uart->Instance->D = c;
	}
	return;
}

/* Function called by ISR to supply a next character on completion of previous transmission
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
char UART0_TX_get_next_char( uart_handle_t* uart )
{
	char c = '0';

	if( !(uart->myRing->empty ) )
	{
		ring_removeData( uart->myRing, &c );
	}
	return c;
}

/* Function called by ISR to receive character
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_RX_char( uart_handle_t* uart )
{
	char c = '0';
	c = uart->Instance->D;
	if( !(uart->myRing->full) )
	{
		if( c == '\r' )
		{
			ring_insert( uart->myRing, '\n');
		}
		ring_insert( uart->myRing, c );
	}

	uint8_t inIdx = (uint8_t)c;
	uart->input[inIdx] = uart->input[inIdx] + 1;

	//print characters
	if( uart->idx > 255 )
	{
		uart->idx = 0;
	}
	while( uart->idx < 256 )
	{
		if( uart->input[uart->idx] != 0 )
		{
			char buffer[10];
			sprintf( buffer, "%c - %d\n\r", (char)uart->idx, uart->input[uart->idx] );
			int j = 0;
			while( j != 10 && buffer[j] != '\0')
			{
				ring_insert( uart->myRing, buffer[j] );
				j++;
			}
			UART0_TX_available( uart );
			if( uart->state == UART_STATE_READY )
			{
				UART0_TX_transmit_char( uart );
			}
		}
		uart->idx++;
	}
	return;
}

/* Initializes UART Peripheral in Interrupt Mode
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_init_interrupt( uart_handle_t* uart )
{
	SIM->SCGC4 |= 0x0400; /* enable clock for UART0 */ //manual p 204
	SIM->SOPT2 |= 0x04000000; /* use FLL(Frequency Locked Loop) output for UART Baud rate generator */
	uart->Instance->C2 = 0; /* turn off UART0 while changing configurations */
	uart->Instance->BDH = 0x00;
	uart->Instance->BDL = 0x17; /* 115200 Baud */
	uart->Instance->C4 = 0x0F; /* Over Sampling Ratio 16 */
	uart->Instance->C1 = 0x00; /* 8-bit data and no parity */
	SIM->SCGC5 |= 0x0200; /* enable clock for PORTA */
	PORTA->PCR[2] = 0x0200; /* make PTA2 UART0_Tx pin */
	PORTA->PCR[1] = 0x0200; /* make PTA1 UART0_Rx pin */
	NVIC->ISER[0] |= 0x00001000;    /* enable INT12 (bit 12 of ISER[0]) */
	uart->Instance->C2 = 0xEC; //turn on interrupts and enable both transmit and receive
	uart->state = UART_STATE_READY;
	return;
}

#endif

#ifdef _POLLING_
/* Functions used for blocking(polling) implementation of application */

/* Function to check whether the transmitter is available to accept a
 * new character for transmission
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_TX_available( uart_handle_t* uart )
{
	if( uart->Instance->S1 & TDRE )
	{
		uart->state = UART_STATE_READY;
	}
	else
	{
		uart->state = UART_STATE_BUSY_TX;
	}
	return;
}

/* Function to transmit a character assuming transmitter is available
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_TX_transmit_char( uart_handle_t* uart )
{
	char c = '0';
	if( !(uart->myRing->empty) )
	{
		ring_removeData( uart->myRing, &c );
		if( c == '\r' )
		{
			uart->Instance->D = c;
			while( !(uart->Instance->S1 & TDRE) );
			uart->Instance->D = '\n';
			return;
		}
		uart->Instance->D = c;
	}
	return;
}

/* Function to check whether the receiver is available to receive a
 * new character
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_RX_available( uart_handle_t* uart )
{
	if( uart->Instance->S1 & RDRF )
	{
		uart->state = UART_STATE_READY;
	}
	else
	{
		uart->state = UART_STATE_BUSY_RX;
	}
	return;
}

/* Function to receive a character assuming transmitter is available
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_RX_get_next_char( uart_handle_t* uart )
{
	char c = uart->Instance->D;
	if( !(uart->myRing->full) )
	{
		ring_insert( uart->myRing, c );
	}
	return;
}

/* Function to wait (block) for the receiver to be available and
 * then once available receives a character, places it in ring buffer
 * and returns
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_RX( uart_handle_t* uart )
{
	uart->state = UART_STATE_RESET;
	while( uart->state != UART_STATE_READY )
	{
		UART0_RX_available( uart );
	}
	UART0_RX_get_next_char( uart );
	return;
}

/* Function to wait (block) for the transmitter to be available and
 * then once available transmits a character and returns
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_TX( uart_handle_t* uart )
{
	uart->state = UART_STATE_RESET;
	while( uart->state != UART_STATE_READY )
	{
		UART0_TX_available( uart );
	}
	UART0_TX_transmit_char( uart );
	return;
}

/* Initializes UART Peripheral in Blocking Mode
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_init_polling( uart_handle_t* uart )
{
	SIM->SCGC4 |= 0x0400; /* enable clock for UART0 */ //manual p 204
	SIM->SOPT2 |= 0x04000000; /* use FLL(Frequency Locked Loop) output for UART Baud rate generator*/
	uart->Instance->C2 = 0; /* turn off UART0 while changing configurations */
	uart->Instance->BDH = 0x00;
	uart->Instance->BDL = 0x17; /* 115200 Baud */
	uart->Instance->C4 = 0x0F; /* Over Sampling Ratio 16 */
	uart->Instance->C1 = 0x00; /* 8-bit data and no parity */
	SIM->SCGC5 |= 0x0200; /* enable clock for PORTA */
	PORTA->PCR[2] = 0x0200; /* make PTA2 UART0_Tx pin */
	PORTA->PCR[1] = 0x0200; /* make PTA1 UART0_Rx pin */
	uart->Instance->C2 = 0x0C; //enable both transmit and receive
	uart->state = UART_STATE_READY;
	return;
}
#endif
