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
void UART0_init( void );

/* Init function for polling method
 * @param[in] = pointer to UART struct
 */
void uartInit_blocking( uart_t* uart0 );

/* Read function for polling method
 * @param[in] = pointer to UART struct
 */
void uartRead_bloacking( uart_t* uart0 );

/* Write function for polling method
 * @param[in] = pointer to UART struct
 */
void uartWrite_blocking( uart_t* uart0 );
#endif /* ECEN5813_UART_H_ */
