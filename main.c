#include <avr/io.h>
#include "UART_polling.h"

#ifndef F_CPU
#define F_CPU 8000000L
#endif

int main(void)
{
	char c;
	UART_init(F_CPU, 9600);
	
	while(1)
	{
		c = UART_RxChar();
		UART_TxChar(c);
	}
}

