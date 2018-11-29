/*
 * RES: https://github.com/niekiran/MasteringMCU.git
 *
 *
 *
 */

#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <MKL25Z4.H>
#include "ring.h"

#define RDRF 0x20
#define TC   0x40
#define TDRE 0x80

typedef enum
{
  UART_STATE_RESET       = 0x00,    /*!< Peripheral is not yet Initialized                  */
  UART_STATE_READY       = 0x01,    /*!< Peripheral Initialized and ready for use           */
  UART_STATE_BUSY        = 0x02,    /*!< an internal process is ongoing                     */
  UART_STATE_BUSY_TX     = 0x12,    /*!< Data Transmission process is ongoing               */
  UART_STATE_BUSY_RX     = 0x22,    /*!< Data Reception process is ongoing                  */
} uart_state_t;

typedef struct
{
	UART0_Type			*Instance;	/* UART registers base address */

	ring_t					*myRing;		/* Circular Buffer to hold characters to transmit */

	uart_state_t		state;			/* Holds current state of UART Peripheral as defined in uart_stat_t */

	uint16_t 				input[256];	/* Simple array to tabulate received characters */

	uint16_t					idx;

} uart_handle_t;


#ifdef _NON_BLOCKING_
/* Functions used for non-blocking implementation of application */

/* Function to check whether the transmitter is available to accept a new character for transmission
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_TX_available( uart_handle_t* uart );

/* Function to transmit a character assuming transmitter is available
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_TX_transmit_char( uart_handle_t* uart );

/* Function called by ISR to supply a next character on completion of previous transmission
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
char UART0_TX_get_next_char( uart_handle_t* uart );

/* Function called by ISR to receive character
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_RX_char(uart_handle_t* uart);

/* Initializes UART Peripheral in Interrupt Mode
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_init_interrupt( uart_handle_t* uart );

#endif

#ifdef _POLLING_
/* Functions used for blocking(polling) implementation of application */

/* Function to check whether the transmitter is available to accept a
 * new character for transmission
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_TX_available( uart_handle_t* uart );

/* Function to transmit a character assuming transmitter is available
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_TX_transmit_char( uart_handle_t* uart );

/* Function to check whether the receiver is available to receive a
 * new character
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_RX_available( uart_handle_t* uart );

/* Function to receive a character assuming transmitter is available
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_RX_get_next_char( uart_handle_t* uart );

/* Function to wait (block) for the receiver to be available and
 * then once available receives a character, places it in ring buffer
 * and returns
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_RX( uart_handle_t* uart );

/* Function to wait (block) for the transmitter to be available and
 * then once available transmits a character and returns
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_TX( uart_handle_t* uart );

/* Initializes UART Peripheral in Blocking Mode
 * @param	*uart:	Pointer to UART Peripheral Handle Struct
 */
void UART0_init_polling( uart_handle_t* uart );
#endif

#endif
