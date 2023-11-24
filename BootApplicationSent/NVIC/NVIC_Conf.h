/*****************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 13/7/2023                                                        */
/* Version        : 1.0                                                              */
/*sw              : NVIC                                                             */
/*****************************************************************************/
//****************** priority options *********************
//      				   Group                        sup
/* SCB_G_16_SUP_NONE       16                           None  - 1
 * SCB_G_8_SUP_4           8                             2    - 2
 * SCB_G_4_SUP_4           4                             4    - 3
 * SCB_G_2_SUP_8           2                             8    - 4
 * SCB_G_NONE_SUP_16       None                          16   - 5
 * */
//**********************************************************
#define NVIC_PR_OPTIONS  SCB_G_4_SUP_4

