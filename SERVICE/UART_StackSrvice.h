
#ifndef UART_STACKSRVICE_H_
#define UART_STACKSRVICE_H_
#include "UART_Services.h"
#include "UART.h"

#define  size 20


/*********** store in stack two dimensions ***********************************************/
void UART_Push(void); //receive by interrupt(receive no block)and push in stack 
u8 pop(u8* pdata); //pop last element from the stack
void UART_StackSrvice_Init(void); //enable receive interrupt


/*********** store in stack two dimensions ***********************************************/
void UART_Push2(void); //receive by interrupt(receive no block)and push in stack
u8 pop_stringStack(u8* str, u8 max_length);//pop last element from the stack
void UART_StackSrvice_Init2(void); //enable receive interrupt






#endif /* UART_STACKSRVICE_H_ */