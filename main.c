
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


int main() {			DIO_Init();	LCD_Init();	LCD_WriteNumber(5);	/************************************************************************/	/*Enable global interrupt*/	sei();	/************************************************************************/	MultiEvents_init();
	  while(1)	  {		  MultiEvents_process();	  }	  	return 0;
}


























