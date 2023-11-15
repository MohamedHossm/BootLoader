/*************************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 15/10/2023                                                       */
/* Version        : 1.0                                                              */
/*sw              : FLASH                                                            */
/*************************************************************************************/

#include "../LIBS/STD_TYPES.h"
#include "../LIBS/BIT_MATH.h"
#include "../LIBS/STMF103C8_MMAP.h"

#include "FLASH_Private.h"
#include "FLASH_Conf.h"
#include "FLASH_Interface.h"

FLASH_enERR_T FLASH_enCalculatePages(u32 Copy_Address, u16 *Ptr_u16ReturnData) {
	FLASH_enERR_T Local_state = FLASH_OK;

	s64 Local_calculatedData = Copy_Address - FLASH_START;

	Local_calculatedData = Local_calculatedData / FLASH_PAGE;

	if (Local_calculatedData < 0) {
		Local_state = FLASH_ERR;
	} else {
		*Ptr_u16ReturnData = Local_calculatedData;
	}

	return Local_state;
}
FLASH_enERR_T FLASH_enWaitClr() {
	FLASH_enERR_T Local_state = FLASH_OK;
	while (READ_BIT(FLASH->FLASH_SR, SR_BSY))
		; // Wait while the flash is busy
	if (READ_BIT(FLASH->FLASH_SR, SR_EOP)) // Check if End of Operation flag is set
		SET_BIT(FLASH->FLASH_SR, SR_EOP);    // Clear the flag
	if (READ_BIT(FLASH->FLASH_SR, SR_PGERR)) // Check for programming error
		SET_BIT(FLASH->FLASH_SR, SR_PGERR);       // Clear the flag
	if (READ_BIT(FLASH->FLASH_SR, SR_WRPRTERR)) // Check for write protection error
		SET_BIT(FLASH->FLASH_SR, SR_WRPRTERR);  // Clear the flag

	return Local_state;
}
FLASH_enERR_T FLASH_enErasePage(u8 Copy_u8page) {

	FLASH_enERR_T Local_state = FLASH_OK;

	u32 local_u32PageAddress = FLASH_START + (Copy_u8page * FLASH_PAGE);
	if (local_u32PageAddress < FLASH_END) {
		FLASH_enUnlock();
		SET_BIT(FLASH->FLASH_CR, CR_PER);           // set page erase
		FLASH->FLASH_AR = local_u32PageAddress;   //select page add
		SET_BIT(FLASH->FLASH_CR, CR_STRT);          // Start

		FLASH_enWaitClr();                                 //wait and clr
		CLR_BIT(FLASH->FLASH_CR, CR_PER);           // clr page erase
		FLASH_enlock();
	} else {
		//do nothing
	}
	return Local_state;
}

FLASH_enERR_T FLASH_enWriteData(u32 ptrAddress, u16 Copy_u8Data) {

	FLASH_enERR_T Local_state = FLASH_OK;
	Local_state = FLASH_enUnlock();

	if (*(volatile u32*) ptrAddress != 0xffffffff) {

		Local_state = FLASH_WRITTEN;
	} else {
		FLASH_enWaitClr();         // wait and clr
		if (Local_state == FLASH_OK) {
			Local_state = FlASH_enEnablePrograming();

		} else {
			//do nothing
		}
		//Write Data on flash location
		//check on location
		if ((ptrAddress) > FLASH_START && (ptrAddress) < FLASH_END
				&& Local_state == FLASH_OK) {
			*(volatile u16*) ptrAddress = Copy_u8Data;

		} else {

			//out of range
			Local_state = FLASH_OUTOFRANGE;
		}

		FLASH_enWaitClr();         // wait and clr

		FlASH_enDisablePrograming();
	}

	return Local_state;

}
FLASH_enERR_T FLASH_enWriteArray(u32 ptrAddress, u32 Copy_Size, u16 *Arr_u8Data) {

	FLASH_enERR_T Local_state = FLASH_OK;
	Local_state = FLASH_enUnlock();
	FLASH_enWaitClr();         // wait and clr
	if (Local_state == FLASH_OK) {
		Local_state = FlASH_enEnablePrograming();

	} else {
		//do nothing
	}

	// wright seq on flash
	for (u32 Local_Index = 0; Local_Index < Copy_Size; Local_Index++) {

		if ((ptrAddress + (Local_Index * FLASH_WORD)) > FLASH_START
				&& (ptrAddress + (Local_Index * FLASH_WORD)) < FLASH_END
				&& Local_state == FLASH_OK) {

			if (*(volatile u32*) (ptrAddress + (Local_Index * FLASH_WORD))
					!= 0xffffffff) {

				Local_state = FLASH_WRITTEN;
				break;
			} else {
				*(volatile u16*) (ptrAddress + (Local_Index * FLASH_WORD)) =
						Arr_u8Data[Local_Index];
			}

		} else {

			//out of range
			Local_state = FLASH_OUTOFRANGE;
			break;
		}
		FLASH_enWaitClr();         // wait and clr

	}
	FlASH_enDisablePrograming(); // close prog session

	return Local_state;
}

// enable flash programming by set PG bit
FLASH_enERR_T FlASH_enEnablePrograming() {
	FLASH_enERR_T Local_state = FLASH_OK;
	SET_BIT(FLASH->FLASH_CR, CR_PG);
	return Local_state;
}

// disable flash programming by set PG bit
FLASH_enERR_T FlASH_enDisablePrograming() {
	FLASH_enERR_T Local_state = FLASH_OK;
	CLR_BIT(FLASH->FLASH_CR, CR_PG);
	return Local_state;
}

FLASH_enERR_T FLASH_enUnlock() {
	FLASH_enERR_T Local_state = FLASH_OK;
	u8 local_FlashLockStatus = READ_BIT(FLASH->FLASH_CR, CR_LOCK);
	if (local_FlashLockStatus == 1) // flash is locked
			{
		// unlock sequance
		FLASH->FLASH_KEYR = FLASH_KEY1;
		FLASH->FLASH_KEYR = FLASH_KEY2;

	} else {
		//dp noting
	}
	 local_FlashLockStatus = READ_BIT(FLASH->FLASH_CR, CR_LOCK);

	if (local_FlashLockStatus == 1) {

		Local_state = FLASH_UNLOCKERR;
	} else {

		Local_state = FLASH_OK;

	}
	return Local_state;
}

FLASH_enERR_T FLASH_enlock() {
	FLASH_enERR_T Local_state = FLASH_OK;

	SET_BIT(FLASH->FLASH_CR, CR_LOCK); // lock flash

	return Local_state;
}
