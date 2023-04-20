/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     TMR0	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _TMR0_CONFIG_H
#define _TMR0_CONFIG_H


/*  Choose Fast PWM Mode    
        Options:
                1-FAST_PWM_NORMAL_MODE
                2-FAST_PWM_CLR_ON_COMPARE   Non INVERTING
                3-FAST_PWM_SET_ON_COMPARE   INVERTING
*/
#define FAST_PWM_MODE   FAST_PWM_SET_ON_COMPARE

/*  Choose Phase Correct PWM Mode    
        Options:
                1-PHASE_PWM_NORMAL_MODE
                2-PHASE_PWM_CLR_ON_RISING   Non INVERTING
                3-PHASE_PWM_SET_ON_RISING   INVERTING
*/
#define PHASE_PWM_MODE   PHASE_PWM_SET_ON_RISING












#endif
