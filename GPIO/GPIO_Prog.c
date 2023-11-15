/*****************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 13/7/2023                                                        */
/* Version        : 1.0                                                              */
/*sw              : GPIO                                                             */
/*****************************************************************************/

#include "../LIBS/STD_TYPES.h"
#include "../LIBS/BIT_MATH.h"
#include "../LIBS/STMF103C8_MMAP.h"

#include "GPIO_CONF.h"
#include "GPIO_Private.h"
#include "GPIO_Interface.h"

extern GPIO_Conf_t GPIO_Conf_ARR[PINTOTAL];

Error_t GPIO_u8Init() {

	for (u8 index = 0; index < PINTOTAL; index++) {
		GPIO_u8SetPinD_ID(GPIO_Conf_ARR[index].GPIO_u8_pin,
				GPIO_Conf_ARR[index].GPIO_u8_Mode);
	}
	return OK;
}

Error_t GPIO_u8SetPortDirection_H(u8 Copy_u8PortId, u8 Copy_u8Mode) {
	Error_t State = OK;
	u32 Copy_Tmode = Copy_u8Mode | Copy_u8Mode << 4 | Copy_u8Mode << 8
			| Copy_u8Mode << 12 | Copy_u8Mode << 16 | Copy_u8Mode << 20
			| Copy_u8Mode << 24 | Copy_u8Mode << 28;
	switch (Copy_u8PortId) {
	case GPIO_PORTA:
		GPIO_A->GPIO_CRH = Copy_Tmode;
		/*
		 for (u8 i = 0 ; i < 8 ; i++){
		 GPIO_A->GPIO_CRH|=(Copy_u8Mode<<(i*GPIO_u8PIN_REG_SIZE));
		 }
		 */
		State = OK;
		break;
	case GPIO_PORTB:
		GPIO_B->GPIO_CRH = Copy_Tmode;
		State = OK;
		break;
	case GPIO_PORTC:
		GPIO_C->GPIO_CRH = Copy_Tmode;
		State = OK;

		break;
	default:
		State = NOK;
		break;
	}
	return State;
}
Error_t GPIO_u8SetPortDirection_L(u8 Copy_u8PortId, u8 Copy_u8Mode) {
	Error_t State = OK;
	u32 Copy_Tmode = Copy_u8Mode | Copy_u8Mode << 4 | Copy_u8Mode << 8
			| Copy_u8Mode << 12 | Copy_u8Mode << 16 | Copy_u8Mode << 20
			| Copy_u8Mode << 24 | Copy_u8Mode << 28;
	switch (Copy_u8PortId) {
	case GPIO_PORTA:
		GPIO_A->GPIO_CRL = Copy_Tmode;
		/*
		 for (u8 i = 0 ; i < 8 ; i++){
		 GPIO_A->GPIO_CRH|=(Copy_u8Mode<<(i*GPIO_u8PIN_REG_SIZE));
		 }
		 */
		State = OK;
		break;
	case GPIO_PORTB:
		GPIO_B->GPIO_CRL = Copy_Tmode;
		State = OK;
		break;
	case GPIO_PORTC:
		GPIO_C->GPIO_CRL = Copy_Tmode;
		State = OK;

		break;
	default:
		State = NOK;
		break;
	}
	return State;
}
Error_t GPIO_u8SetPortValue_L(u8 Copy_u8PortId, u8 Copy_u8Value) {
	Error_t State = OK;
	switch (Copy_u8PortId) {
	case GPIO_PORTA:
		GPIO_A->GPIO_ODR = Copy_u8Value;
		State = OK;
		break;

	case GPIO_PORTB:
		GPIO_B->GPIO_ODR = Copy_u8Value;
		State = OK;
		break;
	case GPIO_PORTC:
		GPIO_C->GPIO_ODR = Copy_u8Value;
		State = OK;

		break;
	default:
		State = NOK;
		break;
	}
	return State;
}
Error_t GPIO_u8SetPortValue_H(u8 Copy_u8PortId, u8 Copy_u8Value) {
	Error_t State = OK;
	switch (Copy_u8PortId) {
	case GPIO_PORTA:

		GPIO_A->GPIO_ODR &= ~(0xff) << GPIO_u8OFSET;
		GPIO_A->GPIO_ODR |= Copy_u8Value << GPIO_u8OFSET;

		State = OK;
		break;
	case GPIO_PORTB:

		GPIO_B->GPIO_ODR &= ~(0xff) << GPIO_u8OFSET;
		GPIO_B->GPIO_ODR |= Copy_u8Value << GPIO_u8OFSET;

		State = OK;
		break;
	case GPIO_PORTC:

		GPIO_C->GPIO_ODR &= ~(0xff) << GPIO_u8OFSET;
		GPIO_C->GPIO_ODR |= Copy_u8Value << GPIO_u8OFSET;

		State = OK;

		break;
	default:
		State = NOK;
		break;
	}
	return State;
}

Error_t GPIO_enSetPinDirection(u8 Copy_u8PortId, u8 Copy_u8PinId,
		u8 Copy_u8Mode) {
	Error_t Local_enStatus = OK;
	switch (Copy_u8PortId) {
	case GPIO_PORTA:
		if (Copy_u8PinId <= GPIO_u8f_REG_LEN) {
			GPIO_A->GPIO_CRL &= ~((GPIO_u8CLR_MASK)
					<< (Copy_u8PinId * GPIO_u8PIN_REG_SIZE));
			GPIO_A->GPIO_CRL |= ((Copy_u8Mode)
					<< (Copy_u8PinId * GPIO_u8PIN_REG_SIZE));
		} else if (Copy_u8PinId <= GPIO_u8L_REG_LEN) {
			Copy_u8PinId = Copy_u8PinId - GPIO_u8OFSET;

			GPIO_A->GPIO_CRH &= ~((GPIO_u8CLR_MASK)
					<< (Copy_u8PinId * GPIO_u8PIN_REG_SIZE));
			GPIO_A->GPIO_CRH |= ((Copy_u8Mode)
					<< (Copy_u8PinId * GPIO_u8PIN_REG_SIZE));

		} else {
			Local_enStatus = NOK;
		}
		break;
	case GPIO_PORTB:
		if (Copy_u8PinId <= GPIO_u8f_REG_LEN) {
			GPIO_B->GPIO_CRL &= ~((GPIO_u8CLR_MASK)
					<< (Copy_u8PinId * GPIO_u8PIN_REG_SIZE));
			GPIO_B->GPIO_CRL |= ((Copy_u8Mode)
					<< (Copy_u8PinId * GPIO_u8PIN_REG_SIZE));
		} else if (Copy_u8PinId <= GPIO_u8L_REG_LEN) {
			Copy_u8PinId = Copy_u8PinId - GPIO_u8OFSET;

			GPIO_B->GPIO_CRH &= ~((GPIO_u8CLR_MASK)
					<< (Copy_u8PinId * GPIO_u8PIN_REG_SIZE));
			GPIO_B->GPIO_CRH |= ((Copy_u8Mode)
					<< (Copy_u8PinId * GPIO_u8PIN_REG_SIZE));

		} else {
			Local_enStatus = NOK;
		}
		break;
	case GPIO_PORTC:
		if (Copy_u8PinId <= GPIO_u8f_REG_LEN) {
			GPIO_C->GPIO_CRL &= ~((GPIO_u8CLR_MASK)
					<< (Copy_u8PinId * GPIO_u8PIN_REG_SIZE));
			GPIO_C->GPIO_CRL |= ((Copy_u8Mode)
					<< (Copy_u8PinId * GPIO_u8PIN_REG_SIZE));
		} else if (Copy_u8PinId <= GPIO_u8L_REG_LEN) {
			Copy_u8PinId = Copy_u8PinId - GPIO_u8OFSET;

			GPIO_C->GPIO_CRH &= ~((GPIO_u8CLR_MASK)
					<< (Copy_u8PinId * GPIO_u8PIN_REG_SIZE));
			GPIO_C->GPIO_CRH |= ((Copy_u8Mode)
					<< (Copy_u8PinId * GPIO_u8PIN_REG_SIZE));

		} else {
			Local_enStatus = NOK;
		}

		break;

	default:
		Local_enStatus = NOK;
		break;
	}

	return Local_enStatus;
}
Error_t GPIO_enSetPinValue(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8Value) {
	Error_t Local_enStatus = OK;
	switch (Copy_u8PortId) {
	case GPIO_PORTA:
		if (Copy_u8Value == GPIO_u8HIGH) {
			SET_BIT(GPIO_A->GPIO_ODR, Copy_u8PinId);
		} else if (Copy_u8Value == GPIO_u8LOW) {
			CLR_BIT(GPIO_A->GPIO_ODR, Copy_u8PinId);

		} else {
			Local_enStatus = NOK;
		}

		break;

	case GPIO_PORTB:
		if (Copy_u8Value == GPIO_u8HIGH) {
			SET_BIT(GPIO_B->GPIO_ODR, Copy_u8PinId);
		} else if (Copy_u8Value == GPIO_u8LOW) {
			CLR_BIT(GPIO_B->GPIO_ODR, Copy_u8PinId);

		} else {
			Local_enStatus = NOK;
		}

		break;
	case GPIO_PORTC:
		if (Copy_u8Value == GPIO_u8HIGH) {
			SET_BIT(GPIO_C->GPIO_ODR, Copy_u8PinId);
		} else if (Copy_u8Value == GPIO_u8LOW) {
			CLR_BIT(GPIO_C->GPIO_ODR, Copy_u8PinId);

		} else {
			Local_enStatus = NOK;
		}

		break;
	default:
		Local_enStatus = NOK;
		break;

	}
	return Local_enStatus;
}
Error_t GPIO_enGetPinValue(u8 Copy_u8PortId, u8 Copy_u8PinId,
		u8 *ptr_u8ReturnValue) {
	Error_t Local_enStatus = OK;
	switch (Copy_u8PortId) {
	case GPIO_PORTA:
		*ptr_u8ReturnValue = SET_BIT(GPIO_A->GPIO_IDR, Copy_u8PinId);
		break;
	case GPIO_PORTB:
		*ptr_u8ReturnValue = SET_BIT(GPIO_B->GPIO_IDR, Copy_u8PinId);
		break;
	case GPIO_PORTC:
		*ptr_u8ReturnValue = SET_BIT(GPIO_C->GPIO_IDR, Copy_u8PinId);
		break;

	default:
		Local_enStatus = NOK;
		break;
	}
	return Local_enStatus;
}

Error_t GPIO_u8SetResetPin(u8 Local_u8Pin, u8 local_mode) {
	u8 local_port = (Local_u8Pin / GPIO_u8R_PINS) + 1;
	u8 local_pin = Local_u8Pin % GPIO_u8R_PINS;
	Error_t local_state = OK;
	switch (local_port) {
	case GPIO_PORTA:
		switch (local_mode) {
		case GPIO_u8SetPin:
			GPIO_A->GPIO_BSRR = (1 << local_pin);
			break;
		case GPIO_u8ResPin:
			GPIO_A->GPIO_BRR = (1 << local_pin);
			break;
		}
		break;
	case GPIO_PORTB:
		switch (local_mode) {
		case GPIO_u8SetPin:
			GPIO_B->GPIO_BSRR = (1 << local_pin);
			break;
		case GPIO_u8ResPin:
			GPIO_B->GPIO_BRR = (1 << local_pin);
			break;
		}
		break;
	case GPIO_PORTC:
		switch (local_mode) {
		case GPIO_u8SetPin:
			GPIO_C->GPIO_BSRR = (1 << local_pin);
			break;
		case GPIO_u8ResPin:
			GPIO_C->GPIO_BRR = (1 << local_pin);
			break;
		}
		break;
	default:
		local_state = NOK;
		break;
	}
	return local_state;
}
Error_t GPIO_u8SetPinD_ID(GPIO_u8PIN_t Copy_u8PinId, u8 Copy_u8Mode) {
	u8 local_port = (Copy_u8PinId / GPIO_u8R_PINS) + 1;
	u8 local_pin = Copy_u8PinId % GPIO_u8R_PINS;
	Error_t local_state = OK;
	switch (local_port) {
	case GPIO_PORTA:
		if (local_pin <= GPIO_u8f_REG_LEN) {
			GPIO_A->GPIO_CRL &= ~((GPIO_u8CLR_MASK)
					<< (local_pin * GPIO_u8PIN_REG_SIZE));
			GPIO_A->GPIO_CRL |= ((Copy_u8Mode)
					<< (local_pin * GPIO_u8PIN_REG_SIZE));
		} else if (local_pin <= GPIO_u8L_REG_LEN) {
			GPIO_A->GPIO_CRH &= ~((GPIO_u8CLR_MASK)
					<< ((local_pin - GPIO_u8OFSET) * GPIO_u8PIN_REG_SIZE));
			GPIO_A->GPIO_CRH |= ((Copy_u8Mode)
					<< ((local_pin - GPIO_u8OFSET) * GPIO_u8PIN_REG_SIZE));
		} else {
			local_state = NOK;
		}
		break;
	case GPIO_PORTB:
		if (local_pin <= GPIO_u8f_REG_LEN) {
			GPIO_B->GPIO_CRL &= ~((GPIO_u8CLR_MASK)
					<< (local_pin * GPIO_u8PIN_REG_SIZE));
			GPIO_B->GPIO_CRL |= ((Copy_u8Mode)
					<< (local_pin * GPIO_u8PIN_REG_SIZE));
		} else if (local_pin <= GPIO_u8L_REG_LEN) {
			GPIO_B->GPIO_CRH &= ~((GPIO_u8CLR_MASK)
					<< ((local_pin - GPIO_u8OFSET) * GPIO_u8PIN_REG_SIZE));
			GPIO_B->GPIO_CRH |= ((Copy_u8Mode)
					<< ((local_pin - GPIO_u8OFSET) * GPIO_u8PIN_REG_SIZE));
		} else {
			local_state = NOK;
		}
		break;
	case GPIO_PORTC:
		if (local_pin <= GPIO_u8f_REG_LEN) {
			GPIO_C->GPIO_CRL &= ~((GPIO_u8CLR_MASK)
					<< (local_pin * GPIO_u8PIN_REG_SIZE));
			GPIO_C->GPIO_CRL |= ((Copy_u8Mode)
					<< (local_pin * GPIO_u8PIN_REG_SIZE));
		} else if (local_pin <= GPIO_u8L_REG_LEN) {
			GPIO_C->GPIO_CRH &= ~((GPIO_u8CLR_MASK)
					<< ((local_pin - GPIO_u8OFSET) * GPIO_u8PIN_REG_SIZE));
			GPIO_C->GPIO_CRH |= ((Copy_u8Mode)
					<< ((local_pin - GPIO_u8OFSET) * GPIO_u8PIN_REG_SIZE));
		} else {
			local_state = NOK;
		}
		break;
	default:
		local_state = NOK;
		break;
	}

	return local_state;
}
Error_t GPIO_u8SetPinV_ID(GPIO_u8PIN_t Copy_u8PinId, u8 Copy_u8Value) {
	u8 local_port = (Copy_u8PinId / GPIO_u8R_PINS) + 1;
	u8 local_pin = Copy_u8PinId % GPIO_u8R_PINS;
	Error_t local_state = OK;
	switch (local_port) {
	case GPIO_PORTA:
		WRITE_BIT(GPIO_A->GPIO_ODR, local_pin, Copy_u8Value);
		break;
	case GPIO_PORTB:
		WRITE_BIT(GPIO_B->GPIO_ODR, local_pin, Copy_u8Value);
		break;
	case GPIO_PORTC:
		WRITE_BIT(GPIO_C->GPIO_ODR, local_pin, Copy_u8Value);
		break;
	default:
		local_state = NOK;
		break;
	}

	return local_state;
}
Error_t GPIO_u8LockPin_ID(GPIO_u8PIN_t Copy_u8PinId, u8 Copy_u8Mode) {
	u8 local_port = (Copy_u8PinId / GPIO_u8R_PINS) + 1;
	u8 local_pin = Copy_u8PinId % GPIO_u8R_PINS;
	Error_t local_state = OK;
	switch (local_port) {
	case GPIO_PORTA:
		WRITE_BIT(GPIO_A->GPIO_LCKR, local_pin, Copy_u8Mode);
		if (Copy_u8Mode == HIGH) {
			SET_BIT(GPIO_A->GPIO_LCKR, GPIO_u8R_PINS); // check lock sequence
			CLR_BIT(GPIO_A->GPIO_LCKR, GPIO_u8R_PINS);
			SET_BIT(GPIO_A->GPIO_LCKR, GPIO_u8R_PINS);
			if (READ_BIT(GPIO_A->GPIO_LCKR, GPIO_u8R_PINS)) {
				local_state = NOK;

			} else {
				if (!READ_BIT(GPIO_A->GPIO_LCKR, GPIO_u8R_PINS)) {
					local_state = NOK;
				}
			}
		}

		break;
	case GPIO_PORTB:
		WRITE_BIT(GPIO_B->GPIO_LCKR, local_pin, Copy_u8Mode);
		if (Copy_u8Mode == HIGH) {
			SET_BIT(GPIO_B->GPIO_LCKR, GPIO_u8R_PINS); // check lock sequence
			CLR_BIT(GPIO_B->GPIO_LCKR, GPIO_u8R_PINS);
			SET_BIT(GPIO_B->GPIO_LCKR, GPIO_u8R_PINS);
			if (READ_BIT(GPIO_B->GPIO_LCKR, GPIO_u8R_PINS)) {
				local_state = NOK;

			} else {
				if (!READ_BIT(GPIO_B->GPIO_LCKR, GPIO_u8R_PINS)) {
					local_state = NOK;
				}
			}
		}

		break;
	case GPIO_PORTC:
		WRITE_BIT(GPIO_C->GPIO_LCKR, local_pin, Copy_u8Mode);
		if (Copy_u8Mode == HIGH) {
			SET_BIT(GPIO_C->GPIO_LCKR, GPIO_u8R_PINS); // check lock sequence
			CLR_BIT(GPIO_C->GPIO_LCKR, GPIO_u8R_PINS);
			SET_BIT(GPIO_C->GPIO_LCKR, GPIO_u8R_PINS);
			if (READ_BIT(GPIO_C->GPIO_LCKR, GPIO_u8R_PINS)) {
				local_state = NOK;

			} else {
				if (!READ_BIT(GPIO_C->GPIO_LCKR, GPIO_u8R_PINS)) {
					local_state = NOK;
				}
			}
		}

		break;
	default:
		local_state = NOK;
		break;
	}

	return local_state;
}
Error_t GPIO_u8GetPinV_ID(GPIO_u8PIN_t Copy_u8PinId, u8 *ptr_u8ReturnValue) {
	u8 local_port = (Copy_u8PinId / GPIO_u8R_PINS) + 1;
	u8 local_pin = Copy_u8PinId % GPIO_u8R_PINS;
	Error_t local_state = OK;
	u8 local_return = 0;
	switch (local_port) {
	case GPIO_PORTA:
		local_return = READ_BIT(GPIO_A->GPIO_IDR, local_pin);
		break;
	case GPIO_PORTB:
		local_return = READ_BIT(GPIO_B->GPIO_IDR, local_pin);
		break;
	case GPIO_PORTC:
		local_return = READ_BIT(GPIO_C->GPIO_IDR, local_pin);
		break;
	default:
		local_state = NOK;
		break;
	}
	*ptr_u8ReturnValue = local_return;
	return local_state;
}

