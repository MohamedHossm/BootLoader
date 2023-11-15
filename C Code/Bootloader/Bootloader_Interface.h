/*************************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 15/10/2023                                                       */
/* Version        : 1.0                                                              */
/*sw              : Bootloader                                                            */
/*************************************************************************************/

#ifndef BOOTLOADER_INTERFACE_H_
#define BOOTLOADER_INTERFACE_H_

#define ReciveLEDIndication Pin_A4


typedef void (*Function_t)(void);

void Bootloader_Jump_To_Application1(u32 address);
void Bootloader_Jump_To_Application();
void BootLocationEreas(void);
void Bootloader_voidfReciveFlash(void);
void Bootloader_Init(void);
void Bootloader_voidfRunnable(void);
typedef enum {

	BOOT_WAITING,BOOT_CHECKFORUPDEATE,BOOT_CHECKSTATES, BOOT_RECIVINGHEX, BOOT_JUMPTOTHEMAINAPP, BOOT_ERROR,BOOT_REQESTHEX,
}

BootloaderStates_t;

#endif /* BOOTLOADER_INTERFACE_H_ */
