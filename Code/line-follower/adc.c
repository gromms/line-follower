
#include "adc.h"
#include "pinout.h"

void adc_init() //AV CC with external capacitor on AREF pin
{ 
	ADCSRA |= (1<<ADEN); //enable ADC
	ADMUX = (1<<REFS0); //AVCC with external capacitor on AREF pin
}

uint16_t adc_read(uint8_t channel) // reads adc value from given channel
{ 
	ADMUX = (1<<REFS0);	// re-init MUXes to 0
	
	ADMUX |= channel;
		
	ADCSRA |= (1<<ADSC);
	
	while(bit_is_set(ADCSRA, ADSC)); // wait for conversion
	
	return ADC;	
}

void read_lights(volatile uint16_t *light_vals) // 0...14 on andurid vasakult paremale
{ 
	PORTE &= ~(1<<MUX_S);		// MUX_s = 0
	
	for(int i = 0; i < LIGHTS; i++)
		light_vals[i] = adc_read(sensor_arr[i]);
	
	PORTE |= (1<<MUX_S);		// MUX_s = 1
	
	for(int i = 0; i < LIGHTS; i++)
		light_vals[i] = adc_read(sensor_arr[i]);
	
}

void read_proxes(uint16_t *prox_vals)
{
	for(uint8_t i = 0; i < PROXES; i++)
		prox_vals[i] = adc_read(prox_arr[i]);
}