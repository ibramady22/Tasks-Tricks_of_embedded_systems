
#ifndef EXINT_H_
#define EXINT_H_

typedef enum
{
	LOW_LEVEL=0,
	ANY_CHANGE=1,
	FALLING_EDGE,
	RISING_EDGE
}EXINT_SenseControl_type;

typedef enum
{
	EX_INT0,
	EX_INT1,
	EX_INT2
}EXINT_IntNumber_type;



extern void EX_INT_SetSenseControl(EXINT_IntNumber_type interrupt,EXINT_SenseControl_type type);
extern void EX_INT_Enable(EXINT_IntNumber_type interrupt);
extern void EX_INT_Disable(EXINT_IntNumber_type interrupt);
extern void EX_INT_SetCall_Back(EXINT_IntNumber_type interrupt, void(*ptr)(void));


#endif /* EXINT_H_ */