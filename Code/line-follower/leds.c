
#include "leds.h"
#include <avr/io.h>
#include "pinout.h"

void leds_init() 
{ // leds on PC6, PC7, PB2 as outputs
	DDRC |= (1<<CALIB_LED) | (1<<STATUS_LED1);
	DDRB |= (1<<STATUS_LED2);
}

void set_led(uint8_t led, bool_t on) 
{
	if(led == STATUS_LED2)
	{
		if (on) 
			BIT_SET(PORTB, STATUS_LED2);
		else
			CLEAR_PIN(PORTB, STATUS_LED2);
	}
	else
	{
		if (on)
			BIT_SET(PORTC, led);
		else
			CLEAR_PIN(PORTC, led);
	}
}