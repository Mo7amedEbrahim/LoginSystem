/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   HAL			      ***************************/
/*************                SWC :     LCD	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#include "KPD.h"


static void RowsInitialization(void);
static void ColumnsInitialization(void);


/**
 * @brief Initialize the Keypad
 * 
 * Initializes the rows of the keypad as outputs and the columns as inputs with pullup resistors.
 * 
 * @return ES_t Local_enuErrorstate Status of the function execution
 * - ES_OK: Function executed successfully
 * - ES_NOK: Function execution failed
 */
ES_t KPD_Init(void){
	ES_t Local_enuErrorstate = ES_NOK;
	/*	Rows	OUTPUT HIGH	*/
	RowsInitialization();

	/*	Columns	 INPUT PULLUP	*/
	ColumnsInitialization();
	Local_enuErrorstate = ES_OK;
	return Local_enuErrorstate;
}



/**

@brief Gets the value of the pressed key on the keypad.

@param void

@return u8 the value of the pressed key

@retval KPD_NO_PRESSED_KEY if no key is pressed.

@retval the value of the pressed key.
*/
u8 KPD_u8GetPressedKey(void){
	u8 Local_u8PressedKey = KPD_NO_PRESSED_KEY;
	u8 Local_u8RowIdx,Local_u8ColumnIdx;
	static u8 Local_u8KPDArr[KPD_ROW_NUM][KPD_COL_NUM] = KPD_ARR_VAL;
	static u8 Local_u8KPDColumnArr[] ={KPD_COL0,KPD_COL1,KPD_COL2,KPD_COL3};
	static u8 Local_u8KPDRowArr[] ={KPD_ROW0,KPD_ROW1,KPD_ROW2,KPD_ROW3};

	for(Local_u8RowIdx = 0;Local_u8RowIdx < KPD_ROW_NUM ; Local_u8RowIdx++){

		DIO_SetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8RowIdx],LOW);

		for(Local_u8ColumnIdx = 0;Local_u8ColumnIdx < KPD_COL_NUM ; Local_u8ColumnIdx++){
			DIO_u8GetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8ColumnIdx]);

			if(DIO_u8GetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8ColumnIdx]) == LOW){

				Local_u8PressedKey =Local_u8KPDArr[Local_u8RowIdx][Local_u8ColumnIdx];

				while(DIO_u8GetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8ColumnIdx]) == LOW){

					DIO_u8GetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8ColumnIdx]);

				}

				DIO_SetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8RowIdx],HIGH);
				return Local_u8PressedKey;
			}
		}
		DIO_SetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8RowIdx],HIGH);

	}
	return Local_u8PressedKey;
}


static void RowsInitialization(void){
	DIO_SetPinDirection(KPD_PORT,KPD_ROW0,OUTPUT);
			DIO_SetPinValue(KPD_PORT,KPD_ROW0,HIGH);
		DIO_SetPinDirection(KPD_PORT,KPD_ROW1,OUTPUT);
			DIO_SetPinValue(KPD_PORT,KPD_ROW1,HIGH);
		DIO_SetPinDirection(KPD_PORT,KPD_ROW2,OUTPUT);
			DIO_SetPinValue(KPD_PORT,KPD_ROW2,HIGH);
		DIO_SetPinDirection(KPD_PORT,KPD_ROW3,OUTPUT);
			DIO_SetPinValue(KPD_PORT,KPD_ROW3,HIGH);
}
static void ColumnsInitialization(void){
	DIO_SetPinDirection(KPD_PORT,KPD_COL0,INPUT);
			DIO_SetPinValue(KPD_PORT,KPD_COL0,HIGH);
		DIO_SetPinDirection(KPD_PORT,KPD_COL1,INPUT);
			DIO_SetPinValue(KPD_PORT,KPD_COL1,HIGH);
		DIO_SetPinDirection(KPD_PORT,KPD_COL2,INPUT);
			DIO_SetPinValue(KPD_PORT,KPD_COL2,HIGH);
		DIO_SetPinDirection(KPD_PORT,KPD_COL3,INPUT);
			DIO_SetPinValue(KPD_PORT,KPD_COL3,HIGH);

}
