
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#include "pinout.h"
#include "adc.h"
#include "uart.h"
#include "esc.h"
#include "buttons.h"
#include "leds.h"
#include "usb_serial.h"
#include  "calib.h"

void usb_write(const char *str) {
	while (*str) {
		usb_serial_putchar(*str);
		str++;
	}
}


int main(void)
{
	// Remove CLKDIV8
	CLKPR = 0x80;
	CLKPR = 0x00;
	
	// Disable JTAG
	MCUCR |= (1 << JTD);
	MCUCR |= (1 << JTD);
	
	// Set MUX_S pin as output
	DDRE = (1 << MUX_S);
	
	// Initializations
	usb_init();
	adc_init();
 	UART_init();
	esc_init();
 	buttons_init();
	leds_init();
	
// 	set_led(STATUS_LED1, TRUE);
// 	set_led(CALIB_LED, TRUE);
	
	sei();
	
	//_delay_ms(3000);
    
	esc_stop();
	
	while(check_start_state());
	
	esc_start();
	esc_set_speed(30);
	calib_load();
	
	_delay_ms(2000);
	
	while (1) 
    {
		char buf[16];
		
		read_lights(light_vals);
		
		for(int i = 0; i < LIGHTS; i++)
		{
			sprintf(buf, "%d ", light_vals[i]);	
			usb_write(buf);	
		}

		read_proxes(prox_vals);

		for(int i = 0; i < PROXES; i++)
		{
			sprintf(buf, "%d ", prox_vals[i]);
			usb_write(buf);
		}

		sprintf(buf, "%d\n", adc_read(IR6));
		usb_write(buf);
    }
}

