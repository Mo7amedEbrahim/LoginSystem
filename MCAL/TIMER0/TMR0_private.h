/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     TMR0	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _TMR0_PRIVATE_H
#define _TMR0_PRIVATE_H


/**************Choose Prescaler*************/
#define NO_CLK_SOURCE            0
#define TMR0_DIV_BY_1            1
#define TMR0_DIV_BY_8            2
#define TMR0_DIV_BY_64           3
#define TMR0_DIV_BY_256          4
#define TMR0_DIV_BY_1024         5
#define TMR0_EXTERNAL_FALLING    6
#define TMR0_EXTERNAL_RISING     7

/**************Choose Mode*************/
#define NORMAL_MODE         0
#define CTC_MODE            1
#define PHASE_CORRECT_PWM   2
#define FAST_PWM            3

/*      Functions Like Macros   */
#define CHOOSE_NORMAL_MODE()    do{                     \
                                    CLR_BIT(TCCR0,TCCR0_WGM00);\
                                    CLR_BIT(TCCR0,TCCR0_WGM01);\
                                }while(0)

#define CHOOSE_CTC_MODE()    do{                     \
                                    CLR_BIT(TCCR0,TCCR0_WGM00);\
                                    SET_BIT(TCCR0,TCCR0_WGM01);\
                                }while(0)

#define CHOOSE_PHASE_CORRECT_PWM()    do{                     \
                                    SET_BIT(TCCR0,TCCR0_WGM00);\
                                    CLR_BIT(TCCR0,TCCR0_WGM01);\
                                }while(0)

#define CHOOSE_FAST_PWM()    do{                     \
                                    SET_BIT(TCCR0,TCCR0_WGM00);\
                                    SET_BIT(TCCR0,TCCR0_WGM01);\
                                }while(0)

#define TMR0_CLK_MASK()                         (TCCR0 &= 0b11111000)
#define TMR0_CLK_SELECT(TMR0_PRESCALER)         (TCCR0 |= TMR0_PRESCALER)

#define TMR0_OVF_INTERRUPT_EN()                 (SET_BIT(TIMSK,TIMSK_TOIE0))
#define TMR0_OVF_INTERRUPT_DIS()                (CLR_BIT(TIMSK,TIMSK_TOIE0))

#define TMR0_CTC_INTERRUPT_EN()                 (SET_BIT(TIMSK,TIMSK_OCIE0))
#define TMR0_CTC_INTERRUPT_DIS()                (CLR_BIT(TIMSK,TIMSK_OCIE0))

#define FAST_PWM_NORMAL_MODE     0
#define FAST_PWM_CLR_ON_COMPARE  1
#define FAST_PWM_SET_ON_COMPARE  2

#define PHASE_PWM_NORMAL_MODE       0
#define PHASE_PWM_CLR_ON_RISING     1
#define PHASE_PWM_SET_ON_RISING     2





#endif