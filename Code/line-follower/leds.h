#ifndef LEDS_H
#define LEDS_H 

#include <avr/io.h>
#include "pinout.h"

void leds_init();
void set_led(uint8_t, bool);

#endif 