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

int16_t light_weight[] = {-64,-32,-16,-8,-4,-2,-1,1,2,4,8,16,32,64};
//int16_t light_weight[] = {-7,-6,-5,-4,-3,-2,-1, 1,2,3,4,5,6,7};

uint16_t p_light_vals[LIGHTS];
bool_t is_on_line = TRUE;

void check_losing_line() 
{
	// check the leftmost sensors
	if (light_vals[0] < p_light_vals[0] && light_vals[1] > p_light_vals[1]) 
	{
		is_on_line = TRUE;
		//moving right
	}
	else 
	{
		//lost line moving left
		is_on_line = FALSE;
		error = light_weight[0];
	}
	
	// check the rightmost sensors
	if (light_vals[13] < p_light_vals[13] && light_vals[12] > p_light_vals[12])
	{
		//moving left
		is_on_line = TRUE;
	}
	else 
	{
		//lost line moving right
		is_on_line = FALSE;
		error = light_weight[13];
	}
}

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
	
	if (error == 0) 
	{
		if (is_on_line)
			check_losing_line();
		else
			error = pError;
	}
	else 
	{
		is_on_line = TRUE;
	}	
	
	for (uint8_t i = 0; i < LIGHTS; i++) 
	{
		p_light_vals[i] = light_vals[i];
	}
	err_sum = err_sum == 0 ? 1 : err_sum;
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