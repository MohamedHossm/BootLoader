/*************************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 15/10/2023                                                       */
/* Version        : 1.0                                                              */
/*sw              : Bootloader                                                            */
/*************************************************************************************/

#ifndef BOOTLOADER_INTERFACE_H_
#define BOOTLOADER_INTERFACE_H_

typedef void (*Function_t)(void);


void Bootloader_Jump_To_Application1(u32 address);
void Bootloader_Jump_To_Application();
void BootLocationEreas() ;
void Bootloader_voidfReciveFlash();
void Bootloader_Init() ;
#endif /* BOOTLOADER_INTERFACE_H_ */
