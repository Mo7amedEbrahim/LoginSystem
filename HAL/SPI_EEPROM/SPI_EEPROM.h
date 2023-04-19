#ifndef _SPI_EEPROM_H
#define _SPI_EEPROM_H


#define EEPROM_CS_PIN 4
#define EEPROM_SIZE 131072 // 1 MB


// Instructions
#define EEPROM_READ 0b00000011      //Read data from memory array beginning at selected address
#define EEPROM_WRITE 0b00000010     //Write data to memory array beginning at selected address
#define EEPROM_WRDI 0b00000100      //Reset the write enable latch (disable write operations)
#define EEPROM_WREN 0b00000110      //Set the write enable latch (enable write operations)
#define EEPROM_RDSR 0b00000101      //Read STATUS register
#define EEPROM_WRSR 0b00000001      //Write STATUS register
#define EEPROM_CE   0b11000111      //Chip Erase

// Status Register bits
#define EEPROM_WIP 0 // Write In Progress
#define EEPROM_WEL 1 // Write Enable Latch
#define EEPROM_BP0 2 // Block Protect bit 0
#define EEPROM_BP1 3 // Block Protect bit 1
#define EEPROM_BP2 4 // Block Protect bit 2
#define EEPROM_BP3 5 // Block Protect bit 3
#define EEPROM_WPEN 7 // Write Protect Enable

/*  Public APIs */
ES_t SPI_EEPROM_Init(void);
ES_t SPI_EEPROM_WriteByte(u32 Copy_u32Address,u8 Copy_u8Data);
ES_t EEPROM_ReadByte(u32 Copy_u32Address, u8 *Copy_pu8Data);
ES_t EEPROM_EraseAll(void);










#endif