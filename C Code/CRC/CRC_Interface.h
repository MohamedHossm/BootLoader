/*************************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 8/11/2023                                                       */
/* Version        : 1.0                                                              */
/*sw              : CRC                                                            */
/*************************************************************************************/

#ifndef CRC_INTERFACE_H_
#define CRC_INTERFACE_H_

#define BYTESIZE 8
#define CRC32_POLYNOMIAL 0x4C11DB7// 0xEDB88320

Error_t CRC_enuReset(void);
Error_t CRC_enuReadRegister(u32 *Ptr_u32DataReg);
Error_t CRC_enuWriteDataRegisterArry(u32 *Ptr_u8DataReg, u8 Copy_SizeData);
Error_t CRC_enuWriteDataRegister(u32 Copy_u32DataReg);

u32 CRC_CalculateCRC32(const u8 *byteArray, const u8 arraySize);
//** Software *//
Error_t CRC_enuWriteDataRegisterSoftWareArray(u8 *Ptr_u8Arrayofdata,
		u8 Copy_ArraySize);
Error_t CRC_enuReadDataRegisterSoftWare(u32 *Ptr_u8Arrayofdata);
Error_t CRC_enuResetSoftWare(void);
#endif /* CRC_INTERFACE_H_ */
