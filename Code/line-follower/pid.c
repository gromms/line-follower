#include <avr/io.h>
#include <stdio.h>
#include "pid.h"
#include "pinout.h"
#include "adc.h"

double Kp = 1;
//double Ki = 0;
double Kd = 0.5;

double pError = 0;
double error = 0;

//int16_t light_weight[] = {-64,-32,-16,-8,-4,-2,-1,1,2,4,8,16,32,64};
int16_t light_weight[] = {-7,-6,-5,-4,-3,-2,-1, 1,2,3,4,5,6,7};

double prev_light_percent[LIGHTS];
double light_percent[LIGHTS];
bool_t is_on_line = TRUE;

void check_losing_line() 
{
	if (prev_light_percent[0] || prev_light_percent[1] || prev_light_percent[2]) 
	{
		// line lost to the left
		is_on_line = FALSE;
		error = light_weight[0] * 100;
	}
	else if (prev_light_percent[11] || prev_light_percent[12] || prev_light_percent[13]) 
	{
		// line lost to the right
		is_on_line = FALSE;
		error = light_weight[13] * 100;
	}
}

double calc_error( uint16_t *lights_max, uint16_t *lights_min)
{
	char buf[16];

	error = 0;
	double err_sum = 0;
	
	read_lights(light_vals);
	
	for (uint8_t i = 0; i < LIGHTS; i++)
	{
		double err_percent = 0;
		if (light_vals[i] <= lights_min[i] + 150) 
		{
			err_percent = 0;
		}
		else if (light_vals[i] >= lights_max[i] - 25) 
		{
			err_percent = 1;
		}
		else 
		{
			err_percent = ((double)((light_vals[i] - lights_min[i])) / (double)((lights_max[i] - lights_min[i])));
		}
		err_sum += err_percent;	
		
		light_percent[i] = err_percent;
	
		error += (int8_t)(err_percent*100) * light_weight[i];
  		/*sprintf(buf, "%d | ", (int8_t)(err_percent*100));
  		usb_write(buf);*/
	}
	//usb_write("\n");
	
	if (err_sum == 0) 
	{
		if (is_on_line)
			check_losing_line();
		else
			error = pError;
	}
	else
		is_on_line = TRUE;
	
	for (uint8_t i = 0; i < LIGHTS; i++) 
	{
		prev_light_percent[i] = light_percent[i];
	}
	err_sum = err_sum == 0 ? 1 : err_sum; // avoid division by zero
	/*sprintf(buf, "%d", (int16_t) ( error / err_sum)  );
	usb_write(buf);
	usb_write("\n");*/
	return error / err_sum;
}

int16_t calc_speed(uint16_t *lights_max, uint16_t *lights_min)
{
	PORTB |= (1 << STATUS_LED2);
	pError = error;
	int16_t error = calc_error(lights_max, lights_min);
	PORTB &= ~(1 << STATUS_LED2);
	
	return (int16_t) (error * Kp + (error - pError) * Kd); 
}
