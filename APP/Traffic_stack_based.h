/*
 * Traffic_stack_based.h
 *
 * Created: 22/10/2024 06:16:35 م
 *  Author: Ibrahim_Mady
 */ 


#ifndef TRAFFIC_STACK_BASED_H_
#define TRAFFIC_STACK_BASED_H_

#include "DIO_interface.h"
#include "LCD_interface.h"
#include "Timers_Services.h"
#include "EXINT.h"

#define STACK_SIZE           10
#define  max_redTime         10
#define  max_greenTime       15
#define  max_yellowTime      5
#define  max_EmergencyTime   8
typedef void (*StateFunc)(void); //type for a state function

#define RED_LED             PINC0
#define GREEN_LED           PINC2
#define YELLOW_LED          PINC1


void red_State(void);
void green_State(void);
void yellow_State(void);
void emergencyModeState(void);
void Traffic_Init(void);
void Traffic_Runnable(void);


#endif /* TRAFFIC_STACK_BASED_H_ */