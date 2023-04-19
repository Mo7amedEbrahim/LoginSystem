/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   HAL			      ***************************/
/*************                SWC :     LCD	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/

#ifndef _LCD_H
#define _LCD_H
/*		Libraries Includes		*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include <util/delay.h>
/*		Configuration Includes	*/
#include "LCD_cfg.h"
/*		MCAL Includes			*/
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../LIB/Error_States.h"


ES_t LCD_8BitInitialize(void);

ES_t LCD_WriteCommand8Bit(u8 Command);

ES_t LCD_WriteData8Bit(u8 Data);

ES_t LCD_WriteString8Bit(char *string);

ES_t LCD_GoToXY8Bit(u8 X_Pos,u8 Y_Pos);

ES_t LCD_WriteNumber8Bit(s32 Number);

/*		 4BIT Mode	*/
ES_t LCD_4BitInitialize(void);

ES_t LCD_WriteCommand4Bit(u8 Command);

ES_t LCD_WriteData4Bit(u8 Data);

ES_t LCD_WriteString4Bit(char *string);
	
ES_t LCD_GoToXY4Bit(u8 X_Pos,u8 Y_Pos);

ES_t LCD_WriteNumber4Bit(s32 Number);


ES_t LCD_ClearDisplay8Bit(void);
ES_t LCD_ClearDisplay4Bit(void);


/*
	TODO : 	Special Chars
*/

/*			UPDATES	
	* 	Created Clear display Function instead of reinitialize every time.
	*	Fixed GoTo X,Y Function in 4Bit Mode
*/
#endif
