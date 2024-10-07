#include "UART_Services.h"

// static u8* str_c;
static u8* strs_c[size]={0};
static u8 in=0,out=0;
static u8 flag_up=0;
static u8 flag_st=0; //start flag
static u8 character=0;

void UART_SendString(u8* str)
{
	u8 i=0;
	for(i=0;str[i];i++)
	{
		UART_Send(str[i]); //busy w8
	}
	UART_Send('#');  //sign to determine 
}
void UART_ReceiveString(u8* str)
{
	u8 i=0;
	str[i]=UART_Receive();
	for(i=0;str[i]!='#';) //until sign
	{
		i++;
		str[i]=UART_Receive(); //busy w8
	}
	str[i]=0;
}
void UART_SendNumber(u32 num) //shifting
{
	UART_Send(num); //busy w8
	UART_Send((u8)(num>>8));
	UART_Send((u8)(num>>16));
	UART_Send((u8)(num>>24));
}
void UART_SendNumber2(u32 num) //using pointer
{
	u8* ptr=&num;
	UART_Send(ptr[0]);
	UART_Send(ptr[1]);
	UART_Send(ptr[2]);
	UART_Send(ptr[3]);
}
u32 UART_ReceiveNumber(void) //shifting
{
	u8 b0=UART_Receive(); //busy w8
	u8 b1=UART_Receive();
	u8 b2=UART_Receive();
	u8 b3=UART_Receive();
	u32 num;
	num=(u32)b0|(u32)b1<<8|(u32)b2<<16|(u32)b3<<24;
	return num;
}
u32 UART_ReceiveNumber2(void) //using pointer
{
	u32 num;
	u8* ptr=&num;
	ptr[0]=UART_Receive();
	ptr[1]=UART_Receive();
	ptr[2]=UART_Receive();
	ptr[3]=UART_Receive();
	return num;
}
void UART_SendStringCheckSum(u8* str) // busy w8 ,send length then bytes data then sum   
{
	u8 i=0,len=0;
	u16 sum=0;
	for(i=0;str[i];i++)
	{
		sum+=str[i];
		len++;
	}
	UART_Send(len);
	for(i=0;i<len;i++)
	{
		UART_Send(str[i]);
	}
	UART_Send((u8)sum);
	UART_Send((u8)(sum>>8));
}
u8 UART_ReceiveStringCheckSum(u8* str) // busy w8 ,receive length then bytes data then sum  
{
	u8 len=UART_Receive();
	u8 i,b0,b1;
	u16 sum_rec=0,sum_calc=0;
	for(i=0;i<len;i++)
	{
		str[i]=UART_Receive();
		sum_calc+=str[i];
	}
	str[i]=0;
	b0=UART_Receive();
	b1=UART_Receive();
	sum_rec=(u16)b0|(u16)b1<<8;
	if(sum_calc==sum_rec)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*********** ( send 1 string asynchronous) **********************************

void TX_func (void)   //in TX_interrupt
{
	static u8 i=1;
	if(str_c[i]!= 0)
	{
		UART_Send_noBlock(str_c[i]);
		i++;
	}
	else
	{
		UART_TX_InterruptDisable();
		i=1;
	}
}

void UART_SendStringAsynch(u8* str)
{
	UART_TX_SetCallBack(TX_func);
	UART_TX_InterruptEnable();
	str_c=str;             //pointer glabal to share str in another function
	UART_Send_noBlock(str_c[0]);
	
}
*/







/*********** ( send many strings asynchronous) **********************************/

void TX_func (void)
{
	if(strs_c[out][character]!= 0)
	{
		UART_Send_noBlock(strs_c[out][character]);
		character++;
	}
	else
	{
		out++;
		if(out==size) //outside the Queue
		{
			flag_up=0;
			out=0;
		}
		if((in==out)&&(flag_up==0)) //emty
		{
			flag_st=1; //stop sending
			out=0;
			in=0;
		}
		else
		{
			UART_Send_noBlock(strs_c[out][0]); //first character in string
			character=1;
		}
	}
}

void UART_TX_StringsAsynch_init(void) 
{
	UART_TX_SetCallBack(TX_func); //function will call inside interrupt
	UART_TX_InterruptEnable();
}


void StartSend_if_stop (void )
{
	if(flag_st==0)
	{
		UART_Send_noBlock(strs_c[out][0]);
		character=1;
		flag_st=1;
	}
}




u8 UART_SendStringsAsynch(u8* str) //return 0 if Queue is full
{
	if(in==size)
	{
		flag_up=1;
		in=0;
	}
	if((in==out)&&(flag_up==1))
	{
		return 0;
	}
	else
	{
		/* put string in buffer*/
		strs_c[in]=str;
		in++;
	}
	
	StartSend_if_stop();
}


/*

q_status_t queue_in(int data)
{
	q_status_t ret;
	if(in==size)
	{
		flag_c=1;
		in=0;
	}
	if((in==out)&&(flag_c==1))
	{
		ret= queue_full;
	}
	else
	{
		queue[in]=data;
		in++;
		ret= queue_done;
	}
	return ret;
}
q_status_t queue_out (int* pdata)
{
	q_status_t ret;
	if(out==size)
	{
		flag_c=0;
		out=0;
	}
	if((in==out)&&(flag_c==0))
	{
		ret= queue_empty;
	}
	else
	{
		*pdata=queue[out];
		out++;
		ret= queue_done;
	}
	return ret;
}
*/





