#ifndef PINOUT_H
#define PINOUT_H

#include <avr/io.h>

#define TRUE 1
#define FALSE 0
typedef unsigned char bool_t;

#define CLEAR_PIN(port, pin) (port &= ~(1 << pin))
//#define BIT_SET(a,b) ((a) = (1<<(b)))
#define CHECK_PIN(port, pin) (port & (1 << pin))

void BIT_SET(uint8_t *port, uint8_t pin);

// Proximity sensors

#define PROX1 0b000000
#define PROX2 0b000001
#define PROX3 0b000100


// Accelerometer 

#define ACCEL_X 0b000101	
#define ACCEL_Z 0b000110


// IR line sensors

#define IR0 0b000111
#define IR1 0b100010
#define IR2 0b100001
#define IR3 0b100000
#define IR4 0b100101
#define IR5 0b100100
#define IR6 0b100011


// Line sensors' multiplexer select

#define MUX_S PE6


// Arduino interrupt pins

#define IP1 INT1
#define IP2 PCINT2


// LEDs

#define STATUS_LED1 PC7
#define STATUS_LED2 PB2
#define CALIB_LED PC6


// Buttons

#define START PD5
#define STOP INT0
#define CALIB PB1


// RS-485 pins

#define DE PB0
#define RX RXD1
#define TX TXD1


// ESC PWM pin

#define ESC_PWM PB7

void write_pins(uint16_t, uint16_t);
void read_pin(uint16_t, uint16_t);

#define LIGHTS_PER_HALF 7
#define LIGHTS 14
#define PROXES 3

uint16_t light_vals[LIGHTS];
uint16_t prox_vals[PROXES];

uint16_t lights_max[LIGHTS];
uint16_t lights_min[LIGHTS];

#endif