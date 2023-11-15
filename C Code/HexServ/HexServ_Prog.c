/*************************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 15/10/2023                                                       */
/* Version        : 1.0                                                              */
/*sw              : HexServ_                                                            */
/*************************************************************************************/

#include "../LIBS/STD_TYPES.h"
#include "../LIBS/BIT_MATH.h"
#include "../LIBS/STMF103C8_MMAP.h"

#include "HexServ_Conf.h"
#include "HexServ_Interface.h"
#include "HexServ_Private.h"

// this function parsing data
void HEX_voidParseFrame(u8 *Array_u8RecivedArray, u16 *ptr_u16ReturnAddress,
		u8 *ptr_u8Data, u8 *ptr_u8SizeData, u8 *ptr_u8checkSum,
		u8 *ptr_u8DataType) {

	u8 local_u8index = 0;

	*ptr_u8SizeData = Array_u8RecivedArray[HEX_RECORD_LEN_POS];   // data size
	*ptr_u16ReturnAddress = (u16) Array_u8RecivedArray[HEX_RECORD_ADDRES_POS]
			<< 8 | Array_u8RecivedArray[HEX_RECORD_ADDRES_POS + 1];   // address
	*ptr_u8DataType = Array_u8RecivedArray[HEX_RECORD_TYPE_POS];    // data type
	for (local_u8index = 0; local_u8index < *ptr_u8SizeData; local_u8index++) { // data array
		ptr_u8Data[local_u8index] = Array_u8RecivedArray[HEX_RECORD_DATA_POS
				+ local_u8index];

	}
	for (; local_u8index < HEX_LINE_MAX; local_u8index++) { // fill array
		ptr_u8Data[local_u8index] = 0;
	}
	*ptr_u8checkSum = Array_u8RecivedArray[HEX_RECORD_CKECKSUM_POS(
			*ptr_u8SizeData)];
}

void RedesignHex2Bytes(u8 *CopyStringHex, u16 *OutArray,
		u16 Copy_u16MaxArraySize) {
	u16 Local_temp0 = 0;
	u16 Local_temp1 = 0;
	u8 Local_index = 0;

	for (Local_index = 0;
			Local_index < Copy_u16MaxArraySize
					&& CopyStringHex[(Local_index * 4)]; Local_index++) {

		for (u8 Local_index1 = 0; Local_index1 < 4; Local_index1++) {
			if ((CopyStringHex[(Local_index * 4) + Local_index1]) >= '0'
					&& (CopyStringHex[(Local_index * 4) + Local_index1])
							<= '9') {
				(CopyStringHex[(Local_index * 4) + Local_index1]) =
						(CopyStringHex[(Local_index * 4) + Local_index1]) - '0';
			} else if ((CopyStringHex[(Local_index * 4) + Local_index1]) >= 'A'
					&& (CopyStringHex[(Local_index * 4) + Local_index1])
							<= 'F') {
				(CopyStringHex[(Local_index * 4) + Local_index1]) =
						((CopyStringHex[(Local_index * 4) + Local_index1]) - 'A')
								+ 10;

			} else {
				//do nothing
			}
		}
		Local_temp0 = 0;
		Local_temp1 = 0;
		Local_temp0 = ((CopyStringHex[(Local_index * 4)] & 0x0f) << 4)
				| (CopyStringHex[(Local_index * 4) + 1] & 0x0f);
		Local_temp1 = ((CopyStringHex[(Local_index * 4) + 2] & 0x0f) << 4)
				| (CopyStringHex[(Local_index * 4) + 3] & 0x0f);
		/*(((CopyStringHex[(Local_index * 4) + 3])) & 0x0f)
		 | ((((CopyStringHex[(Local_index * 4) + 2])) & 0x0f) << 4);
		 Local_temp1 = (((CopyStringHex[(Local_index * 4) + 1])) & 0x0f)
		 | ((((CopyStringHex[Local_index * 4])) & 0x0f) << 4);
		 */
		OutArray[Local_index] = Local_temp0 << 8 | Local_temp1;
		//UART1_u8SendNumString(OutArray[Local_index]);

		//UART1_u8SendStringBusyW8("\n");

	}

}

void ConvertHextoAscii(u8 *CopyHex, u8 *OutArray, u8 Copy_u8Size) {

for (;;){

}




}
void RedesignHex1Bytes(u8 *CopyStringHex, u8 *OutArray, u8 Copy_u8Size) {
	u16 Local_temp0 = 0;

	u8 Local_index = 0;

	for (Local_index = 0;
			Local_index < Copy_u8Size && CopyStringHex[(Local_index * 2)];
			Local_index++) {

		for (u8 Local_index1 = 0; Local_index1 < 2; Local_index1++) {
			if ((CopyStringHex[(Local_index * 2) + Local_index1]) >= '0'
					&& (CopyStringHex[(Local_index * 2) + Local_index1])
							<= '9') {
				(CopyStringHex[(Local_index * 2) + Local_index1]) =
						(CopyStringHex[(Local_index * 2) + Local_index1]) - '0';
			} else if ((CopyStringHex[(Local_index * 2) + Local_index1]) >= 'A'
					&& (CopyStringHex[(Local_index * 2) + Local_index1])
							<= 'F') {
				(CopyStringHex[(Local_index * 2) + Local_index1]) =
						((CopyStringHex[(Local_index * 2) + Local_index1]) - 'A')
								+ 10;

			} else {
				//do nothing
			}
		}
		Local_temp0 = 0;

		Local_temp0 = ((CopyStringHex[(Local_index * 2)] & 0x0f) << 4)
				| (CopyStringHex[(Local_index * 2) + 1] & 0x0f);

		/*(((CopyStringHex[(Local_index * 4) + 3])) & 0x0f)
		 | ((((CopyStringHex[(Local_index * 4) + 2])) & 0x0f) << 4);
		 Local_temp1 = (((CopyStringHex[(Local_index * 4) + 1])) & 0x0f)
		 | ((((CopyStringHex[Local_index * 4])) & 0x0f) << 4);
		 */
		OutArray[Local_index] = Local_temp0;
		//	UART1_u8SendNumString(OutArray[Local_index]);

		//	UART1_u8SendStringBusyW8("\n");

	}
	for (; Local_index < Copy_u8Size; Local_index++) {
		OutArray[Local_index] = 0;
	}

}

u8 DataCeckSum(u8 *ptrArraySum, u8 Copy_u8Size, u8 Copy_u8Checksum) {
	u16 localSum = 0;
	for (u8 local_index; local_index < Copy_u8Size; local_index++) {
		localSum += ptrArraySum[local_index];
	}
	u16 data = 0;
	data = localSum - Copy_u8Checksum;
	data = ((u8) (~(data & 0x00ff))) + 1;
	return (u8) data;
}

