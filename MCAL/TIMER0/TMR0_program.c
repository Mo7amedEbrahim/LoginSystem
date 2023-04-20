/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     TMR0	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#include "TMR0_interface.h"
/*      Used in CallBack Functions      */
static void (*TMR0_OvfCallbackFuncPTR)(void) = NULLPTR;
static void (*TMR0_CTCCallbackFuncPTR)(void) = NULLPTR;

ES_t TMR0_Init(TMR0_t *Copy_Timer0){
	ES_t Local_enuErrorstate = ES_NOK;
    if(Copy_Timer0 == NULLPTR){
        Local_enuErrorstate = ES_NULL_POINTER;
    }
    else{
    /*      Choose Mode     */
    if(Copy_Timer0->TIMER0_Mode == NORMAL_MODE){
                
        CHOOSE_NORMAL_MODE();
        /*Timer Over flow flag Enable*/
	    TMR0_OVF_INTERRUPT_EN();
    }
    else if(Copy_Timer0->TIMER0_Mode == CTC_MODE){
        CHOOSE_CTC_MODE();
        /*OUTPUT COMPARE MATCH INTERRUPT ENABLE*/
	    TMR0_CTC_INTERRUPT_EN();
        /*Set compare match value*/
        OCR0 = Copy_Timer0->TMR0_OCR0;
    }
    else if(Copy_Timer0->TIMER0_Mode == PHASE_CORRECT_PWM){
        CHOOSE_PHASE_CORRECT_PWM();
        #if PHASE_PWM_MODE == PHASE_PWM_NORMAL_MODE
            CLR_BIT(TCCR0,TCCR0_COM00);
            CLR_BIT(TCCR0,TCCR0_COM01);
        #elif PHASE_PWM_MODE == PHASE_PWM_CLR_ON_RISING       //Inverting
            CLR_BIT(TCCR0,TCCR0_COM00);
            SET_BIT(TCCR0,TCCR0_COM01);
        #elif PHASE_PWM_MODE == PHASE_PWM_SET_ON_RISING      //Non Inverting
            SET_BIT(TCCR0,TCCR0_COM00);
            SET_BIT(TCCR0,TCCR0_COM01);
        #endif
        OCR0 = Copy_Timer0->TMR0_OCR0;
        /*TODO: */
    }
    else if(Copy_Timer0->TIMER0_Mode == FAST_PWM){
        CHOOSE_FAST_PWM();
        #if FAST_PWM_MODE == FAST_PWM_NORMAL_MODE
            CLR_BIT(TCCR0,TCCR0_COM00);
            CLR_BIT(TCCR0,TCCR0_COM01);
        #elif FAST_PWM_MODE == FAST_PWM_CLR_ON_COMPARE       //Inverting
            CLR_BIT(TCCR0,TCCR0_COM00);
            SET_BIT(TCCR0,TCCR0_COM01);
        #elif FAST_PWM_MODE == FAST_PWM_SET_ON_COMPARE      //Non Inverting
            SET_BIT(TCCR0,TCCR0_COM00);
            SET_BIT(TCCR0,TCCR0_COM01);
        #endif
        OCR0 = Copy_Timer0->TMR0_OCR0;
    }
    /*      Clock Select    */
    TMR0_CLK_MASK();
    TMR0_CLK_SELECT(Copy_Timer0->TIMER0_Prescaler);
    /*      */
    Local_enuErrorstate = ES_OK;
    }
    return Local_enuErrorstate;
}

ES_t TMR0_OvfSetCallBack(TMR0_t *Copy_Timer0){
    	ES_t Local_enuErrorstate = ES_NOK;
    if(Copy_Timer0 == NULLPTR){
        Local_enuErrorstate = ES_NULL_POINTER;
    }
    else{
        TMR0_OvfCallbackFuncPTR = Copy_Timer0->ActionFunction;
        Local_enuErrorstate = ES_OK;
    }
    return Local_enuErrorstate;
}

ES_t TMR0_CTCSetCallBack(TMR0_t *Copy_Timer0){
    	ES_t Local_enuErrorstate = ES_NOK;
    if(Copy_Timer0 == NULLPTR){
        Local_enuErrorstate = ES_NULL_POINTER;
    }
    else{
        TMR0_CTCCallbackFuncPTR = Copy_Timer0->ActionFunction;
        Local_enuErrorstate = ES_OK;
    }
    return Local_enuErrorstate;
}

ES_t TMR0_SetDutyCycle(u8 Copy_u8DutyCycle){
    ES_t Local_enuErrorstate = ES_NOK;
    OCR0 = Copy_u8DutyCycle;
    Local_enuErrorstate = ES_OK;
    return Local_enuErrorstate;
}

//OVF ISR
ISR(__vector_11){
    if(TMR0_OvfCallbackFuncPTR == NULLPTR){
        /*  Do Nothing  */
    }
    else{
    TMR0_OvfCallbackFuncPTR();
    }
}
//CTC ISR
ISR(__vector_10){
    if(TMR0_CTCCallbackFuncPTR == NULLPTR){
        /*  Do Nothing  */
    }
    else{
    TMR0_CTCCallbackFuncPTR();
    }
}

/*
    Prescaler 64
    tick time = 64/8000000 = 8us
        We need 5000 us -> 1000 us
    No of compare matches -> 5
    CTC Value = 1000/8 = 125


*/
