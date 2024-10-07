#include "SPI.h"

static  void(*SPI_fptr)(void)=NULL_PTR;
void SPI_Init(SPI_ModeType mode)
{
	//clock
	/*default is 2 MHZ*/
	//Master or slave
	if(mode==MASTER)
	{
		SET_BIT(SPCR,MSTR);
	}
	else
	{
		CLR_BIT(SPCR,MSTR);
	}
	// SPI enable
	SET_BIT(SPCR,SPE);
}
u8 SPI_SendReceive(u8 data)
{
	SPDR=data;
	while(!READ_BIT(SPSR,SPIF)); //flag is set when transfer is done 
	return SPDR; //flag is clr if you read SPDR 
}
void SPI_Send_NoBlock(u8 data)
{
	SPDR=data;
}
void SPI_InterruptEnable(void)
{
	SET_BIT(SPCR,SPIE);
}
void SPI_InterruptDisable(void)
{
	CLR_BIT(SPCR,SPIE);
}
void SPI_SetCallback(void(*ptr)(void))
{
	SPI_fptr=ptr;
}
ISR(SPI_STC_vect)
{
	if(SPI_fptr!=NULL_PTR)
	{
		SPI_fptr();
	}
}