#define F_CPU 16000000

#include "uart.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "pinout.h"
#include "leds.h"
#include <util/delay.h>

void UART_init() 
{
	UBRR1 = 7; // 9600 (51 : 19200) 
	UCSR1B |= (1<<TXEN1); // TX enable
	UCSR1C |= (1<<UCSZ10)|(1<<UCSZ11); // Set frame format: 8data, 1 stop bit
	
	DDRB |= (1 << DE);
	PORTB |= (1 << DE);
}

static void UART_sendChar(char c)
{
	while(!(UCSR1A  & (1 << UDRE1)))
	{
		
	}
	UDR1 = c;
}

void UART_write(char *data) 
{	
	while(*data)
	{
		UART_sendChar(*data);
		data++;
	}
}

void motor_drive(int16_t left, int16_t right)
{
	char buf[16];
	//int * intlocation = (int*)(&buf[3]);
	
	//int32_t leftSpeed = ((left << 16) / 1000) << 8;
	//int32_t rightSpeed = ((right << 16) / 1000) << 8;

	sprintf(buf, "1:s%s0.%.3d\n", -left < 0 ? "" : "-", abs(left));

	UART_write(buf);

	sprintf(buf, "2:s%s0.%.3d\n", -right < 0 ? "" : "-", abs(right));
	UART_write(buf);
	
//  	buf[1] = '2';
// 
// 	*intlocation = rightSpeed;
// 
}