#define F_CPU 16000000

#include <avr/io.h>
#include "pinout.h"

void esc_set_speed(uint8_t spd);

void esc_init()
{
	DDRB |= (1<<ESC_PWM);
	
	TCCR1A |= (1<<COM1C1)|(1<<WGM11);
	TCCR1B |= (1<<WGM13)|(1<<WGM12); 

	ICR1=4999;  //fPWM=50Hz (Period = 20ms Standard).
	TCCR1B |= (1<<CS11)|(1<<CS10);
	esc_set_speed(0);
}

void esc_set_speed(uint8_t spd)
{
	if(spd >= 0 && spd <= 100)
		OCR1C = 250 + spd * 2.5; // (1 + spd / 100) * 1000 / 4
}

void esc_stop()
{
	esc_set_speed(0);
	//TCCR1B &= ~((1<<CS11) | (1<<CS10));
}

void esc_start()
{
	//TCCR1B |= (1<<CS11)|(1<<CS10);
	esc_set_speed(0);
}