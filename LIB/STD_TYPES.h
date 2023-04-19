#ifndef _STD_TYPES_H
#define _STD_TYPES_H

typedef unsigned char 				u8;
typedef unsigned short int 			u16;
typedef unsigned long int			u32;
typedef signed char					s8;
typedef signed short int			s16;
typedef signed long int 			s32;
typedef float						f32;
typedef double						f64;

#define NULL    0
#define NULLPTR ((void *)0)

/*          Dealing with Interrupt      */
#define ISR(__vector_num)                                                     \
    void __vector_num(void) __attribute__((signal));\
    void __vector_num(void)
#endif