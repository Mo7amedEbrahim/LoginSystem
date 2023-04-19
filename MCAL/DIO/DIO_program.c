#include "DIO_interface.h"




ES_t DIO_SetPinDirection(u8 Port,u8 Pin, u8 Direction){
	ES_t Local_enuErrorstate = ES_NOK;
	switch(Port){
		case PORTA:
		if(Direction == INPUT){
			CLR_BIT(DDRA_REG,Pin);
		}
		else if(Direction == OUTPUT){
			SET_BIT(DDRA_REG,Pin);
		}
		Local_enuErrorstate = ES_OK;
		break;
		case PORTB:
		if(Direction == INPUT){
			CLR_BIT(DDRB_REG,Pin);
		}
		else if(Direction == OUTPUT){
			SET_BIT(DDRB_REG,Pin);
		}
		Local_enuErrorstate = ES_OK;
		break;
		case PORTC:
		if(Direction == INPUT){
			CLR_BIT(DDRC_REG,Pin);
		}
		else if(Direction == OUTPUT){
			SET_BIT(DDRC_REG,Pin);
		}
		Local_enuErrorstate = ES_OK;
		break;
		case PORTD:
		if(Direction == INPUT){
			CLR_BIT(DDRD_REG,Pin);
		}
		else if(Direction == OUTPUT){
			SET_BIT(DDRD_REG,Pin);
		}
		Local_enuErrorstate = ES_OK;
		break;
		default:
			Local_enuErrorstate = ES_OUT_OF_RANGE;	
			break;
	}
	return Local_enuErrorstate;
}



ES_t DIO_SetPortDirection(u8 Port,u8 Direction){
	ES_t Local_enuErrorstate = ES_NOK;
	switch(Port){
		case PORTA: DDRA_REG = Direction; Local_enuErrorstate = ES_OK; break;
		case PORTB: DDRB_REG = Direction; Local_enuErrorstate = ES_OK; break;
		case PORTC: DDRC_REG = Direction; Local_enuErrorstate = ES_OK; break;
		case PORTD: DDRD_REG = Direction; Local_enuErrorstate = ES_OK; break;
		default: Local_enuErrorstate = ES_OUT_OF_RANGE;				   break;
	}
	return Local_enuErrorstate;
}


ES_t DIO_SetPinValue(u8 Port,u8 Pin, u8 Value){
	ES_t Local_enuErrorstate = ES_NOK;
	switch(Port){
		case PORTA:
		if(Value == LOW){
			CLR_BIT(PORTA_REG,Pin);
		}
		else if(Value == HIGH){
			SET_BIT(PORTA_REG,Pin);
		}
		Local_enuErrorstate = ES_OK;
		break;
		case PORTB:
		if(Value == LOW){
			CLR_BIT(PORTB_REG,Pin);
		}
		else if(Value == HIGH){
			SET_BIT(PORTB_REG,Pin);
		}
		Local_enuErrorstate = ES_OK;
		break;
		case PORTC:
		if(Value == LOW){
			CLR_BIT(PORTC_REG,Pin);
		}
		else if(Value == HIGH){
			SET_BIT(PORTC_REG,Pin);
		}
		Local_enuErrorstate = ES_OK;
		break;
		case PORTD:
		if(Value == LOW){
			CLR_BIT(PORTD_REG,Pin);
		}
		else if(Value == HIGH){
			SET_BIT(PORTD_REG,Pin);
		}
		Local_enuErrorstate = ES_OK;
		break;
		default:
		Local_enuErrorstate = ES_OUT_OF_RANGE;
		break;
	}
	return Local_enuErrorstate;
}

ES_t DIO_TogPinValue(u8 Port,u8 Pin){
	ES_t Local_enuErrorstate = ES_NOK;
	switch(Port){
			case PORTA:
				TOG_BIT(PORTA_REG,Pin);
				Local_enuErrorstate = ES_OK;
			break;
			case PORTB:
				TOG_BIT(PORTB_REG,Pin);
				Local_enuErrorstate = ES_OK;
			break;
			case PORTC:
				TOG_BIT(PORTC_REG,Pin);
				Local_enuErrorstate = ES_OK;
			break;
			case PORTD:
				TOG_BIT(PORTD_REG,Pin);
				Local_enuErrorstate = ES_OK;
			break;
			default:
				Local_enuErrorstate = ES_OUT_OF_RANGE;
			break;
		}
	return Local_enuErrorstate;
}



ES_t DIO_SetPortValue(u8 Port,u8 Value){
	ES_t Local_enuErrorstate = ES_NOK;
	switch(Port){
		case PORTA: PORTA_REG = Value; Local_enuErrorstate = ES_OK; break;
		case PORTB: PORTB_REG = Value; Local_enuErrorstate = ES_OK; break;
		case PORTC: PORTC_REG = Value; Local_enuErrorstate = ES_OK; break;
		case PORTD: PORTD_REG = Value; Local_enuErrorstate = ES_OK; break;
		default: Local_enuErrorstate = ES_OUT_OF_RANGE;				break;

	}
	return Local_enuErrorstate;
}


u8 DIO_u8GetPinValue(u8 Port,u8 Pin){
	switch(Port){
		case PORTA: return GET_BIT(PINA_REG,Pin); break;
		case PORTB: return GET_BIT(PINB_REG,Pin); break;
		case PORTC: return GET_BIT(PINC_REG,Pin); break;
		case PORTD: return GET_BIT(PIND_REG,Pin); break;
	}
	return 0;
}


