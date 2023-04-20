/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     TMR0	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _TMR0_INTERFACE_H
#define _TMR0_INTERFACE_H

/*		TMR0 files Includes		*/
#include "TMR0_config.h"
#include "TMR0_register.h"
#include "TMR0_private.h"
/*		LIB includes			*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Error_States.h"


typedef struct{
    u8 TIMER0_Mode;
    u8 TIMER0_Prescaler;
    u8 TMR0_OCR0;
    void (*ActionFunction)(void);
}TMR0_t;
/*          APIs Prototypes     */
ES_t TMR0_Init(TMR0_t *Copy_Timer0);
ES_t TMR0_OvfSetCallBack(TMR0_t *Copy_Timer0);
ES_t TMR0_CTCSetCallBack(TMR0_t *Copy_Timer0);
ES_t TMR0_SetDutyCycle(u8 Copy_u8DutyCycle);
/*
	TODO : * 
*/

/*  
    UPDATES : * PostBuild Using Struct
              * CTC Mode Debug
              * Both PWM Modules
*/









#endif