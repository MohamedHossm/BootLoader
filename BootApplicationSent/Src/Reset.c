#include "../LIBS/STD_TYPES.h"
#include "../LIBS/STMF103C8_MMAP.h"
#include "../Systick/SYSTICK_Interface.h"

#include "Reset.h"

#define NVICKEY 0x05FA0004
// Function to perform a software reset
void SoftwareReset(void) {

	STK_u8StopTimer();
	// Trigger a system reset by writing the key and reset request bit to AIRCR
	SCB->AIRCR = NVICKEY;

	// Wait for the reset to take effect
	while (1)
		;
}
