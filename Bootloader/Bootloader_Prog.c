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



Function_t jumpToApplication = NULLPTR;


/*
 *
 *
 * */
u8 Flash_lock = 1;
char arr[100] = { 0 };
u8 arr1[40] = { 0 };
u8 Stack_ptr = 0;
u16 data = 0;
u8 RedesignHexdata[HEXFILESIZE] = { 0 };
u8 dataReciev = 0;
volatile u32 FlagCounter = 0;
static volatile u8 dataRx = 'S';
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

}

/*
void set_stack_pointer(void* stack_ptr) {
   // Inline assembly to set the Stack Pointer
    asm volatile (
        "ldr sp, [%0]\n"   // Load the stack pointer value from the variable
        :
        : "r"(stack_ptr)
    );
}
*/
void __set_CONTROL(u32 control_value) {
    __asm volatile (
        "msr control, %0"
        :
        : "r" (control_value)
    );
}
void change_pc(u32 new_address) {
    asm volatile (
        "ldr r0, %[new_addr]\n"
        "bx r0\n"
        :
        : [new_addr] "m" (new_address)
        : "r0"
    );
}

void jump_to_address(u32 new_address) {
    // Disable interrupts if needed

    // Set the MSP (Main Stack Pointer) to a known value
    // This step is essential for correct operation
    __set_MSP(*((u32 *)new_address));

    // Set the PC (Program Counter) to the desired address
    __set_CONTROL(0x2); // Set CONTROL register to use the MSP
    asm volatile ("bx %0" : : "r" (new_address));

    // Enable interrupts if needed

    // Code after changing the PC (will not be executed)
}
// Function to jump to the application
void Bootloader_Jump_To_Application1(u32 address) {


	    SCB->VTOR = FLASH_BASE_ADDRESS; // Set the VTOR to the base address of the vector table
	    Function_t jumpToApplication = (Function_t)address;
	    jumpToApplication();

}

void Bootloader_Jump_To_Application() {
	// Read MSP value from flash memory
	u32 MSP_Value = *(volatile u32*) FLASH_BASE_ADDRESS;

	Function_t jumpToApplication = (Function_t)FLASH_RESET_HANDLER;


	UART1_u8SendNumString((u32)jumpToApplication);
	UART1_u8SendStringBusyW8(" ");
	UART1_u8SendNumString(MSP_Value);
	UART1_u8SendStringBusyW8(" ");

	// Disable interrupts
	UART1_u8EnterruptDsRX();

	// Deinitialize peripherals (if needed)
	RCC_voidDisablePeriphralCLK(APB2_IOPAEN);
	RCC_voidDisablePeriphralCLK(APB2_IOPBEN);
	RCC_voidDisablePeriphralCLK(APB2_IOPCEN);
	RCC_voidDisablePeriphralCLK(APB2_USART1EN);

	// Set the MSP value
	DMB();
	SCB->VTOR = FLASH_RESET_HANDLER;
	DMB();
	// Function pointer for the reset handler
	// Call the reset handler
/*
	asm volatile (
		        "ldr r0, =0x08004004\n"   // Load the target address into R0
		        "mov pc, r0\n"             // Set the PC register to the target address
		   );
*/
	//jump_to_address(FLASH_RESET_HANDLER);
	//change_pc((u32)FLASH_RESET_HANDLER);
	//jumpToApplication();
	__set_MSP(*(volatile u32 *)FLASH_BASE_ADDRESS);

	unsigned int *address = (unsigned int *)(FLASH_RESET_HANDLER);
		unsigned int instruction = *address;
		((void (*)(void))instruction)();
		//jumpToApplication();
}
void Bootloader_voidfReciveFlash(){

	if (dataReciev == 1) {
		if (Flash_lock == 1) {
			Flash_lock = 0;
			BootLocationEreas();
		}else {

			// do nothing
		}

		RedesignHex1Bytes((u8*) arr, (u8*) RedesignHexdata, HEXFILESIZE);
		u16 ReturnAdd = 0;
		u8 ReturnSize = 0;
		u8 ReturnTybe = 0;
		u8 ReturnChecksum = 0;
		u8 ReturnData[16] = { 0 };




		HEX_voidParseFrame((u8*) RedesignHexdata, &ReturnAdd, ReturnData,
				&ReturnSize, &ReturnChecksum, &ReturnTybe);
		/*
		 for (int i = 0; i < HEXFILESIZE; i++) {
		 UART1_u8SendNumString(RedesignHexdata[i]);
		 UART1_u8SendStringBusyW8("-");
		 }
		 */

		if (ReturnTybe == HEX_DATARECORDER) {
			FLASH_enWriteArray(FLASH_BASE_ADDRESSTest + (ReturnAdd),
					ReturnSize / 2, (u16*) ReturnData);
			UART1_u8SendStringBusyW8("WROTE");

		} else if (ReturnTybe == HEX_ENDOFRECORD) {
			UART1_u8SendStringBusyW8("\n");
			UART1_u8SendStringBusyW8("OK");

		}

		UART1_u8SendStringBusyW8("\n");

		UART1_u8SendStringBusyW8("OK");
		Stack_ptr = 0;
		dataReciev = 0;

	}


	STK_u8SetBusyWait(20);
	GPIO_u8SetPinV_ID(Pin_C13, data);
	data = !data;
	GPIO_u8SetPinV_ID(Pin_A6, LOW);
}
/*
 void func(void) {



 RCC_voidDisablePeriphralCLK(APB2_IOPAEN);
 RCC_voidDisablePeriphralCLK(APB2_IOPBEN);
 RCC_voidDisablePeriphralCLK(APB2_IOPCEN);
 RCC_voidDisablePeriphralCLK(APB2_USART1EN);

 u32 MSP_Value = *((volatile u32*) FLASH_START_Prog);
 addr_to_call = (Function_t) (*(volatile u32*) FLASH_START_Prog_JUMB);

 __set_MSP(MSP_Value);
 //(ApplicationEntryPoint)(*(volatile u32*)(appAddress + 4));
 SCB_VTOR = FLASH_START_Prog_JUMB;
 if (addr_to_call != NULLPTR) {
 addr_to_call();
 }
 }
 */

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



void RX_Fun(void) {
	FlagCounter++;
	static u8 datalast = 'A';

	UART1_u8RecieveByte(&datalast);
	if (datalast != ':' && datalast != '#') {
		arr[Stack_ptr] = datalast;
		Stack_ptr++;
	}

	if (datalast == '#') {
		arr[Stack_ptr] = 0;
		dataReciev = 1;
	}
	static u8 data1 = 0;
	// STK_u8SetBusyWait(2);
//	Delay(500);
	GPIO_u8SetPinV_ID(Pin_A6, data1);
	data1 = !data1;
}

