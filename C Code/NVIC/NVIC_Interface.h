/*****************************************************************************/
/* Auther         : Mohamed Hoasm                                                   */
/* Date           : 13/7/2023                                                       */
/* Version        : 1.0                                                             */
/* SW             : NVIC                                                             */
/*****************************************************************************/
typedef enum {
	/*
	INTERRUPT_NMI = -2,
	INTERRUPT_HARD_FAULT,
	INTERRUPT_MEM_MANAGE,
	INTERRUPT_BUS_FAULT,
	INTERRUPT_USAGE_FAULT,
	INTERRUPT_SVC,
	INTERRUPT_DEBUG,
	INTERRUPT_PENDSV,
	INTERRUPT_SYSTICK,
	*/
	INTERRUPT_WWDG = 0,
	INTERRUPT_PVD,
	INTERRUPT_TAMPER,
	INTERRUPT_RTC,
	INTERRUPT_FLASH,
	INTERRUPT_RCC,
	INTERRUPT_EXTI0,
	INTERRUPT_EXTI1,
	INTERRUPT_EXTI2,
	INTERRUPT_EXTI3,        // EXTI Line3 interrupt
	INTERRUPT_EXTI4,       // EXTI Line4 interrupt
	INTERRUPT_DMA1_CHANNEL1, // DMA1 Channel 1 global interrupt
	INTERRUPT_DMA1_CHANNEL2, // DMA1 Channel 2 global interrupt
	INTERRUPT_DMA1_CHANNEL3, // DMA1 Channel 3 global interrupt
	INTERRUPT_DMA1_CHANNEL4, // DMA1 Channel 4 global interrupt
	INTERRUPT_DMA1_CHANNEL5, // DMA1 Channel 5 global interrupt
	INTERRUPT_DMA1_CHANNEL6, // DMA1 Channel 6 global interrupt
	INTERRUPT_DMA1_CHANNEL7, // DMA1 Channel 7 global interrupt
	INTERRUPT_ADC1_2,      // ADC1 and ADC2 global interrupt
	INTERRUPT_USB_HP_CAN_TX, // USB High priority/CAN TX interrupt
	INTERRUPT_USB_LP_CAN_RX0, // USB Low priority/CAN RX0 interrupt
	INTERRUPT_CAN_RX1,     // CAN RX1 interrupt
	INTERRUPT_CAN_SCE,     // CAN SCE interrupt
	INTERRUPT_EXTI9_5,     // EXTI Line[9:5] interrupts
	INTERRUPT_TIM1_BRK,    // TIM1 Break interrupt
	INTERRUPT_TIM1_UP,     // TIM1 Update interrupt
	INTERRUPT_TIM1_TRG_COM, // TIM1 Trigger and Commutation interrupts
	INTERRUPT_TIM1_CC,     // TIM1 Capture Compare interrupt
	INTERRUPT_TIM2,        // TIM2 global interrupt
	INTERRUPT_TIM3,        // TIM3 global interrupt
	INTERRUPT_TIM4,        // TIM4 global interrupt
	INTERRUPT_I2C1_EV,     // I2C1 event interrupt
	INTERRUPT_I2C1_ER,     // I2C1 error interrupt
	INTERRUPT_I2C2_EV,     // I2C2 event interrupt
	INTERRUPT_I2C2_ER,     // I2C2 error interrupt
	INTERRUPT_SPI1,        // SPI1 global interrupt
	INTERRUPT_SPI2,        // SPI2 global interrupt
	INTERRUPT_USART1,      // USART1 global interrupt
	INTERRUPT_USART2,      // USART2 global interrupt
	INTERRUPT_USART3,      // USART3 global interrupt
	INTERRUPT_EXTI15_10,   // EXTI Line[15:10] interrupts
	INTERRUPT_RTC_ALARM,   // RTC alarm through EXTI line interrupt
	INTERRUPT_USB_WAKEUP, // USB wakeup from suspend through EXTI line interrupt
	INTERRUPT_TIM8_BRK,
	INTERRUPT_TIM8_UP,
	INTERRUPT_TIM8_TRG_COM,
	INTERRUPT_TIM8_CC,
	INTERRUPT_ADC3,
	INTERRUPT_FSMC,
	INTERRUPT_SDIO,
	INTERRUPT_TIM5,
	INTERRUPT_SPI3,
	INTERRUPT_UART4,
	INTERRUPT_UART5,
	INTERRUPT_TIM6,
	INTERRUPT_TIM7,
	INTERRUPT_DMA2_Channel1,
	INTERRUPT_DMA2_Channel2,
	INTERRUPT_DMA2_Channel3,
	INTERRUPT_DMA2_Channel5,
	INTERRUPT_TOTAL
} NVIC_Prority_t;

#define NVIC_REG_SIZE 32
//**********************************************************
Error_t NVIC_u8Set_PR_options();

Error_t NVIC_u8Set_EN_IRQ(NVIC_Prority_t Copy_IRQ_ID);
Error_t NVIC_u8Clr_EN_IRQ(NVIC_Prority_t Copy_IRQ_ID);

Error_t NVIC_u8Set_Pend_IRQ(NVIC_Prority_t Copy_IRQ_ID);
Error_t NVIC_u8Clr_Pend_IRQ(NVIC_Prority_t Copy_IRQ_ID);

Error_t NVIC_u8Get_Active_IRQ(NVIC_Prority_t Copy_IRQ_ID, u8* PtrActive_Value);

Error_t NVIC_u8Set_PR_Value(NVIC_Prority_t Copy_IRQ_ID ,
		                    u8 Copy_Periority_G_ID ,u8 Copy_Periority_SUB_ID );





