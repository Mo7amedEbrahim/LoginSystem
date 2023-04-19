/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     EXTI	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/

#ifndef _EXTI_INTERFACE_H
#define _EXTI_INTERFACE_H


/*		Enums and Macros	*/
/*************************************/
enum Sense_Control
{
	LOW_LEVEL =0,
	ON_CHANGE =1,
	FALLING_EDGE =2,
	RISING_EDGE =3
};

enum Status 
{
	INTERRUPT_TRIGGERED=0,
	INTERRUPT_NOT_TRIGGERED=1,
	ERROR_OCCURED =2
};

enum INT{
	INT0 =0,
	INT1,
	INT2
};
/*************************************/


//TODO: DOCUMENTATION FOR ALL APIs

/*	External Interrupt 0	*/
ES_t EXTI_INT0Init(u8 Local_u8Sense);
ES_t EXTI_SetCallBackINT0( void(*LocalPtr)(void) );
ES_t EXTI_u8INT0Status(u8 *Copy_u8Status);

/*	External Interrupt 1	*/
ES_t EXTI_INT1Init(u8 Local_u8Sense);
ES_t EXTI_SetCallBackINT1( void(*LocalPtr)(void) );
ES_t EXTI_u8INT1Status(u8 *Copy_u8Status);

/*	External Interrupt 2	*/
ES_t EXTI_INT2Init(u8 Local_u8Sense);
ES_t EXTI_SetCallBackINT2( void(*LocalPtr)(void) );
ES_t EXTI_u8INT2Status(u8 *Copy_u8Status);

ES_t EXTI_DisableINT(u8 Local_u8INT);


/*
	TODO : * Tail Chain
		   * Interrupt saturation
*/

// UPDATED ERROR STATES
// ADDED FEATURE TO DISABLE SPECIFIC INTERRUPT


#endif
