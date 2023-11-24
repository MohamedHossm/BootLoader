/*************************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 15/10/2023                                                       */
/* Version        : 1.0                                                              */
/*sw              : Bootloader                                                            */
/*************************************************************************************/

#ifndef BOOTLOADER_PRIVATE_H_
#define BOOTLOADER_PRIVATE_H_


void  RX_Fun(void);
static void Bootloader_StateMachienChangeToApp() ;
static Bool_t localBootloader_updateAvailable()  ;
static Bool_t localBootloader_SellectAPP(void) ;
static void Bootloader_StateMachienChangeToFactoryApp();
void Bootloader_HandelFlames();
#endif /* BOOTLOADER_PRIVATE_H_ */
