#include "Ultrasonic_interface.h"
#include "Ultrasonic_private.h"

volatile static u8 Flag=0;
volatile static s32 Time1=0;
volatile static s32 Time2=0;
volatile static u16 Count=0;

static void Measure_ISR(void);
static void Timer_Ov_ISR(void);
u16 Get_Distance(Ultrasonic_Number_type u)
{
	u32 diff=0;
	u16 distance=0;
	//set callback
	Timer1_ICU_SetCallBack(Measure_ISR);
	Timer1_OVF_SetCallBack(Timer_Ov_ISR);
	//enable interrupts.
	Timer1_InputCaptureEdge(RISING);
	Timer1_ICU_InterruptEnable();
	Timer1_OVF_InterruptEnable();
	//enable trigger for ultrasonic.
	DIO_WritePin(Ultra_Trigger_Array[u],HIGH);
	_delay_us(10);
	DIO_WritePin(Ultra_Trigger_Array[u],LOW);
	/*Busy Wait.*/
	while(2 > Flag);
	diff = ((Count*(u32)OV_VALUE)+Time2) - Time1;
	distance = diff/58;
	Flag=0;
	Count=0;
	return (distance);
}

static void Measure_ISR(void)
{
	if(0 == Flag)
	{
		Time1 = ICR1;
		Count=0;
		Timer1_InputCaptureEdge(FALLING);
		Flag=1;
	}
	else if(1 == Flag)
	{
		Time2=ICR1;
		Timer1_ICU_InterruptDisable();
		Timer1_OVF_InterruptDisable();
		Flag=2;
	}
	else{;}
}
static void Timer_Ov_ISR(void)
{
	Count++;
}
