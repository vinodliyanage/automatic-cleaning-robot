#include <avr/io.h>
#include <avr/interrupt.h>

void UART_init(unsigned long F_CPU, unsigned long BAUDRATE)
{
	/*
	Asynchronous Normal Mode 
	
	BAUD (BAUDRATE OR BITS RATE) = F_CPU / (16UL * (UBRR + 1)) 
	UBRR (BAUD_PRESCALE) = (F_CPU / (BAUDRATE * 16UL)) - 1
	*/
	
	unsigned long BAUD_PRESCALE;
	BAUD_PRESCALE = (F_CPU / (BAUDRATE * 16L)) - 1;
	
	/*
	UCSRB Register: USART Control and Status Register B

	Bit 7 – RXCIE: RX Complete Interrupt Enable
	Writing one to this bit enables interrupt on the RXC Flag.

	Bit 6 – TXCIE: TX Complete Interrupt Enable
	Writing one to this bit enables interrupt on the TXC Flag.

	Bit 5 – UDRIE: USART Data Register Empty Interrupt Enable
	Writing one to this bit enables interrupt on the UDRE Flag.

	Bit 4 – RXEN: Receiver Enable
	Writing one to this bit enables the USART Receiver.

	Bit 3 – TXEN: Transmitter Enable
	Writing one to this bit enables the USART Transmitter.

	Bit 2 – UCSZ2: Character Size
	
	In order to receive and transmit data using serial communication, we need to put logic 1 to,
	RXEN AND TXEN bits.
	*/
	
	UCSRB |= (1 << RXEN) | (1 << TXEN) | (1 << RXCIE) | (1 << UDRIE); // Turn on transmission and reception
	
	/*
	UCSRC: USART Control and Status Register C
	
	Bit 7 – URSEL: Register Select
	This bit selects between accessing the UCSRC or the UBRRH Register, as both register shares the same address. 
	The URSEL must be *one (1) when writing the UCSRC or else data will be written in the UBRRH register.
	
	Bit 6 – UMSEL: USART Mode Select
	This bit selects between the Asynchronous and Synchronous mode of operation.

	0 = Asynchronous Operation
	1 = Synchronous Operation
	
	
	Bit 2:1 – UCSZ1:0: Character Size
	The UCSZ1:0 bits combined with the UCSZ2 bit in UCSRB sets the number of data bits (Character Size) 
	in a frame the Receiver and Transmitter use
	
	UCSZ2	UCSZ1	UCSZ0
	  0		  1		  1			8 bit
	 
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	 
	(1 << UCSZ0) | (1 << UCSZ1) :
	This part is for the character size, here I'm choosing 8 bit character size.
	*/
	
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); // Use 8-bit char size 
	
	/*
	UBRRL and UBRRH: USART Baud Rate Registers (store baud rate)
	
	UBRR Contents of the UBRRH and UBRRL Registers
	
	Bit 15 – URSEL: Register Select
	This bit selects between accessing the UCSRC or the UBRRH Register, as both register shares the same address. 
	The URSEL must be one when writing the UCSRC or else data will be written in the UBRRH register.
	
	UBRRH - UBRR[11:8] upper 8-bits
	UBBRL - URR[7:0] lower 8-bits of the baud rate
	
	e.g.
	
	UBRR - 0010 1001 1111 1010
	UBRRH - UBRR[11:8] = 0010 1001
	if UBRR >> 8 then the value is 0000 0000 0010 1001. therefore this way we can get upper 8 bits of UBRR
	
	UBBRL - UBRR[7:0] = 1111 1010
	*/
	
	UBRRL = BAUD_PRESCALE;		
	UBRRH = (BAUD_PRESCALE >> 8);
}

/*
UDR: USART Data Register

It has basically two registers, one is Tx. Byte and the other is Rx Byte. 
Both share the same UDR register. Do remember that, when we write to the UDR reg. 
Tx buffer will get written and when we read from this register, Rx Buffer will get read. 
Buffer uses the FIFO shift register to transmit the data.

**************************************************************************************************

UCSRA: USART Control and Status Register A

Bit 7 – RXC: USART Receive Complete
This flag bit is set when there is unread data in UDR. The RXC Flag can be used to generate a Receive Complete interrupt.

Bit 6 – TXC: USART Transmit Complete
This flag bit is set when the entire frame from Tx Buffer is shifted out and there is no new data currently present in the transmit buffer (UDR). The TXC Flag bit is automatically cleared when a transmit complete interrupt is executed, or it can be cleared by writing a one to its bit location. The TXC Flag can generate a Transmit Complete interrupt.

Bit 5 – UDRE: USART Data Register Empty
If UDRE is one, the buffer is empty which indicates the transmit buffer (UDR) is ready to receive new data. The UDRE Flag can generate a Data Register Empty Interrupt. 
UDRE is set after a reset to indicate that the transmitter is ready.

*/


ISR(USART_RXC_vect)
{	
	/*
	Receive Complete interrupt.
	this function will call when the data is received and there is unread data in the UDR register.
	add code down below
	*/
}

ISR(USART_UDRE_vect)
{	
	/*
	transmit Complete interrupt.
	this function will call when the transmit is completed.
	add code down below.
	*/	
}
