/*
 * LED.c
 *
 *  Created on: Nov 21, 2018
 *      Author: rober
 */

#include "LED.h"

/* Initialize all three LEDs on the FRDM board */
void LED_init( void )
{
	SIM->SCGC5 |= 0x400;		/* enable clock for Port B */
	SIM->SCGC5 |= 0x1000;		/* enable clock for Port D */
	PORTB->PCR[18] = 0x100;	/* make PTB18 pin as GPIO */
	PTB->PDDR |= 0x40000;		/* make PTB18 as ouput pin */
	PTB->PSOR = 0x40000;		/* turn off red LED */
	PORTB->PCR[19] = 0x100;	/* make PTB19 pin as GPIO */
	PTB->PDDR |= 0x80000;		/* make PTB19 as output pin */
	PTB->PSOR = 0x80000;		/* turn off green LED */
	PORTD->PCR[1] = 0x100;	/* make PTD1 as GPIO */
	PTD->PDDR |= 0x02;			/* make PTD1 as output pin */
	PTD->PSOR = 0x02;				/* turn off blue LED */
	return;
}

/* Toggle LEDs according to bit 2-0 of input value */
void LED_set( int value )
{
	if( value & 0b1 )		/* use bit 0 of value to control red LED */
	{
		PTB->PCOR = 0x40000;	/* turn on red LED */
	}
	else
	{
		PTB->PSOR = 0x40000;	/* turn off red LED */
	}
	if ( value & 0b10)	/* use bit 1 of value to control green LED */
	{
		PTB->PCOR = 0x80000;	/* turn on green LED */
	}
	else
	{
		PTB->PSOR = 0x80000;	/* turn off green LED */
	}
	if ( value & 0b100 )	/* use bit 2 of value to control blue LED */
	{
		PTB->PCOR = 0x02;		/* turn on blue LED */
	}
	else
	{
		PTB->PSOR = 0x02;		/* turn off blue LED */
	}
	return;
}
