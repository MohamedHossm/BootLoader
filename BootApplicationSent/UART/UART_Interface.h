/*****************************************************************************/
/* Auther          : Mohamed Hoasm                                                    */
/* Date            : 3/8/2023                                                        */
/* Version         : 1.0                                                              */
/* SW              : UART                                                             */
/*****************************************************************************/
#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#define UART_CALLBACK_SIZE 4
#define UART_FRAME_SIZE 20
#define UART_STR_SIZE   20
#define UART1_ENDFRAM '#'

void UART1_voidInit() ;
Error_t UART1_u8SendByteBusyw8(u8 data ) ;
Error_t UART1_u8RecieveByteBusyw8(u8* data) ;

Error_t UART1_u8SendByteAsynch(u8 data) ;
Error_t UART1_u8RecieveByteAsynch(void) ;

Error_t UART1_u8SendStringBusyW8(char* data) ;
Error_t UART1_u8RecieveStringBusyW8(u8* data) ;

Error_t UART1_u8RecieveByte(volatile u8 *data);

Error_t UART1_u8SendArrayBusyW8(u8 *data , u8 Copy_Size) ;

Error_t UART1_u8EnterruptEnRX(void);
Error_t UART1_u8EnterruptDsRX(void);
Error_t UART1_u8EnterruptCallBackRX(void (*Rx)(void)) ;
Error_t UART1_u8EnterruptEnTX(void);
Error_t UART1_u8EnterruptDsTX(void);
Error_t UART1_u8EnterruptCallBackTX(void);

Error_t UART1_u8SendNumString(u32 copy_u32num);
Error_t UART1_u8SendNum(u32 copy_u32num);

void UART1_Runnable(void);
u8 UART1_IsDataReady(void);
void UART1_GETdata(u8 *UART1ptrStr, u16 *UART1ptrNum);
//****************************************************************************************************************/
// uart2
void UART2_voidInit() ;
Error_t UART2_u8SendByteBusyw8(u8 data) ;
Error_t UART2_u8RecieveByteBusyw8(u8 *data) ;
Error_t UART2_u8SendStringBusyW8(char *data) ;
Error_t UART2_u8SendArrayBusyW8(u8 *data , u8 Copy_Size);
Error_t UART2_u8RecieveByte(volatile u8 *data) ;
Error_t UART2_u8SendNum(u32 copy_u32num) ;
Error_t UART2_u8SendNumString(u32 copy_u32num) ;
Error_t UART2_u8RecieveStringBusyW8(u8 *data);
Error_t UART2_u8EnterruptEnRX(void) ;
Error_t UART2_u8EnterruptDsRX(void) ;
Error_t UART2_u8EnterruptCallBackRX(void (*Rx)(void)) ;// not working
Error_t UART2_u8EnterruptEnTX(void) ;
Error_t UART2_u8EnterruptDsTX(void) ;
Error_t UART2_u8EnterruptCallBackTX(void) ;
#endif //UART_INTERFACE_H_

