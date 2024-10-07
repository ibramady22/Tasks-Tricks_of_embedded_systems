

#ifndef STEPPER_H_
#define STEPPER_H_

#include "DIO_interface.h"
#include "StdTypes.h"
#define F_CPU 8000000
#include <util/delay.h>


/******************** config*********************/
#define COIL1A PIND0
#define COIL1B PIND1
#define COIL2A PIND2
#define COIL2B PIND3
#define DELAY    50
#define STEP     1.8
/***********************************************/
void STEPPER_Bipolar_CW(void);
void STEPPER_Bipolar_CCW(void);
void STEPPER_Unipolar_CW(void);
void STEPPER_Unipolar_CCW(void);
void STEPPER_Unipolar_CW_HS(void);
void STEPPER_Unipolar_CCW_HS(void);
void STEPPER_Hybrid_ByAngle(s16 angle); /* step for hybrid is 1.8 */
void STEPPER_Hybrid_ByRotations(s16 angle); /* step for hybrid is 1.8 */
#endif /* STEPPER_H_ */ 