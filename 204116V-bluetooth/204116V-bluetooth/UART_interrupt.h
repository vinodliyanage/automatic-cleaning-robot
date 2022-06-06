#ifndef UART_INTERRUPT_H_
#define UART_INTERRUPT_H_

#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz clock speed
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#define BAUDRATE 9600
#define BAUD_PRESCALE ((F_CPU / (BAUDRATE * 16L)) - 1)


void UART_init();
void UART_TxString(char *str);
		
#endif /* UART_INTERRUPT_H_ */