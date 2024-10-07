#include "DIO_interface.h"
#include "MOTOR_cfg.h"
/*************pin config***********************/
const DIO_Pin_type MOTORS_Pins[NUMBER_Motors][2]={
	            /*IN1   IN2*/
	/*MOTOR1*/  {PIND0,PIND7},
	/*MOTOR2*/  {PIND3,PIND4},
	/*MOTOR3*/  {PINC0,PINB2},
	/*MOTOR4*/  {PINB4,PINB5}
};