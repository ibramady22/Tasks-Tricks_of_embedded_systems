#ifndef SPI_H_
#define SPI_H_

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

typedef enum{
	MASTER,
	SLAVE
	}SPI_ModeType;
	
void SPI_Init(SPI_ModeType mode);
u8 SPI_SendReceive(u8 data);  
void SPI_Send_NoBlock(u8 data);
void SPI_InterruptEnable(void);
void SPI_InterruptDisable(void);
void SPI_SetCallback(void(*ptr)(void));



#endif /* SPI_H_ */