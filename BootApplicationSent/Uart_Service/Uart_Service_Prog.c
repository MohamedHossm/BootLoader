/*****************************************************************************/
/* Auther          : Mohamed Hoasm                                                    */
/* Date            : 19/11/2023                                                        */
/* Version         : 1.0                                                              */
/* SW              : Uart_Service                                                     */
/*****************************************************************************/
#include "../LIBS/STD_TYPES.h"
#include "../LIBS/BIT_MATH.h"

#include "../UART/UART_Interface.h"
#include "../RCC/RCC_Interface.h"
#include "../NVIC/NVIC_Interface.h"

#include "Uart_Service_Conf.h"
#include "Uart_Service_Interface.h"
#include "Uart_Service_Pivate.h"

/*****************************************************************************************************************/
extern APP_StateMach Global_enuAppStates;
/*****************************************************************************************************************/

/*****************************************************************************************************************/
// uart1
char Global_u8ArryReciveDirectUart[BUFFERSIZE] = { 0 };
u8 Global_u8StackPointerArryRecive = 0;
volatile u8 dataReciev = 0;
/*****************************************************************************************************************/
//uart 2
char Global_u8ArryReciveDirectUart2[BUFFERSIZE] = { 0 };
u8 Global_u8StackPointerArryRecive2 = 0;
volatile u8 dataReciev2 = 0;
/*****************************************************************************************************************/

void Uart_Service_voidInit() {

	/***********************************uart1************************************************/
	RCC_voidEnablePeriphralCLK(APB2_USART1EN);
	UART1_voidInit(); // init uart 9600
	NVIC_u8Set_EN_IRQ(INTERRUPT_USART1);
	UART1_u8EnterruptCallBackRX(&UartFunction);
	UART1_u8EnterruptEnRX();
	/***********************************************************************************/

	/************************************uart2***********************************************/

	RCC_voidEnablePeriphralCLK(APB1_USART2EN);
	UART2_voidInit(); // init uart 115200
	NVIC_u8Set_EN_IRQ(INTERRUPT_USART2);
	UART2_u8EnterruptCallBackRX(&Uart2Function);
	UART2_u8EnterruptEnRX();
	/***********************************************************************************/

}
Bool_t StringCom(const char *ptr_SourceSTring, const char *ptr_CopySTring) {
	Bool_t ReturnValue = TRUE;
	for (u8 index = 0;
			ptr_SourceSTring[index] != '#' || ptr_CopySTring[index] != '#';
			index++) {
		if (ptr_SourceSTring[index] == ptr_CopySTring[index]) {

		} else {
			ReturnValue = FALSE;
			break;
		}
	}
	return ReturnValue;
}
int String_u8len(const char *ptr_SourceSTring) {
	int local_stringlen = 0;
	for (local_stringlen = 0; ptr_SourceSTring[local_stringlen];
			local_stringlen++)
		;
	return local_stringlen;
}

Bool_t StringIncluded(const char *ptr_SourceSTring, const char *ptr_CopySTring) {
	Bool_t ReturnValue = FALSE;
	//Bool_t local_enuFlag = FALSE;
	int local_u8SourceLen = String_u8len(ptr_SourceSTring);
	int local_u8Counter = 0;
	for (int index = 0; ptr_CopySTring[index]; index++) {
		if (ptr_SourceSTring[local_u8Counter] == ptr_CopySTring[index]) {
			local_u8Counter++;

			if (local_u8Counter == local_u8SourceLen) {
				ReturnValue = TRUE;
				break;
			}
		} else {
			local_u8Counter = 0;
		}
	}
	return ReturnValue;
}

void App_HandelFlames(void) {

	if (dataReciev == 1) {
		//UART1_u8SendStringBusyW8(Global_u8ArryReciveDirectUart);
		//UART1_u8SendStringBusyW8("\n");
		if (StringCom(WIFI_FRAMECASE_HAVEUPDATE,
				Global_u8ArryReciveDirectUart) == TRUE) {
			Global_enuAppStates = APP_normal_CHECKPB;
		}  else {

		}
	}
	if (Global_u8StackPointerArryRecive > WIFI_MAXSIZE || dataReciev == 1) {
		dataReciev = 0;
		for (u8 index = 0; index <= WIFI_MAXSIZE; index++) {
			Global_u8ArryReciveDirectUart[index] = 0;
		}
		Global_u8StackPointerArryRecive = 0;

	}

}
void App_HandelFlames2(void) {


	if (dataReciev2 == 1) {
		//UART1_u8SendStringBusyW8(Global_u8ArryReciveDirectUart2);
		//UART1_u8SendStringBusyW8("\n");
		if (StringCom(WIFI_REPORT_ERR, Global_u8ArryReciveDirectUart2) == TRUE) {
			//UART2_u8SendStringBusyW8("OK");
			//	UART1_u8SendStringBusyW8(Global_u8ArryReciveDirectUart2);
			//	UART1_u8SendStringBusyW8("\n");
			Global_enuAppStates = APP_REPORT_ERR1;
		} else if (StringCom(WIFI_REPORT_ERR2,
				Global_u8ArryReciveDirectUart2) == TRUE) {
			//	UART2_u8SendStringBusyW8("OK");
			//	UART1_u8SendStringBusyW8(Global_u8ArryReciveDirectUart2);
			//	UART1_u8SendStringBusyW8("\n");
			Global_enuAppStates = APP_REPORT_ERR2;
		} else if (StringCom(CAR_REPORT_REQ,
				Global_u8ArryReciveDirectUart2) == TRUE) {
			//	UART2_u8SendStringBusyW8("OK");
			//	UART1_u8SendStringBusyW8(Global_u8ArryReciveDirectUart2);
			//	UART1_u8SendStringBusyW8("\n");
			Global_enuAppStates = APP_REPORT_CONF;
		} else {

			//do noting
		}
	}

	if (Global_u8StackPointerArryRecive2 > WIFI_MAXSIZE || dataReciev2 == 1) {
		dataReciev2 = 0;
		for (u8 index = 0; index <= WIFI_MAXSIZE; index++) {
			Global_u8ArryReciveDirectUart2[index] = 0;
		}
		Global_u8StackPointerArryRecive2 = 0;
	}

}

void UartFunction(void) {
	u8 local_u8datalast = 0;

	UART1_u8RecieveByte(&local_u8datalast);
	UART2_u8SendByteBusyw8(local_u8datalast);

	Global_u8ArryReciveDirectUart[Global_u8StackPointerArryRecive] =
			local_u8datalast;
	Global_u8StackPointerArryRecive++;
	if (local_u8datalast == '#') {
		dataReciev = 1;
	}

}
void Uart2Function(void) {
	u8 local_u8datalast = 0;

	UART2_u8RecieveByte(&local_u8datalast);
	//UART1_u8SendByteBusyw8(local_u8datalast);

	Global_u8ArryReciveDirectUart2[Global_u8StackPointerArryRecive2] =
			local_u8datalast;
	Global_u8StackPointerArryRecive2++;
	/*
	 if (Global_u8StackPointerArryRecive2 > WIFI_MAXSIZE) {
	 //	dataReciev2 = 1;
	 for (u8 index = 0; index <= WIFI_MAXSIZE; index++) {
	 Global_u8ArryReciveDirectUart2[index] = 0;
	 }
	 Global_u8StackPointerArryRecive2 = 0;
	 }
	 */
	if (local_u8datalast == '#') {
		dataReciev2 = 1;
	}

}
