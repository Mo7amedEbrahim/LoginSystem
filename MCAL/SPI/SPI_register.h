/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     SPI	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _SPI_REGISTER_H
#define _SPI_REGISTER_H



#define SPCR                    *((volatile u8 *) 0x2D)
#define SPCR_SPR0               0
#define SPCR_SPR1               1
#define SPCR_CPHA               2
#define SPCR_CPOL               3
#define SPCR_MSTR               4
#define SPCR_DORD               5
#define SPCR_SPE                6
#define SPCR_SPIE               7



#define SPSR                    *((volatile u8 *) 0x2E)
#define SPSR_SPI2X              0
#define SPSR_WCOL               6
#define SPSR_SPIF               7

#define SPDR                    *((volatile u8 *) 0x2F)





#endif