#include "DIO_interface.h"
#include <stdio.h>
#include <math.h>  // For using the sin() function from the math library
#include "SINE_LUT_interface.h"
#include "TIMER.h"
#include "LCD_interface.h"
#include "MemMap.h"


#define TABLE_SIZE 91  //Seta 0 to 90
#define ANGLE 45      //angle in degrees
u16 Counter =0;
const int sine_lookup_table[TABLE_SIZE] = {
	0, 17, 35, 52, 70, 87, 105, 122, 139, 156, 174, 191, 208, 225, 242, 259,
	275, 292, 309, 325, 342, 358, 374, 390, 406, 422, 438, 453, 469, 484,
	499, 515, 529, 544, 559, 573, 587, 601, 615, 629, 642, 656, 669, 682,
	695, 707, 719, 731, 743, 755, 766, 777, 788, 798, 809, 819, 829, 838,
	848, 857, 866, 874, 883, 891, 898, 906, 913, 920, 927, 933, 939, 945,
	951, 956, 961, 966, 970, 975, 979, 983, 986, 989, 992, 994, 996, 998,
	999, 1000
};

// Function to calculate sine using the lookup table
 static double sine_lookup(int angle)
  {
	  
	  // Handle angles greater than 90 by using symmetry
	  if (angle < 0 || angle > 90) 
	    {
		   return 0;
	    }
		// Get sine from the lookup table, dividing by 1000 to convert to a float
		return (double)sine_lookup_table[angle] / 1000.0;
	}

	// to compare the execution time between getting sine wave by lookup table and by math library with floating operation
void sine_lut(void )
{
	//DIO_WritePin(PIND0,LOW);  // the exec time will be the high range over PIND0 on OSCILLISCOPE
	//while(1)
	{
		Timer0_Init(TIMER0_NORMAL_MODE,TIMER0_SCALER_1); //every tick is 0.125 us
 
		double sine_from_table;
		//DIO_WritePin(PIND0,HIGH);
		TCNT0=0;
		for(u16 i=0;i<1000;i++)
		{
			sine_from_table = sine_lookup_table[45]; // value *1000
		}
		Counter=TCNT0;
		LCD_WriteNumber(Counter); //166 us
		//DIO_WritePin(PIND0,LOW);
		sine_from_table=(double)sine_from_table/1000.0;
	}
}

void sine_without_lut(void )
{
	// the exec time will be the high range over PIND1 on OSCILLISCOPE
	//DIO_WritePin(PIND1,LOW);
	//while(1)
	{
		Timer0_Init(TIMER0_NORMAL_MODE,TIMER0_SCALER_8); //every tick is 0.125 us
		double angle_in_radians = ANGLE * (M_PI / 180.0);  // Convert degrees to radians
		//DIO_WritePin(PIND1,HIGH);
		TCNT0=0;
		for(u16 i=0;i<1000;i++)
		{
			double sine_from_math_lib = sin(angle_in_radians);	
		}
		Counter=TCNT0;
		LCD_WriteNumber(Counter); //244  us
		//DIO_WritePin(PIND1,LOW);
	}
}