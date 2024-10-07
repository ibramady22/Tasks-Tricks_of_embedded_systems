

#ifndef SENSORS_H_
#define SENSORS_H_

#include "StdTypes.h"
#include "ADC.h"

typedef enum
{
	H2=0,
	LPG,
	ch4,
	CO,
	ALCHOL,
		}PRES_GasName;
	typedef enum
	{
		LOW_C,
		MEDUIM_C,
		HIGH_C
		}PRES_Gas_Concentrate;

/***********config**********/
#define LM35_CH CH_7
#define PRES_CH CH_0
#define POT_CH CH_7
#define MQ_CH CH_0

/**************************/

u16 TEMP_Read(void);     /*lm35*/ //return (temp*10) in cellesuis 
u16 TEMP2_Read(void);    /*potentiometer*/ //return (temp) in cellesuis
u16 PRES_MPX_Read(void); //return pressure in (kpa*10)
PRES_Gas_Concentrate PRES_MQ_ReadLevel(PRES_GasName gas); //return type of gas concentration 


#endif /* SENSORS_H_ */