/*****************************************************************************/
/* Auther          : Mohamed Hoasm                                                    */
/* Date            : 25/7/2023                                                        */
/* Version         : 1.0                                                              */
/* SW              : SYSTICK                                                             */
/*****************************************************************************/
#include "../LIBS/STD_TYPES.h"
#include "../LIBS/BIT_MATH.h"
#include "../LIBS/STMF103C8_MMAP.h"

#include"SYSTICK_Conf.h"
#include"SYSTICK_Pivate.h"
#include"SYSTICK_Interface.h"

static void (*STK_PtrCallBack)(void) = {NULLPTR };
static u8 STK_CHAECK_PERODIC = 0;
static u8 STK_ProtectionFlage = 0;
Error_t STK_u8Init() {

// Enable ISR
#if STK_SOURCE == STK_u8AHB
	SET_BIT(SYSTICK->STK_CTRL ,2);
	#elif STK_SOURCE == STK_u8AHB_8
	CLR_BIT(SYSTICK->STK_CTRL, 2);
#else
	 CLR_BIT(SYSTICK->STK_CTRL ,2);
     #warning"define STK_SOURCE "
	#endif 
	// enable STK
	//SET_BIT(SYSTICK->STK_CTRL, 0);
	// Enable CR source
	return OK;
}
Error_t STK_u8SetBusyWait(u32 Copy_time_MS) {
	Error_t local_u8status = OK;
	// disable inturrupt
	STK_u8DSInterrupt();
	// set loud
	//STK_u8StopTimer();
	Copy_time_MS = Copy_time_MS * 1000;
	if (Copy_time_MS < STK_MAXVALUE) {
		SYSTICK->STK_LOAD = Copy_time_MS;
		SET_BIT(SYSTICK->STK_CTRL, 0);
	} else {
		local_u8status = NOK;
	}
	// W8 counter flage
	while (!READ_BIT(SYSTICK->STK_CTRL, 16)) {
		// do noting
	}
	// stop timer
	STK_u8StopTimer();
	// return
	return local_u8status;

}
Error_t STK_u8SetIntervalSingleOV(u32 Copy_time_MS, void (*STK_FunISR)(void)) {
	Error_t local_u8status = NOK;
	local_u8status = OK;
	STK_ProtectionFlage = 1;
	STK_u8StopTimer();
	// enable inturrupt

	// forward function to isr -- clear load and
	STK_CHAECK_PERODIC = 1;
	if (STK_FunISR != NULLPTR) {
		STK_u8SetCallBack(STK_FunISR);
	} else {
		local_u8status = NOK;
	}
	// set loud
	if (Copy_time_MS < STK_MAXVALUE) {
		SYSTICK->STK_LOAD = Copy_time_MS;
		STK_u8StartTimer();
	} else {
		local_u8status = NOK;

	}
	// return
	return local_u8status;
}
Error_t STK_u8SetIntervalSingle(u32 Copy_time_MS, void (*STK_FunISR)(void)) {
	Error_t local_u8status = NOK;
	if (STK_ProtectionFlage == 0) {
		local_u8status = OK;
		STK_ProtectionFlage = 1;
		// enable inturrupt
		//STK_u8ENInterrupt();
		// forward function to isr -- clear load and
		STK_CHAECK_PERODIC = 1;
		if (STK_FunISR != NULLPTR) {
			STK_u8SetCallBack(STK_FunISR);
		} else {
			local_u8status = NOK;
		}
		// set loud
		if (Copy_time_MS < STK_MAXVALUE) {
			SYSTICK->STK_LOAD = Copy_time_MS;
			STK_u8StartTimer();
		} else {
			local_u8status = NOK;
		}
	}
	// return
	return local_u8status;
}

Error_t STK_u8SetIntervalPeriodic(u32 Copy_time_MS, void (*STK_FunISR)(void)) {
	Error_t local_u8status = OK;

	// forward function to isr --
	if (*STK_FunISR != NULLPTR) {
		STK_u8SetCallBack(STK_FunISR);
	} else {
		local_u8status = NOK;
	}
	// set loud
	if (Copy_time_MS < STK_MAXVALUE) {
		SYSTICK->STK_LOAD = Copy_time_MS;
		STK_u8StartTimer();

	} else {
		local_u8status = NOK;
	}

	// return
	return local_u8status;
}
Error_t STK_u8StopTimer() {
	// set loud and value with zeroxs
	Error_t local_u8status = OK;
	CLR_BIT(SYSTICK->STK_CTRL, 0);
	SYSTICK->STK_LOAD = 0;
	SYSTICK->STK_VAL = 0;
	STK_u8DSInterrupt();

	return local_u8status;
}
Error_t STK_u8StartTimer() {
	// set loud and value with zeroxs
	Error_t local_u8status = OK;
	STK_u8ENInterrupt();
	SET_BIT(SYSTICK->STK_CTRL, 0);
	return local_u8status;
}
Error_t STK_u8SpentTimer(u32 *Ptr_SpentTime) {
	// diffrence between load and value
	Error_t local_u8status = OK;
	*Ptr_SpentTime = ((SYSTICK->STK_LOAD) - (SYSTICK->STK_VAL));
	return local_u8status;
}

Error_t STK_u8GetRemining(u32 *Ptr_Remind) {
	// return valuereg value
	Error_t local_u8status = OK;
	*Ptr_Remind = SYSTICK->STK_VAL;
	return local_u8status;

}
Error_t STK_u8ENInterrupt() {
	SET_BIT(SYSTICK->STK_CTRL, 1);
	return OK;

}
Error_t STK_u8DSInterrupt() {
	CLR_BIT(SYSTICK->STK_CTRL, 1);
	return OK;
}
Error_t STK_u8SetCallBack(void (*FunPtr)(void)) {
	Error_t local_u8status = OK;
	if (*FunPtr != NULLPTR) {
		STK_PtrCallBack = FunPtr;
	} else {
		local_u8status = NOK;
	}
	return local_u8status;
}
void SysTick_Handler() {

	if (STK_CHAECK_PERODIC == 1) {
		STK_u8StopTimer();
		STK_CHAECK_PERODIC = 0;
		STK_ProtectionFlage = 0;
	} else {
		// do nothing
	}
	STK_PtrCallBack();

}
