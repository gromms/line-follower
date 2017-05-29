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


uint16_t Kp = 10;
uint16_t Ki = 0;
uint16_t Kd = 0;

uint16_t base_motor_speed = 200;

int16_t light_weight = {-7,-6,-5,-4,-3,-2,-1, 1,2,3,4,5,6,7};
int16_t get_error(uint16_t *lights, uint16_t *min_vals, uint16_t *max_vals)
{
	int16_t error = 0;
	for (uint8_t i = 0; i < 14; i++)
	{
		error += ( 1 - (lights[i]-min_vals[i]) / (max_val[i] - min_val[i]) ) * light_weight[i];
	}
	return error;
}

void usb_write(const char *str) {
	while (*str) {
		usb_serial_putchar(*str);
		str++;
	}
}

void usb_debug()
{
	char buf[16];
	
	read_lights(light_vals);
	
	for(int i = 0; i < LIGHTS; i++)
	{
		sprintf(buf, "%d ", light_vals[i]);
		usb_write(buf);
	}
	/*
	read_proxes(prox_vals);
	for(int i = 0; i < PROXES; i++)
	{
		sprintf(buf, "%d ", prox_vals[i]);
		usb_write(buf);
	}
	printf(buf, "%d\n", adc_read(IR6));
 	
	usb_write(buf);*/
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
// 	UART_init();
//	esc_init();
 	buttons_init();
	leds_init();
	
// 	set_led(STATUS_LED1, TRUE);
// 	set_led(CALIB_LED, TRUE);
	
	sei();
	
	//_delay_ms(3000);
    
	//esc_stop();
	//motor_drive(0, 0);
	
	//while(check_start_state());
	
	//_delay_ms(1000);
	
	//esc_start();
	//esc_set_speed(20);
	//calib_load();
	
	//_delay_ms(1000);
	
	while (1) 
    {
 		char buf[16];
 		
 		read_lights(light_vals);
 		
 		for(int i = 0; i < LIGHTS; i++)
 		{
	 		sprintf(buf, "%d ", light_vals[i]);
	 		usb_write(buf);
 		}
		usb_write("\n");

// 		read_proxes(prox_vals);
// 		for(int i = 0; i < PROXES; i++)
// 		{
// 			sprintf(buf, "%d ", prox_vals[i]);
// 			usb_write(buf);
// 		}
// 		usb_write("\n");
		
		uint16_t error_motor_speed = Kp*get_error(light_vals, miinimum ja maksimus);
		
		motor_drive(base_motor_speed - error_motor_speed, base_motor_speed + error_motor_speed);
    }
}