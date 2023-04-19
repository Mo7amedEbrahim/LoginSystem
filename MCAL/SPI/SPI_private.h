/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     SPI	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _SPI_PRIVATE_H
#define _SPI_PRIVATE_H


/*      Data Order Configurations       */
#define SPI_LSB_FIRST               0
#define SPI_MSB_FIRST               1

/*      Clock Polarity Configurations       */
#define SPI_SCK_HIGH_IDLE           0
#define SPI_SCK_LOW_IDLE            1

/*      Clock Phase Configurations          */
#define SPI_DATA_SAMPLED_LEADING    0
#define SPI_DATA_SAMPLED_TRAILING   1

/*      Clock Rate Configurations           */
#define SPI_DIV_BY_4                0
#define SPI_DIV_BY_16               1
#define SPI_DIV_BY_128              2

/*      Status      */
#define SPI_BUSY 0
#define SPI_IDLE 1





#endif