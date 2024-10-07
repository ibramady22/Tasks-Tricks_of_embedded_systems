#include "Sensors.h"




/**** (RS/RO *100) FOR (H2,LPG,ch4,CO,ALCHOL) in this order at(30%  and  50%)***/
static const u16 RS_RO[5][2]={{78,72},{24,19},{35,28},{260,250},{205,190}};

u16 TEMP_Read(void)
{
	u16 volt=ADC_GetVolt(LM35_CH);
	u16 temp=volt;
	return temp;
}

u16 TEMP2_Read(void)
{
	u16 adc=ADC_Read(POT_CH);
	u16 temp=(120*(u32)adc)/980;
	return temp;
}


u16 PRES_MPX_Read(void)
{
	u16 adc=ADC_Read(LM35_CH);
	u16 pres=((u32)(1150-150)*(adc-55))/(976-55)+150;
	return pres;
}
PRES_Gas_Concentrate PRES_MQ_ReadLevel(PRES_GasName gas)
{
	PRES_Gas_Concentrate conc=LOW_C;
	u16 volt=ADC_GetVolt(MQ_CH);
	u16 rs_ro=((((u32)5000-volt)*100)/5000);
	if(rs_ro>RS_RO[gas][0])
	{
		conc=LOW_C;
	}
	else if(rs_ro>RS_RO[gas][1])
	{
		conc=MEDUIM_C;
	}
	else if(rs_ro<RS_RO[gas][1])
	{
		conc=HIGH_C;
	}
	else
	{	
	}
	return conc;
}