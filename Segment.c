#include "MemMap.h"
#include "Utils.h"
#define F_CPU 8000000
#define SEG_PORT PORTA
#define SEG_PORT2 PORTC


#include <util/delay.h>

void segment_dis(char n)
{
	char pattern[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; //pattern 0 to F
	PORTD=pattern[n];
}
void segment_2dis(char n)
{
	char pattern[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};   //pattern 0 to F
	PORTD=pattern[n/10];
	PORTC=pattern[n%10];
}
void segment_2dis_bsd(char n) //one port
{
	PORTC=((n/10)<<4)| (n%10);
}
void segment_2dis_bsdHEX(char n) //one port
{
	PORTC=n;
}
void segment_2dis_MUX(char n)
{
	char pattern[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};   //pattern 0 to F
	char d0=n/10;
	char d1=n%10;
	
	SET_BIT(SEG_PORT2,6);
	SEG_PORT=pattern[d1]<<1;
	CLR_BIT(SEG_PORT2,7);
	_delay_ms(10);
	SET_BIT(SEG_PORT2,7);
	SEG_PORT=pattern[d0]<<1;
	CLR_BIT(SEG_PORT2,6);
	_delay_ms(10);
	
}