
#ifndef PID_H_
#define PID_H_

int16_t calc_error(uint16_t *lights_min, uint16_t *lights_max);
int16_t calc_speed(uint16_t *lights_min, uint16_t *lights_max);

#endif /* PID_H_ */