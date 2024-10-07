#include "RGB.h"
#include "TIMER.h"

static RGB_Color_type color;
void RGB_Init(void)
{
	/*timer0 setting*/
	Timer0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	Timer0_OC0_Mode(OCO_NON_INVERTING);
	/*timer1 setting*/
	Timer1_InputCaptureEdge(RISING);
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER0_SCALER_8,OCRA_NON_INVERTING,OCRB_NON_INVERTING);
	ICR1=255; //top
}
void RGB_Get_color(RGB_Color_type color)
{
	RED_PIN=RGB_COLORS[color][0];
	GREEN_PIN=RGB_COLORS[color][1];
	BLUE_PIN=RGB_COLORS[color][2];
}

void RGB_shadow(RGB_Color_type color1 ,RGB_Color_type color2)
{
	RGB_Get_color(color1);	
	color=color2;
	Timer0_OV_InterruptEnable();
}
// ISR(TIMER0_OVF_vect)
// {
// 	static u16 C=0;
// 	C++;
// 	if(C%100==0)
// 	{
// 		if((RED_PIN==RGB_COLORS[color][0])&&(GREEN_PIN==RGB_COLORS[color][1])&&(BLUE_PIN==RGB_COLORS[color][2]))
// 		{
// 			Timer0_OV_InterruptDisable();
// 		}
// 		else
// 		{
// 			if(RED_PIN>RGB_COLORS[color][0])
// 			{
// 				RED_PIN--;
// 			}
// 			else if (RED_PIN<RGB_COLORS[color][0])
// 			{
// 				RED_PIN++;
// 			}
// 			if(GREEN_PIN>RGB_COLORS[color][1])
// 			{
// 				GREEN_PIN--;
// 			}
// 			else if (GREEN_PIN<RGB_COLORS[color][1])
// 			{
// 				GREEN_PIN++;
// 			}
// 			if(BLUE_PIN>RGB_COLORS[color][2])
// 			{
// 				BLUE_PIN--;
// 			}
// 			else if (BLUE_PIN<RGB_COLORS[color][2])
// 			{
// 				BLUE_PIN++;
// 			}
// 		}
// 	}
// }