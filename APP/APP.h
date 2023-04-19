#ifndef _APP_H_
#define _APP_H_

#define LOGIN_STATUS_ADDRESS	0x00000007
typedef enum{
	FIRST_TIME_LOGIN = 0xFF,
	NOT_FIRST_TIME = 0x11
}LOGIN;
#define PASS_START_ADDRESS		0x00000001
typedef enum{
	CORRECT,
	NOT_CORRECT
}CORRECT_PASS;

#define LOGGED_IN	PIN0
#define LOGGED_OUT	PIN1

u8 KPD_Press(void);
void Accept_Password(u8 *Copy_u8Password);
void SaveAdmin_Password(u8 *Copy_u8Password);
u8 IsCorrect(u8 *Copy_u8Password);
void LoadAdminPassword(void);




#endif
