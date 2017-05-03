
#include "buttons.h"
#include "pinout.h"

void buttons_init() {
	DDRD &= ~((1<<START)|(1<<STOP));	// start		stop
	DDRB &= ~(1<<CALIB);				// calibrate
	
	// make stop interrupt driven
	EICRA = (1<<ISC11); // The falling edge of INTn generates asynchronously an interrupt request.
	EIMSK |= (1<<STOP);
}

ISR(INT0_vect) { // freezes when stop is high
	while(1); 	
}