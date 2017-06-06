
#include <util/atomic.h>
#include "adc.h"
#include "pinout.h"

uint8_t lights_arr[LIGHTS_PER_HALF] = {IR6, IR5, IR4, IR0, IR1, IR3, IR2};
uint8_t prox_arr[PROXES] = {PROX1, PROX2, PROX3};


void adc_init() //AV CC with external capacitor on AREF pin
{ 

	ADCSRA |= (1<<ADEN); //enable ADC
	ADMUX = (1<<REFS0); //AVCC with external capacitor on AREF pin
	DIDR0 = 0b11110011;
	DIDR2 = 0b00111111;
}

uint16_t adc_read(uint8_t channel) // reads adc value from given channel
{ 
	ADMUX = (1<<REFS0) | (channel & 0b011111);	// re-init MUXes to 
	ADCSRB =  (1 << ADHSM) | (channel & (1 << MUX5));
		
	ADCSRA |= (1<<ADSC) | (1<<ADPS1) | (1<<ADPS0);
	
	while(ADCSRA & (1 << ADSC));
	
	return ADC;	
}

void read_lights(uint16_t *light_vals) // 0...14 on andurid vasakult paremale
{ 
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		CLEAR_PIN(PORTE, MUX_S);
		
		light_vals[1] = adc_read(lights_arr[6]);
		light_vals[3] = adc_read(lights_arr[5]);
		light_vals[4] = adc_read(lights_arr[4]);
		light_vals[6] = adc_read(lights_arr[3]);
		light_vals[8] = adc_read(lights_arr[2]);
		light_vals[11] = adc_read(lights_arr[1]);
		light_vals[13] = adc_read(lights_arr[0]);
				
// 		for(uint8_t i = 0; i < LIGHTS_PER_HALF; i++)
// 			light_vals[i] = adc_read(lights_arr[i]);
// 
 		PORTE |= (1 << MUX_S);

		light_vals[0] = adc_read(lights_arr[6]);
		light_vals[2] = adc_read(lights_arr[5]);
		light_vals[5] = adc_read(lights_arr[3]);
		light_vals[7] = adc_read(lights_arr[4]);
		light_vals[9] = adc_read(lights_arr[2]);
		light_vals[10] = adc_read(lights_arr[1]);
		light_vals[12] = adc_read(lights_arr[0]);

// 				
// 		for(int i = 0; i < LIGHTS_PER_HALF; i++)
// 			light_vals[i + 7] = adc_read(lights_arr[i]);
	}
}

void read_proxes(uint16_t *prox_vals)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		for(uint8_t i = 0; i < PROXES; i++)
			prox_vals[i] = (adc_read(prox_arr[i])+adc_read(prox_arr[i]))>>1;
	}
}

int8_t detect_obtsacle(uint16_t* prox_vals)
{
	 read_proxes(prox_vals);
	if (prox_vals[1] > 170)
	{
		if (prox_vals[0] + 40 > prox_vals[1])
		{
			return -1; // hill
		}
		else
		{
			return 1; // wall
		}
	}
	return 0; //no obtsacle
}