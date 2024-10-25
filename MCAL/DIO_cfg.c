#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_interface.h"


const DIO_PinStatus_type PinsStatusArray[TOTAL_PINS]={
	INFREE, /* port A pin 0 ADC0*/
	OUTPUT, /* port A pin 1 */
	OUTPUT, /* port A pin 2 */
	OUTPUT, /* port A pin 3 */
	OUTPUT, /* port A pin 4 */
	OUTPUT, /* port A pin 5  clk*/
	INFREE, /* port A pin 6 ADC7*/
	INFREE, /* port A pin 7 alarm */
	OUTPUT, /* port B pin 0 */
	OUTPUT, /* port B pin 1 */
	OUTPUT, /* port B pin 2 */
	OUTPUT, /* port B pin 3 */
	INFREE, /* port B pin 4 /SS*/
	INFREE, /* port B pin 5  /MOSI */ 
	OUTPUT, /* port B pin 6 /MISO*/
	INFREE, /* port B pin 7 /CLK*/
	OUTPUT, /* port C pin 0 */
	OUTPUT, /* port C pin 1 */
	OUTPUT, /* port C pin 2 */
	INPULL, /* port C pin 3 */
	INPULL, /* port C pin 4 */
	OUTPUT, /* port C pin 5 */
	OUTPUT, /* port C pin 6 ADC2 */
	OUTPUT, /* port C pin 7 */
	OUTPUT, /* port D pin 0 */
	OUTPUT, /* port D pin 1 */
	INPULL, /* port D pin 2 EXI0*/
	OUTPUT, /* port D pin 3 EXI1*/
	OUTPUT, /* port D pin 4 */
	OUTPUT, /* port D pin 5 */
	OUTPUT, /* port D pin 6 */
	OUTPUT, /* port D pin 7 */
};

