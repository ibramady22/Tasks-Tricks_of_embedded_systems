
#include "Stepper.h"

void STEPPER_Bipolar_CW(void)
{
	DIO_WritePin(COIL1A,HIGH); //coil1 +-
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW); //coil2 +-
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,HIGH);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,LOW); //coil1 -+
	DIO_WritePin(COIL1B,HIGH);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,LOW);//coil2 -+
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,HIGH);
	_delay_ms(DELAY);
}
void STEPPER_Bipolar_CCW(void)
{
		DIO_WritePin(COIL1A,LOW);//coil2 -+
		DIO_WritePin(COIL1B,LOW);
		DIO_WritePin(COIL2A,LOW);
		DIO_WritePin(COIL2B,HIGH);
		_delay_ms(DELAY);
		DIO_WritePin(COIL1A,LOW); //coil1 -+
		DIO_WritePin(COIL1B,HIGH);
		DIO_WritePin(COIL2A,LOW);
		DIO_WritePin(COIL2B,LOW);
		_delay_ms(DELAY);
		DIO_WritePin(COIL1A,LOW); //coil2 +-
		DIO_WritePin(COIL1B,LOW);
		DIO_WritePin(COIL2A,HIGH);
		DIO_WritePin(COIL2B,LOW);
		_delay_ms(DELAY);
		DIO_WritePin(COIL1A,HIGH); //coil1 +-
		DIO_WritePin(COIL1B,LOW);
		DIO_WritePin(COIL2A,LOW);
		DIO_WritePin(COIL2B,LOW);
		_delay_ms(DELAY);
}

void STEPPER_Unipolar_CW(void)
{
	
	
	DIO_WritePin(COIL1A,LOW); 
	DIO_WritePin(COIL1B,HIGH);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,LOW); 
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,HIGH);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,HIGH); 
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
}
void STEPPER_Unipolar_CCW(void)
{
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,HIGH);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,HIGH);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	
	
}
void STEPPER_Unipolar_CW_HS(void)
{
	
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,HIGH);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,HIGH);
	DIO_WritePin(COIL2A,HIGH);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,HIGH);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
		DIO_WritePin(COIL1A,LOW);
		DIO_WritePin(COIL1B,LOW);
		DIO_WritePin(COIL2A,HIGH);
		DIO_WritePin(COIL2B,HIGH);
		_delay_ms(DELAY);
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL1B,HIGH);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
}
void STEPPER_Unipolar_CCW_HS(void)
{
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,HIGH);
	DIO_WritePin(COIL2B,HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,LOW);
	DIO_WritePin(COIL2A,HIGH);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,HIGH);
	DIO_WritePin(COIL2A,HIGH);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	
	DIO_WritePin(COIL1A,LOW);
	DIO_WritePin(COIL1B,HIGH);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A,HIGH);
	DIO_WritePin(COIL1B,HIGH);
	DIO_WritePin(COIL2A,LOW);
	DIO_WritePin(COIL2B,LOW);
	_delay_ms(DELAY);
	
	
}
void STEPPER_Hybrid_ByAngle(s16 angle)
{
	s16 i;
	angle*=10;
	if(angle>0)
	{
		for(i=0;i<(s16)(angle/(STEP*10*4));i++)
		{
			STEPPER_Unipolar_CW();
		}
	}
	else if (angle<0)
	{
		for(i=(angle/(-STEP*10*4));i>=0;i--)
		{
			STEPPER_Unipolar_CCW();
		}
	}
}
void STEPPER_Hybrid_ByRotations(s16 rot)
{
	s16 i;
	s8 j;
	if(rot>0)
	{
		for(j=0;j<rot;j++)
		{
			for(i=0;i<(3600/(STEP*10*4));i++)
			{
				STEPPER_Unipolar_CW();
			}	
		}
	}
	else if (rot<0)
	{
		for(j=rot;j>0;j--)
		{
			for(i=0;i<(3600/(STEP*10*4));i++)
			{
				STEPPER_Unipolar_CW();
			}
		}
	}
}