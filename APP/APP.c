#include <util/delay.h>
/****MCAL Includes****/
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/PORT/PORT_interface.h"
#include "../MCAL/SPI/SPI_interface.h"
#include "../MCAL/GIE/GIE_interface.h"
#include "../MCAL/TIMER0/TMR0_interface.h"
/****HAL Includes****/
#include "../HAL/LED/LED.h"
#include "../HAL/KEYPAD/KPD.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/SPI_EEPROM/SPI_EEPROM.h"
/*****************************************/
#include "APP.h"

u8 Entered_Pass[4],seconds;

int main(void){
	/*	Variables Initialization	*/
	u8 Admin_Registerd 	,	LoginAttempts=0	,	Login_Status = NOT_LOGGED_IN;
	/*	Timer0 Configurations	*/
	TMR0_t Waiting ={
			.TIMER0_Mode = CTC_MODE,
			.TIMER0_Prescaler = TMR0_DIV_BY_8,
			.TMR0_OCR0 = 250,
			.ActionFunction = WaitingISR
	};
	/*	Initialization	*/
	PORT_Init();				// Initialize ports
	LCD_4BitInitialize();		// Initialize LCD in 4-bit mode
	KPD_Init();					// Initialize Keypad
	SPI_EEPROM_Init();			// Initialize SPI EEPROM
	GIE_Enable();				//	Enable Global Interrupt
	//EEPROM_EraseAll();
	 /* ------------ */
	// Display welcome message
	LED_ON(PORTD,LOGGED_OUT_LED);
	LCD_ClearDisplay4Bit();
	LCD_GoToXY4Bit(3,0);
	LCD_WriteString4Bit("Welcome To ");
	LCD_GoToXY4Bit(2,1);
	LCD_WriteString4Bit("Login System !");
	LED_ON(PORTD,LOGGED_OUT_LED);
	_delay_ms(700);
	LCD_ClearDisplay4Bit();
	EEPROM_ReadByte(LOGIN_STATUS_ADDRESS,&Admin_Registerd);

	// Check if it's the first login
	if(Admin_Registerd == NOT_REGISTERED){
		// First login, prompt user to set admin password
		LCD_WriteString4Bit("First Login");
		LCD_GoToXY4Bit(0,1);
		LCD_WriteString4Bit("Set Admin Pass");
		_delay_ms(700);
		LCD_ClearDisplay4Bit();
		// Prompt user to enter password and save it
		LCD_GoToXY4Bit(0,0);
		LCD_WriteString4Bit("Password : ");
		LCD_GoToXY4Bit(0,1);
		Accept_Password(Entered_Pass);
		LCD_ClearDisplay4Bit();
		LCD_GoToXY4Bit(0,0);
		LCD_WriteString4Bit("Login Successful");
		Login_Status = LOGGED_IN;
		// Set login status to indicate first login has occurred
		SPI_EEPROM_WriteByte(LOGIN_STATUS_ADDRESS,0x11);
		// Save admin password
		SaveAdmin_Password(Entered_Pass);
		_delay_ms(1000);
	}
	else if(Admin_Registerd == REGISTERED){
		while (LoginAttempts < 3) {
			// Not first login, prompt user to enter password
			LCD_WriteString4Bit("PLS Enter Pass");
			LCD_GoToXY4Bit(0, 1);
			Accept_Password(Entered_Pass);
			LCD_ClearDisplay4Bit();
			// Check if entered password is correct
			if (IsCorrect(Entered_Pass) == CORRECT) {
				LCD_WriteString4Bit("Correct Password");
				_delay_ms(1000);
				LED_OFF(PORTD,LOGGED_OUT_LED);
				LED_ON(PORTD,LOGGED_IN_LED);
				Login_Status = LOGGED_IN;
				break;  // Exit the loop if the password is correct
			} else {
				// Password is incorrect, prompt user to enter password again
				LCD_WriteString4Bit("Wrong Password");
				_delay_ms(1000);
				LCD_ClearDisplay4Bit();
				LoginAttempts++;
			}
			if(LoginAttempts >= 3) {
				LCD_ClearDisplay4Bit();
				LCD_WriteString4Bit("Too many attempts");
				_delay_ms(1000);
				/*	Waiting	*/
				TMR0_Init(&Waiting);
				TMR0_CTCSetCallBack(&Waiting);
				LCD_ClearDisplay4Bit();
				LCD_WriteString4Bit("Please Wait !");
				while(seconds <= 30){
					LCD_GoToXY4Bit(0,1);
					LCD_WriteNumber4Bit(30-seconds);
				}
				seconds = 0;
				LoginAttempts = 0;
				LCD_ClearDisplay4Bit();
			}
		}
	}
	while(1){
		if(Login_Status == LOGGED_IN){
			/*	Write Your Program Here	*/
			for(u8 i=0;i<9;i++){
				LCD_ClearDisplay4Bit();
				LCD_GoToXY4Bit(i,0);
				LCD_WriteString4Bit("Welcome!");
				_delay_ms(100);
			}
			for(u8 i=0;i<9;i++){
				LCD_ClearDisplay4Bit();
				LCD_GoToXY4Bit(i,1);
				LCD_WriteString4Bit("Welcome!");
				_delay_ms(100);
			}
		}
		else{
			/*	Do NoThing	*/
		}
	}
	return 0;
}

void Accept_Password(u8 *Copy_u8Password){
	u8 iterator=0;
	for(iterator = 0;iterator<4;iterator++){
		Copy_u8Password[iterator] = KPD_Press();
		LCD_WriteData4Bit(Copy_u8Password[iterator]);
		_delay_ms(70);
		LCD_GoToXY4Bit(iterator,1);
		LCD_WriteData4Bit('*');
	}
}

void SaveAdmin_Password(u8 *Copy_u8Password){
	u32 Address=PASS_START_ADDRESS;
	u8 iterator = 0;
	for(iterator = 0;iterator <4;iterator++,Address++){
		SPI_EEPROM_WriteByte(Address,Copy_u8Password[iterator]);
	}
}

u8 KPD_Press(void){
	u8 PressedKey = 0xff;
	while(PressedKey == 0Xff){
		PressedKey = KPD_u8GetPressedKey();
	}
	return PressedKey;
}

u8 IsCorrect(u8 *Copy_u8Password) {
    u32 Address = PASS_START_ADDRESS;
    u8 iterator, state = NOT_CORRECT;
    u8 Local_u8Pass[4] = {0};

    // Load password from EEPROM into Local_u8Pass
    for (iterator = 0; iterator < 4; iterator++, Address++) {
            EEPROM_ReadByte(Address, &Local_u8Pass[iterator]);
        }

    // Compare entered password with stored password
    for (iterator = 0; iterator < 4; iterator++) {
        if (Copy_u8Password[iterator] != Local_u8Pass[iterator]) {
            state = NOT_CORRECT;
        } else {
            state = CORRECT;
        }
    }

    return state;
}

void WaitingISR(void){
	static u16 Counter = 0;
	Counter++;
	if(Counter == 4000){
		seconds++;
		Counter = 0;
	}
}

