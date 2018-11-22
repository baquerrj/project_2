/*
 * Copyright 2016-2018 NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    Project_2_UART.c
 * @brief   Application entry point.
 */
#include <stdio.h>
//#include "board.h"
//#include "peripherals.h"
//#include "pin_mux.h"
//#include "clock_config.h"
#include "MKL25Z4.h"
//#include "fsl_debug_console.h"
#include "ecen5813_uart.h"
#include "ring.h"
#include "LED.h"

void delay( int n );

int main( void )
{
	LED_init();
	ring_t* p_ring = ring_init( 10 );
	ring_insert( p_ring, 'r' );
	ring_insert( p_ring, 'e' );
	ring_insert( p_ring, 'a' );
	ring_insert( p_ring, 'd' );
	ring_insert( p_ring, 'y' );

	char* data;
	while (1)
	{
		/* Transmit ready message */
		UART0_Tx_init();
		UART0_Tx_blocking( p_ring );

		/* TX won't return until ring buffer is empty */
		UART0_Rx_init();
		UART0_Rx_blocking( p_ring );

		/* Pop last entry - if ! - exit program */
		if( !(p_ring->empty) )
		{
			ring_removeData( p_ring, data );
			if ( '!' == *data )
			{
				break;
			}
			else
			{
				/* Last entry wasn't ! - so re-insert and keep going with the loop */
				ring_insert( p_ring, data );
			}
		}
	}
#if 0
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("Hello World\n");

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
    }
#endif
    return 0 ;
}


/* Delay n milliseconds */
void delay( int n )
{
	int i = 0;
	int j = 0;
	while( i < n )
	{
		i++;
	}
	while( j < 7000 )
	{
		j++;
	}
	return;
}

