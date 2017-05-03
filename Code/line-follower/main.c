#define F_CPU 16000000UL
#include <avr/io.h>

#include "pinout.h"
#include "adc.h"
#include "uart.h"
#include "buttons.h"
#include "leds.h"

int main(void)
{
	adc_init();
	UART_init();
	buttons_init();
	leds_init();
    
    while (1) 
    {
    }
}

