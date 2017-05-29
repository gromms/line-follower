
#include <avr/io.h>

void UART_init();


// UART andmed massiivides, ilma katkestuseta
void UART_write(char *data);
void motor_drive(int16_t left, int16_t right);
