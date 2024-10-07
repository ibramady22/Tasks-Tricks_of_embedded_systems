


#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_
 
#include "UART.h"

#define  size 20  

void UART_SendString(u8* str); //busy w8
void UART_ReceiveString(u8* str); //busy w8
void UART_SendNumber(u32 num);  //busy w8 
void UART_SendNumber2(u32 num); //busy w8 && use pointer
u32 UART_ReceiveNumber(void);  //busy w8
u32 UART_ReceiveNumber2(void);  //busy w8 && use pointer
void UART_SendStringCheckSum(u8* str); //busy w8
u8 UART_ReceiveStringCheckSum(u8* str); //busy w8

// void UART_SendStringAsynch(u8* str); 
void UART_TX_StringsAsynch_init(void); 
u8 UART_SendStringsAsynch(u8* str); // send strings by Queue && asynchronous by interrupt








#endif /* UART_SERVICES_H_ */