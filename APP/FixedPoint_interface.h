/*
 * FixedPoint_interface.h
 *
 * Created: 9/24/2024 1:24:48 AM
 *  Author: Ibrahim_Mady
 */ 


#ifndef FIXEDPOINT_INTERFACE_H_
#define FIXEDPOINT_INTERFACE_H_

#include "StdTypes.h"

#define FP_SHIFT 16                               // shifts to produce a fixed-point number
#define FP_SCALE ((u32)1 << 16)                   // scaling factor
typedef u32 FIXPOINT;

#define INT_TO_FIXP(n) (((n << FP_SHIFT)))                    //macro that converts an integer to fixed-point
#define FLOAT_TO_FIXP(n) ((FIXPOINT)((n) * FP_SCALE))         // macro to convert floating-point numbers to fixed-point#define FIXP_INT_PART(n) (n >> FP_SHIFT)                      //extract the integer part from float number#define FIXP_DEC_PART(n) (n & (FP_SCALE - 1))                 //get the decimal portion in the lower 8 bitsFIXPOINT Add_fixed_point (float n1,float n2);FIXPOINT Sub_fixed_point (float n1,float n2);FIXPOINT mul_fixed_point (float n1,float n2);FIXPOINT div_fixed_point (float n1,float n2);float fix_point_to_float(FIXPOINT f);




#endif /* FIXEDPOINT_INTERFACE_H_ */