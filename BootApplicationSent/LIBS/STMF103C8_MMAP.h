#ifndef _STMF103C8_MMAP_H_
#define _STMF103C8_MMAP_H_
/*********************************************************/
/*******************RCC Registers************************/
/*********************************************************/
#define RCC_u32BASE_ADDRESS 0x40021000
typedef struct {
	u32 RCC_CR;
	u32 RCC_CFGR;
	u32 RCC_CIR;
	u32 RCC_APB2RSTR;
	u32 RCC_APB1RSTR;
	u32 RCC_AHBENR;
	u32 RCC_APB2ENR;
	u32 RCC_APB1ENR;
	u32 RCC_BDCR;
	u32 RCC_CSR;

} RCC_REG_DEF_t;

#define RCC ((RCC_REG_DEF_t*)RCC_u32BASE_ADDRESS)

/*********************************************************/
/*******************GPIO Registers************************/
/*********************************************************/
#define GPIO_C_u32BASE_ADDRESS 0x40011000
#define GPIO_B_u32BASE_ADDRESS 0x40010C00
#define GPIO_A_u32BASE_ADDRESS 0x40010800

typedef struct {
	u32 GPIO_CRL;
	u32 GPIO_CRH;
	u32 GPIO_IDR;
	u32 GPIO_ODR;
	u32 GPIO_BSRR;
	u32 GPIO_BRR;
	u32 GPIO_LCKR;

} GPIO_REG_DEF_t;

#define GPIO_C ((GPIO_REG_DEF_t*)GPIO_C_u32BASE_ADDRESS)
#define GPIO_B ((GPIO_REG_DEF_t*)GPIO_B_u32BASE_ADDRESS)
#define GPIO_A ((GPIO_REG_DEF_t*)GPIO_A_u32BASE_ADDRESS)
/*********************************************************/
/*******************NVIC Registers************************/
/*********************************************************/
#define NVIC_u32BASE_ADDRESS 0xE000E100
#define NVIC_res 29
#define NVIC_RES2 61
#define NCIC_NVIC_IPR_SIZE 84
#define NVIC_SIZE 3
typedef struct {
	u32 NVIC_ISER[NVIC_SIZE];
	u32 NVIC_ISER_RES[NVIC_res];

	u32 NVIC_ICER[NVIC_SIZE];
	u32 NVIC_ICER_RES[NVIC_res];

	u32 NVIC_ISPR[NVIC_SIZE];
	u32 NVIC_ISPR_RES[NVIC_res];

	u32 NVIC_ICPR[NVIC_SIZE];
	u32 NVIC_ICPR_RES[NVIC_res];

	u32 NVIC_IABR[NVIC_SIZE];
	u32 NVIC_IABR_RES[NVIC_RES2];
	volatile u8 NVIC_IPR[NCIC_NVIC_IPR_SIZE];
} NVIC_REG_DEF_t;

#define NVIC ((NVIC_REG_DEF_t*)NVIC_u32BASE_ADDRESS)
/*********************************************************/
/*******************SYS Registers************************/
/*********************************************************/
// Define the SCB (System Control Block) structure for STM32
typedef struct {
    volatile u32 CPUID;         // CPUID Base Register
    volatile u32 ICSR;          // Interrupt Control and State Register
    volatile u32 VTOR;          // Vector Table Offset Register
    volatile u32 AIRCR;         // Application Interrupt and Reset Control Register
    volatile u32 SCR;           // System Control Register
    volatile u32 CCR;           // Configuration and Control Register
    volatile u8  SHP[12];       // System Handler Priority Registers
    volatile u32 SHCSR;         // System Handler Control and State Register
    volatile u32 CFSR;          // Configurable Fault Status Register
    volatile u32 HFSR;          // HardFault Status Register
    volatile u32 DFSR;          // Debug Fault Status Register
    volatile u32 MMFAR;         // MemManage Fault Address Register
    volatile u32 BFAR;          // BusFault Address Register
    volatile u32 AFSR;          // Auxiliary Fault Status Register
    volatile u32 PFR[2];        // Processor Feature Register
    volatile u32 DFR;           // Debug Feature Register
    volatile u32 ADR;           // Auxiliary Feature Register
    volatile u32 MMFR[4];       // Memory Model Feature Register
    volatile u32 ISAR[5];       // Instruction Set Attribute Register
    volatile u32 CLIDR;         // Cache Level ID Register
    volatile u32 CTR;           // Cache Type Register
    volatile u32 CCSIDR;        // Cache Size ID Register
    volatile u32 CSSELR;        // Cache Size Selection Register
} SCB_Type;

// Define a pointer to the SCB structure
#define SCB ((SCB_Type *)0xE000ED00)


/*********************************************************/
/*******************EXTI Registers************************/
/*********************************************************/

#define EXTI_u32BASE_ADDRESS  0x40010400

typedef struct {
	u32 EXTI_IMR;
	u32 EXTI_EMR;
	u32 EXTI_RTSR;
	u32 EXTI_FTSR;
	u32 EXTI_SWIER;
	u32 EXTI_PR;

} EXTI_REG_DEF_t;

#define EXTI ((EXTI_REG_DEF_t*)EXTI_u32BASE_ADDRESS)

/*********************************************************/
/*******************AFIO Registers************************/
/*********************************************************/
#define AFIO_u32BASE_ADDRESS  0x40010000
#define AFIO_EXTICRSIZE 4
typedef struct {
	u32 AFIO_EVCR;
	u32 AFIO_MAPR;
	u32 AFIO_EXTICR[AFIO_EXTICRSIZE];
	u32 AFIO_MAPR2;
} AFIO_REG_DEF_t;

#define AFIO ((AFIO_REG_DEF_t*)AFIO_u32BASE_ADDRESS)

/*************************************************************/
/*******************SYSTICK Registers*************************/
/*************************************************************/

#define SYSTICK_u32BASE_ADDRESS  0xE000E010

typedef struct {
	volatile u32 STK_CTRL;
	volatile u32 STK_LOAD;
	volatile u32 STK_VAL;
	volatile u32 STK_CALIB;
} SYSTICK_REG_DEF_t;

#define SYSTICK ((SYSTICK_REG_DEF_t*)SYSTICK_u32BASE_ADDRESS)
/*************************************************************/
/*******************DMA Registers*************************/
/*************************************************************/

#define DMA_u32BASE_ADDRESS  0x40020000
#define DMA_CONF_SIZE 7
/*
 typedef struct {

 volatile u32 DMA_ISR ;
 volatile u32 DMA_IFCR ;
 //--------------------1------------------------
 volatile u32 DMA_CCR1;
 volatile u32 DMA_CNDTR1;
 volatile u32 DMA_CPAR1;
 volatile u32 DMA_CMAR1 ;
 volatile u32 RESEVED1 ;
 //---------------------2-----------------------
 volatile u32 DMA_CCR2 ;
 volatile u32 DMA_CNDTR2 ;
 volatile u32 DMA_CPAR2 ;
 volatile u32 DMA_CMAR2 ;
 volatile u32 RESEVED2 ;
 //----------------------3-----------------------
 volatile u32 DMA_CCR3 ;
 volatile u32 DMA_CNDTR3 ;
 volatile u32 DMA_CPAR3 ;
 volatile u32 DMA_CMAR3 ;
 volatile u32 RESEVED3 ;
 //-----------------------4----------------------
 volatile u32 DMA_CCR4 ;
 volatile u32 DMA_CNDTR4 ;
 volatile u32 DMA_CPAR4 ;
 volatile u32 DMA_CMAR4 ;
 volatile u32 RESEVED4 ;
 //-----------------------5----------------------
 volatile u32 DMA_CCR5 ;
 volatile u32 DMA_CNDTR5 ;
 volatile u32 DMA_CPAR5 ;
 volatile u32 DMA_CMAR5 ;
 volatile u32 RESEVED5 ;
 //------------------------6---------------------
 volatile u32 DMA_CCR6 ;
 volatile u32 DMA_CNDTR6 ;
 volatile u32 DMA_CPAR6 ;
 volatile u32 DMA_CMAR6 ;
 volatile u32 RESEVED6 ;
 //-------------------------7--------------------
 volatile u32 DMA_CCR7 ;
 volatile u32 DMA_CNDTR7 ;
 volatile u32 DMA_CPAR7 ;
 volatile u32 DMA_CMAR7 ;
 volatile u32 RESEVED7 ;
 //---------------------------------------------

 }DMA_REG_DEF_t;
 */

typedef struct {
	u16 DMA_EN :1;
	u16 DMA_TCIE :1;
	u16 DMA_HTIE :1;
	u16 DMA_TEIE :1;
	u16 DMA_DIR :1;
	u16 DMA_CIRC :1;
	u16 DMA_PINC :1;
	u16 DMA_MINC :1;
	u16 DMA_PSIZE :2;
	u16 DMA_MSIZE :2;
	u16 DMA_PL :2;
	u16 DMA_MEM2MEM :1;
	u16 DMA_RESERV :1;
	u16 DMA_RESERVval;
} DMAConf_t;
typedef struct {
	volatile DMAConf_t DMA_CCR;
	volatile u32 DMA_CNDTR;
	volatile u32 DMA_CPAR;
	volatile u32 DMA_CMAR;
	volatile u32 RESEVED;
} DMA_CH_REG_t;
typedef struct {

	volatile u32 DMA_ISR;
	volatile u32 DMA_IFCR;

	DMA_CH_REG_t DMA_CH[DMA_CONF_SIZE];
} DMA_REG_DEF_t;

#define DMA ((DMA_REG_DEF_t*)DMA_u32BASE_ADDRESS)
/*************************************************************/
/*******************UART Registers****************************/
/*************************************************************/

#define UART1_u32BASE_ADDRESS  0x40013800
#define UART2_u32BASE_ADDRESS  0x40004400
#define UART3_u32BASE_ADDRESS  0x40004800
#define UART4_u32BASE_ADDRESS  0x40004C00
#define UART5_u32BASE_ADDRESS  0x40005000

typedef struct {

	u32 USART_SR;
	u32 USART_DR;
	u32 USART_BRR;
	u32 USART_CR1;
	u32 USART_CR2;
	u32 USART_CR3;
	u32 USART_GTPR;

} UART_REG_DEF_t;

#define UART1 ((UART_REG_DEF_t*)UART1_u32BASE_ADDRESS)
#define UART2 ((UART_REG_DEF_t*)UART2_u32BASE_ADDRESS)
#define UART3 ((UART_REG_DEF_t*)UART3_u32BASE_ADDRESS)
#define UART4 ((UART_REG_DEF_t*)UART4_u32BASE_ADDRESS)
#define UART5 ((UART_REG_DEF_t*)UART5_u32BASE_ADDRESS)
/*************************************************************/
/*******************SPI Registers****************************/
/*************************************************************/

#define SPI1_u32BASE_ADDRESS  0x40013000
#define SPI2_u32BASE_ADDRESS  0x40003800
#define SPI3_u32BASE_ADDRESS  0x40003C00

typedef struct {

	u32 SPI_CR1;
	u32 SPI_CR2;
	u32 SPI_SR;
	u32 SPI_DR;
	u32 SPI_CRCPR;
	u32 SPI_RXCRCR;
	u32 SPI_TXCRCR;
	u32 SPI_I2SCFGR;
	u32 SPI_I2SPR;

} SPI_REG_DEF_t;

#define SPI1 ((SPI_REG_DEF_t*)SPI1_u32BASE_ADDRESS)
#define SPI2 ((SPI_REG_DEF_t*)SPI2_u32BASE_ADDRESS)

/*************************************************************/
/*******************ADC Registers****************************/
/*************************************************************/

#define ADC1_u32BASE_ADDRESS  0x40012400
#define ADC2_u32BASE_ADDRESS  0x40012800
#define ADC3_u32BASE_ADDRESS  0x40013C00
// size of regesters

#define  ADC_CRSIZE    2
#define  ADC_SMPRSIZE  2
#define  ADC_JOFRSIZE  4
#define  ADC_SQRSIZE   3
#define  ADC_JDRSIZE   4

typedef struct {
	u32 ADC_SR;
	u32 ADC_CR[ADC_CRSIZE];
	u32 ADC_SMPR[ADC_SMPRSIZE];
	u32 ADC_JOFR[ADC_JOFRSIZE];
	u32 ADC_HTR;
	u32 ADC_LTR;
	u32 ADC_SQR[ADC_SQRSIZE];
	u32 ADC_JSQR;
	u32 ADC_JDR[ADC_JDRSIZE];
	u32 ADC_DR;
} ADC_REG_DEF_t;

#define ADC1 ((ADC_REG_DEF_t*)ADC1_u32BASE_ADDRESS)
#define ADC2 ((ADC_REG_DEF_t*)ADC2_u32BASE_ADDRESS)

/*************************************************************/
/*******************I2C Registers****************************/
/*************************************************************/

#define I2C1_u32BASE_ADDRESS  0x40005400
#define I2C2_u32BASE_ADDRESS  0x40005800

typedef struct {

	volatile u32 I2C_CR1;
	volatile u32 I2C_CR2;
	volatile u32 I2C_OAR1;
	volatile u32 I2C_OAR2;
	volatile u32 I2C_DR;
	volatile u32 I2C_SR1;
	volatile u32 I2C_SR2;
	volatile u32 I2C_CCR;
	volatile u32 I2C_TRISE;

} I2C_REG_DEF_t;
/*************************************************************/
/*******************FLASH Registers****************************/
/*************************************************************/

#define FLASH_u32BASE_ADDRESS  0x40022000
// FLASH_CR  bits
#define CR_LOCK     7
#define CR_STRT     6
#define CR_PER      1
#define CR_PG       0


// FLASH_SR  bits
#define SR_BSY            0
#define SR_EOP            0
#define SR_WRPRTERR       0
#define SR_PGERR          0

typedef struct {

	volatile u32 FLASH_ACR;
	volatile u32 FLASH_KEYR;
	volatile u32 FLASH_OPTKEYR;
	volatile u32 FLASH_SR;
	volatile u32 FLASH_CR;
	volatile u32 FLASH_AR;
	volatile u32 FLASH_res;
	volatile u32 FLASH_OBR;
	volatile u32 FLASH_WRPR;

} FLASH_REG_DEF_t;
#define FLASH ((FLASH_REG_DEF_t*)FLASH_u32BASE_ADDRESS)

/*************************************************************/
/*******************CRC Registers****************************/
/*************************************************************/

#define CRC_u32BASE_ADDRESS  0x40023000
// crc config libs
#define CRC_RESET 0

typedef struct {

	volatile u32 CRC_DR;
	volatile u32 CRC_IDR;
	volatile u32 CRC_CR;

} CRC_REG_DEF_t;
#define CRC ((CRC_REG_DEF_t*)CRC_u32BASE_ADDRESS)
#endif //_STMF103C8_MMAP_H_
