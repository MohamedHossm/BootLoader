/*************************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 15/10/2023                                                       */
/* Version        : 1.0                                                              */
/*sw              : FLASH                                                            */
/*************************************************************************************/

#ifndef FLASH_INTERFACE_H_
#define FLASH_INTERFACE_H_

#define FLASH_START  0x08000000
#define FLASH_END    0x0807FFFF


typedef enum {
	FLASH_OK = 0,
	FLASH_WRITTEN,
	FLASH_OUTOFRANGE,
	FLASH_UNLOCKERR,
	FLASH_PROTECTIONERR,
	FlASH_BUSY,
	FLASH_PROGRAMINGERR,
	FLASH_ERR

}FLASH_enERR_T;

///interface APIS
FLASH_enERR_T FLASH_enErasePage(u8 Copy_u8page) ;
FLASH_enERR_T FLASH_enWriteData(u32 ptrAddress, u16 Copy_Data);
FLASH_enERR_T FLASH_enWriteArray(u32 ptrAddress, u32 Copy_Size, u16 *Arr_u8Data) ;
FLASH_enERR_T FLASH_enCalculatePages(u32 Copy_Address, u16 *Ptr_u16ReturnData) ;
FLASH_enERR_T FlASH_enEnablePrograming();
FLASH_enERR_T FlASH_enDisablePrograming() ;
FLASH_enERR_T FLASH_enUnlock();
FLASH_enERR_T FLASH_enlock();
FLASH_enERR_T FLASH_enWaitClr() ;
#endif /* FLASH_INTERFACE_H_ */
