/*************************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 15/10/2023                                                       */
/* Version        : 1.0                                                              */
/*sw              : Bootloader                                                            */
/*************************************************************************************/
#ifndef BOOTLOADER_CONF_H_
#define BOOTLOADER_CONF_H_

// Flash memory base addresses
#define FLASH_BASE_ADDRESS 0x08004000
#define FLASH_BASE_ADDRESSTest 0x08000000
#define FLASH_RESET_HANDLER (FLASH_BASE_ADDRESS + 0x00000004)


#define  FLASH_ERASE_SIZE 5

#define  HEXFILESIZE 40

#endif /* BOOTLOADER_CONF_H_ */
