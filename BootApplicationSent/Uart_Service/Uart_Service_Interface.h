/*****************************************************************************/
/* Auther          : Mohamed Hoasm                                                    */
/* Date            : 19/11/2023                                                        */
/* Version         : 1.0                                                              */
/* SW              : Uart_Service                                                     */
/*****************************************************************************/
#ifndef UART_SERVICE_INTERFACE_H_
#define UART_SERVICE_INTERFACE_H_

#define BUFFERSIZE 100

#define  WIFI_MAXSIZE 50
#define  WIFI_REPORT_ERR   "ERR1#"
#define  WIFI_REPORT_ERR2  "ERR2#"
#define  WIFI_REPORT_ERR3  "ERR3#"
#define  WIFI_REPORT_ERR4  "ERR4#"

#define  CAR_REPORT_REQ    "REQ#"

#define  WIFI_FRAMECASE_HAVEUPDATE  "UPDATE#"

void Uart_Service_voidInit();
int String_u8len(const char *ptr_SourceSTring);
Bool_t StringIncluded(const char *ptr_SourceSTring, const char *ptr_CopySTring);
Bool_t StringCom(const char *ptr_SourceSTring, const char *ptr_CopySTring);
void App_HandelFlames(void);
void App_HandelFlames2(void);

void UartFunction(void);
void Uart2Function(void);
#endif //UART_SERVICE_INTERFACE_H_

