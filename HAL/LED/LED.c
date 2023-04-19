/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   HAL			      ***************************/
/*************                SWC :     LED	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/

#include "LED.h"

/**
 * @brief Initialize the LED
 * 
 * @param DIO_PORT Port number for the LED pin
 * @param DIO_PIN Pin number for the LED
 * 
 * @return ES_t Local_enuErrorstate Status of the function execution
 * - ES_OK: Function executed successfully
 * - ES_NOK: Function execution failed
 */
ES_t LED_init(u8 DIO_PORT,u8 DIO_PIN){
	ES_t Local_enuErrorstate = ES_NOK;
	DIO_SetPinDirection(DIO_PORT,DIO_PIN,OUTPUT);
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}


/**
 * @brief Turn ON the LED
 * 
 * @param DIO_PORT Port number for the LED pin
 * @param DIO_PIN Pin number for the LED
 * 
 * @return ES_t Local_enuErrorstate Status of the function execution
 * - ES_OK: Function executed successfully
 * - ES_NOK: Function execution failed
 */
ES_t LED_ON(u8 DIO_PORT,u8 DIO_PIN){
	ES_t Local_enuErrorstate = ES_NOK;
	DIO_SetPinValue(DIO_PORT,DIO_PIN,HIGH);
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}


/**
 * @brief Turn OFF the LED
 * 
 * @param DIO_PORT Port number for the LED pin
 * @param DIO_PIN Pin number for the LED
 * 
 * @return ES_t Local_enuErrorstate Status of the function execution
 * - ES_OK: Function executed successfully
 * - ES_NOK: Function execution failed
 */
ES_t LED_OFF(u8 DIO_PORT,u8 DIO_PIN){
	ES_t Local_enuErrorstate = ES_NOK;
	DIO_SetPinValue(DIO_PORT,DIO_PIN,LOW);
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}


/**
 * @brief Toggle the LED state
 * 
 * @param DIO_PORT Port number for the LED pin
 * @param DIO_PIN Pin number for the LED
 * 
 * @return ES_t Local_enuErrorstate Status of the function execution
 * - ES_OK: Function executed successfully
 * - ES_NOK: Function execution failed
 */
ES_t LED_Toggle(u8 DIO_PORT,u8 DIO_PIN){
	ES_t Local_enuErrorstate = ES_OK;
	DIO_TogPinValue(DIO_PORT,DIO_PIN);
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}
