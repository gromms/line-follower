
#include "uart.h"
#include <avr/io.h>
#include "pinout.h"

void UART_init() 
{
	UBRR1 = 51; // baudrate 19200 @16MHz 
	UCSR1B |= (1<<TXEN1); // TX enable
	UCSR1C |= (1<<UCSZ10)|(1<<UCSZ11); // Set frame format: 8data, 1 stop bit
}

// UART andmed massiivides, ilma katkestuseta
/* void UART_read(uint8_t *massiiv) {
	
}
void UART_write(uint8_t *massiiv) {
	
} */