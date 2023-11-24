
/*****************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 13/7/2023                                                        */
/* Version        : 1.0                                                              */
/*sw              : RCC                                                             */
/*****************************************************************************/




#ifndef _RCC_INT_H
#define _RCC_INT_H


typedef enum
{
	/*****AHB********/
	AHB_DMA1EN=	100,
	AHB_DMA2EN=	101,
	AHB_SRAMEN=	102,
	AHB_FLITFEN=104,
	AHB_CRCEN=	106,
	AHB_FSMCEN=	108,
	AHB_SDIOEN=	110,
	/*****APB1********/
	APB2_AFIOEN  =	200,
	APB2_IOPAEN  =	202,
	APB2_IOPBEN  =	203,
	APB2_IOPCEN  =	204,
	APB2_IOPDEN  =	205,
	APB2_IOPEEN  =	206,
	APB2_IOPFEN  =	207,
	APB2_IOPGEN  =	208,
	APB2_ADC1EN  =	209,
	APB2_ADC2EN  =	210,
	APB2_TIM1EN  =	211,
	APB2_SPI1EN  =	212,
	APB2_TIM8EN  =	213,
	APB2_USART1EN=	214,
	APB2_ADC3EN  =	215,
	APB2_TIM9EN  =	219,
	APB2_TIM10EN =	220,
	APB2_TIM11EN =	221,
	/*****APB2********/
	APB1_TIM2EN =	300,
	APB1_TIM3EN =	301,
	APB1_TIM4EN =	302,
	APB1_TIM5EN =	303,
	APB1_TIM6EN =	304,
	APB1_TIM7EN =	305,
	APB1_TIM12EN=	306,
	APB1_TIM13EN=	307,
	APB1_TIM14EN=	308,
	APB1_WWDGEN =	311,
	APB1_SPI2EN =	314,
	APB1_SPI3EN =	315,
	APB1_USART2EN=	317,
	APB1_USART3EN=	318,
	APB1_UART4EN=	319,
	APB1_UART5EN =	320,
	APB1_I2C1EN  =	321,
	APB1_I2C2EN =	322,
	APB1_USBEN =	323,
	APB1_CANEN =	325,
	APB1_BKPEN =	327,
	APB1_PWREN =	328,
	APB1_DACEN =	329


}PeriphralBusId_t;

typedef enum {
	RCC_ADC_CLK_D_2 =0 ,
	RCC_ADC_CLK_D_4 ,
	RCC_ADC_CLK_D_6,
	RCC_ADC_CLK_D_8
}RCC_ADC_PRESCALER ;

#define RCC_u8AHB  1
#define RCC_u8APB2 2
#define RCC_u8APB1 3

#define  RCC_ADC_LOCATION 15

Error_t RCC_vSetADC_CLK(RCC_ADC_PRESCALER Copy_u8ADCSelectionOption);

void RCC_voidInitSystemClock(void);
Error_t RCC_voidEnablePeriphralCLK(PeriphralBusId_t Copy_enPeriphralId);
Error_t RCC_voidDisablePeriphralCLK(PeriphralBusId_t Copy_enPeriphralId);

#endif /* _RCC_INT_H */
