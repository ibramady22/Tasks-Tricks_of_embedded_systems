#include "UART.h"
static void (*UART_TX_Fptr)(void)=NULL_PTR;
static void (*UART_RX_Fptr)(void)=NULL_PTR;
void UART_Init(void)
{
	/*baud rate=9600   */
	UBRRL=51;
	/* normal mode */
	CLR_BIT(UCSRA,U2X);
	/* frame 
	default bits in AVR in UCSRC
	no parity, 1 stop , asynchronous , 8 bits data*/
	
	/* enable */
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
}

void UART_Send(u8 data)
{
	while(!READ_BIT(UCSRA,UDRE));
	UDR=data;
}
u8 UART_Receive(void)
{
	while(!READ_BIT(UCSRA,RXC));
	return UDR;
}
void UART_Send_noBlock(u8 data)
{
	UDR=data;
}
u8 UART_Receive_noBlock(void)
{
	return UDR;
}

u8 UART_ReceivePeriodic(u8* pdata)
{
	if(READ_BIT(UCSRA,RXC))
	{
		*pdata=UDR;
		return 1;
	}
	return 0;
}

void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}
void UART_TX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
}
void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}
void UART_RX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
}
void UART_TX_SetCallBack(void(*localFptr)(void))
{
	UART_TX_Fptr=localFptr;
}

void UART_RX_SetCallBack(void(*localFptr)(void))
{
	UART_RX_Fptr=localFptr;
}

 ISR(USART_TXC_vect)
 {
	 if(UART_TX_Fptr!=NULL_PTR)
	 {
		 UART_TX_Fptr();
	 }
	 
 }
  ISR(USART_RXC_vect)
  {
	  if(UART_RX_Fptr!=NULL_PTR)
	  {
		  UART_RX_Fptr();
	  }
	  
  }