/*
 * Event_Based_program.c
 *
 * Created: 10/6/2024 11:32:58 AM
 *  Author: Ibrahim_Mady
 */ 

#include "DIO_interface.h"
#include "EXINT.h"
#include "Timers_Services.h"
#include "LCD_interface.h"
#include "Event_Based_interface.h"


static u8 counter_time =0;
static void Toggle_led1(void)
{
	DIO_TogglePin(LED1_PIN);
}
static void Toggle_led2(void)
{
	counter_time++;
	if(counter_time==60)
	{
		DIO_TogglePin(LED2_PIN);
		counter_time=0;
	}
	
}

/* external event: pressing button */
void ButtonLed_System_Run (void )
{
	/* initiate the dio */
	DIO_Init();
	/* initiate the external interrupt with  ext interrupt (0) and SenseControl (falling edge) */
	EX_INT_SetSenseControl(EX_INT0,FALLING_EDGE);
	EX_INT_SetCall_Back(EX_INT0,Toggle_led1);
	/* enable the interrupt & global interrupt */
	EX_INT_Enable(EX_INT0);
}

/* internal event: overflow timer (3 sec) */
void Timer_3s_System_Run (void )
{
	/* initiate the dio */
	DIO_Init();
	/**/
	Timer1_SetInterruptTime_ms(50,Toggle_led2);
	
}