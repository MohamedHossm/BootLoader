/*************************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 8/11/2023                                                       */
/* Version        : 1.0                                                              */
/*sw              : CRC                                                            */
/*************************************************************************************/

#include "../LIBS/STD_TYPES.h"
#include "../LIBS/BIT_MATH.h"
#include "../LIBS/STMF103C8_MMAP.h"

#include "CRC_Conf.h"
#include "CRC_Interface.h"
#include "CRC_Private.h"

//**********************************************************************
//for debug
#include "../UART/UART_Interface.h"
//**********************************************************************
static u32 Global_u32crcContainer = 0xFFFFFFFF;
static const u32 generator_polynomial = 0x4C11DB7;

Error_t CRC_enuReset(void) {
	Error_t local_u8status = OK;
	SET_BIT(CRC->CRC_CR, CRC_RESET);
	return local_u8status;

}

Error_t CRC_enuWriteDataRegister(u32 Copy_u32DataReg) {
	Error_t local_u8status = OK;
	CRC->CRC_DR = Copy_u32DataReg;
	return local_u8status;
}

Error_t CRC_enuReadRegister(u32 *Ptr_u32DataReg) {
	Error_t local_u8status = OK;
	*Ptr_u32DataReg = CRC->CRC_DR;
	return local_u8status;

}
Error_t CRC_enuWriteDataRegisterArry(u32 *Ptr_u8DataReg, u8 Copy_SizeData) {

	Error_t local_u8status = OK;
	//u8 *reg = (u8*) Ptr_u8DataReg;

	//CRC_enuReset();
	for (u8 localindex = 0; localindex < Copy_SizeData; localindex++) {

		/*
		 for (u8 localindex_1 = 0; localindex_1 < 4; localindex_1++) {
		 if (reg[localindex * 4 + localindex_1] < 10) {
		 reg[localindex * 4 + localindex_1] = reg[localindex * 4 + localindex_1] + '0';
		 UART1_u8SendByteBusyw8(

		 reg[localindex * 4 + localindex_1] );
		 } else {
		 reg[localindex * 4 + localindex_1] = reg[localindex * 4 + localindex_1] - 10 + 'A';

		 UART1_u8SendByteBusyw8(
		 reg[localindex * 4 + localindex_1] );
		 }

		 }
		 */

		CRC->CRC_DR = Ptr_u8DataReg[localindex];
	}
	return local_u8status;

}

Error_t CRC_enuWriteDataRegisterSoftWareArray(u8 *Ptr_u8Arrayofdata,
		u8 Copy_ArraySize) {

	Error_t local_u8status = OK;

	for (u32 local_index_1 = 0; local_index_1 < Copy_ArraySize;
			local_index_1++) {
		Global_u32crcContainer ^= Ptr_u8Arrayofdata[local_index_1];
// debug
		UART1_u8SendByteBusyw8(Ptr_u8Arrayofdata[local_index_1]);

		for (u32 local_index_2 = 0; local_index_2 < BYTESIZE; local_index_2++) {
			if (Global_u32crcContainer & 1) {
				Global_u32crcContainer = (Global_u32crcContainer >> 1)
						^ CRC32_POLYNOMIAL;
			} else {
				Global_u32crcContainer >>= 1;
			}
		}
	}
	//debug
	UART1_u8SendStringBusyW8("\n");

	//Global_u32crcContainer = Global_u32crcContainer ^ 0xFFFFFFFF;
	return local_u8status;

}

u32 CRC_CalculateCRC32(const u8 *byteArray, const u8 arraySize) {
	/* CRC32 value */
	u32 crc = 0xFFFFFFFF;

	/* Check null pointer */
	if (NULLPTR != byteArray) {
		/* Process all bytes */
		for (u32 byte_idx = 0; byte_idx < arraySize; ++byte_idx) {
			/* XOR input byte into MSB of CRC */
			crc ^= (u32) (byteArray[byte_idx] << 24);

			/* Process all bits */
			for (u32 idx = 0; idx < 8; ++idx) {
				/* Check the MSB bit is equal to 1 */
				if (0x80000000 == (crc & 0x80000000)) {
					/* Last bit is 1, shift it out, then XOR with poly */
					crc = (u32) ((crc << 1) ^ generator_polynomial);
				} else {
					/* Last bit is not 1, shift */
					crc <<= 1;
				}
			}
		}
	} else {
		/* Null pointer detected */
	}

	/* Return */
	return crc;
}

Error_t CRC_enuReadDataRegisterSoftWare(u32 *Ptr_u8Arrayofdata) {
	Error_t local_u8status = OK;
	*Ptr_u8Arrayofdata = Global_u32crcContainer ^ 0xFFFFFFFF;
	return local_u8status;
}

Error_t CRC_enuResetSoftWare(void) {
	Error_t local_u8status = OK;

	Global_u32crcContainer = 0xFFFFFFFF;
	return local_u8status;

}
