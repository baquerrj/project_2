/*
 * ecen5813_uart.h
 *

 * REF: http://cache.freescale.com/files/32bit/doc/quick_ref_guide/KLQRUG.pdf 	pg 84
 * REF: http://www.simplyembedded.org/tutorials/msp430-uart/
 * REF: Embedded Systems with ARM Cortex-M Microcontrollers in Assembly Language and C, Dr. Yifeng Zhu
 */

#ifndef ECEN5813_UART_H_
#define ECEN5813_UART_H_

#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.H>
#include "ring.h"

typedef struct
{
	uint8_t* buffer;
	uint32_t nBytes;
} uart_data_TX, uart_data_RX;

typedef struct
{
	uint8_t* buffer;
	uint32_t nBytes;
} uart_t;

/* Initialize UART0 to transmit */
void UART0_Tx_init( void );

/* Initialize UART0 to transmit */
void UART0_Rx_init( void );

/* Blocking Transfer */
void UART0_Tx_blocking( ring_t* p_ring );

/* Blocking Read */
void UART0_Rx_blocking( ring_t* p_ring );

#endif /* ECEN5813_UART_H_ */
