#include "Utils.h"
#include "MemMap.h"
#include "StdTypes.h"
#include "EXINT.h"

static void (*NTO_fptr)(void)=NULL_PTR; 
static void (*NT1_fptr)(void)=NULL_PTR; 
static void (*NT2_fptr)(void)=NULL_PTR; 

void EX_INT_SetSenseControl(EXINT_IntNumber_type interrupt,EXINT_SenseControl_type type)
{
	if(interrupt==EX_INT1)
	{
		switch(type)
		{
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
			case ANY_CHANGE:
			SET_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
			break;
			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
		}
	}
	else if(interrupt==EX_INT0)
	{
		switch(type)
		{
			case LOW_LEVEL:
			CLR_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
			case ANY_CHANGE:
			SET_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
			case FALLING_EDGE:
			CLR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
		}
	}
	else if(interrupt==EX_INT2) //has  2 options only(rising or falling edge)
	{
		switch(type)
		{
			case LOW_LEVEL:
			SET_BIT(MCUCSR,ISC2);
			break;
			case ANY_CHANGE:
			SET_BIT(MCUCSR,ISC2);
			break;
			case FALLING_EDGE:
			CLR_BIT(MCUCSR,ISC2);
			break;
			case RISING_EDGE:
			SET_BIT(MCUCSR,ISC2);
			break;
		}
	}
}

void EX_INT_Enable(EXINT_IntNumber_type interrupt)
{
	if(interrupt==EX_INT1)
	{
		SET_BIT(GICR,INT1);
	}
	else if(interrupt==EX_INT0)
	{
		SET_BIT(GICR,INT0);
	}
	else if(interrupt==EX_INT2)
	{
		SET_BIT(GICR,INT2);
	}
	
	
}
void EX_INT_Disable(EXINT_IntNumber_type interrupt)
{
	if(interrupt==EX_INT1)
	{
		CLR_BIT(GICR,INT1);
	}
	else if(interrupt==EX_INT0)
	{
		CLR_BIT(GICR,INT0);
	}
	else if(interrupt==EX_INT2)
	{
		CLR_BIT(GICR,INT2);
	}
	
}

void EX_INT_SetCall_Back(EXINT_IntNumber_type interrupt, void(*ptr)(void))
{
	switch (interrupt)
	{
		case EX_INT1:
		NT1_fptr=ptr;
		break;
		case EX_INT0:
		NTO_fptr=ptr;
		break;
		case EX_INT2:
		NT2_fptr=ptr;
		break;
	}
}


ISR (INT0_vect)
{
	if(NTO_fptr!=NULL_PTR)
	{
		NTO_fptr();
	}
}
ISR (INT1_vect)
{
	if(NT1_fptr!=NULL_PTR)
	{
		NT1_fptr();
	}
}
ISR (INT2_vect)
{
	if(NT2_fptr!=NULL_PTR)
	{
		NT2_fptr();
	}
}