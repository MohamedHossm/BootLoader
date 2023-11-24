/*************************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 15/10/2023                                                       */
/* Version        : 1.0                                                              */
/*sw              : Bootloader                                                            */
/*************************************************************************************/

#include "../LIBS/STD_TYPES.h"
#include "../LIBS/STMF103C8_MMAP.h"

#include "Bootloader_Conf.h"
#include "Bootloader_Interface.h"
#include "Bootloader_Private.h"

#include "../HexServ/HexServ_Interface.h"
#include "../GPIO/GPIO_Interface.h"
#include "../UART/UART_Interface.h"
#include "../Systick/SYSTICK_Interface.h"
#include "../NVIC/NVIC_Interface.h"
#include "../RCC/RCC_Interface.h"
#include "../Flash/FLASH_Interface.h"
#include "../CRC/CRC_Interface.h"
#include "../DELAY/Delay.h"

#define TESTING_MODE  1

u32 Global_u32FlashAddrssLocation = 0;
Function_t jumpToApplication = NULLPTR;

BootloaderStates_t Global_Bootloader_enuStateMachien = BOOT_CHECKFORUPDEATE;

u8 Global_u8FrameSendRequestFlag = 0;
/*
 *
 *
 * */
u8 Flash_lock = 1;
char Global_u8ArryReciveDirectUart[100] = { 0 };
u8 Global_u8ArryReciveDirectUart1[40] = { 0 };
u8 Global_u8StackPointerArryRecive = 0;
u16 data = 0;
u8 RedesignHexdata[HEXFILESIZE] = { 0 };
u8 dataReciev = 0;
volatile u32 FlagCounter = 0;

/*
 *
 *
 * */

void DMB(void) {
	__asm volatile ("dmb");
	// Use "dmb" assembly instruction
}

__attribute__((always_inline)) static inline void __set_MSP(u32 topOfMainStack) {
	__asm volatile("MSR msp, %0\n" : : "r" (topOfMainStack) );
}

void Bootloader_Init() {
	///  UART INIT
	RCC_voidEnablePeriphralCLK(APB2_USART1EN);
	UART1_voidInit(); // init uart 9600
	NVIC_u8Set_EN_IRQ(INTERRUPT_USART1);
	UART1_u8EnterruptCallBackRX(&RX_Fun);
	UART1_u8EnterruptEnRX();

	STK_u8Init();
	//CRC_enuReset();

}

void Bootloader_Jump_To_Application() {
	u16 local_u8CalculatePages = 5000;
// earease date
	FLASH_enCalculatePages(BOOT_APPDDRESSMARK, &local_u8CalculatePages);
	FLASH_enErasePage(local_u8CalculatePages);
	// Disable interrupts
	UART1_u8EnterruptDsRX();
	GPIO_u8DeInit();
	// Deinitialize peripherals
	RCC_voidDisablePeriphralCLK(APB2_IOPAEN);
	RCC_voidDisablePeriphralCLK(APB2_IOPBEN);
	RCC_voidDisablePeriphralCLK(APB2_IOPCEN);
	RCC_voidDisablePeriphralCLK(APB2_USART1EN);
	RCC_voidDisablePeriphralCLK(APB1_USART2EN);

	// Set the SCB value
	DMB();
	SCB->VTOR = FLASH_RESET_HANDLER;
	DMB();
// set msp
	__set_MSP(*(volatile u32*) FLASH_BASE_ADDRESS);

	u32 *address = (u32*) (FLASH_RESET_HANDLER);
	u32 instruction = *address;
	// check on application
	if (instruction != 0xffffffff) {
		((void (*)(void)) instruction)();
	} else {

		//do nothong4
	}

	//jumpToApplication();
}
void Bootloader_Jump_To_FactoryApplication() {
	// but marker
	if (*(u16*) BOOT_APPDDRESSMARK == BOOT_FLASHAPPMARKER) {
		//do nothing
	} else {
		FLASH_enWriteData(BOOT_APPDDRESSMARK, BOOT_FLASHAPPMARKER);

	}
	// Disable interrupts
	UART1_u8EnterruptDsRX();
	UART2_u8EnterruptDsRX();

	GPIO_u8DeInit();
	// Deinitialize peripherals
	RCC_voidDisablePeriphralCLK(APB2_IOPAEN);
	RCC_voidDisablePeriphralCLK(APB2_IOPBEN);
	RCC_voidDisablePeriphralCLK(APB2_IOPCEN);
	RCC_voidDisablePeriphralCLK(APB2_USART1EN);
	RCC_voidDisablePeriphralCLK(APB1_USART2EN);

	// Set the SCB value
	DMB();
	SCB->VTOR = FACTORY_FLASH_RESET_HANDLER;
	DMB();
// set msp
	__set_MSP(*(volatile u32*) FACTORY_FLASH_BASE_ADDRESS);

	u32 *address = (u32*) (FACTORY_FLASH_RESET_HANDLER);
	u32 instruction = *address;
	// check on application
	if (instruction != 0xffffffff) {
		((void (*)(void)) instruction)();
	} else {

		//do nothong4
	}

	//jumpToApplication();
}
void Bootloader_voidfReciveFlash() {

	Bool_t boot_enuCheckSum = 0;
	u8 boot_u8CheckSumValue = 0;
	Bool_t boot_enuSelectApp = FALSE;
	static Bool_t bootRuntimeout = TRUE;
	// switch Main App and factory app and chaeck for time out
	if (bootRuntimeout == TRUE) {
		boot_enuSelectApp = localBootloader_SellectAPP();
		if (boot_enuSelectApp == FALSE) {
			STK_u8StopTimer();
			STK_u8SetIntervalSingle(TIMEOUTDEALY + TIMEOUTDEALYFORREQ,
					Bootloader_StateMachienChangeToApp);
		} else {
			STK_u8StopTimer();
			STK_u8SetIntervalSingle(TIMEOUTDEALY + TIMEOUTDEALYFORREQ,
					Bootloader_StateMachienChangeToFactoryApp);

		}

		bootRuntimeout = FALSE;
	} else {
		//do nothing
	}
	/*
	 if (Flash_lock == 1) {
	 UART2_u8SendStringBusyW8("BOOT");
	 UART2_u8SendStringBusyW8("\n");

	 UART1_u8SendStringBusyW8("BOOT");
	 } else {

	 // do nothing
	 }
	 */

	if (dataReciev == 1) {

		if (Flash_lock == 1) {
			Flash_lock = 0;

#if  TESTING_MODE
			BootLocationEreas();

#endif
		} else {

			// do nothing
		}
		//CRC_enuWriteDataRegisterSoftWareArray(
		//	(u8*) Global_u8ArryReciveDirectUart,
		//	(u8) Global_u8StackPointerArryRecive);
		RedesignHex1Bytes((u8*) Global_u8ArryReciveDirectUart,
				(u8*) RedesignHexdata, HEXFILESIZE);
		u16 ReturnAdd = 0;
		u8 ReturnSize = 0;
		u8 ReturnTybe = 0;
		u8 ReturnChecksum = 0;
		u8 ReturnData[16] = { 0 };

		HEX_voidParseFrame((u8*) RedesignHexdata, &ReturnAdd, ReturnData,
				&ReturnSize, &ReturnChecksum, &ReturnTybe);
		boot_u8CheckSumValue = DataCeckSum(RedesignHexdata, HEXFILESIZE,
				ReturnChecksum);
		if (boot_u8CheckSumValue == ReturnChecksum) {
			boot_enuCheckSum = TRUE;
		} else {
			boot_enuCheckSum = FALSE;

		}
		UART1_u8SendNumString(boot_enuCheckSum);
		/*
		 UART1_u8SendNumString(boot_u8CheckSumValue);
		 UART1_u8SendStringBusyW8("/n");
		 */
		/*
		 for (int i = 0; i < HEXFILESIZE; i++) {
		 UART1_u8SendNumString(RedesignHexdata[i]);
		 UART1_u8SendStringBusyW8("-");
		 }
		 */
		//UART2_u8SendStringBusyW8((char*) Global_u8ArryReciveDirectUart);
		/*if (ReturnTybe == HEX_EXTENDEDLINEQR) {
		 Global_u32FlashAddrssLocation = (ReturnData[0] << 8 | ReturnData[1])
		 << 16;

		 } else */

		if (ReturnTybe == HEX_DATARECORDER) {
			STK_u8StopTimer();
			STK_u8SetIntervalSingle(TIMEOUTDEALY,
					Bootloader_StateMachienChangeToFactoryApp);
			//UART1_u8SendNumString(Global_u32FlashAddrssLocation + (ReturnAdd));
			//UART1_u8SendStringBusyW8("\n");

			//CRC_enuWriteDataRegisterArry((u64*) (Global_u8ArryReciveDirectUart+8), ReturnSize/2);
			//	UART1_u8SendStringBusyW8("----\n");

#if TESTING_MODE
			FLASH_enWriteArray(FLASH_BASE_ADDRESSTest + (ReturnAdd),
					ReturnSize / 2, (u16*) ReturnData);
#endif

			//UART1_u8SendStringBusyW8("WROTE");

		} else if (ReturnTybe == HEX_ENDOFRECORD) {

			/*UART1_u8SendStringBusyW8("\n");
			 UART1_u8SendStringBusyW8("END");
			 UART1_u8SendStringBusyW8("\n");

			 UART1_u8SendStringBusyW8("OK");
			 */
			STK_u8StopTimer();
			/*
			 u32 CRC_Get = 0;
			 CRC_enuReadRegister(&CRC_Get);
			 UART1_u8SendNumString(CRC_Get);
			 CRC_enuResetSoftWare();
			 */
			u16 local_u8CalculatePages = 5000;
			FLASH_enCalculatePages(BOOT_DDRESSMARK, &local_u8CalculatePages);
			FLASH_enErasePage(local_u8CalculatePages);
			Global_Bootloader_enuStateMachien = BOOT_JUMPTOTHEMAINAPP;
			//	UART2_u8SendStringBusyW8("\n");
			//	UART2_u8SendStringBusyW8("OK");
			//	UART2_u8SendStringBusyW8("\n");
			//UART2_u8SendStringBusyW8("END");
		}			//
		/*
		 UART2_u8SendStringBusyW8("\n");
		 UART2_u8SendStringBusyW8("OK");

		 UART1_u8SendStringBusyW8("\n");

		 UART1_u8SendStringBusyW8("OK");

		 Global_u8StackPointerArryRecive = 0;
		 dataReciev = 0;
		 */

		if (boot_enuCheckSum == TRUE) {
			//	UART2_u8SendStringBusyW8("\n");
			//	UART2_u8SendStringBusyW8("OK");
			UART1_u8SendStringBusyW8("\n");
			UART1_u8SendStringBusyW8("OK");

			Global_u8StackPointerArryRecive = 0;
			dataReciev = 0;
			Global_u8StackPointerArryRecive = 0;
			dataReciev = 0;

		} else if (boot_enuCheckSum == FALSE) {
			//UART2_u8SendStringBusyW8("\n");
			//UART2_u8SendStringBusyW8("OK");
			UART1_u8SendStringBusyW8("\n");
			UART1_u8SendStringBusyW8("NOK");

			Global_u8StackPointerArryRecive = 0;
			dataReciev = 0;
		} else {
			//do nothing
		}

	}

}

void BootLocationEreas() {
	u16 local_u16page = 0;
	FLASH_enCalculatePages(FLASH_BASE_ADDRESS, &local_u16page);
	UART1_u8SendByteBusyw8(local_u16page);
	for (u8 indxFlash_u8Page = local_u16page;
			indxFlash_u8Page < local_u16page + FLASH_ERASE_SIZE;
			indxFlash_u8Page++) {
		FLASH_enErasePage(indxFlash_u8Page);

	}
}

void Bootloader_voidfRunnable() {
	Bool_t boot_enuSelectApp = FALSE;

	switch (Global_Bootloader_enuStateMachien) {
	case BOOT_CHECKFORUPDEATE:

		Bool_t local_State = localBootloader_updateAvailable();
		if (local_State == TRUE) {
// go to state request .
			Global_Bootloader_enuStateMachien = BOOT_REQESTHEX;
			Global_u8FrameSendRequestFlag = 1;
		} else {
			Global_Bootloader_enuStateMachien = BOOT_WAITING;
		}
		break;
	case BOOT_WAITING:

		boot_enuSelectApp = localBootloader_SellectAPP();
		if (boot_enuSelectApp == FALSE) {
			STK_u8StartTimer();
			STK_u8SetIntervalSingle(TIMEOUTDEALY,
					Bootloader_StateMachienChangeToApp);
		} else {
			STK_u8StartTimer();
			STK_u8SetIntervalSingle(TIMEOUTDEALY,
					Bootloader_StateMachienChangeToFactoryApp);
		}

		Bootloader_HandelFlames();
		//UART1_u8SendStringBusyW8("Wait");

		break;
	case BOOT_REQESTHEX:
		// Uart send command for Update
		boot_enuSelectApp = localBootloader_SellectAPP();
		if (boot_enuSelectApp == FALSE) {
			STK_u8StartTimer();
			STK_u8SetIntervalSingle(TIMEOUTDEALY + TIMEOUTDEALYFORREQ,
					Bootloader_StateMachienChangeToApp);
		} else {

			STK_u8SetIntervalSingle(TIMEOUTDEALY + TIMEOUTDEALYFORREQ,
					Bootloader_StateMachienChangeToFactoryApp);

		}

		if (Global_u8FrameSendRequestFlag == 1) {
			// 	UART1_u8SendStringBusyW8("DIAG_1_UPDATE_END");

			//UART1_u8SendStringBusyW8("A\n");

			Global_Bootloader_enuStateMachien = BOOT_RECIVINGHEX;

			Global_u8FrameSendRequestFlag = 0;
			//UART2_u8SendStringBusyW8("BOOT");
			//UART2_u8SendStringBusyW8("\n");

			UART1_u8SendStringBusyW8("BOOT");
			UART1_u8SendStringBusyW8("\n");
			Delay(100);
			UART1_u8SendStringBusyW8("BOOT");
			UART1_u8SendStringBusyW8("\n");
			Delay(200);

			UART1_u8SendStringBusyW8("BOOT");
			UART1_u8SendStringBusyW8("\n");

			//UART1_u8SendStringBusyW8("\n");

		} else {
			Bootloader_HandelFlames();
		}
		break;
	case BOOT_CHECKSTATES:

		break;
	case BOOT_RECIVINGHEX:

		Bootloader_voidfReciveFlash();
		break;

	case BOOT_JUMPTOTHEMAINAPP:
		Bootloader_Jump_To_Application();
		break;
	case BOOT_JUMPTOTHEFACTORYAPP:
		Bootloader_Jump_To_FactoryApplication();
		break;

	case BOOT_ERROR:
		// report error  and go Waiting
		Global_Bootloader_enuStateMachien = BOOT_WAITING;
		break;
	default:
		break;
	}

}
void Bootloader_HandelFlames(void) {
	u16 local_u16DataCheckOverFrame = 0;
	u8 localArray_u8temparr[2] = { 0 };
// check on frist 2bytes for Stages data
	if (Global_u8StackPointerArryRecive > 1) {
		RedesignHex1Bytes((u8*) Global_u8ArryReciveDirectUart,
				localArray_u8temparr, 2);
		local_u16DataCheckOverFrame = ((u16) localArray_u8temparr[0] << 8)
				| localArray_u8temparr[1];
		Global_u8StackPointerArryRecive = 0;
		*(u16*) Global_u8ArryReciveDirectUart = 0;

	} else {
		//do nothing
	}

// switch on cases .. flash sequence .. update sequances ..
	switch (local_u16DataCheckOverFrame) {

	case BOOT_FRAMECASE_FLASHING:
		STK_u8StopTimer();
		//send for server for data .
		UART1_u8SendStringBusyW8("ACKFLASH");
		Global_Bootloader_enuStateMachien = BOOT_RECIVINGHEX;
		break;
	default:
		break;
	}

}
static void Bootloader_StateMachienChangeToApp() {
	Global_Bootloader_enuStateMachien = BOOT_JUMPTOTHEMAINAPP;
	STK_u8StopTimer();
}
static void Bootloader_StateMachienChangeToFactoryApp() {
	Global_Bootloader_enuStateMachien = BOOT_JUMPTOTHEFACTORYAPP;
	STK_u8StopTimer();
}

static Bool_t localBootloader_updateAvailable(void) {
	Bool_t local_BReturn = TRUE;
	u16 *local_ptrFindMarker = (u16*) BOOT_DDRESSMARK;
	if (local_ptrFindMarker >= (u16*) FLASH_START
			&& local_ptrFindMarker <= (u16*) FLASH_END) {
		if (*local_ptrFindMarker == BOOT_FLASHMARK) {
			// do noting
			// earease this location later
			Global_Bootloader_enuStateMachien = BOOT_REQESTHEX;

		} else {

			local_BReturn = FALSE;
		}

	}

	return local_BReturn;
}
static Bool_t localBootloader_SellectAPP(void) {
	Bool_t local_BReturn = TRUE;
	u16 *local_ptrFindMarker = (u16*) BOOT_APPDDRESSMARK;
	if (local_ptrFindMarker >= (u16*) FLASH_START
			&& local_ptrFindMarker <= (u16*) FLASH_END) {
		if (*local_ptrFindMarker == BOOT_FLASHAPPMARKER) {
			// do noting
			// earease this location later
			//	Global_Bootloader_enuStateMachien = BOOT_JUMPTOTHEFACTORYAPP;

		} else {

			local_BReturn = FALSE;
		}

	}

	return local_BReturn;
}
void RX_Fun(void) {
	FlagCounter++;
	static u8 local_u8datalast = 0;
	static u16 local_u8Counter = 0;

	UART1_u8RecieveByte(&local_u8datalast);
//	UART2_u8SendByteBusyw8(local_u8datalast);
	if (local_u8datalast != ':' && local_u8datalast != '#') {
		Global_u8ArryReciveDirectUart[Global_u8StackPointerArryRecive] =
				local_u8datalast;
		Global_u8StackPointerArryRecive++;
	}

	if (local_u8datalast == '#') {
		Global_u8ArryReciveDirectUart[Global_u8StackPointerArryRecive] = 0;
		dataReciev = 1;
		local_u8Counter++;
		//	UART2_u8SendNumString(local_u8Counter);

	}

}

