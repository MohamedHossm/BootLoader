/*****************************************************************************/
/* Author         : Mohamed Hoasm                                                    */
/* Date           : 13/7/2023                                                        */
/* Version        : 1.0                                                              */
/*sw              : GPIO                                                             */
/*****************************************************************************/
#include "../LIBS/STD_TYPES.h"
#include "GPIO_Interface.h"
#include "GPIO_CONF.h"

const   GPIO_Conf_t  GPIO_Conf_ARR [PINTOTAL] ={

		{Pin_A0      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_A1      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_A2      ,GPIO_u8OUT_AF_PP_10MHZ }, //tx1
		{Pin_A3      ,GPIO_u8OUT_AF_PP_10MHZ }, // rx1
		{Pin_A4      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_A5      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_A6      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_A7      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_A8      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_A9      ,GPIO_u8OUT_AF_PP_10MHZ }, // tx 1
		{Pin_A10     ,GPIO_u8INPUT_FLOATING }, // RX 1
		{Pin_A11     ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_A12     ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_A13     ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_A14     ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_A15     ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_B0      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_B1      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_B2      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_B3      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_B4      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_B5      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_B6      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_B7      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_B8      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_B9      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_B10     ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_B11     ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_B12     ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_B13     ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_B14     ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_B15     ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_C0      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_C1      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_C2      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_C3      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_C4      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_C5      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_C6      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_C7      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_C8      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_C9      ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_C10     ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_C11     ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_C12     ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_C13     ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_C14     ,GPIO_u8OUT_PUSH_PULL_2MHZ },
		{Pin_C15     ,GPIO_u8OUT_PUSH_PULL_2MHZ }

} ;

