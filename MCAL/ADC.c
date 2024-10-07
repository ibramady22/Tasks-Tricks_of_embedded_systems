#include "ADC.h"

u16 volt_ref;
u8 adc_flag=1;

void ADC_Init(ADC_Vref_type vref,ADC_Prescaler_type scaler)
{
	/* clock*/
	scaler&=0x07;
	ADCSRA&=0xf8;
	ADCSRA|=scaler;
	/* volt ref*/
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS1);
		CLR_BIT(ADMUX,REFS0);
		volt_ref=AREF;
		break;
		case VREF_AVCC:
		CLR_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		volt_ref=5000;
		break;
		case VREF_256:
		SET_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		volt_ref=2560;
		break;
	}
	
	CLR_BIT(ADMUX,ADLAR); // adcl,adch
	/* ADC ENABLE */
	SET_BIT(ADCSRA,ADEN);
}
u16 ADC_Read(ADC_Channel_type ch)  
{
	u16 adc, adcl,adch;
	/*select channel*/
	ADMUX&=0xe0; //11100000
	ADMUX|=ch;
	/* start conversion */
	SET_BIT(ADCSRA,ADSC);
	/*wait until finish*/
	while(READ_BIT(ADCSRA,ADSC));
	/* return read */
    adcl=ADCL; //As ADCL must read first due to data sheet
	adch=ADCH;
	adc=(u16)adcl | ((u16)adch<<8);
	//adc=ADC; p* to short
	return adc;
}

void ADC_StartConversion(ADC_Channel_type ch)
{
	if(adc_flag==1)
	{
		/*select channel*/
		ADMUX&=0xe0; //11100000
		ADMUX|=ch;
		/* start conversion */
		SET_BIT(ADCSRA,ADSC);
		adc_flag=0;
	}
}
Error_type ADC_GetReadPeriodic(u8* padc)
{
	u16 adcl,adch;
	if(!(READ_BIT(ADCSRA,ADSC)))
	{
			/* return read */
			adcl=ADCL; //As ADCL must read first due to data sheet
			adch=ADCH;
			padc=(u16)adcl | ((u16)adch<<8);
			adc_flag=1;
			return OK;
	}
	else
	{
		return NOK;
	}
}

u16 ADC_GetVolt(ADC_Channel_type ch)
{
	u16 adc=ADC_Read(ch);
	u16 volt=(adc*(u32)volt_ref)/1024;
	return volt;
}