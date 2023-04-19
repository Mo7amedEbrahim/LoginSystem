/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     SPI	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _SPI_INTERFACE_H
#define _SPI_INTERFACE_H



ES_t SPI_InitMaster(void);
ES_t SPI_InitSlave(void);
ES_t SPI_Transceive(u8 Data,u8 *pRxData);
ES_t SPI_SendBufferSynch(u8 *DataBuffer,u8 BufferSize);
ES_t SPI_SendBufferASynch(u8 *DataBuffer, u8 BufferSize, void(*LocalFunc)(void));
ES_t SPI_EnableInterrupt(void);
ES_t SPI_DisableInterrupt(void);
ES_t SPI_GetStatus(u8* Copy_u8Status);

//TODO Deal with recieved in BUFFERS
#endif