#include "NVM.h"



u8 NVM_Read(u16 address)
{
	while(READ_BIT(EECR,EEWE)); /* Wait for completion of previous write */
	EEAR=address; 
	SET_BIT(EECR,EERE); /* Start eeprom read by writing EERE */
	return EEDR;
}

void NVM_Write(u16 address, u8 data)
{
	while(READ_BIT(EECR,EEWE)); /* Wait for completion of previous write */
	EEAR=address;
	EEDR=data;
	SET_BIT(EECR,EEMWE); /* Write logical one to EEMWE */
	SET_BIT(EECR,EEWE); /* Start eeprom write by setting EEWE */	
}