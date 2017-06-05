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
#include "pid.h"

uint16_t base_motor_speed = 220;
uint8_t esc_speed = 20;

bool_t esc_enabled = TRUE;

void usb_write();

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
 	UART_init();
	if (esc_enabled)
	{
		esc_init();
	}
 	buttons_init();
	leds_init();
	calib_init(lights_max, lights_min);
	
// 	set_led(STATUS_LED1, TRUE);
// 	set_led(CALIB_LED, TRUE);
	
	sei();
	
	//_delay_ms(3000);
    
	//esc_stop();
	//motor_drive(0, 0);
	
	while(check_start_state());
	while(calib_state())
	{
		calib_start(lights_max, lights_min);
	}
	//_delay_ms(1000);
	
	if(esc_enabled)
	{
		esc_start();
		esc_set_speed(esc_speed);
	}
	//calib_load();
	
	_delay_ms(1000);
	
	while (1) 
    {
 		//char buf[16];
 		
  		//read_lights(light_vals);
		
		int16_t speed = calc_speed(lights_max, lights_min);
// 		sprintf(buf, "%d \n", speed);
// 		usb_write(buf);
// 		for(int i = 0; i < LIGHTS; i++)
// 		{
// 			//sprintf(buf, "%d ", (100 * (light_vals[i] - lights_min[i])) / (lights_max[i] - lights_min[i]));
// 			sprintf(buf, "%d ",  light_vals);
// 			
// 			usb_write(buf);
// 		}
// 		usb_write("\n");
// 		read_proxes(prox_vals);
// 		for(int i = 0; i < PROXES; i++)
// 		{
// 			sprintf(buf, "%d ", prox_vals[i]);
// 			usb_write(buf);
// 		}
// 		usb_write("\n");
		
// 		int16_t error_motor_speed = Kp*get_error(light_vals, lights_min, lights_max);
// 		

// 		PORTC ^= (1 << STATUS_LED1);
// 		motor_drive(200, 200);
// 		
// 		_delay_ms(100);
// 		PORTC ^= (1 << STATUS_LED1);
// 		motor_drive(400, 400);
// 		
//  		_delay_ms(100);
// 		int16_t speed_left = speed < -100 ? -(int16_t)((double)(-speed) / 1.5) - 100 : base_motor_speed + speed;
// 		int16_t speed_right = speed > 100 ? -100 - (int16_t)((double)speed / 1.5)  : base_motor_speed - speed; 
		int16_t speed_left = base_motor_speed + speed;
		int16_t speed_right = base_motor_speed - speed;
 		motor_drive(speed_left, speed_right);
		//motor_drive(0, 0);
// 		
// 		sprintf(buf, " -- %d", error_motor_speed);
// 		usb_write(buf);
// 
// 		usb_write("\n");

// 		for(int i = 0; i < 800; i++)
// 		{
// 			motor_drive(i, i);
// 			_delay_ms(10);
// 		}
// 		for(int i = 800; i > 0; i--)
// 		{
// 			motor_drive(i, i);
// 			_delay_ms(10);
// 		}
// 	    
 	}
}