#include "WDT.h"

void WDT_Set(TimeOut_type time)
{
	u8 wdt_value=0x08;  //WDE set,WDTOE cleared  0B00001000
	wdt_value|=time; 
	WDTCR |= (1>>WDE) | (1<<WDTOE);
	WDTCR |=wdt_value;
	
} 

void WDT_Stop(void)
{
	WDTCR |= (1>>WDE) | (1<<WDTOE);
	WDTCR=0;
}
