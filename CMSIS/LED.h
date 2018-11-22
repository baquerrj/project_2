/*
 * LED.h
 *
 *  Created on: Nov 21, 2018
 *      Author: rober
 */

#ifndef LED_H_
#define LED_H_
#include <MKL25Z4.h>

/* Initialize all three LEDs on the FRDM board */
void LED_init( void );

/* Toggle LEDs according to bit 2-0 of input value */
void LED_set( int value );

#endif /* LED_H_ */
