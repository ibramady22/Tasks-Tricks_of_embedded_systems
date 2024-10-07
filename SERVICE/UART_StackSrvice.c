#include "UART_StackSrvice.h"


/******* store in stack one dimensions ****************************************************************/
static int sp=0; //stack pointer
static int stack[size];
void UART_Push(void)
{
	u8 data;
	if(sp==size)
	{
		data=UART_Receive_noBlock();
		UART_SendString("stack full");
	}
	else
	{
		data=UART_Receive_noBlock();
		stack[sp]=data;
		sp++;
	}
}

u8 pop(u8* pdata)
{
	if(sp==0)
	{
		return 0;
	}
	else
	{
		sp--;
		*pdata=stack[sp];
		return 1;
	}
}

void UART_StackSrvice_Init(void) 
{
	UART_RX_SetCallBack(UART_Push);
	UART_RX_InterruptEnable();
}


/*********** store in stack two dimensions ***********************************************/
#define  max_chars 20
static u8 sp2=0; //stack pointer
static u8 character=0;
static u8 stack2[size][max_chars];


void UART_Push2(void)
{
	u8 data;
	if(sp2==size)
	{
		data=UART_Receive_noBlock();
		UART_SendString("stack full");
	}
	else
	{
		data=UART_Receive_noBlock();
		stack2[sp2][character]=data;
		if(data==13)
		{
			stack2[sp2][character]=0;
			sp2++;
			character=0;
		}
		else
		{
			character++;
		}
	}
}

u8 pop_stringStack(u8* str, u8 max_length) //return 0 if stack is empty  or 1  ,and take string which will fill it
{
	u8 i=0;
	if(sp2==0)
	{
		return 0;
	}
	else
	{
		sp2--;
		for(i=0;i<(max_length-1) && (stack2[sp2][i]!=0);i++)
		{
			str[i]=stack2[sp2][i];
		}
		str[i]=0;
		return 1;
	}
}

void UART_StackSrvice_Init2(void)
{
	UART_RX_SetCallBack(UART_Push2);
	UART_RX_InterruptEnable();
}

