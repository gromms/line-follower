#include <avr/io.h>
#include <stdio.h>
#include "pid.h"
#include "pinout.h"
#include "adc.h"

double Kp = 0.2;
uint16_t Ki = 0;
uint16_t Kd = 0.0;

int16_t pError = 0;
int16_t error = 0;

int16_t light_weight[] = {-64,-32,-16,-8,-4,-2,-1, 1,2,3,8,16,32,64};
//int16_t light_weight[] = {-7,-6,-5,-4,-3,-2,-1, 1,2,3,4,5,6,7};

int16_t calc_error( uint16_t *lights_max, uint16_t *lights_min)
{
	//char buf[16];
	
	error = 0;
	double err_sum = 0;
	
	read_lights(light_vals);
	
	for (uint8_t i = 0; i < LIGHTS; i++)
	{

		double err_percent = ((double)((light_vals[i] - lights_min[i])) / (double)((lights_max[i] - lights_min[i])));			
		err_sum += err_percent;	
		err_percent = err_percent < 0.05 ? 0 : err_percent * 100;
	
		error += (int16_t)(err_percent) * light_weight[i];
//  		sprintf(buf, "%d | ", (int16_t)err);
//  		usb_write(buf);
	}
	
	//sprintf(buf, "%d", error);
	//usb_write(buf);
	//usb_write("\n");
	return error / err_sum;
}

int16_t calc_speed(uint16_t *lights_max, uint16_t *lights_min)
{
	PORTB |= (1 << STATUS_LED2);
	pError = error;
	int16_t error = calc_error(lights_max, lights_min);
	PORTB &= ~(1 << STATUS_LED2);
	
	return error * Kp + (error - pError) * Kd; 
}