#ifndef UART_H_
#define UART_H_

void UART_init(long F_CPU, long BAUDRATE);
char UART_RxChar();
void UART_TxChar(char ch);
void UART_SendString(char *str);



#endif /* UART_H_ */