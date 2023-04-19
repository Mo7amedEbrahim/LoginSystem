/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   HAL			      ***************************/
/*************                SWC :     LCD	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/


#include "LCD.h"


/*		LOCAL FUNCTIONS		*/
static void SendEnablePulse(void);

static void FunctionSet8Bit(void);

static void DisplayOnOffControl8Bit(void);

static void DisplayClear8Bit(void);

static void EntryModeSet8Bit(void);

static void SetDirections8Bit(void);

static void FunctionSet4Bit(void);

static void DisplayOnOffControl4Bit(void);

static void DisplayClear4Bit(void);

static void EntryModeSet4Bit(void);

static void SetDirections4Bit(void);

/***********************************************************************/

/**

@brief Writes a command to the 8-bit data port of the LCD
@param Command The command to be written to the LCD
@return ES_OK if the command was written successfully, ES_NOK otherwise
*/
ES_t LCD_WriteCommand8Bit(u8 Command){
	ES_t Local_enuErrorstate = ES_NOK;
	//Set RS PIN to LOW		(INSTRUCTION)
	DIO_SetPinValue(CONTROL_PORT,RS_PIN,LOW);
	//Send the command throw data port
	DIO_SetPortValue(DATA_PORT_8_BIT,Command);
	//Send Enable Pulse
	SendEnablePulse();
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}

/**
 * @brief Write data to the 8-bit data bus of the LCD.
 * 
 * This function sets the RS (Register Select) pin to HIGH, indicating that the data being sent is not an instruction but actual data.
 * It then writes the data to the 8-bit data bus using the `DIO_SetPortValue` function.
 * Finally, it sends an enable pulse using the `SendEnablePulse` function to latch the data onto the LCD.
 * 
 * @param Data The data to be written to the LCD
 * 
 * @return An error state indicating the success or failure of the operation.
 * @retval ES_OK The data was successfully written to the LCD.
 * @retval ES_NOK The data was not successfully written to the LCD.
 */
ES_t LCD_WriteData8Bit(u8 Data){
	ES_t Local_enuErrorstate = ES_NOK;
	//Set RS PIN to HIGH		(DATA)
	DIO_SetPinValue(CONTROL_PORT,RS_PIN,HIGH);
	//Send the DATA throw data port
	DIO_SetPortValue(DATA_PORT_8_BIT,Data);
	//Send Enable Pulse
	SendEnablePulse();
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}

ES_t LCD_8BitInitialize(void){
	ES_t Local_enuErrorstate = ES_NOK;
	/*	Set Directions	*/
	SetDirections8Bit();
	/*					*/
	FunctionSet8Bit();
	DisplayOnOffControl8Bit();
	DisplayClear8Bit();
	EntryModeSet8Bit();
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}
/***********************************************************************/
ES_t LCD_WriteCommand4Bit(u8 Command){
	ES_t Local_enuErrorstate = ES_NOK;
	//Set RS PIN to LOW		(INSTRUCTION)
	DIO_SetPinValue(CONTROL_PORT,RS_PIN,LOW);
	//Send the D7:D4 data first
	DIO_SetPortValue(DATA_PORT_8_BIT,Command>>4);
	//Send Enable Pulse
	SendEnablePulse();
	//Send the D3:D0 data second
	DIO_SetPortValue(DATA_PORT_8_BIT,Command&0x0f);
	//Send Enable Pulse
	SendEnablePulse();
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}

ES_t LCD_WriteData4Bit(u8 Data){
	ES_t Local_enuErrorstate = ES_NOK;
	//Set RS PIN to HIGH		(DATA)
	DIO_SetPinValue(CONTROL_PORT,RS_PIN,HIGH);
	//Send the D7:D4 data first
	DIO_SetPortValue(DATA_PORT_8_BIT,Data>>4);
	//Send Enable Pulse
	SendEnablePulse();
	//Send the D3:D0 data second
	DIO_SetPortValue(DATA_PORT_8_BIT,Data&0x0f);
	//Send Enable Pulse
	SendEnablePulse();
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}

ES_t LCD_4BitInitialize(void){
	ES_t Local_enuErrorstate = ES_NOK;
	SetDirections4Bit();
	FunctionSet4Bit();
	DisplayOnOffControl4Bit();
	DisplayClear4Bit();
	EntryModeSet4Bit();
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}






ES_t LCD_WriteString8Bit(char *string){
	ES_t Local_enuErrorstate = ES_NOK;
	u8 i=0;
	while(string[i] != '\0'){
		LCD_WriteData8Bit(string[i]);
		i++;
	}
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}

ES_t LCD_GoToXY8Bit(u8 X_Pos,u8 Y_Pos){
	ES_t Local_enuErrorstate = ES_NOK;
	u8 Address;
	/*	Location at First row	*/
	if(Y_Pos == 0){
		Address = X_Pos;
	}
	/*	Location at second Row	*/
	else if(Y_Pos == 1){
		Address = X_Pos + 0x40;
	}
	LCD_WriteCommand8Bit(128+Address);
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}

ES_t LCD_WriteNumber8Bit(s32 Number){
	ES_t Local_enuErrorstate = ES_NOK;
	s32 NUM = 1;
	if(Number == 0){
		LCD_WriteData8Bit('0');
	}
	else if(Number < 0){
		LCD_WriteData8Bit('-');
		Number = Number * (-1);
	}
	while(Number){
		NUM = ((NUM * 10) + (Number % 10));
		Number = Number / 10;
	}
	while(NUM != 1){
		LCD_WriteData8Bit((NUM % 10) + 48);
		NUM = (NUM / 10);
	}
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}
/******************************************************************/
ES_t LCD_WriteString4Bit(char *string){
	ES_t Local_enuErrorstate = ES_NOK;
	u8 i=0;
	while(string[i] != '\0'){
		LCD_WriteData4Bit(string[i]);
		i++;
	}
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}

ES_t LCD_GoToXY4Bit(u8 X_Pos,u8 Y_Pos){
	ES_t Local_enuErrorstate = ES_NOK;
	u8 Address;
	/*	Location at First row	*/
	if(Y_Pos == 0){
		Address = X_Pos;
	}
	/*	Location at second Row	*/
	else if(Y_Pos == 1){
		Address = X_Pos + 0x40;
	}
	LCD_WriteCommand4Bit(128+Address);
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}

ES_t LCD_WriteNumber4Bit(s32 Number){
	ES_t Local_enuErrorstate = ES_NOK;
	s32 NUM = 1;
	if(Number == 0){
		LCD_WriteData4Bit('0');
	}
	else if(Number < 0){
		LCD_WriteData4Bit('-');
		Number = Number * (-1);
	}
	while(Number){
		NUM = ((NUM * 10) + (Number % 10));
		Number = Number / 10;
	}
	while(NUM != 1){
		LCD_WriteData4Bit((NUM % 10) + 48);
		NUM = (NUM / 10);
	}
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;

}

ES_t LCD_ClearDisplay8Bit(void){
	ES_t Local_enuErrorstate = ES_NOK;
	LCD_WriteCommand8Bit(1);
	Local_enuErrorstate = ES_OK;
		return Local_enuErrorstate;
}
ES_t LCD_ClearDisplay4Bit(void){
	ES_t Local_enuErrorstate = ES_NOK;
		LCD_WriteCommand4Bit(1);
		Local_enuErrorstate = ES_OK;
			return Local_enuErrorstate;
}



/*		LOCAL FUNCTIONS Implementation		*/

static void SetDirections8Bit(void){
	DIO_SetPortDirection(DATA_PORT_8_BIT,0xff);
	DIO_SetPinDirection(CONTROL_PORT,RS_PIN,OUTPUT);
	DIO_SetPinDirection(CONTROL_PORT,E_PIN,OUTPUT);
}
static void SetDirections4Bit(void){
	DIO_SetPortDirection(DATA_PORT_8_BIT,0xf);
	DIO_SetPinDirection(CONTROL_PORT,RS_PIN,OUTPUT);
	DIO_SetPinDirection(CONTROL_PORT,E_PIN,OUTPUT);
}


static void SendEnablePulse(void){
	DIO_SetPinValue(CONTROL_PORT,E_PIN,HIGH);
	_delay_ms(2);
	DIO_SetPinValue(CONTROL_PORT,E_PIN,LOW);
	_delay_ms(5);
}
/****************************************************/
static void FunctionSet8Bit(void){
	_delay_ms(50);
	LCD_WriteCommand8Bit(0x3C);
}
static void DisplayOnOffControl8Bit(void){
	_delay_us(50);
	LCD_WriteCommand8Bit(0x0E);
}
static void DisplayClear8Bit(void){
	_delay_us(50);
	LCD_WriteCommand8Bit(0x01);
}
static void EntryModeSet8Bit(void){
	_delay_ms(2);
	LCD_WriteCommand8Bit(0x06);
}
/*****************************************************/
static void FunctionSet4Bit(void){
	_delay_ms(50);
	LCD_WriteCommand4Bit(0x2);
	_delay_us(10);
	LCD_WriteCommand4Bit(0x28);
}
static void DisplayOnOffControl4Bit(void){
	_delay_us(50);
	LCD_WriteCommand4Bit(0x0);
	_delay_us(10);
	LCD_WriteCommand4Bit(0xC);
}
static void DisplayClear4Bit(void){
	_delay_us(50);
	LCD_WriteCommand4Bit(0x0);
	_delay_us(10);
	LCD_WriteCommand4Bit(0x1);
}
static void EntryModeSet4Bit(void){
	_delay_ms(2);
	LCD_WriteCommand4Bit(0x0);
	_delay_us(10);
	LCD_WriteCommand4Bit(0x6);
}


