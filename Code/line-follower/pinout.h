#ifndef PINOUT_H
#define PINOUT_H


// Proximity sensors

#define PROX1 ADC0
#define PROX2 ADC1
#define PROX3 ADC4


// Accelerometer 

#define ACCEL_X ADC5	
#define ACCEL_Z ADC6


// IR line sensors

#define IR0 ADC7
#define IR1 ADC10
#define IR2 ADC9
#define IR3 ADC8
#define IR4 ADC13
#define IR5 ADC12
#define IR6 ADC11


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

#define ESC_PWM OC0A

void write_pins(uint16_t port, uint16_t pins);
void read_pin(uint16_t port, uint16_t pin);


#endif