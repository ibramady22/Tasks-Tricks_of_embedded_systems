
#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#define COLS 4
#define  ROWS 4


/*************** instead of cfg.c *******************/
#ifdef KEYPAD_C /* visible in (.c) if only ,KEYPAD_C defined */
const  u8 KeysArray[COLS][ROWS]={{'7','8','9','/'},
                                 {'4','5','6','*'},
                                 {'1','2','3','-'},
				                 {'c','0','=','+'}};
#endif
/****************************************************/
						
#define NO_KEY 'T'
#define FIRST_OUTPUT  PINB4
#define  FIRST_INPUT PIND2


#endif /* KEYPAD_CFG_H_ */