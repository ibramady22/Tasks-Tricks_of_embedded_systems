


#ifndef NVM_H_
#define NVM_H_
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

u8 NVM_Read(u16 address);

void NVM_Write(u16 address, u8 value);



#endif /* NVM_H_ */