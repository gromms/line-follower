#ifndef ADC_H
#define ADC_H

#include "pinout.h"

void adc_init();
void choose_mux(uint8_t);

uint16_t adc_read(uint8_t);
void read_lights(uint16_t*);
void read_proxes(uint16_t*);


#endif