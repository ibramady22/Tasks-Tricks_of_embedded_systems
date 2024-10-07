

#ifndef RGB_H_
#define RGB_H_

#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "TIMER.h"
#include "RGB_cfg.h" 



typedef enum
{
	BLACK=0 ,
	WHITE,
	LIGHT_GRAY,
	GRAY,
	DARK_GRAY,
	RED,
	PINK,
	PURPLE,
	LIGHT_BLUE,
	BLUE,
	YELLOW_GREEN,
	GREEN,
	YELLOW,
	ORANGE,
	BROWN,
	PALE_PINK,
	COLORS_COUNT
	}RGB_Color_type;

extern u8 RGB_COLORS[COLORS_COUNT][3];

void RGB_Init(void);
void RGB_Get_color(RGB_Color_type color);
void RGB_shadow(RGB_Color_type color1 ,RGB_Color_type color2);

#endif /* RGB_H_ */