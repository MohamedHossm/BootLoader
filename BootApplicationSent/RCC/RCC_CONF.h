/*****************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 13/7/2023                                                        */
/* Version        : 1.0                                                              */
/*sw              : RCC                                                             */
/*****************************************************************************/




#ifndef _RCC_CONFIG_H
#define _RCC_CONFIG_H

/* 
*****************************
choose clock type:
1-RCC_u8HSE_CRYSTAL
2-RCC_u8HSE_RC
3-RCC_u8HSI
4-RCC_u8PLL
*****************************
 */

#define RCC_u8CLK_TYPE 	RCC_u8HSE_CRYSTAL



#if RCC_u8CLK_TYPE==RCC_u8PLL
/* 
*****************************
choose clock type:
1-RCC_u8PLL_HSI_DIV_2
2-RCC_u8PLL_HSE_DIV_2
3-RCC_u8PLL_HSE

*****************************
 */

#define RCC_u8PLL_INPUT  RCC_u8PLL_HSI_DIV_2
#endif

#endif /* _RCC_CONFIG_H */
