

#ifndef UART_H_
#define UART_H_

#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"

void UART_Init(void);
void UART_Send(u8 data);
u8 UART_Receive(void);
void UART_Send_noBlock(u8 data);
u8 UART_Receive_noBlock(void);
u8 UART_ReceivePeriodic(u8* pdata);
void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);
void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);
void UART_TX_SetCallBack(void(*localFptr)(void));
void UART_RX_SetCallBack(void(*localFptr)(void));



#endif /* UART_H_ */