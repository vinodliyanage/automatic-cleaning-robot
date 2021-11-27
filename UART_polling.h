/***********************************************************************
  
            https://github.com/VinodLiyanage/GLASS-CLEANER-ROBOT
  -------------------------------- (C) ---------------------------------
  
  @name UART_polling.h
  @version 1.0.0
  @author Vinod Liyanage
  @description UART serial communication library (polling method)

************************************************************************/


#ifndef UART_H_
#define UART_H_

void UART_init(unsigned long F_CPU, unsigned long BAUDRATE);
char UART_RxChar();
void UART_TxChar(char ch);
void UART_SendString(char *str);



#endif /* UART_H_ */