#define KEYPAD_C  /* to include  Keys_array*/
#include "KEYPAD.h"


void KEYPAD_Init(void)
{
	DIO_WritePin(FIRST_OUTPUT,HIGH);
	DIO_WritePin(FIRST_OUTPUT+1,HIGH);
	DIO_WritePin(FIRST_OUTPUT+2,HIGH);
	DIO_WritePin(FIRST_OUTPUT+3,HIGH);
}

u8 KEYPAD_GetKey(void)   
{
	u8 r,c,key=NO_KEY;
	for(r=0;r<ROWS;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,LOW);
		for(c=0;c<COLS;c++)
		{
			if(DIO_ReadPin(FIRST_INPUT+c)==LOW)
			{
				key=KeysArray[r][c];
				while(DIO_ReadPin(FIRST_INPUT+c)==LOW);//busy wait
			}
		}
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
	}
	return key;
}