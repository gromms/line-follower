
#ifndef CALIB_H_
#define CALIB_H_

#include "pinout.h"

void calib_init(uint16_t*, uint16_t*);
void calib_start(uint16_t*, uint16_t*);
void calib_load();
bool_t calib_state();

#endif /* CALIB_H_ */