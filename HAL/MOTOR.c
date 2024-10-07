#include "StdTypes.h"
#include "DIO_interface.h"
#include "MOTOR_interface.h"
#include "MOTOR_cfg.h"
#include "MOTOR_private.h"


Error_type MOTOR_Stop(MOTOR_type motor)
{
	if(motor>=NUMBER_Motors)
	{
		return OUT_OF_RENGE;
	}
	DIO_WritePin2(MOTORS_Pins[motor][IN1],LOW);
	DIO_WritePin2(MOTORS_Pins[motor][IN2],LOW);
	return OK;
	
}
Error_type MOTOR_CW(MOTOR_type motor)
{
	if(motor>=NUMBER_Motors)
	{
		return OUT_OF_RENGE;
	}
	DIO_WritePin2(MOTORS_Pins[motor][IN1],LOW);
	DIO_WritePin2(MOTORS_Pins[motor][IN2],HIGH);
	return OK;
	
}
Error_type MOTOR_CCW(MOTOR_type motor)
{
	if(motor>=NUMBER_Motors)
	{
		return OUT_OF_RENGE;
	}
	DIO_WritePin2(MOTORS_Pins[motor][IN1],HIGH);
	DIO_WritePin2(MOTORS_Pins[motor][IN2],LOW);
	return OK;
	
}