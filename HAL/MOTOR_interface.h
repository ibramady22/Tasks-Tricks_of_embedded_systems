

#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_


typedef enum {
	M1,
	M2,
	M3, 
	M4
	}MOTOR_type;

Error_type MOTOR_Stop(MOTOR_type motor);
Error_type MOTOR_CW(MOTOR_type motor);
Error_type MOTOR_CCW(MOTOR_type motor);

#endif /* MOTOR_INTERFACE_H_ */