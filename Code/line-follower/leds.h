#ifndef LEDS_H
#define LEDS_H 

#include <avr/io.h>

void leds_init();
void set_led(uint8_t channel, uint8_t on_off);

#endif 