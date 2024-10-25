/*
 * Traffic_stack_based.c
 *
 * Created: 22/10/2024 06:16:17 م
 *  Author: Ibrahim_Mady
 */ 

#include "Traffic_stack_based.h"

StateFunc stateStack[STACK_SIZE];

int top = -1;
static u8 time_counter=0;
static u8 flag_red_stert=0 ;
static u8 flag_green_stert=0 ;
static u8 flag_yellow_stert=0 ;
static u8 flag_Emergency_stert=0 ;
static u8 emergencyState_flag=0;


// Global variable to hold the current state function
volatile StateFunc currentState;

// Stack operations
static void pushState(StateFunc state) {
	if (top < STACK_SIZE - 1) {
		stateStack[++top] = state; //pre_increament
	}
}

static StateFunc  popState(void) {
	if (top >= 0) {
		return stateStack[top--];  //post_increament
	}
	return NULL;
}

/* update timer counter & handle popping from stack */
static void Update_TimeCounter(void)
{
	LCD_SetCursor(2,1);
	LCD_WriteNumber(time_counter);
	if(flag_Emergency_stert==1) // emergency mode is called
	{
		/*toggle lights*/
		DIO_TogglePin(PINC0);
		DIO_TogglePin(PINC1);
		DIO_TogglePin(PINC2);
		time_counter++;
		if(time_counter== max_EmergencyTime)
		{
			time_counter=0;
			/* back the timer interrupt to 400 u_sec*/
			Timer1_SetInterruptTime_ms(400,Update_TimeCounter);
			currentState=popState();
			flag_Emergency_stert=0;
			/*turn off all lights */
			DIO_WritePin(PINC0,LOW);
			DIO_WritePin(PINC1,LOW);
			DIO_WritePin(PINC2,LOW);
		}
	}
	else if(currentState==red_State)
	{
		if(time_counter==max_redTime+1)
		{
			time_counter=0;
			currentState=popState();
			/* reset all start_flags*/
			flag_red_stert=0;
			flag_green_stert=0;
			flag_yellow_stert=0;
			/*turn off red light */
			DIO_WritePin(RED_LED,LOW);
		}
		else
		{
			time_counter++;
		}
	}
	else if(currentState==green_State)
	{
		if(time_counter==max_greenTime+1)
		{
			time_counter=0;
			currentState=popState();
			/* reset all start_flags*/
			flag_red_stert=0;
			flag_green_stert=0;
			flag_yellow_stert=0;
			/*turn off red light */
			DIO_WritePin(GREEN_LED,LOW);
		}
		else
		{
			time_counter++;
		}
	}
	else if(currentState==yellow_State)
	{
		if(time_counter==max_yellowTime+1)
		{
			time_counter=0;
			currentState=popState();
			/* reset all start_flags*/
			flag_red_stert=0;
			flag_green_stert=0;
			flag_yellow_stert=0;
			/*turn off red light */
			DIO_WritePin(YELLOW_LED,LOW);
		}
		else
		{
			time_counter++;
		}
	}
	else 
	{
		/* no thing*/
	}
	
	
}
	

void red_State(void) 
{
	if( flag_red_stert==0)
	{
		/* LCD Screen */
		LCD_Clear();
		LCD_WriteString("STOP: ");
		/* turn on light & push next state */
		DIO_WritePin(RED_LED,HIGH);
		DIO_WritePin(GREEN_LED,LOW);
		DIO_WritePin(YELLOW_LED,LOW);
		pushState(green_State);
		flag_red_stert=1;
	}	
	else
	{
		/* do nothing*/
	}
}
void green_State(void) 
{
	if(flag_green_stert==0)
	{
		/* LCD Screen */
		LCD_Clear();
		LCD_WriteString("GO-- ");
		/* turn on light & push next state */
		DIO_WritePin(RED_LED,LOW);
		DIO_WritePin(GREEN_LED,HIGH);
		DIO_WritePin(YELLOW_LED,LOW);
		pushState(yellow_State);
		flag_green_stert=1;
	}
	else
	{
		/* do nothing*/
	}
}
void yellow_State(void) 
{
	if(flag_yellow_stert==0)
	{
		/* LCD Screen */
		LCD_Clear();
		LCD_WriteString("READY_2_STOP");
		/* turn on light & push next state */
		DIO_WritePin(RED_LED,LOW);
		DIO_WritePin(GREEN_LED,LOW);
		DIO_WritePin(YELLOW_LED,HIGH);
		pushState(red_State);
		flag_yellow_stert=1;
	}
	else
	{
		/* do nothing */
	}
}
void emergencyModeState(void) 
{
	if(flag_Emergency_stert==0)
	{
		/* empty the stack */
		popState();
		pushState(red_State);
		/* turn on all lights */
		DIO_WritePin(PINC0,HIGH);
		DIO_WritePin(PINC1,HIGH);
		DIO_WritePin(PINC2,HIGH);
		/* get interrupt every 100 u_sec */
		time_counter=0;
		Timer1_SetInterruptTime_ms(200,Update_TimeCounter);
		flag_Emergency_stert = 1;
		LCD_Clear();
		LCD_WriteString("EMERGENCY..");
	}
	
	
}

void Traffic_Init(void) 
{
	//set led pins as output(DIO_cfg.c) && turn off them
	DIO_WritePin(RED_LED,LOW);
	DIO_WritePin(GREEN_LED,LOW);
	DIO_WritePin(YELLOW_LED,LOW);
	
	/* initiate timer to get interrupt every 400 u_sec */
	/* Handle red,green and yellow modes           */
	Timer1_SetInterruptTime_ms(400,Update_TimeCounter);
	/* configure external interrupt                */
	/* handle Emergency Mode (pedestrian )         */
	EX_INT_SetSenseControl(EX_INT0,FALLING_EDGE);
	EX_INT_Enable(EX_INT0);
	EX_INT_SetCall_Back(EX_INT0,emergencyModeState);
	
	/* initiate the current state */
	currentState=red_State;
	
}
/* every state will push the next state by itself */
void Traffic_Runnable(void)
{
	currentState();
}