#ifndef _DIO_INTERFACE_H
#define _DIO_INTERFACE_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Error_States.h"
#include "DIO_register.h"

enum PORTS
{
	PORTA = 0,
	PORTB,
	PORTC,
	PORTD
};

enum PINS 
{
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
};

enum DIRECTION
{
	INPUT = 0,
	OUTPUT
};

enum VALUE
{
	LOW = 0,
	HIGH
};

//TODO: DOCUMENTATION FOR ALL APIs
ES_t DIO_SetPinDirection(u8 Port,u8 Pin, u8 Direction);
ES_t DIO_SetPortDirection(u8 Port,u8 Direction);
ES_t DIO_SetPinValue(u8 Port,u8 Pin, u8 Value);
ES_t DIO_TogPinValue(u8 Port,u8 Pin);
ES_t DIO_SetPortValue(u8 Port,u8 Value);
u8 DIO_u8GetPinValue(u8 Port,u8 Pin);







// UPDATED ERROR STATES
// ADDED FEATURE TO TOGGLE PIN VALUE








#endif
