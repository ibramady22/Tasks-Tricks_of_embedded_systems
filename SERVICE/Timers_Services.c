
#include "Timers_Services.h"
#include "DIO_interface.h"
#include "LCD_interface.h"

volatile u16 t1,t2,t3,flag=0;

/**********************************************PWM*********************************************************/
void PWM_Init(void)
{
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8,OCRA_NON_INVERTING,OCRB_DISCONNECTED);
	
}
void PWM_Freq_KHZ(u16 freq)
{
	if (freq==0);
	else
	{
		u16 Ttotal=1000/freq;
		if (Ttotal>=1)
		{
			ICR1=Ttotal-1;
		}
		else ICR1=0;
		
	}
}
void PWM_Freq_HZ(u16 freq)
{
	if (freq==0);
	else
	{
		u16 Ttotal=(u32)1000000/freq;
		if (Ttotal>=1)
		{
			ICR1=Ttotal-1;
		}
		else ICR1=0;
	}



}
void PWM_Duty(u16 duty)
{
	 if (duty<=100)
	{
		u16 Ton=((u32)duty*(ICR1+1))/100;
		if (Ton>1)
		{
			OCR1A=Ton-1;	
		}
		else
		OCR1A=0;	
	}
}
/******************************************Set Interrupt Time******************************************************/
/* maximum 65 ms**/
void Timer1_SetInterruptTime_ms (u16 time,void(*LocalFptr)(void))
{
	Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_8,OCRA_DISCONNECTED,OCRB_DISCONNECTED);
	OCR1A=(u32)((u32)time*1000)-1;
	Timer1_OCA_SetCallBack(LocalFptr);
	Timer1_OCA_InterruptEnable();
}
void Timer1_SetInterruptTime_us (u16 time,void(*LocalFptr)(void))
{
	Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_8,OCRA_DISCONNECTED,OCRB_DISCONNECTED);
	OCR1A=(time)-1;
	Timer1_OCA_SetCallBack(LocalFptr);
	Timer1_OCA_InterruptEnable();
}

/**********************************************Measure PWM*********************************************************/
void PWM_Measure2(u32* Pfreq,u8* Pduty)
{
	u16 Ton,Toff;
	flag=0;
	TCNT1=0;
	while (DIO_ReadPin(PIND6));
	while (!DIO_ReadPin(PIND6));
	TCNT1=0;
	while (DIO_ReadPin(PIND6));
	Ton=TCNT1;
	TCNT1=0;
	while (!DIO_ReadPin(PIND6));
	Toff=TCNT1;
	*Pduty=((u32)Ton*100)/(Ton+Toff);
	*Pfreq=(u32)1000000/((u32)Toff+Ton);
}


void PWM_Measure(u32* Pfreq,u8* Pduty)
{
	u16 Ton,Toff;
	
	TCNT1=0;
	Timer1_ICU_SetCallBack(Func_ICU);
	Timer1_InputCaptureEdge(RISING);
	Timer1_ICU_InterruptEnable();
	flag=0;
	while(flag<3);
	Ton=t2-t1;
	Toff=t3-t2;

	*Pduty=((u32)Ton*100)/((u32)Ton+Toff);
	*Pfreq=(u32)1000000/((u32)Toff+Ton);

}

static void Func_ICU(void)
{
	if (flag==0)
	{
		t1=ICR1;
		Timer1_InputCaptureEdge(FALLING);
		flag=1;
	}
	else if (flag==1)
	{
		t2=ICR1;
		Timer1_InputCaptureEdge(RISING);
		flag=2;		
	}
	else if (flag==2)
	{
		t3=ICR1;
		Timer1_ICU_InterruptDisable();
		flag=3;
	}	
	
	
	
}