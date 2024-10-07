


#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_
extern const DIO_PinStatus_type PinsStatusArray[TOTAL_PINS];
static void DIO_InitPin(DIO_Pin_type pin, DIO_PinStatus_type status );
static void DIO_InitPin2(DIO_Pin_type pin, DIO_PinStatus_type status ); //with different implement



#endif /* DIO_PRIVATE_H_ */