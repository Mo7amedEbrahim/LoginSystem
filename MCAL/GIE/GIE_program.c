/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     GIE	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/

#include "GIE_interface.h"


ES_t GIE_Enable(void){
	ES_t Local_enuErrorstate = ES_NOK;
	SET_BIT(SREG,SREG_GIE);
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}

ES_t GIE_Disable(void){
	ES_t Local_enuErrorstate = ES_NOK;
	CLR_BIT(SREG,SREG_GIE);
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}
