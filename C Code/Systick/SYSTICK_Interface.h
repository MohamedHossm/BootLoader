/*****************************************************************************/
/* Auther          : Mohamed Hoasm                                                    */
/* Date            : 25/7/2023                                                        */
/* Version         : 1.0                                                              */
/* SW              : SYSTICK                                                             */
/*****************************************************************************/
#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

#define STK_MAXVALUE 16777215

Error_t STK_u8Init();

Error_t STK_u8SetBusyWait (u32 Copy_time_MS) ;
Error_t STK_u8SetIntervalSingle (u32 Copy_time_MS , void(*STK_FunISR)(void));
Error_t STK_u8SetIntervalPeriodic (u32 Copy_time_MS , void(*STK_FunISR)(void));
Error_t STK_u8SetIntervalSingleOV(u32 Copy_time_MS, void (*STK_FunISR)(void)) ;

Error_t STK_u8StopTimer ();
Error_t STK_u8StartTimer();

Error_t STK_u8SpentTimer (u32 *Ptr_SpentTime);
Error_t STK_u8GetRemining(u32 *Ptr_Remind);
Error_t STK_u8ENInterrupt();
Error_t STK_u8DSInterrupt();
Error_t STK_u8SetCallBack(void (*FunPtr)(void));
#endif //SYSTICK_INTERFACE_H_

