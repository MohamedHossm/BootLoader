/*****************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 13/7/2023                                                        */
/* Version        : 1.0                                                              */
/*sw              : NVIC                                                             */
/*****************************************************************************/
#include "../LIBS/STD_TYPES.h"
#include "../LIBS/BIT_MATH.h"
#include "../LIBS/STMF103C8_MMAP.h"

#include"NVIC_Conf.h"
#include"NVIC_Pivate.h"
#include"NVIC_Interface.h"

Error_t NVIC_u8Set_PR_options() {

	SCB->AIRCR = NVIC_PR_OPTIONS;

	return OK;
}

Error_t NVIC_u8Set_EN_IRQ(NVIC_Prority_t Copy_IRQ_ID) {
	Error_t Copy_status = OK;
	u8 Copy_ID_Index = Copy_IRQ_ID / NVIC_REG_SIZE;
	if (Copy_IRQ_ID < INTERRUPT_TOTAL) {
		Copy_IRQ_ID = Copy_IRQ_ID % NVIC_REG_SIZE;
		NVIC->NVIC_ISER[Copy_ID_Index] = 1 << Copy_IRQ_ID;
	} else {
		Copy_status = NOK;
	}
	return Copy_status;
}
Error_t NVIC_u8Clr_EN_IRQ(NVIC_Prority_t Copy_IRQ_ID) {
	Error_t Copy_status = OK;
	u8 Copy_ID_Index = Copy_IRQ_ID / NVIC_REG_SIZE;
	if (Copy_IRQ_ID < INTERRUPT_TOTAL) {
		Copy_IRQ_ID = Copy_IRQ_ID % NVIC_REG_SIZE;
		NVIC->NVIC_ICER[Copy_ID_Index] = 1 << Copy_IRQ_ID;
	} else {
		Copy_status = NOK;
	}
	return Copy_status;
}
Error_t NVIC_u8Set_Pend_IRQ(NVIC_Prority_t Copy_IRQ_ID) {
	Error_t Copy_status = OK;
	u8 Copy_ID_Index = Copy_IRQ_ID / NVIC_REG_SIZE;
	if (Copy_IRQ_ID < INTERRUPT_TOTAL) {
		Copy_IRQ_ID = Copy_IRQ_ID % NVIC_REG_SIZE;
		NVIC->NVIC_ISPR[Copy_ID_Index] = (1 << Copy_IRQ_ID);
	} else {
		Copy_status = NOK;
	}
	return Copy_status;
}
Error_t NVIC_u8Clr_Pend_IRQ(NVIC_Prority_t Copy_IRQ_ID) {
	Error_t Copy_status = OK;
	u8 Copy_ID_Index = Copy_IRQ_ID / NVIC_REG_SIZE;
	if (Copy_IRQ_ID < INTERRUPT_TOTAL) {
		Copy_IRQ_ID = Copy_IRQ_ID % NVIC_REG_SIZE;
		NVIC->NVIC_ICPR[Copy_ID_Index] = (1 << Copy_IRQ_ID);
	} else {
		Copy_status = NOK;
	}
	return Copy_status;
}
Error_t NVIC_u8Get_Active_IRQ(NVIC_Prority_t Copy_IRQ_ID, u8 *PtrActive_Value) {
	Error_t Copy_status = OK;
	u8 Copy_ID_Index = Copy_IRQ_ID / NVIC_REG_SIZE;
	if (Copy_IRQ_ID < INTERRUPT_TOTAL) {
		Copy_IRQ_ID = Copy_IRQ_ID % NVIC_REG_SIZE;
		*PtrActive_Value = READ_BIT(NVIC->NVIC_IABR[Copy_ID_Index],
				Copy_IRQ_ID);
	} else {
		Copy_status = NOK;
	}
	return Copy_status;
}
Error_t NVIC_u8Set_PR_Value(NVIC_Prority_t Copy_IRQ_ID, u8 Copy_Periority_G_ID,
		u8 Copy_Periority_SUB_ID) {

	Error_t local_u8status = OK;

#if NVIC_PR_OPTIONS == SCB_G_16_SUP_NONE
	u8 local_u8G_Mask  		 = 0x0f;
	u8 local_u8SUB_Mask 	 = 0x00;
	u8 local_8uSUB_Offsit    = 0   ;

#elif NVIC_PR_OPTIONS == SCB_G_8_SUP_4
	u8 local_u8G_Mask  		 = 0x08;
	u8 local_u8SUB_Mask 	 = 0x01;
    u8 local_8uSUB_Offsit    = 1   ;

#elif NVIC_PR_OPTIONS == SCB_G_4_SUP_4
	u8 local_u8G_Mask  		 = 0x03;
	u8 local_u8SUB_Mask 	 = 0x03;
    u8 local_8uSUB_Offsit    = 2   ;

#elif NVIC_PR_OPTIONS == SCB_G_2_SUP_8
    u8 local_u8G_Mask  		 = 0x01;
    u8 local_u8SUB_Mask 	 = 0x03;
    u8 local_8uSUB_Offsit    = 3   ;
#elif NVIC_PR_OPTIONS == SCB_G_NONE_SUP_16
	u8 local_u8G_Mask        = 0x00;
	u8 local_u8SUB_Mask      = 0x0f;
	u8 local_8uSUB_Offsit    = 4;
#endif

	u8 local_u8Periority;
	if (Copy_IRQ_ID < INTERRUPT_TOTAL) {
		local_u8Periority = (((Copy_Periority_G_ID & local_u8G_Mask)
				<< local_8uSUB_Offsit)
				| (Copy_Periority_SUB_ID & local_u8SUB_Mask)) & 0b00001111;
		local_u8Periority <<= 4 ;
		NVIC->NVIC_IPR[Copy_IRQ_ID] = local_u8Periority;
	} else {
		local_u8status = NOK;
	}
	return local_u8status;
}
