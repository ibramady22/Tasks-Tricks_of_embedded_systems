
#define F_CPU 8000000
#include <util/delay.h>
#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "Stepper.h"
#include "KEYPAD.h"
#include "ADC.h"
#include "EXINT.h"
#include "Sensors.h"
#include "SINE_LUT_interface.h"
#include "TIMER.h"
#include "Timers_Services.h"
#include "FixedPoint_interface.h"
#include "Event_Based_interface.h"

static num=0;
void tog (void )
{
	num++;
	if(num==20)
	{
		DIO_TogglePin(PINC1);
		num=0;
	}
	
}
int main() {			DIO_Init();	LCD_Init();	LCD_WriteNumber(3);	/*Enable global interrupt*/	sei();	/*************************	/* External event base system              	* event:   pressing button  	* action:  toggle 1            	*************************/	ButtonLed_System_Run();	/*************************	/* Internal event base system              	* event:   overflow timer 3s  	* action:  toggle led2            	*************************/	Timer_3s_System_Run();
	  while(1)	  {		  	  }	  	return 0;
}


























