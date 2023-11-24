/*****************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 24/7/2023                                                        */
/* Version        : 1.0                                                              */
/*sw              : EXTI                                                             */
/*****************************************************************************/
#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

typedef enum
{
  EXTI_Line0  ,  /* EXTI Line 0 */
  EXTI_Line1  ,  /* EXTI Line 1 */
  EXTI_Line2  ,  /* EXTI Line 2 */
  EXTI_Line3  ,  /* EXTI Line 3 */
  EXTI_Line4  ,  /* EXTI Line 4 */
  EXTI_Line5  ,  /* EXTI Line 5 */
  EXTI_Line6  ,  /* EXTI Line 6 */
  EXTI_Line7  ,  /* EXTI Line 7 */
  EXTI_Line8  ,  /* EXTI Line 8 */
  EXTI_Line9  ,  /* EXTI Line 9 */
  EXTI_Line10 ,  /* EXTI Line 10 */
  EXTI_Line11 ,  /* EXTI Line 11 */
  EXTI_Line12 ,  /* EXTI Line 12 */
  EXTI_Line13 ,  /* EXTI Line 13 */
  EXTI_Line14 ,  /* EXTI Line 14 */
  EXTI_Line15 ,   /* EXTI Line 15 */
  EXTI_TOTAL
} EXTI_Line_t;

typedef enum
{
	EXTI_FAILING ,
	EXTI_RISING ,
	EXTI_FAILING_RISING 
}EXTI_MODE_t;

Error_t EXTI_u8Iint(void) ;

Error_t EXTI_u8En(EXTI_Line_t copy_u8Line) ;
Error_t EXTI_u8Ds(EXTI_Line_t copy_u8Line) ;

Error_t EXTI_u8SW_interrupt(EXTI_Line_t copy_u8Line) ;
Error_t EXTI_u8Set_Inturrupt_latch(EXTI_Line_t copy_u8Line ,
  EXTI_MODE_t copy_u8Mode); 

Error_t EXTI_u8Set_pend(EXTI_Line_t copy_u8Line) ; 
Error_t EXTI_u8CLR_pend(EXTI_Line_t copy_u8Line);

Error_t EXTI_u8Read_pend(EXTI_Line_t copy_u8Line, u8* returnData) ;

Error_t EXTI_u8Setter_IRQ(EXTI_Line_t copy_u8Line, void (*CopyFun)(void)) ;

#endif //EXTI_INTERFACE_H_


