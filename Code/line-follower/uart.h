
#include <avr/io.h>

void UART_init();


// UART andmed massiivides, ilma katkestuseta
void UART_write(char *data);
void motor_drive(uint8_t left, uint8_t right);
