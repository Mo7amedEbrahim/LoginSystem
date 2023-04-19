#ifndef _APP_H_
#define _APP_H_

#define LOGIN_STATUS_ADDRESS	0x00000007
typedef enum{
	NOT_REGISTERED = 0xFF,
	REGISTERED = 0x11
}ADMIN_REGISTERED;
#define PASS_START_ADDRESS		0x00000001
typedef enum{
	CORRECT,
	NOT_CORRECT
}CORRECT_PASS;

typedef enum{
	LOGGED_IN,
	NOT_LOGGED_IN
}LOGIN_STATUS;

#define LOGGED_IN_LED	PIN0
#define LOGGED_OUT_LED	PIN1

u8 KPD_Press(void);
void Accept_Password(u8 *Copy_u8Password);
void SaveAdmin_Password(u8 *Copy_u8Password);
u8 IsCorrect(u8 *Copy_u8Password);
void LoadAdminPassword(void);




#endif
