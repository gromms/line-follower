
#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "pinout.h"

void buttons_init();

bool_t check_stop_state();
bool_t check_start_state();

#endif