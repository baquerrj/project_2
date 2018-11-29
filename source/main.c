/*
 * References:
 * 			https://github.com/niekiran/MasteringMCU
 * 			https://electrovolt.ir/wp-content/uploads/2017/07/Freescale_ARM_Cortex_M_Embedded_ElectroVolt.ir_.pdf
 *
*/
#include <MKL25Z4.H>
#include <stdint.h>
#include "ring.h"
#include "uart_driver.h"
#include "LED.h"
uart_handle_t uart_handle;

#ifdef _POLLING_
int main (void)
{
	MCG->C4 = 0x20;
	uart_handle.Instance = UART0;
 	uart_handle.myRing = ring_init( 200 );
 	uart_handle.state = UART_STATE_RESET;

 	UART0_init_polling( &uart_handle );
  ring_insert( uart_handle.myRing, 'r');
  ring_insert( uart_handle.myRing, 'e');
  ring_insert( uart_handle.myRing, 'a');
  ring_insert( uart_handle.myRing, 'd');
  ring_insert( uart_handle.myRing, 'y');
  ring_insert( uart_handle.myRing, '\r');

  while( !(uart_handle.myRing->empty) )
  {
  	UART0_TX( &uart_handle );
  }
  while (1)
  {
  	UART0_RX( &uart_handle );
  	UART0_TX( &uart_handle );
  }

  return 1;
}
#endif
#ifdef _NON_BLOCKING_

int main( void )
{
	MCG->C4 = 0x20;
	LED_init();
	uart_handle.Instance = UART0;
	uart_handle.myRing 	 = ring_init( 200 );
	uart_handle.state 	 = UART_STATE_RESET;
	uart_handle.idx 		 = 0;

	ring_insert( uart_handle.myRing, 'r');
	ring_insert( uart_handle.myRing, 'e');
	ring_insert( uart_handle.myRing, 'a');
	ring_insert( uart_handle.myRing, 'd');
	ring_insert( uart_handle.myRing, 'y');
	ring_insert( uart_handle.myRing, '\n');
	ring_insert( uart_handle.myRing, '\r');

	__disable_irq();        /* global disable IRQs */
	UART0_init_interrupt( &uart_handle );
	__enable_irq();         /* global enable IRQs */
	while (1)
	{
		UART0_TX_available( &uart_handle );
		if( uart_handle.state == UART_STATE_READY )
		{
			UART0_TX_transmit_char( &uart_handle );
		}
		LED_toggle();
	}
	return 1;
}

/* UART0 interrupt handler */
void UART0_IRQHandler( void )
{
	if( uart_handle.Instance->S1 & TDRE )
	{
		if( !uart_handle.myRing->empty)
		{
			uart_handle.Instance->D = UART0_TX_get_next_char( &uart_handle );
		}
	}
	if( uart_handle.Instance->S1 & RDRF )
	{
		UART0_RX_char(&uart_handle);
	}
	return;
}
#endif
