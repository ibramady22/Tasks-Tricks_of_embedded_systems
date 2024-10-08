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
/*********************************************************************************************************************************/
/*  Handling multiple action through one interrupt & Queue iclude all ctions to events & poll on keys   **************************/
/*********************************************************************************************************************************/

/* array has the events recorded and arranged by priority : index 0 has the highest priority   */
u8 Event_queue[4]={0};
	
	
	
/* to push an event in the queue **/
static void push_event (u8 event)
{
	Event_queue[event]++;
}
 /* to pop an event from the queue */
static void pop_event (u8 event)
{
	if(Event_queue[event]!=0)
	{
		Event_queue[event]--;
	}
}


/****************************************************************************/
/* to capture the events(poll on the keys ) recorded by priority ************/
/* an sw_timer interrupt every 100 ms (as the minimum press_key take 300 ms)*/
/* note: volt high---> not pressed    volt low--------->pressed             */
/****************************************************************************/
static void check_keys (void)
{
	static u8 key1_new=0,key1_prev=0,key2_new=0,key2_prev=0,key3_new=0,key3_prev=0,key4_new=0,key4_prev=0;
	key1_new=DIO_ReadPin(BUT1_PIN);
	key2_new=DIO_ReadPin(BUT2_PIN);
	key3_new=DIO_ReadPin(BUT3_PIN);
	key4_new=DIO_ReadPin(BUT4_PIN);
	if(key1_new==LOW && key1_prev==HIGH ) //to sure that it's new press on button 
	{
		push_event(EVNT_BUT1);
		key1_prev=key1_new;
	}
	else if(key1_new==HIGH)
	{
		key1_prev=HIGH;                    // return the button to not press state
	}
	else
	{
		/* Do nothing*/
	}
    if(key2_new==LOW && key2_prev==HIGH ) 
	{
		push_event(EVNT_BUT2);
		key2_prev=key2_new;
	}
	else if(key2_new==HIGH)
	{
		key2_prev=HIGH;
	}
	else
	{
		/* Do nothing*/
	}
    if(key3_new==LOW && key3_prev==HIGH ) 
	{
		push_event(EVNT_BUT3);
		key3_prev=key3_new;
	}
	else if(key3_new==HIGH)
	{
		key3_prev=HIGH;
	}
	else
	{
		/* Do nothing*/
	}
    if(key4_new==LOW && key4_prev==HIGH ) 
	{
		push_event(EVNT_BUT4);
		key4_prev=key4_new;
	}
	else if(key4_new==HIGH)
	{
		key4_prev=HIGH;
	}
	else
	{
		/* Do nothing*/
	}
}

/****************************************************************************/
/* set checking button occurred periodically */
/* set timer interrupt to fire every 100 ms  */
/****************************************************************************/
void MultiEvents_init(void)
{
	/* use timer service to get interrupt to check pressing buttons */
	Timer1_SetInterruptTime_ms(50,check_keys);
}


/****************************************************************************/	
/* to run the events recorded by priority */
/****************************************************************************/
void MultiEvents_process(void )
{
	if(Event_queue[EVNT_BUT1]!=0) //event 1
	{
		while(Event_queue[EVNT_BUT1]) // if this event 1 recorded more than 1 time
		{
			/*code of action 1*/
			DIO_TogglePin(LED1_PIN);
			/* pop the event from the queue */
			pop_event(EVNT_BUT1);
		}
	}
	else if(Event_queue[EVNT_BUT2]!=0) 
	{
		while(Event_queue[EVNT_BUT2]) 
		{
			/*code of action 2*/
			DIO_TogglePin(LED2_PIN);
			/* pop the event from the queue */
			pop_event(EVNT_BUT2);
		}
	} 
	else if(Event_queue[EVNT_BUT3]!=0)
	{
		while(Event_queue[EVNT_BUT3])
		{
			/*code of action 3*/
			DIO_TogglePin(LED3_PIN);
			/* pop the event from the queue */
			pop_event(EVNT_BUT3);
			
		}
	}
	else if(Event_queue[EVNT_BUT4]!=0)
	{
		while(Event_queue[EVNT_BUT4])
		{
			/*code of action 4*/
			DIO_TogglePin(LED4_PIN);
			/* pop the event from the queue */
			pop_event(EVNT_BUT4);
		}
	}
	else
	{
		/* do nothing*/
	}
}

	
/*********************************************************************************************************************************/

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