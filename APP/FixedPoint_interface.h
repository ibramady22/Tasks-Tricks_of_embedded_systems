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
#define FLOAT_TO_FIXP(n) ((FIXPOINT)((n) * FP_SCALE))         // macro to convert floating-point numbers to fixed-point




#endif /* FIXEDPOINT_INTERFACE_H_ */