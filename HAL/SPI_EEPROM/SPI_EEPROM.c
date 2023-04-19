#include "../../LIB/Error_States.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/SPI/SPI_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "SPI_EEPROM.h"

static void EEPROM_WriteEnable(void);
static void EEPROM_WriteDisable(void);
static u8 EEPROM_ReadStatusRegister(void);
static ES_t EEPROM_WaitForWriteComplete(void);
static void EEPROM_SendAddress(u32 Copy_u32Address);

ES_t SPI_EEPROM_Init(void){
    ES_t Local_enuErrorState = ES_NOK;
    Local_enuErrorState = SPI_InitMaster();
    Local_enuErrorState = DIO_SetPinDirection(PORTB,EEPROM_CS_PIN,OUTPUT);
    Local_enuErrorState = DIO_SetPinValue(PORTB,EEPROM_CS_PIN,HIGH);
    return Local_enuErrorState;
}

ES_t SPI_EEPROM_WriteByte(u32 Copy_u32Address,u8 Copy_u8Data){
    // Wait for any previous write operation to complete
    EEPROM_WaitForWriteComplete();

    // Enable write
    EEPROM_WriteEnable();

    // Send write command and address
    DIO_SetPinValue(PORTB,EEPROM_CS_PIN,LOW);
    SPI_Transceive(EEPROM_WRITE,NULLPTR);
    EEPROM_SendAddress(Copy_u32Address);
    SPI_Transceive(Copy_u8Data,NULLPTR);
    DIO_SetPinValue(PORTB,EEPROM_CS_PIN,HIGH);

    // Wait for write operation to complete
    EEPROM_WaitForWriteComplete();
    return ES_OK;
}

ES_t EEPROM_ReadByte(u32 Copy_u32Address, u8 *Copy_pu8Data)
{
	Copy_u32Address--;
    // Send read command and address
    DIO_SetPinValue(PORTB,EEPROM_CS_PIN,LOW);
    SPI_Transceive(EEPROM_READ,NULLPTR);
    EEPROM_SendAddress(Copy_u32Address);
    SPI_Transceive(NULL,Copy_pu8Data);
    DIO_SetPinValue(PORTB,EEPROM_CS_PIN,HIGH);
    return ES_OK;
}


ES_t EEPROM_EraseAll(void)
{
    // Wait for any previous write operation to complete
    EEPROM_WaitForWriteComplete();

    // Enable write
    EEPROM_WriteEnable();

    // Send erase command
    DIO_SetPinValue(PORTB,EEPROM_CS_PIN,LOW);
    SPI_Transceive(EEPROM_CE,NULLPTR);
    DIO_SetPinValue(PORTB,EEPROM_CS_PIN,HIGH);

    EEPROM_WaitForWriteComplete();
    // Send write disable command
    EEPROM_WriteDisable();
    return ES_OK;
}

/*  Private functions   */
static void EEPROM_WriteEnable(void)
{
    DIO_SetPinValue(PORTB,EEPROM_CS_PIN,LOW);
    SPI_Transceive(EEPROM_WREN,NULLPTR);
    DIO_SetPinValue(PORTB,EEPROM_CS_PIN,HIGH);
}

static void EEPROM_WriteDisable(void)
{
    DIO_SetPinValue(PORTB,EEPROM_CS_PIN,LOW);
    SPI_Transceive(EEPROM_WRDI,NULLPTR);
    DIO_SetPinValue(PORTB,EEPROM_CS_PIN,HIGH);
}

static u8 EEPROM_ReadStatusRegister(void)
{
    u8 status = 0;
    DIO_SetPinValue(PORTB,EEPROM_CS_PIN,LOW);
    SPI_Transceive(EEPROM_RDSR,NULLPTR);
    SPI_Transceive(NULL,&status);
    DIO_SetPinValue(PORTB,EEPROM_CS_PIN,HIGH);
    return status;
}

static ES_t EEPROM_WaitForWriteComplete(void)
{
    ES_t Local_enuErrorState = ES_NOK;
    while (EEPROM_ReadStatusRegister()& (1 << EEPROM_WIP)) {
        // Wait for write to complete
    }
    Local_enuErrorState = ES_OK;
    return Local_enuErrorState;
}


static void EEPROM_SendAddress(u32 Copy_u32Address)
{
    u8 addressBytes[3];
    addressBytes[0] = (u8)((Copy_u32Address >> 16) & 0xFF);
    addressBytes[1] = (u8)((Copy_u32Address >> 8) & 0xFF);
    addressBytes[2] = (u8)(Copy_u32Address & 0xFF);
    SPI_Transceive(addressBytes[0],NULLPTR);
    SPI_Transceive(addressBytes[1],NULLPTR);
    SPI_Transceive(addressBytes[2],NULLPTR);
}
