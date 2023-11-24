/*****************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 13/7/2023                                                        */
/* Version        : 1.0                                                              */
/*sw              : GPIO                                                             */
/*****************************************************************************/


#ifndef _GPIO_INTERFACE_H_
#define _GPIO_INTERFACE_H_

#define GPIO_PORTA 1
#define GPIO_PORTB 2
#define GPIO_PORTC 3

#define GPIO_u8SetPin 1 
#define GPIO_u8ResPin 2 

#define GPIO_u8HIGH 1
#define GPIO_u8LOW 0

#define GPIO_u8R_PINS 16

#define GPIO_u8PIN0 0
#define GPIO_u8PIN1 1
#define GPIO_u8PIN2 2
#define GPIO_u8PIN3 3
#define GPIO_u8PIN4 4
#define GPIO_u8PIN5 5
#define GPIO_u8PIN6 6
#define GPIO_u8PIN7 7
#define GPIO_u8PIN8 8
#define GPIO_u8PIN9 9
#define GPIO_u8PIN10 10
#define GPIO_u8PIN11 11
#define GPIO_u8PIN12 12
#define GPIO_u8PIN13 13
#define GPIO_u8PIN14 14
#define GPIO_u8PIN15 15

/* INPUT */
#define GPIO_u8INPUT_ANALOG  		 0b0000
#define GPIO_u8INPUT_FLOATING		 0b0100
#define GPIO_u8INPUT_PULL_UP_DOWN 	 0b1000
/* OUTPUT */
#define GPIO_u8OUT_PUSH_PULL_2MHZ    0b0010
#define GPIO_u8OUT_PUSH_PULL_10MHZ   0b0001
#define GPIO_u8OUT_PUSH_PULL_50MHZ   0b0011


#define GPIO_u8OUT_PUSH_PULL_OPEN_DRAIN_2MHZ    0b0110
#define GPIO_u8OUT_PUSH_PULL_OPEN_DRAIN_10MHZ   0b0101
#define GPIO_u8OUT_PUSH_PULL_OPEN_DRAIN_50MHZ   0b0111


#define GPIO_u8OUT_AF_DRAIN_2MHZ        0b1110
#define GPIO_u8OUT_AF_PP_10MHZ   		0b1001
#define GPIO_u8OUT_AF_PP_50MHZ   		0b1011

typedef enum {
	Pin_A0 = 0,
	Pin_A1,
	Pin_A2,
	Pin_A3,
	Pin_A4,
	Pin_A5,
	Pin_A6,
	Pin_A7,
	Pin_A8,
	Pin_A9,
	Pin_A10,
	Pin_A11,
	Pin_A12,
	Pin_A13,
	Pin_A14,
	Pin_A15,
	Pin_B0,
	Pin_B1,
	Pin_B2,
	Pin_B3,
	Pin_B4,
	Pin_B5,
	Pin_B6,
	Pin_B7,
	Pin_B8,
	Pin_B9,
	Pin_B10,
	Pin_B11,
	Pin_B12,
	Pin_B13,
	Pin_B14,
	Pin_B15,
	Pin_C0,
	Pin_C1,
	Pin_C2,
	Pin_C3,
	Pin_C4,
	Pin_C5,
	Pin_C6,
	Pin_C7,
	Pin_C8,
	Pin_C9,
	Pin_C10,
	Pin_C11,
	Pin_C12,
	Pin_C13,
	Pin_C14,
	Pin_C15,
	PINTOTAL
} GPIO_u8PIN_t;
typedef struct {
	GPIO_u8PIN_t GPIO_u8_pin;
	u8 GPIO_u8_Mode;
} GPIO_Conf_t;




#define INPUT  0
#define OUTPUT 1

#define HIGH 1
#define LOW  0

Error_t GPIO_enSetPinDirection(u8 Copy_u8PortId,u8 Copy_u8PinId,u8 Copy_u8Mode);
Error_t GPIO_enSetPinValue(u8 Copy_u8PortId,u8 Copy_u8PinId,u8 Copy_u8Value);
Error_t GPIO_enGetPinValue(u8 Copy_u8PortId,u8 Copy_u8PinId,u8 * ptr_u8ReturnValue);

Error_t GPIO_u8SetPortDirection_H(u8 Copy_u8PortId ,u8 Copy_u8Mode) ;
Error_t GPIO_u8SetPortDirection_L(u8 Copy_u8PortId ,u8 Copy_u8Mode) ;
Error_t GPIO_u8SetPortValue_H(u8 Copy_u8PortId ,u8 Copy_u8Value) ;
Error_t GPIO_u8SetPortValue_L(u8 Copy_u8PortId ,u8 Copy_u8Value) ;

Error_t GPIO_u8SetResetPin(u8 Local_u8Pin, u8 local_mode) ;

Error_t GPIO_u8SetPinD_ID(GPIO_u8PIN_t Copy_u8PinId ,u8 Copy_u8Mode ) ;
Error_t GPIO_u8SetPinV_ID(GPIO_u8PIN_t Copy_u8PinId ,u8 Copy_u8Mode ) ;
Error_t GPIO_u8GetPinV_ID(GPIO_u8PIN_t Copy_u8PinId ,u8 * ptr_u8ReturnValue);
Error_t GPIO_u8LockPin_ID(GPIO_u8PIN_t Copy_u8PinId ,u8 Copy_u8Mode ) ;

Error_t GPIO_u8Init() ;
Error_t GPIO_u8DeInit();
#endif //_GPIO_INTERFACE_H_
 
