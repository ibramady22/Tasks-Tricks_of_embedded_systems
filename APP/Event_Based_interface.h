/*
 * Event_Based_interface.h
 *
 * Created: 10/6/2024 11:33:37 AM
 *  Author: Ibrahim_Mady
 */ 


#ifndef EVENT_BASED_INTERFACE_H_
#define EVENT_BASED_INTERFACE_H_



/*********************************************************************************************************************************/
/*  Handling multiple action through one interrupt & Queue iclude all ctions to events & poll on keys   **************************/
/*********************************************************************************************************************************/
#define MAX_EVENTS 3

typedef enum{
	EVNT_BUT1=0,
	EVNT_BUT2,
	EVNT_BUT3,
	EVNT_BUT4,
	}Event_type;

#define  BUT1_PIN PINC1
#define  BUT2_PIN PINC2
#define  BUT3_PIN PINC3
#define  BUT4_PIN PINC4

#define  LED1_PIN PIND1
#define  LED2_PIN PIND2
#define  LED3_PIN PIND3
#define  LED4_PIN PIND4

void MultiEvents_process(void );
void MultiEvents_init(void);


/*********************************************************************************************************************************/





void ButtonLed_System_Run (void );
void Timer_3s_System_Run (void );


#endif /* EVENT_BASED_INTERFACE_H_ */