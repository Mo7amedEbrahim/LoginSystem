/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     PORT	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/

#ifndef _PORT_CONFIG_H
#define _PORT_CONFIG_H

/*			PIN DIRECTION
 *		Choose 0 FOR INPUT
 *		Choose 1 FOR OUTPUT
 */
 
 /*			Port A		*/
#define PORTA_PIN0_DIR		0
#define PORTA_PIN1_DIR		0
#define PORTA_PIN2_DIR		0
#define PORTA_PIN3_DIR		0
#define PORTA_PIN4_DIR		0
#define PORTA_PIN5_DIR		0
#define PORTA_PIN6_DIR		0
#define PORTA_PIN7_DIR		0

 /*			Port B		*/
#define PORTB_PIN0_DIR		0
#define PORTB_PIN1_DIR		0
#define PORTB_PIN2_DIR		0
#define PORTB_PIN3_DIR		0
#define PORTB_PIN4_DIR		1			//SS
#define PORTB_PIN5_DIR		1			//MOSI
#define PORTB_PIN6_DIR		0			//MISO
#define PORTB_PIN7_DIR		1			//CLK

 /*			Port C		*/
#define PORTC_PIN0_DIR		0
#define PORTC_PIN1_DIR		0
#define PORTC_PIN2_DIR		0
#define PORTC_PIN3_DIR		0
#define PORTC_PIN4_DIR		0
#define PORTC_PIN5_DIR		0
#define PORTC_PIN6_DIR		0
#define PORTC_PIN7_DIR		0

 /*			Port D		*/
#define PORTD_PIN0_DIR		1
#define PORTD_PIN1_DIR		1
#define PORTD_PIN2_DIR		0
#define PORTD_PIN3_DIR		0
#define PORTD_PIN4_DIR		0
#define PORTD_PIN5_DIR		0
#define PORTD_PIN6_DIR		0
#define PORTD_PIN7_DIR		0


/*			Initial Value
 *		IF Output Choose 0 for LOW OR 1 for HIGH
 *		IF Input Choose 0 for floating OR 1 for PULLUP
 */
 
  /*			Port A		*/
#define PORTA_PIN0_Value		0
#define PORTA_PIN1_Value		0
#define PORTA_PIN2_Value		0
#define PORTA_PIN3_Value		0
#define PORTA_PIN4_Value		0
#define PORTA_PIN5_Value		0
#define PORTA_PIN6_Value		0
#define PORTA_PIN7_Value		0


 /*			Port B		*/
#define PORTB_PIN0_Value		0
#define PORTB_PIN1_Value		0
#define PORTB_PIN2_Value		0
#define PORTB_PIN3_Value		0
#define PORTB_PIN4_Value		0
#define PORTB_PIN5_Value		0
#define PORTB_PIN6_Value		0
#define PORTB_PIN7_Value		0


 /*			Port C		*/
#define PORTC_PIN0_Value		0
#define PORTC_PIN1_Value		0
#define PORTC_PIN2_Value		0
#define PORTC_PIN3_Value		0
#define PORTC_PIN4_Value		0
#define PORTC_PIN5_Value		0
#define PORTC_PIN6_Value		0
#define PORTC_PIN7_Value		0


 /*			Port D		*/
#define PORTD_PIN0_Value		0
#define PORTD_PIN1_Value		0
#define PORTD_PIN2_Value		0
#define PORTD_PIN3_Value		0
#define PORTD_PIN4_Value		0
#define PORTD_PIN5_Value		0
#define PORTD_PIN6_Value		0
#define PORTD_PIN7_Value		0

#endif
