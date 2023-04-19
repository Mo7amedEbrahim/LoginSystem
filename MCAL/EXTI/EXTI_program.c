/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     EXTI	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/

/*		LIB includes			*/
#include "../../LIB/Error_States.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
/*		EXTI files Includes		*/
#include "EXTI_interface.h"
#include "EXTI_register.h"
#include "EXTI_config.h"
#include "EXTI_private.h"

/*	Pointers to Functions to Use in callback functions	*/
static void (*INT0_FunctionPointer) (void) = NULLPTR;
static void (*INT1_FunctionPointer) (void) = NULLPTR;
static void (*INT2_FunctionPointer) (void) = NULLPTR;



/*		External Interrupt 0 APIs   	*/
ES_t EXTI_INT0Init(u8 Local_u8Sense){
	ES_t Local_enuErrorstate = ES_NOK;
	/*Select Sense Control*/
	if(Local_u8Sense <= 3){

	switch(Local_u8Sense){
		case LOW_LEVEL:
			CLR_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);
			break;
		case ON_CHANGE:
			SET_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);
			break;
		case FALLING_EDGE:
			CLR_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
			break;
		}
			Local_enuErrorstate = ES_OK;
	}
	else{
		Local_enuErrorstate = ES_OUT_OF_RANGE;
	}
	/*Peripheral Interrupt Enable*/
	SET_BIT(GICR,GICR_INT0);
	return Local_enuErrorstate;
}

ES_t   EXTI_u8INT0Status(u8 *Copy_u8Status){
	ES_t Local_enuErrorstate = ES_NOK;
	if(GET_BIT(GIFR,GIFR_INTF0) == 1){
		*Copy_u8Status = INTERRUPT_TRIGGERED;
		Local_enuErrorstate = ES_OK;
	}
	else if(GET_BIT(GIFR,GIFR_INTF0) == 0){
		*Copy_u8Status = INTERRUPT_NOT_TRIGGERED;
		Local_enuErrorstate = ES_OK;
	}
	return Local_enuErrorstate;
}

ES_t EXTI_SetCallBackINT0( void(*LocalPtr)(void) ){
	ES_t Local_enuErrorstate = ES_NOK;
	if(LocalPtr != NULLPTR){
	INT0_FunctionPointer = LocalPtr;
	Local_enuErrorstate = ES_OK;
	}
	else{
		Local_enuErrorstate = ES_NULL_POINTER;
	}
	return Local_enuErrorstate;
}

ISR(__vector_1){
	INT0_FunctionPointer();
}


/*		External Interrupt 1 APIs   	*/
ES_t EXTI_INT1Init(u8 Local_u8Sense){
	ES_t Local_enuErrorstate = ES_NOK;
	/*Select Sense Control*/
	if(Local_u8Sense <= 3){
	switch(Local_u8Sense){
		case LOW_LEVEL:
			CLR_BIT(MCUCR,MCUCR_ISC10);
			CLR_BIT(MCUCR,MCUCR_ISC11);
			break;
		case ON_CHANGE:
			SET_BIT(MCUCR,MCUCR_ISC10);
			CLR_BIT(MCUCR,MCUCR_ISC11);
			break;
		case FALLING_EDGE:
			CLR_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
			break;
		}
		Local_enuErrorstate = ES_OK;
	}
	else{
		Local_enuErrorstate = ES_OUT_OF_RANGE;
	}
	/*Peripheral Interrupt Enable*/
	SET_BIT(GICR,GICR_INT1);
	return Local_enuErrorstate;
}

ES_t EXTI_u8INT1Status(u8 *Copy_u8Status){
	ES_t Local_enuErrorstate = ES_NOK;
	if(GET_BIT(GIFR,GIFR_INTF1) == 1){
		*Copy_u8Status = INTERRUPT_TRIGGERED;
		Local_enuErrorstate = ES_OK;
	}
	else if(GET_BIT(GIFR,GIFR_INTF1) == 0){
		*Copy_u8Status = INTERRUPT_NOT_TRIGGERED;
		Local_enuErrorstate = ES_OK;
	}
	return Local_enuErrorstate;
}

ES_t EXTI_SetCallBackINT1( void(*LocalPtr)(void) ){
	ES_t Local_enuErrorstate = ES_NOK;
	if(LocalPtr != NULLPTR){
	INT1_FunctionPointer = LocalPtr;
	Local_enuErrorstate = ES_OK;
	}
	else{
		Local_enuErrorstate = ES_NULL_POINTER;
	}
	return Local_enuErrorstate;
}

ISR(__vector_2){
	INT1_FunctionPointer();
}


/*		External Interrupt 2 APIs   	*/
ES_t EXTI_INT2Init(u8 Local_u8Sense){
	ES_t Local_enuErrorstate = ES_NOK;
		if(Local_u8Sense <= 3){
	/*Select Sense Control*/
	switch(Local_u8Sense){
		case FALLING_EDGE:
			CLR_BIT(MCUCSR,MCUCSR_ISC2);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCSR,MCUCSR_ISC2);
			break;
		}
		Local_enuErrorstate = ES_OK;
	}
	else{
		Local_enuErrorstate = ES_OUT_OF_RANGE;
	}
	/*Peripheral Interrupt Enable*/
	SET_BIT(GICR,GICR_INT2);
	return Local_enuErrorstate;
}


ES_t EXTI_u8INT2Status(u8 *Copy_u8Status){
	ES_t Local_enuErrorstate = ES_NOK;
	if(GET_BIT(GIFR,GIFR_INTF2) == 1){
		*Copy_u8Status = INTERRUPT_TRIGGERED;
		Local_enuErrorstate = ES_OK;
	}
	else if(GET_BIT(GIFR,GIFR_INTF2) == 0){
		*Copy_u8Status = INTERRUPT_NOT_TRIGGERED;
		Local_enuErrorstate = ES_OK;
	}
	return Local_enuErrorstate;
}

ES_t EXTI_SetCallBackINT2( void(*LocalPtr)(void) ){
	ES_t Local_enuErrorstate = ES_NOK;
	if(LocalPtr != NULLPTR){
	INT2_FunctionPointer = LocalPtr;
	Local_enuErrorstate = ES_OK;
	}
	else{
		Local_enuErrorstate = ES_NULL_POINTER;
	}
	return Local_enuErrorstate;
}

ISR(__vector_3){
	INT2_FunctionPointer();
}


ES_t EXTI_DisableINT(u8 Local_u8INT){
	ES_t Local_enuErrorstate = ES_NOK;
	if(Local_u8INT <= 2){
		switch(Local_u8INT){
			case INT0:	CLR_BIT(GICR,GICR_INT0);	break;
			case INT1:	CLR_BIT(GICR,GICR_INT1);	break;
			case INT2:	CLR_BIT(GICR,GICR_INT2);	break;
		}
		Local_enuErrorstate = ES_OK;
	}
	else{
		Local_enuErrorstate = ES_OUT_OF_RANGE;
	}
	return Local_enuErrorstate;
}
