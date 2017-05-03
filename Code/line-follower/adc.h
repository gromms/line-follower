#ifndef ADC_H
#define ADC_H

#include "pinout.h"

void adc_init();
void choose_mux(uint8_t mux);
void read_lights(uint16_t*);


#endif