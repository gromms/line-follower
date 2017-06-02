
#include "calib.h"
#include "pinout.h"
#include "uart.h"
#include "adc.h"
#include "leds.h"
#include <stdio.h>

void calib_init(uint16_t *lights_max, uint16_t *lights_min)
{
	for(uint8_t i = 0; i < LIGHTS; i++)
	{
		lights_min[i] = 1024;
		lights_max[i] = 0;
	}
}

void calib_start(uint16_t *lights_max, uint16_t *lights_min)
{
	motor_drive(0, 0);
	
	set_led(CALIB_LED, TRUE);
	
	for(uint8_t i = 0; i < LIGHTS; i++)
	{
		read_lights(light_vals);
		
		uint16_t current_reading = light_vals[i];
		uint16_t current_max = lights_max[i];
		uint16_t current_min = lights_min[i]; 
		
		if(current_reading < current_min)
			lights_min[i] = current_reading;
		else if(current_reading > current_max)
			lights_max[i] = current_reading;
		
// 		char buf[16];	
// 		sprintf(buf, "%d | %d -- ", lights_min[i], lights_max[i]);
// 		usb_write(buf);
	}
	/*usb_write("\n");*/
	set_led(CALIB_LED, FALSE);
}

void calib_load()
{
	//load calibration from eeprom
}