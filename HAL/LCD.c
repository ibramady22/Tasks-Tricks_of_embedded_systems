#include "LCD_interface.h"
#include "Utils.h"


#define F_CPU 8000000
#include <util/delay.h>

u8 lcd_cursorCell=MIN_CELL; 
u8 lcd_cursorLine=MIN_LINE;


#if LCD_MODE ==_8_BIT


 void WriteInstruction(u8 ins) //write number on lcd port
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH); // trigger
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH); // trigger
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
void LCD_Init(void)
{
	_delay_ms(50);
	WriteInstruction(0x38); //  2 line    8 bit mode
	WriteInstruction(0x0c); //  cursor     0x0c off ,0x0f on
	WriteInstruction(0x01); // clear screen
	_delay_ms(1);
	WriteInstruction(0x06); // increase DDRAM address , no Shifting
}


#elif LCD_MODE==_4_BIT



 void WriteInstruction(u8 ins) //write number on lcd port
{
	DIO_WritePin(RS,LOW);
	/*****High data ****/
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	DIO_WritePin(EN,HIGH); // trigger
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	/*****Low data ****/
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	DIO_WritePin(EN,HIGH); // trigger
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}


static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	/*****High data ****/
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));
	DIO_WritePin(EN,HIGH); // trigger
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	/*****Low data ****/
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	DIO_WritePin(EN,HIGH); // trigger
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
void LCD_Init(void)
{
	_delay_ms(50);
	WriteInstruction(0x02);
	WriteInstruction(0x28); //  2 line    4 bit mode
	WriteInstruction(0x0c); //  cursor     0x0c off ,0x0f on
	WriteInstruction(0x01); // clear screen
	_delay_ms(1);
	WriteInstruction(0x06); // increase DDRAM address , no Shifting
}
#endif 


void LCD_ManageCursor()
{
	if(lcd_cursorCell>MAX_CELL)
	{
		if(lcd_cursorLine==MIN_LINE)
		{
			LCD_SetCursor(MAX_LINE,MIN_CELL);
		}
		else if(lcd_cursorLine==MAX_LINE)
		{
			LCD_SetCursor(MIN_LINE,MIN_CELL);
		}
	}
}

void LCD_WriteChar(u8 ch)
{
	LCD_ManageCursor();
	WriteData(ch);
	lcd_cursorCell++;
}
void LCD_WriteNumber(s32 num)
{
	u8 i=0,str[16];
	s8 j;
	if(num==0)
	{
		LCD_WriteChar('0');
		return;
	}
	else if (num<0)
	{
		num*=-1;
		LCD_WriteChar('-');
	}
	else
	{
		
	}
	while(num)
	{
		str[i]=num%10 +'0';
		num=num/10;
		i++;
	}
	for(j=i-1;j>=0;j--)
	{
		LCD_WriteChar(str[j]);
	}
}
void LCD_WriteNumber_4digits(s32 num)
{
	u8 i=0,str[16];
	s8 j;
	 if (num<0)
	{
		num*=-1;
		LCD_WriteChar('-');
	}
	for(i=0;i<SPECIFIC_DIGITS;i++)
	{
		str[i]=num%10 +'0';
		num/=10;
	}
	for(j=i-1;j>=0;j--)
	{
		LCD_WriteChar(str[j]);
	}
}

void LCD_WriteBinary(u8 num)  
{
	u8 i=128;   
	LCD_WriteString("0b");
	for(i=128;i>=1;i/=2)   // or use READ_BIT
	{
		LCD_WriteNumber(num/i);
		num=num-(num/i)*i;
	}
}
void LCD_WriteHex(u8 num)
{
	u8 i=16;
	LCD_WriteString("0x");
	for(i=16;i>=1;i/=16)
	{
		if((num/i)<10)
		{
			LCD_WriteNumber(num/i);
		}
		else
		{
			LCD_WriteChar('a'+((num/i)-10));
		}
		num=num-(num/i)*i;
	}
}
void LCD_WriteString(u8* str)
{
	u8 i;
	for(i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
}

Error_type LCD_SetCursor(u8 line,u8 cell) //line 1,2 cell 1:16
{
	cell--; //cells began with address 0 in CGRAM
	if(line==MIN_LINE && cell<MAX_CELL)
	{
		WriteInstruction((0x80)|cell); 
	}
	else if(line==MAX_LINE && cell<MAX_CELL)
	{
		WriteInstruction(((0x80)|cell)+0x40);
	}
	else
	{
		return OUT_OF_RENGE;
	}
	lcd_cursorCell=cell;
	lcd_cursorLine=line;
	return OK;
}

void LCD_Clear(void)
{
	WriteInstruction(0x01); // clear screen
	_delay_ms(1);
	lcd_cursorCell=MIN_CELL;
	lcd_cursorLine=MIN_LINE;
}
/*****************************************/
void LCD_SnakeString(u8* str)
{
	u8 i;
	for(i=MIN_CELL;i<=MAX_CELL;i++)
	{
		LCD_SetCursor(MIN_LINE,i);
		LCD_WriteString(str);
		_delay_ms(300);
		LCD_Clear();
	}
	for(i=MIN_CELL;i<=MAX_CELL;i++)
	{
		LCD_SetCursor(MAX_LINE,i);
		LCD_WriteString(str);
		_delay_ms(300);
		LCD_Clear();
	}
}



	 
void LCD_SetShape(u8* pattern,u8 location)
{
	u8 i;
	WriteInstruction(0x40|(location*8)); //address in CGRAM
	for(i=0;i<8;i++) 
	{
		WriteData(pattern[i]); //pattern
	}
	LCD_SetCursor(MIN_LINE,MIN_CELL); // return to DDRAM
}
void LCD_ClearCells(u8 line,u8 cell,u8 num)
{
	u8 i;
	LCD_SetCursor(line,cell);
	for(i=0;i<num;i++)
	{
		LCD_WriteChar(' ');
	}
	LCD_SetCursor(line,cell); //return cursor to its address
}
