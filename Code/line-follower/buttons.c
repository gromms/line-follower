
#define F_CPU 16000000

#include <avr/interrupt.h>
#include <util/delay.h>
#include "buttons.h"
#include "uart.h"
#include "pinout.h"
#include "esc.h"
#include "calib.h"
#include "leds.h"

void buttons_init() {
	// Set button pins of input
	DDRD &= ~((1<<START)|(1<<STOP));	// start		stop
	DDRB &= ~(1<<CALIB);				// calibrate
	
	//PORTD |= (1<<START)|(1<<STOP);
	PORTB |= (1 << CALIB);
	
	// make stop interrupt driven
	EICRA = (1<<ISC00); // The falling edge of INTn generates asynchronously an interrupt request.
	EIMSK |= (1<<STOP);
	
	PCMSK0 |= (1 << PCINT1);
	PCICR |= (1 << PCIE0);
}

bool_t check_stop_state()
{
	return CHECK_PIN(PIND, STOP);
}

bool_t check_start_state()
{
	return CHECK_PIN(PIND, START);
}

bool_t check_calib_state()
{
	return CHECK_PIN(PINB, CALIB);
}

ISR(PCINT0_vect)
{
	calib_start();
}

ISR(INT0_vect)  // freezes when stop button is pressed 
{
	motor_drive(0, 0);
	esc_stop();
	motor_drive(0, 0);
	esc_stop();
	motor_drive(0, 0);
	esc_stop();
	while(1)
	{
		set_led(STATUS_LED2, TRUE);
		set_led(STATUS_LED1, TRUE);
		_delay_ms(100);
		set_led(STATUS_LED2, FALSE);
		set_led(STATUS_LED1, FALSE);
		_delay_ms(100);
	} 	
}