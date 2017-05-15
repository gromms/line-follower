
#ifndef ESC_H_
#define ESC_H_

#include <avr/io.h>

void esc_init();
void esc_set_speed(uint8_t spd);
void esc_stop();
void esc_start();

#endif