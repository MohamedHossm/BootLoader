/*****************************************************************************/
/* Auther          : Mohamed Hoasm                                                    */
/* Date            : 3/8/2023                                                        */
/* Version         : 1.0                                                              */
/* SW              : UART                                                             */
/*****************************************************************************/
#include "../LIBS/STD_TYPES.h"
#include "../LIBS/BIT_MATH.h"
#include "../LIBS/STMF103C8_MMAP.h"

#include "UART_Conf.h"
#include "UART_Interface.h"
#include "UART_Pivate.h"
/*********************************************************/
//#include "GPIO_Interface.h"  //debuge
//#include "../Systick/SYSTICK_Interface.h" // debuge
/**********************************************************/

static volatile u8 UART1_u8GlobalFrame[UART_FRAME_SIZE] = { 0 };
static volatile u8 UART1_u8index = 0;
static volatile u8 UART1_u8EndFrameRecieved = 0;

static char UART1_StringRX[UART_STR_SIZE] = { 0 };
static u16 UART1_MUNRX = 0;

static u8 UART1_DataReady = 0;

static void (*GlobalRX)(void) = {NULLPTR };
static void (*GlobalRX_UART2)(void) = {NULLPTR };

/*
 void (*UART1_CallBack[UART_CALLBACK_SIZE])(void) =
 {	NULLPTR, NULLPTR,NULLPTR,NULLPTR };
 */

void UART1_voidInit() {

	/******** baud rate **********/
	UART1->USART_BRR = BAUDRATE;

	/******** frame format *******/
//no parity
	CLR_BIT(UART1->USART_CR1, PCE);
// 1 start 8bit data n stop
	CLR_BIT(UART1->USART_CR1, M);
// 1 stop bit
	CLR_BIT(UART1->USART_CR2, StOP_0);
	CLR_BIT(UART1->USART_CR2, StOP_1);

	/******** enable RX **********/
	SET_BIT(UART1->USART_CR1, RE);
	/******** enable TX **********/
	SET_BIT(UART1->USART_CR1, TE);
	/*********UART enable ********/
	SET_BIT(UART1->USART_CR1, UE);
	// clr status reg
	UART1->USART_SR = 0;
}

Error_t UART1_u8SendByteBusyw8(u8 data) {
	Error_t local_u8Status = OK;
	while (!READ_BIT(UART1->USART_SR, TXE))
		; // txe ---- time out is needed
	UART1->USART_DR = data;
	CLR_BIT(UART1->USART_SR, TXE);
	return local_u8Status;
}
Error_t UART1_u8RecieveByteBusyw8(u8 *data) {
	Error_t local_u8Status = OK;
	while (!READ_BIT(UART1->USART_SR, RXNE))
		; // RXne ---- time out is needed
	*data = UART1->USART_DR;
	CLR_BIT(UART1->USART_SR, RXNE);
	return local_u8Status;
}

Error_t UART1_u8SendStringBusyW8(char *data) {
	Error_t local_u8Status = OK;

	for (u8 local_index = 0; data[local_index]; local_index++) {
		UART1_u8SendByteBusyw8(data[local_index]);
	}
	return local_u8Status;
}

Error_t UART1_u8SendArrayBusyW8(u8 *data , u8 Copy_Size){
	Error_t local_u8Status = OK;

	for (u8 local_index = 0;local_index< Copy_Size; local_index++) {
			UART1_u8SendByteBusyw8(data[local_index]);
		}

	return local_u8Status;

}

Error_t UART1_u8RecieveByte(volatile u8 *data) {
	Error_t local_u8Status = OK;
// return DR reg
	*data = UART1->USART_DR;
	return local_u8Status;

}
Error_t UART1_u8SendNum(u32 copy_u32num) {
	Error_t local_u8Status = OK;

	u8 *localptr = (u8*) (&copy_u32num);
	UART1_u8SendByteBusyw8(localptr[0]);
	UART1_u8SendByteBusyw8(localptr[1]);
	UART1_u8SendByteBusyw8(localptr[2]);
	UART1_u8SendByteBusyw8(localptr[3]);

	return local_u8Status;

}
Error_t UART1_u8SendNumString(u32 copy_u32num) {
	Error_t local_u8Status = OK;
	u8 local_String[10];
	s8 index;
	if (copy_u32num != 0) {
		for (index = 0; copy_u32num; index++) {
			local_String[index] = copy_u32num % 10 + '0';
			copy_u32num /= 10;
		}
		index--;
		for (; index >= 0; index--) {
			UART1_u8SendByteBusyw8(local_String[index]);
		}
	} else {
		UART1_u8SendByteBusyw8('0');
	}

	return local_u8Status;

}

void separate_string() {
	u8 i, j = 0;
	for (i = 0;
			UART1_u8GlobalFrame[i] != '#' && UART1_u8GlobalFrame[i] != ' '
					&& i < UART_FRAME_SIZE; i++) {
		if (UART1_u8GlobalFrame[i] >= 'a' && UART1_u8GlobalFrame[i] <= 'z') {
			UART1_StringRX[j] = UART1_u8GlobalFrame[i];
			j++;
		}
	}
	UART1_StringRX[j] = 0;
	UART1_MUNRX = 0;
	for (; UART1_u8GlobalFrame[i] != '#' && i < UART_FRAME_SIZE; i++) {
		if (UART1_u8GlobalFrame[i] >= '0' && UART1_u8GlobalFrame[i] <= '9') {
			UART1_MUNRX = (UART1_MUNRX * 10) + (UART1_u8GlobalFrame[i] - '0');
		}
	}

}
void UART1_Runnable(void) {
	if (UART1_u8EndFrameRecieved) {

		separate_string();
		UART1_DataReady = 1;
		UART1_u8EndFrameRecieved = 0;
		UART1_u8index = 0;
	} else {
		//do nothing
	}

}

u8 UART1_IsDataReady(void) {
	return UART1_DataReady;
}
void UART1_GETdata(u8 *UART1ptrStr, u16 *UART1ptrNum) {
	u8 index = 0;
	*UART1ptrNum = UART1_MUNRX;
	for (; UART1_StringRX[index]; index++) {
		UART1ptrStr[index] = UART1_StringRX[index];
		UART1_StringRX[index] = 0;
	}
	UART1ptrStr[index] = 0;
	UART1_MUNRX = 0;
	UART1_DataReady = 0;
}

Error_t UART1_u8RecieveStringBusyW8(u8 *data);
Error_t UART1_u8EnterruptEnRX(void) {
	Error_t local_u8Status = OK;
	SET_BIT(UART1->USART_CR1, RXNEIE);
	return local_u8Status;
}
Error_t UART1_u8EnterruptDsRX(void) {
	Error_t local_u8Status = OK;
	CLR_BIT(UART1->USART_CR1, RXNEIE);
	return local_u8Status;
}
Error_t UART1_u8EnterruptCallBackRX(void (*Rx)(void)) {
	Error_t local_u8Status = OK;
	if (Rx != NULLPTR) {
		GlobalRX = Rx;
	} else {
		local_u8Status = NULL_PTR;
	}
	return local_u8Status;
}

Error_t UART1_u8EnterruptEnTX(void) {
	Error_t local_u8Status = OK;

	return local_u8Status;
}
Error_t UART1_u8EnterruptDsTX(void) {
	Error_t local_u8Status = OK;

	return local_u8Status;
}
Error_t UART1_u8EnterruptCallBackTX(void) {
	Error_t local_u8Status = OK;

	return local_u8Status;
}

void USART1_IRQHandler(void) {
	/*
	 if (READ_BIT(UART1->USART_SR, RXNE)) {
	 UART1_u8RecieveByte(&UART1_u8GlobalFrame[UART1_u8index]); //-
	 if (UART1_u8GlobalFrame[UART1_u8index] == UART1_ENDFRAM
	 || UART1_u8index == UART_FRAME_SIZE - 1) {
	 UART1_u8EndFrameRecieved = 1;
	 }
	 if (UART1_u8index < UART_FRAME_SIZE - 1) {
	 UART1_u8index++;
	 } else {
	 // do nothing
	 }
	 }
	 */
	if (READ_BIT(UART1->USART_SR, RXNE)) {
		if (GlobalRX) {
			GlobalRX();

		}
		CLR_BIT(UART1->USART_SR, RXNE);

	}

}
//*****************************************************************************************************************************************************/

/*********************************************************/
//#include "GPIO_Interface.h"  //debuge
//#include "../Systick/SYSTICK_Interface.h" // debuge
/**********************************************************/

static volatile u8 UART2_u8GlobalFrame[UART_FRAME_SIZE] = { 0 };
static volatile u8 UART2_u8index = 0;
static volatile u8 UART2_u8EndFrameRecieved = 0;
/*
static char UART2_StringRX[UART_STR_SIZE] = { 0 };
static u16 UART2_MUNRX = 0;

static u8 UART2_DataReady = 0;

static void (*UART2GlobalRX)(void) = {NULLPTR };
*/
/*
 void (*UART2_CallBack[UART_CALLBACK_SIZE])(void) =
 {	NULLPTR, NULLPTR,NULLPTR,NULLPTR };
 */

void UART2_voidInit() {

	/******** baud rate **********/
	UART2->USART_BRR = BAUDRATE2;

	/******** frame format *******/
//no parity
	CLR_BIT(UART2->USART_CR1, PCE);
// 1 start 8bit data n stop
	CLR_BIT(UART2->USART_CR1, M);
// 1 stop bit
	CLR_BIT(UART2->USART_CR2, StOP_0);
	CLR_BIT(UART2->USART_CR2, StOP_1);

	/******** enable RX **********/
	SET_BIT(UART2->USART_CR1, RE);
	/******** enable TX **********/
	SET_BIT(UART2->USART_CR1, TE);
	/*********UART enable ********/
	SET_BIT(UART2->USART_CR1, UE);
	// clr status reg
	UART2->USART_SR = 0;
}

Error_t UART2_u8SendByteBusyw8(u8 data) {
	Error_t local_u8Status = OK;
	while (!READ_BIT(UART2->USART_SR, TXE))
		; // txe ---- time out is needed
	UART2->USART_DR = data;
	CLR_BIT(UART2->USART_SR, TXE);
	return local_u8Status;
}
Error_t UART2_u8RecieveByteBusyw8(u8 *data) {
	Error_t local_u8Status = OK;
	while (!READ_BIT(UART2->USART_SR, RXNE))
		; // RXne ---- time out is needed
	*data = UART2->USART_DR;
	CLR_BIT(UART2->USART_SR, RXNE);
	return local_u8Status;
}

Error_t UART2_u8SendStringBusyW8(char *data) {
	Error_t local_u8Status = OK;

	for (u8 local_index = 0; data[local_index]; local_index++) {
		UART2_u8SendByteBusyw8(data[local_index]);
	}
	return local_u8Status;
}

Error_t UART2_u8SendArrayBusyW8(u8 *data , u8 Copy_Size){
	Error_t local_u8Status = OK;

	for (u8 local_index = 0;local_index< Copy_Size; local_index++) {
			UART2_u8SendByteBusyw8(data[local_index]);
		}

	return local_u8Status;

}

Error_t UART2_u8RecieveByte(volatile u8 *data) {
	Error_t local_u8Status = OK;
// return DR reg
	*data = UART2->USART_DR;
	return local_u8Status;

}
Error_t UART2_u8SendNum(u32 copy_u32num) {
	Error_t local_u8Status = OK;

	u8 *localptr = (u8*) (&copy_u32num);
	UART2_u8SendByteBusyw8(localptr[0]);
	UART2_u8SendByteBusyw8(localptr[1]);
	UART2_u8SendByteBusyw8(localptr[2]);
	UART2_u8SendByteBusyw8(localptr[3]);

	return local_u8Status;

}
Error_t UART2_u8SendNumString(u32 copy_u32num) {
	Error_t local_u8Status = OK;
	u8 local_String[10];
	s8 index;
	if (copy_u32num != 0) {
		for (index = 0; copy_u32num; index++) {
			local_String[index] = copy_u32num % 10 + '0';
			copy_u32num /= 10;
		}
		index--;
		for (; index >= 0; index--) {
			UART2_u8SendByteBusyw8(local_String[index]);
		}
	} else {
		UART2_u8SendByteBusyw8('0');
	}

	return local_u8Status;

}




Error_t UART2_u8RecieveStringBusyW8(u8 *data);
Error_t UART2_u8EnterruptEnRX(void) {
	Error_t local_u8Status = OK;
	SET_BIT(UART2->USART_CR1, RXNEIE);
	return local_u8Status;
}
Error_t UART2_u8EnterruptDsRX(void) {
	Error_t local_u8Status = OK;
	CLR_BIT(UART2->USART_CR1, RXNEIE);
	return local_u8Status;
}
Error_t UART2_u8EnterruptCallBackRX(void (*Rx)(void)) {
	Error_t local_u8Status = OK;
	if (Rx != NULLPTR) {
		GlobalRX_UART2 = Rx;
	} else {
		local_u8Status = NULL_PTR;
	}
	return local_u8Status;
}

Error_t UART2_u8EnterruptEnTX(void) {
	Error_t local_u8Status = OK;

	return local_u8Status;
}
Error_t UART2_u8EnterruptDsTX(void) {
	Error_t local_u8Status = OK;

	return local_u8Status;
}
Error_t UART2_u8EnterruptCallBackTX(void) {
	Error_t local_u8Status = OK;

	return local_u8Status;
}

void USART2_IRQHandler(void) {
	/*
	 if (READ_BIT(UART1->USART_SR, RXNE)) {
	 UART1_u8RecieveByte(&UART1_u8GlobalFrame[UART1_u8index]); //-
	 if (UART1_u8GlobalFrame[UART1_u8index] == UART1_ENDFRAM
	 || UART1_u8index == UART_FRAME_SIZE - 1) {
	 UART1_u8EndFrameRecieved = 1;
	 }
	 if (UART1_u8index < UART_FRAME_SIZE - 1) {
	 UART1_u8index++;
	 } else {
	 // do nothing
	 }
	 }
	 */
	if (READ_BIT(UART2->USART_SR, RXNE)) {
		if (GlobalRX_UART2) {
			GlobalRX_UART2();

		}
		CLR_BIT(UART2->USART_SR, RXNE);

	}

}




