/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     SPI	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/


/*  Librarys Includes   */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Error_States.h"
/*  SPI Includes  */
#include "SPI_config.h"
#include "SPI_private.h"
#include "SPI_register.h"
#include "SPI_interface.h"
/*  DIO Include     */
#include "../DIO/DIO_interface.h"

static u8 SPI_State = SPI_IDLE;
/******For SendBuffer Asynch**********/
static u8 *pGu8_DataBuffer = NULL;
static u8 Gu8_BufferSize = 0;
static u8 Gu8_BufferIndex = 0;
static void(*SPI_FunctionPTR)(void) = NULLPTR ;

ES_t SPI_InitMaster(void){
    ES_t Local_enuErrorstate = ES_NOK;
    /*  Select Master   */
    SET_BIT(SPCR,SPCR_MSTR);
    /*  Data Order Select  */
            #if SPI_DATA_ORDER == SPI_MSB_FIRST
            CLR_BIT(SPCR,SPCR_DORD);
            #elif SPI_DATA_ORDER == SPI_LSB_FIRST
            SET_BIT(SPCR,SPCR_DORD);
            #endif
    /*  Select Clock Polarity   */
            #if SPI_CLK_POLARITY  ==  SPI_SCK_HIGH_IDLE
            SET_BIT(SPCR,SPCR_CPOL);
            #elif SPI_CLK_POLARITY  ==  SPI_SCK_LOW_IDLE
            CLR_BIT(SPCR,SPCR_CPOL);
            #endif
    /*  Select Clock Phase  */
            #if SPI_CLK_PHASE   ==    SPI_DATA_SAMPLED_LEADING
            CLR_BIT(SPCR,SPCR_CPHA);
            #elif SPI_CLK_PHASE   ==    SPI_DATA_SAMPLED_TRAILING
            SET_BIT(SPCR,SPCR_CPHA);
            #endif
    /*  Choose SCK Freq/8*/
            SET_BIT(SPSR,SPSR_SPI2X);
            SET_BIT(SPCR,SPCR_SPR0);
            CLR_BIT(SPCR,SPCR_SPR1);
    /*  Enable SPI Module  */
    SET_BIT(SPCR,SPCR_SPE);
    Local_enuErrorstate = ES_OK;
    return Local_enuErrorstate;
}

ES_t SPI_InitSlave(void){
    	ES_t Local_enuErrorstate = ES_NOK;
        /*  Select Slave   */
    	CLR_BIT(SPCR,SPCR_MSTR);
    	/*  Data Order Select  */
                #if SPI_DATA_ORDER == SPI_MSB_FIRST
                CLR_BIT(SPCR,SPCR_DORD);
                #elif SPI_DATA_ORDER == SPI_LSB_FIRST
                SET_BIT(SPCR,SPCR_DORD);
                #endif
        /*  Select Clock Polarity   */
                #if SPI_CLK_POLARITY  ==  SPI_SCK_HIGH_IDLE
                SET_BIT(SPCR,SPCR_CPOL);
                #elif SPI_CLK_POLARITY  ==  SPI_SCK_LOW_IDLE
                CLR_BIT(SPCR,SPCR_CPOL);
                #endif
        /*  Select Clock Phase  */
                #if SPI_CLK_PHASE   ==    SPI_DATA_SAMPLED_LEADING
                CLR_BIT(SPCR,SPCR_CPHA);
                #elif SPI_CLK_PHASE   ==    SPI_DATA_SAMPLED_TRAILING
                SET_BIT(SPCR,SPCR_CPHA);
                #endif
        /*  Enable SPI Module  */
        SET_BIT(SPCR,SPCR_SPE);
    return Local_enuErrorstate;
}




ES_t SPI_Transceive(u8 Data,u8 *pRxData)
{
    ES_t Local_enuErrorState = ES_OK;

        if(SPI_State == SPI_BUSY){
            Local_enuErrorState = ES_BUSY_FUNCTION;
        }
        else{
        SPI_State = SPI_BUSY;
        /* Set SS low to select slave */
        //DIO_SetPinValue(PORTB,PIN4,LOW);
        
        /* Write data to SPI data register */
        SPDR = Data;
        
        /* Wait for the SPIF flag to be set */
        while (GET_BIT(SPSR, SPSR_SPIF) == 0);
        
        /* Read received data from SPI data register */
        *pRxData = SPDR;
        
        /* Set SS high to deselect slave */
        //DIO_SetPinValue(PORTB,PIN4,HIGH);
        SPI_State = SPI_IDLE;
    }
    return Local_enuErrorState;
}

ES_t SPI_SendBufferSynch(u8 *DataBuffer,u8 BufferSize){
    ES_t Local_enuErrorState = ES_NOK;
    if(DataBuffer == NULLPTR){
        Local_enuErrorState = ES_NULL_POINTER;
    }
    else{
        if(SPI_State == SPI_BUSY){
            Local_enuErrorState = ES_BUSY_FUNCTION;
        }
        else{
            SPI_State = SPI_BUSY;
            u8 Local_Index = 0;
            while(Local_Index < BufferSize){
                Local_enuErrorState = SPI_Transceive(DataBuffer[Local_Index],NULLPTR);
                if (Local_enuErrorState != ES_OK) {
                break;
                }
                Local_Index++;
            }
        }
        SPI_State = SPI_IDLE;
    }
    return Local_enuErrorState;
}

ES_t SPI_SendBufferASynch(u8 *DataBuffer, u8 BufferSize, void(*LocalFunc)(void)){
    ES_t Local_enuErrorState = ES_OK;
    if(DataBuffer == NULLPTR || LocalFunc == NULLPTR){
        Local_enuErrorState = ES_NULL_POINTER;
    }
    else{
        if(SPI_State == SPI_BUSY){
            Local_enuErrorState = ES_BUSY_FUNCTION;
        }
        else{
            SPI_State = SPI_BUSY;
            pGu8_DataBuffer = DataBuffer;
            Gu8_BufferSize = BufferSize;
            SPI_FunctionPTR = LocalFunc;
            Gu8_BufferIndex = 0;
            /*  Enable SPI Interrupt    */
            SET_BIT(SPCR,SPCR_SPIE);
            /*  Start Transmission  */
            SPDR = pGu8_DataBuffer[Gu8_BufferIndex];
            Gu8_BufferIndex++;
            Local_enuErrorState = ES_OK;
        }
    }
    return Local_enuErrorState;
}



ES_t SPI_EnableInterrupt(void){
    SET_BIT(SPCR,SPCR_SPIE);
    return ES_OK;
}

ES_t SPI_DisableInterrupt(void){
    CLR_BIT(SPCR,SPCR_SPIE);
    return ES_OK;
}

ES_t SPI_GetStatus(u8* Copy_u8Status)
{
    /* Check if the input argument is NULL */
    if (Copy_u8Status == NULLPTR) {
        return ES_NULL_POINTER;
    }
    
    /* Check if SPI is busy */
    if (GET_BIT(SPSR, SPSR_SPIF) == 0) {
        /* SPI is busy */
        *Copy_u8Status = SPI_BUSY;
    } else {
        /* SPI is not busy */
        *Copy_u8Status = SPI_IDLE;
    }
    
    /* Return success status */
    return ES_OK;
}


ISR(__vector_12){
    /* Check if all data has been sent */
    if(Gu8_BufferIndex < Gu8_BufferSize){
        /* Send the next byte of data */
        SPDR = pGu8_DataBuffer[Gu8_BufferIndex];
        Gu8_BufferIndex++;
    }
    else{
        /*  Disable SPI Interrupt   */
        CLR_BIT(SPCR,SPCR_SPIE);
        /*  Reset SPI State */
        SPI_State = SPI_IDLE;
        /*  Call Back Fucntion  */
        SPI_FunctionPTR();
    }
}
