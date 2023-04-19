/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     PORT	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/

#include "PORT_interface.h"
/**
*@brief Initializes the PORT peripheral.
This function configures the direction and initial values of the PORTA, PORTB, PORTC, and PORTD registers.
*@return ES_t Returns ES_OK if the initialization was successful, otherwise ES_NOK.
*/
ES_t PORT_Init(void)
{
   ES_t Local_enuErrorstate = ES_NOK;
	/*DIRECTION*/
   DDRA_REG = PORTA_DIR ;
   DDRB_REG = PORTB_DIR ;
   DDRC_REG = PORTC_DIR ;
   DDRD_REG = PORTD_DIR ;
   /*INITIAL VALUE*/
   PORTA_REG = PORTA_VALUE ;
   PORTB_REG = PORTB_VALUE ;
   PORTC_REG = PORTC_VALUE ;
   PORTD_REG = PORTD_VALUE ;

   Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;

}
