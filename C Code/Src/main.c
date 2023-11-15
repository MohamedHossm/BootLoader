#include "../LIBS/STD_TYPES.h"
#include "../LIBS/STMF103C8_MMAP.h"

#include "../DELAY/Delay.h"
#include "../RCC/RCC_Interface.h"
#include "../GPIO/GPIO_Interface.h"
#include "../Flash/FLASH_Interface.h"
#include "../UART/UART_Interface.h"
#include "../Systick/SYSTICK_Interface.h"
#include "../NVIC/NVIC_Interface.h"
#include "../CRC/CRC_Interface.h"

#include "../Bootloader/Bootloader_Interface.h"
u32 dataget = 0;

int main(void) {

	RCC_voidInitSystemClock();
	RCC_voidEnablePeriphralCLK(APB2_IOPAEN);
	RCC_voidEnablePeriphralCLK(APB2_IOPBEN);
	RCC_voidEnablePeriphralCLK(APB2_IOPCEN);
	RCC_voidEnablePeriphralCLK(APB1_USART2EN);
	RCC_voidEnablePeriphralCLK(AHB_CRCEN);

	GPIO_u8Init();
	UART2_voidInit();
	//UART1_voidInit();

	GPIO_u8SetPinV_ID(Pin_B1, LOW);
	Bootloader_Init();
	//UART2_u8SendStringBusyW8("A7la mesa 3leeak ");
	//BootLocationEreas();
	//0x11223344
	//CRC_enuWriteDataRegister(0x11223344);
	//BootLocationEreas();
	while (1) {
#if 1

		GPIO_u8SetPinV_ID(Pin_A5, HIGH);
		Delay(100);
		GPIO_u8SetPinV_ID(Pin_A5, LOW);
		Delay(100);
		Bootloader_voidfRunnable();		//func();

#endif
#if 0



		UART2_u8SendNumString(111);
		UART2_u8SendStringBusyW8("\n");
		//CRC_enuReset();

#endif
#if 0
Bootloader_voidfReciveFlash();
#endif
#if 0
static u8 data  =0 ;
		STK_u8SetBusyWait(1000);
		GPIO_u8SetPinV_ID(Pin_A6, data);
		data = !data;
#endif
		//	UART1_u8RecieveByteBusyw8(&page);
# if 0
		u8 State = FLASH_enWriteData(0x080180F0, arr[0]);

		if (State == FLASH_WRITTEN) {
			GPIO_u8SetPinV_ID(Pin_A6, HIGH);
			FLASH_enCalculatePages(0x080180F0, &page);
			FLASH_enErasePage(page);
		}else {
			GPIO_u8SetPinV_ID(Pin_A6, LOW);

		}

		FLASH_enlock();
		//FLASH_enErasePage(page);
#endif
#if 0

		UART1_u8SendStringBusyW8("A7la mesa 3leeak ");
		static u8 data = 1;
		STK_u8SetBusyWait(1000);
		GPIO_u8SetPinV_ID(Pin_A5, data);
		data = !data;

#endif

	}
}
