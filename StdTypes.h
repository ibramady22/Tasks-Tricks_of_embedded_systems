

#ifndef STDTYPES_H_
#define STDTYPES_H_

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned int u16;
typedef signed int s16;

typedef unsigned long u32;
typedef signed long s32;

#define  NULL_PTR ((void*)0)

typedef enum
{
	OK,
	NOK,
	NULL,
	OUT_OF_RENGE
	}Error_type;
	
typedef enum
{
	FALSE,
	TRUE
	}Bool_type;

#define MAX_U8 ((u8)255)
#define  MIN_U8 ((u8)0)
#define MAX_S8 ((s8)127)
#define  MIN_S8 ((s8)-128)

#define MAX_U16 ((u16)65535)
#define  MIN_U16 ((u16)0)
#define MAX_S16 ((s16)32767)
#define  MIN_S16 ((s16)-32768)

#define MAX_U32 ((u32)4294967295)
#define  MIN_U32 ((u32)0)
#define MAX_S32 ((s32)2147483647)
#define  MIN_S32 ((s32)-2147483648)

#endif 