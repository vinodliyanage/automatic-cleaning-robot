#include <avr/io.h>

#include "lcdlib.h"
#include "UART_interrupt.h"

#ifndef F_CPU
#define F_CPU 8000000L
#endif

#include <util/delay.h>

static volatile unsigned char a = 0;

int main(void)
{
	sei();
	LCD_init();
	UART_init();
	
	while (1)
	{
		if(a == 1)
		{
			LCD_write_char(PINB, 1,1);
			a = 0;
		}
	}
}


ISR(USART_RXC_vect)
{
	PORTB = UDR;
	a = 1;
}



ISR(USART_UDRE_vect)
{

}