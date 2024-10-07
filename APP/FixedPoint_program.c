/*
 * FixedPoint_program.c
 *
 * Created: 9/24/2024 1:23:59 AM
 *  Author: Ibrahim_Mady
 */ 

#include "FixedPoint_interface.h"
#include "LCD_interface.h"

FIXPOINT Add_fixed_point (float n1,float n2)            //to add floating numbers using fixed point representation
{
	FIXPOINT f1=FLOAT_TO_FIXP(n1);
	FIXPOINT f2=FLOAT_TO_FIXP(n2);
	FIXPOINT f3 =f1+f2; //sum_result
	return f3;	
}
FIXPOINT Sub_fixed_point (float n1,float n2)          //to sub floating numbers using fixed point representation
{
	FIXPOINT f1=FLOAT_TO_FIXP(n1);
	FIXPOINT f2=FLOAT_TO_FIXP(n2);
	FIXPOINT f3 =f1-f2; //sub_result
	return f3;
}
FIXPOINT mul_fixed_point (float n1,float n2)          //to multiply floating numbers using fixed point representation
{
	FIXPOINT f1=FLOAT_TO_FIXP(n1);
	FIXPOINT f2=FLOAT_TO_FIXP(n2);
	FIXPOINT f3 = ((long long)((long long)f1 * f2) >> FP_SHIFT); 
	return f3;
}
FIXPOINT div_fixed_point(float n1, float n2)            //to divide floating numbers using fixed point representation
{
	FIXPOINT f1 = FLOAT_TO_FIXP(n1);
	FIXPOINT f2 = FLOAT_TO_FIXP(n2);
	
	if (f2 == 0) return 0; // Avoid division by zero
	
	FIXPOINT f3 = ((long long)((long long)f1 << FP_SHIFT) / f2);   
	return f3;
}

float fix_point_to_float(FIXPOINT f)   //convert fixed point representation to float number
{
	return ((float)f) / FP_SCALE;
}