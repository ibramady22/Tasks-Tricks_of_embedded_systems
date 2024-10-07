
#ifndef WDT_H_
#define WDT_H_

#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"

typedef enum{
	timeout_16ms=0,
	timeout_32ms,
	timeout_65ms,
	timeout_130ms,
	timeout_260ms,
	timeout_520ms,
	timeout_1000ms,
	timeout_2100ms,
	
	}TimeOut_type;
	
void WDT_Set(TimeOut_type time);
void WDT_Stop(void);
	




#endif /* WDT_H_ */