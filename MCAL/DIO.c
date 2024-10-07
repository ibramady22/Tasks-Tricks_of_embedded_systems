#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_interface.h"
#include "DIO_private.h"






void DIO_Init(void)
{
	DIO_Pin_type i;
	for(i=PINA0;i<TOTAL_PINS;i++)
	{
		DIO_InitPin(i,PinsStatusArray[i]);
	}
}

 static void DIO_InitPin(DIO_Pin_type pin, DIO_PinStatus_type status )
{
	DIO_Port_type port=pin/8;
	u8 Pin_num=pin%8;
	switch (status)
	{
		case OUTPUT:
		switch(port)
		{
			case PA:
			SET_BIT (DDRA,Pin_num);
			CLR_BIT(PORTA,Pin_num);
			break;
			case PB:
			SET_BIT (DDRB,Pin_num);
			CLR_BIT(PORTB,Pin_num);
			break;
			case PC:
			SET_BIT (DDRC,Pin_num);
			CLR_BIT(PORTC,Pin_num);
			break;
			case PD:
			SET_BIT (DDRD,Pin_num);
			CLR_BIT(PORTD,Pin_num);
			break;
		}
		break;
		case INFREE:
		switch(port)
		{
			case PA:
			CLR_BIT (DDRA,Pin_num);
			CLR_BIT(PORTA,Pin_num);
			break;
			case PB:
			CLR_BIT (DDRB,Pin_num);
			CLR_BIT(PORTB,Pin_num);
			break;
			case PC:
			CLR_BIT (DDRC,Pin_num);
			CLR_BIT(PORTC,Pin_num);
			break;
			case PD:
			CLR_BIT (DDRD,Pin_num);
			CLR_BIT(PORTD,Pin_num);
			break;
		}
		break;
		case INPULL:
		switch(port)
		{
			case PA:
			CLR_BIT (DDRA,Pin_num);
			SET_BIT(PORTA,Pin_num);
			break;
			case PB:
			CLR_BIT (DDRB,Pin_num);
			SET_BIT(PORTB,Pin_num);
			break;
			case PC:
			CLR_BIT (DDRC,Pin_num);
			SET_BIT(PORTC,Pin_num);
			break;
			case PD:
			CLR_BIT (DDRD,Pin_num);
			SET_BIT(PORTD,Pin_num);
			break;
		}
		break;
	}
	
}


void DIO_WritePin(DIO_Pin_type pin,DIO_PinVoltage_type volt  ) //write ..... always output
{
	DIO_Port_type port=pin/8;
	u8 Pin_num=pin%8;
	if(volt==HIGH)
	{
		switch(port)
		{
			case PA:
			SET_BIT(PORTA,Pin_num);
			break;
			case PB:
			SET_BIT(PORTB,Pin_num);
			break;
			case PC:
			SET_BIT(PORTC,Pin_num);
			break;
			case PD:
			SET_BIT(PORTD,Pin_num);
			break;
		}
	}
	else if (volt==LOW)
	{
		switch(port)
		{
			case PA:
			CLR_BIT(PORTA,Pin_num);
			break;
			case PB:
			CLR_BIT(PORTB,Pin_num);
			break;
			case PC:
			CLR_BIT(PORTC,Pin_num);
			break;
			case PD:
			CLR_BIT(PORTD,Pin_num);
			break;
		}
	}
}
DIO_PinVoltage_type DIO_ReadPin(DIO_Pin_type pin ) //read.... always input
{
	DIO_Port_type port=pin/8;
	u8 Pin_num=pin%8;
	DIO_PinVoltage_type volt;
	if(port==PA)
	{		
		volt=READ_BIT(PINA,Pin_num);  /* necessary to put LOW=0 and HIGH=1 in enum*/
	}
	else if(port==PB)
	{
		volt=READ_BIT(PINB,Pin_num);
	}
	else if(port==PC)
	{
		volt=READ_BIT(PINC,Pin_num);
	}
	else 
	{
		volt=READ_BIT(PIND,Pin_num);
	}
	return volt;
}
static void DIO_InitPin2(DIO_Pin_type pin, DIO_PinStatus_type status )
{
	if(pin<PINB0)
	{
		switch(status)
		{
			case OUTPUT:
			SET_BIT(DDRA,pin);
			CLR_BIT(PORTA,pin);
			break;
			case INFREE:
			CLR_BIT(DDRA,pin);
			CLR_BIT(PORTA,pin);
			break;
			case INPULL:
			CLR_BIT(DDRA,pin);
			SET_BIT(PORTA,pin);
		}
	}
	else if(pin<PINC0)
	{
		switch(status)
		{
			case OUTPUT:
			SET_BIT(DDRB,(pin-PINB0));
			CLR_BIT(PORTB,(pin-PINB0));
			break;
			case INFREE:
			CLR_BIT(DDRB,(pin-PINB0));
			CLR_BIT(PORTB,(pin-PINB0));
			break;
			case INPULL:
			CLR_BIT(DDRB,(pin-PINB0));
			SET_BIT(PORTB,(pin-PINB0));
		}
	}
	else if(pin<PIND0)
	{
		switch(status)
		{
			case OUTPUT:
			SET_BIT(DDRC,(pin-PINC0));
			CLR_BIT(PORTC,(pin-PINC0));
			break;
			case INFREE:
			CLR_BIT(DDRC,(pin-PINC0));
			CLR_BIT(PORTC,(pin-PINC0));
			break;
			case INPULL:
			CLR_BIT(DDRC,(pin-PINC0));
			SET_BIT(PORTC,(pin-PINC0));
		}
	}
	else
	{
		switch(status)
		{
			case OUTPUT:
			SET_BIT(DDRD,(pin-PIND0));
			CLR_BIT(PORTD,(pin-PIND0));
			break;
			case INFREE:
			CLR_BIT(DDRD,(pin-PIND0));
			CLR_BIT(PORTD,(pin-PIND0));
			break;
			case INPULL:
			CLR_BIT(DDRD,(pin-PIND0));
			SET_BIT(PORTD,(pin-PIND0));
		}
	}
}
void DIO_WritePin2(DIO_Pin_type pin,DIO_PinVoltage_type volt ) 
{
	if(pin<PINB0)
	{
		if(volt==HIGH)
		{
			SET_BIT(PORTA,pin);
		}
		else if (volt==LOW)
		{
			CLR_BIT(PORTA,pin);
		}
	}
	else if(pin<PINC0)
	{
		if(volt==HIGH)
		{
			SET_BIT(PORTB,(pin-PINB0));
		}
		else if (volt==LOW)
		{
			CLR_BIT(PORTB,(pin-PINB0));
		}
	}
	else if(pin<PIND0)
	{
		if(volt==HIGH)
		{
			SET_BIT(PORTC,(pin-PINC0));
		}
		else if (volt==LOW)
		{
			CLR_BIT(PORTC,(pin-PINC0));
		}
	}
	else 
	{
		if(volt==HIGH)
		{
			SET_BIT(PORTD,(pin-PIND0));
		}
		else if (volt==LOW)
		{
			CLR_BIT(PORTD,(pin-PIND0));
		}
	}
}
DIO_PinVoltage_type DIO_ReadPin2(DIO_Pin_type pin)
{
	DIO_PinVoltage_type volt;
	if(pin<PINB0)
	{
		volt=READ_BIT(PINA,pin); /* necessary to put LOW=0 and HIGH=1 in enum*/
	}
	else if(pin<PINC0)
	{
		volt=READ_BIT(PINB,(pin-PINB0));
	}
	else if(pin<PIND0)
	{
		volt=READ_BIT(PINC,(pin-PINC0));
	}
	else
	{
		volt=READ_BIT(PIND,(pin-PIND0));
	}
	return volt;
}

void DIO_TogglePin(DIO_Pin_type pin)
{
	if(pin<PINB0)
	{
		TOGGLE_BIT(PORTA,pin);
	}
	else if(pin<PINC0)
	{
		TOGGLE_BIT(PORTB,(pin-PINB0));
	}
	else if(pin<PIND0)
	{
		TOGGLE_BIT(PORTC,(pin-PINC0));
	}
	else
	{
		TOGGLE_BIT(PORTD,(pin-PIND0));
	}
}

void DIO_WritePort (DIO_Port_type port, u8 value)
{
	switch(port)
	{
		case PA:
		PORTA=value;
		break;
		case PB:
		PORTB=value;
		break;
		case PC:
		PORTC=value;
		break;
		case PD:
		PORTD=value;
		break;
	}
}
u8 DIO_ReadPort(DIO_Port_type port )
{
	u8 value;
	switch(port)
	{
		case PA:
		value=PINA;
		break;
		case PB:
		value=PINB;
		break;
		case PC:
		value=PINC;
		break;
		case PD:
		value=PIND;
		break;
	}
	return value;
}

