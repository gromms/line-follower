
#include "leds.h"
#include <avr/io.h>
#include "pinout.h"

void leds_init() 
{ // leds on PC6, PC7, PB2 as outputs
	DDRC |= (1<<CALIB_LED)|(1<<STATUS_LED1);
	DDRB |= (1<<STATUS_LED2);
}

void set_led(uint8_t led, bool on) 
{
	if(led == STATUS_LED2)
	{
		if (on) 
			PORTB |= (1<<led);
		else
			PORTB &= ~(1<<led);
	}
	else
	{
		if (on)
			PORTC |= (1<<led);
		else
			PORTC &= ~(1<<led);
	}
}