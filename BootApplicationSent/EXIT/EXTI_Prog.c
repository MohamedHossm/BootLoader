/*****************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 24/7/2023                                                        */
/* Version        : 1.0                                                              */
/*sw              : EXTI                                                             */
/*****************************************************************************/
#include "../LIBS/STD_TYPES.h"
#include "../LIBS/BIT_MATH.h"
#include "../LIBS/STMF103C8_MMAP.h"

#include"EXTI_Pivate.h"
#include"EXTI_Conf.h"
#include"EXTI_Interface.h"

static void (*EXTI_PtrCallBack[EXTI_TOTAL])(void) = {NULLPTR };

Error_t EXTI_u8Setter_IRQ(EXTI_Line_t copy_u8Line, void (*CopyFun)(void)) {
	Error_t local_u8Status = OK;
	if (*CopyFun != NULLPTR) {
		if (copy_u8Line <= EXTI_Line15) {
			EXTI_PtrCallBack[copy_u8Line] = CopyFun;
		} else {
			local_u8Status = NOK;
		}
	} else {
		local_u8Status = NOK;
	}
	return local_u8Status;
}
Error_t EXTI_u8Iint(void) {
	/*
	 #if LINE_0EN
	 SET_BIT(EXTI->EXTI_IMR,EXTI_Line0);
	 #if LINE_0MODE == EXTI_PRE_FAILING
	 SET_BIT(EXTI->EXTI_FTSR,EXTI_Line0);
	 #elif LINE_0MODE == EXTI_PRE_RISING
	 SET_BIT(EXTI->EXTI_RTSR,EXTI_Line0);
	 #elif LINE_0MODE == EXTI_PRE_FAILING_RISING
	 SET_BIT(EXTI->EXTI_FTSR,EXTI_Line0);
	 SET_BIT(EXTI->EXTI_RTSR,EXTI_Line0);
	 #endif // STATE
	 #endif // if LINE_0EN

	 #if LINE_1EN
	 SET_BIT(EXTI->EXTI_IMR,EXTI_Line1);
	 #if STATE == EXTI_PRE_FAILING
	 SET_BIT(EXTI->EXTI_FTSR,EXTI_Line1);
	 #elif STATE == EXTI_PRE_RISING
	 SET_BIT(EXTI->EXTI_RTSR,EXTI_Line1);
	 #elif STATE == EXTI_PRE_FAILING_RISING
	 SET_BIT(EXTI->EXTI_FTSR,EXTI_Line1);
	 SET_BIT(EXTI->EXTI_RTSR,EXTI_Line1);
	 #endif // STATE
	 #endif // if LINE_1EN

	 #if LINE_2EN
	 SET_BIT(EXTI->EXTI_IMR,EXTI_Line2);
	 #if STATE == EXTI_PRE_FAILING
	 SET_BIT(EXTI->EXTI_FTSR,EXTI_Line2);
	 #elif STATE == EXTI_PRE_RISING
	 SET_BIT(EXTI->EXTI_RTSR,EXTI_Line2);
	 #elif STATE == EXTI_PRE_FAILING_RISING
	 SET_BIT(EXTI->EXTI_FTSR,EXTI_Line2);
	 SET_BIT(EXTI->EXTI_RTSR,EXTI_Line2);
	 #endif // STATE
	 #endif // if LINE_2EN

	 #if LINE_3EN
	 SET_BIT(EXTI->EXTI_IMR,EXTI_Line3);
	 #if STATE == EXTI_PRE_FAILING
	 SET_BIT(EXTI->EXTI_FTSR,EXTI_Line3);
	 #elif STATE == EXTI_PRE_RISING
	 SET_BIT(EXTI->EXTI_RTSR,EXTI_Line3);
	 #elif STATE == EXTI_PRE_FAILING_RISING
	 SET_BIT(EXTI->EXTI_FTSR,EXTI_Line3);
	 SET_BIT(EXTI->EXTI_RTSR,EXTI_Line3);
	 #endif // STATE
	 #endif // if LINE_3EN

	 #if LINE_4EN
	 SET_BIT(EXTI->EXTI_IMR,EXTI_Line4);
	 #if STATE == EXTI_PRE_FAILING
	 SET_BIT(EXTI->EXTI_FTSR,EXTI_Line4);
	 #elif STATE == EXTI_PRE_RISING
	 SET_BIT(EXTI->EXTI_RTSR,EXTI_Line4);
	 #elif STATE == EXTI_PRE_FAILING_RISING
	 SET_BIT(EXTI->EXTI_FTSR,EXTI_Line4);
	 SET_BIT(EXTI->EXTI_RTSR,EXTI_Line4);
	 #endif // STATE
	 #endif // if LINE_4EN

	 #if LINE_5EN
	 SET_BIT(EXTI->EXTI_IMR,EXTI_Line5);
	 #if STATE == EXTI_PRE_FAILING
	 SET_BIT(EXTI->EXTI_FTSR,EXTI_Line5);
	 #elif STATE == EXTI_PRE_RISING
	 SET_BIT(EXTI->EXTI_RTSR,EXTI_Line5);
	 #elif STATE == EXTI_PRE_FAILING_RISING
	 SET_BIT(EXTI->EXTI_FTSR,EXTI_Line5);
	 SET_BIT(EXTI->EXTI_RTSR,EXTI_Line5);
	 #endif // STATE
	 #endif // if LINE_5EN

	 #if LINE_6EN
	 SET_BIT(EXTI->EXTI_IMR,EXTI_Line6);
	 #if STATE == EXTI_PRE_FAILING
	 SET_BIT(EXTI->EXTI_FTSR,EXTI_Line6);
	 #elif STATE == EXTI_PRE_RISING
	 SET_BIT(EXTI->EXTI_RTSR,EXTI_Line6);
	 #elif STATE == EXTI_PRE_FAILING_RISING
	 SET_BIT(EXTI->EXTI_FTSR,EXTI_Line6);
	 SET_BIT(EXTI->EXTI_RTSR,EXTI_Line6);
	 #endif // STATE
	 #endif // if LINE_6EN
	 */
	// do nothing
	return OK;
}

Error_t EXTI_u8En(EXTI_Line_t copy_u8Line) {
	Error_t Copy_u8State = OK;
	if (copy_u8Line < EXTI_TOTAL) {
		SET_BIT(EXTI->EXTI_IMR, copy_u8Line);
	} else {
		Copy_u8State = NOK;
	}
	return Copy_u8State;
}

Error_t EXTI_u8Ds(EXTI_Line_t copy_u8Line) {

	Error_t Copy_u8State = OK;
	if (copy_u8Line < EXTI_TOTAL) {
		CLR_BIT(EXTI->EXTI_IMR, copy_u8Line);
	} else {
		Copy_u8State = NOK;
	}
	return Copy_u8State;
}
Error_t EXTI_u8SW_interrupt(EXTI_Line_t copy_u8Line) {
	Error_t Copy_u8State = OK;
	if (copy_u8Line < EXTI_TOTAL) {
		SET_BIT(EXTI->EXTI_SWIER, copy_u8Line);
		EXTI_u8Set_pend(copy_u8Line);
	} else {
		Copy_u8State = NOK;
	}
	return Copy_u8State;
}
Error_t EXTI_u8Set_pend(EXTI_Line_t copy_u8Line) {
	Error_t Copy_u8State = OK;
	if (copy_u8Line < EXTI_TOTAL) {
		CLR_BIT(EXTI->EXTI_PR, copy_u8Line);
	} else {
		Copy_u8State = NOK;
	}
	return Copy_u8State;
}

Error_t EXTI_u8Read_pend(EXTI_Line_t copy_u8Line, u8 *returnData) {
	Error_t Copy_u8State = OK;
	if (copy_u8Line < EXTI_TOTAL) {
		//returnData = READ_BIT(EXTI->EXTI_PR, copy_u8Line);
	} else {
		Copy_u8State = NOK;
	}
	return Copy_u8State;
}
Error_t EXTI_u8CLR_pend(EXTI_Line_t copy_u8Line) {
	Error_t Copy_u8State = OK;
	if (copy_u8Line < EXTI_TOTAL) {
		SET_BIT(EXTI->EXTI_PR, copy_u8Line);
	} else {
		Copy_u8State = NOK;
	}
	return Copy_u8State;
}

Error_t EXTI_u8Set_Inturrupt_latch(EXTI_Line_t copy_u8Line,
		EXTI_MODE_t copy_u8Mode) {
	Error_t Copy_u8State = OK;
	if (copy_u8Line < EXTI_TOTAL) {
		switch (copy_u8Mode) {
		case EXTI_FAILING:
			SET_BIT(EXTI->EXTI_FTSR, copy_u8Line);
			break;
		case EXTI_RISING:
			SET_BIT(EXTI->EXTI_RTSR, copy_u8Line);
			break;
		case EXTI_FAILING_RISING:
			SET_BIT(EXTI->EXTI_RTSR, copy_u8Line);
			SET_BIT(EXTI->EXTI_FTSR, copy_u8Line);
			break;
		default:
			Copy_u8State = NOK;
			break;
		}
	} else {
		Copy_u8State = NOK;
	}
	return Copy_u8State;
}

/******************************************************************/
/******************************************************************/
/******************************************************************/
/******************************************************************/
// IRQS
void EXTI0_IRQHandler(void) /* EXTI Line0 interrupt */
{
	EXTI_PtrCallBack[EXTI_Line0]();
	EXTI_u8CLR_pend(EXTI_Line0);
}
/* EXTI Line1 interrupt                             */
void EXTI1_IRQHandler(void) {
	EXTI_PtrCallBack[EXTI_Line1]();
	EXTI_u8CLR_pend(EXTI_Line1);

}
/* EXTI Line2 interrupt                             */
void EXTI2_IRQHandler(void) {
	EXTI_PtrCallBack[EXTI_Line2]();
	EXTI_u8CLR_pend(EXTI_Line2);

}
/* EXTI Line3 interrupt                             */
void EXTI3_IRQHandler(void) {
	EXTI_PtrCallBack[EXTI_Line3]();
	EXTI_u8CLR_pend(EXTI_Line3);

}
/* EXTI Line4 interrupt                             */
void EXTI4_IRQHandler(void) {
	EXTI_PtrCallBack[EXTI_Line4]();
	EXTI_u8CLR_pend(EXTI_Line4);

}
/* EXTI Line9_5 interrupt */
void EXTI9_5_IRQHandler(void) {
	if (READ_BIT(EXTI->EXTI_PR, EXTI_Line5)) {
		if (EXTI_PtrCallBack[EXTI_Line5] != NULLPTR) {
			EXTI_PtrCallBack[EXTI_Line5]();
			EXTI_u8CLR_pend(EXTI_Line5);

		}
	}
	if (READ_BIT(EXTI->EXTI_PR, EXTI_Line6)) {
		if (EXTI_PtrCallBack[EXTI_Line6] != NULLPTR) {
			EXTI_PtrCallBack[EXTI_Line6]();
			EXTI_u8CLR_pend(EXTI_Line6);

		}
	}
	if (READ_BIT(EXTI->EXTI_PR, EXTI_Line7)) {
		if (EXTI_PtrCallBack[EXTI_Line7] != NULLPTR) {
			EXTI_PtrCallBack[EXTI_Line7]();
			EXTI_u8CLR_pend(EXTI_Line7);

		}
	}
	if (READ_BIT(EXTI->EXTI_PR, EXTI_Line8)) {
		if (EXTI_PtrCallBack[EXTI_Line8] != NULLPTR) {
			EXTI_PtrCallBack[EXTI_Line8]();
			EXTI_u8CLR_pend(EXTI_Line8);

		}
	}
	if (READ_BIT(EXTI->EXTI_PR, EXTI_Line9)) {
		if (EXTI_PtrCallBack[EXTI_Line9] != NULLPTR) {
			EXTI_PtrCallBack[EXTI_Line9]();
			EXTI_u8CLR_pend(EXTI_Line9);

		}
	}
}

/* EXTI Line15_10 interrupt */
void EXTI15_10_IRQHandler(void) {
	if (READ_BIT(EXTI->EXTI_PR, EXTI_Line10)) {
		if (EXTI_PtrCallBack[EXTI_Line10] != NULLPTR) {
			EXTI_PtrCallBack[EXTI_Line10]();
			EXTI_u8CLR_pend(EXTI_Line10);
		}
	}
	if (READ_BIT(EXTI->EXTI_PR, EXTI_Line11)) {
		if (EXTI_PtrCallBack[EXTI_Line11] != NULLPTR) {
			EXTI_PtrCallBack[EXTI_Line11]();
			EXTI_u8CLR_pend(EXTI_Line11);
		}
	}
	if (READ_BIT(EXTI->EXTI_PR, EXTI_Line12)) {
		if (EXTI_PtrCallBack[EXTI_Line12] != NULLPTR) {
			EXTI_PtrCallBack[EXTI_Line12]();
			EXTI_u8CLR_pend(EXTI_Line12);
		}
	}
	if (READ_BIT(EXTI->EXTI_PR, EXTI_Line13)) {
		if (EXTI_PtrCallBack[EXTI_Line13] != NULLPTR) {
			EXTI_PtrCallBack[EXTI_Line13]();
			EXTI_u8CLR_pend(EXTI_Line13);
		}
	}
	if (READ_BIT(EXTI->EXTI_PR, EXTI_Line14)) {
		if (EXTI_PtrCallBack[EXTI_Line14] != NULLPTR) {
			EXTI_PtrCallBack[EXTI_Line14]();
			EXTI_u8CLR_pend(EXTI_Line14);
		}
	}
	if (READ_BIT(EXTI->EXTI_PR, EXTI_Line15)) {
		if (EXTI_PtrCallBack[EXTI_Line15] != NULLPTR) {
			EXTI_PtrCallBack[EXTI_Line15]();
			EXTI_u8CLR_pend(EXTI_Line15);
		}
	}
}
/******************************************************************/
