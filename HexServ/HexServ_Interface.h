/*************************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 15/10/2023                                                       */
/* Version        : 1.0                                                              */
/*sw              : HexServ_                                                            */
/*************************************************************************************/

#ifndef HEXSERV_INTERFACE_H_
#define HEXSERV_INTERFACE_H_

/*************************DAtA TYBES ********************************/
#define  HEX_DATARECORDER 	     00
#define  HEX_ENDOFRECORD         01
#define  HEX_EXTENDEDSEDADD      02
#define  HEX_STARTSEGMENT  		 03
#define  HEX_EXTENDEDLINEQR 	 04
#define  HEX_STARTLINEARADD 	 05
/*******************************************************************/

/************************* FRAME POSES ********************************/

#define HEX_RECORD_LEN_POS             0    // size 1 bite
#define HEX_RECORD_LEN                 1    // size byte

#define HEX_RECORD_ADDRES_POS          1    // size 1 bite
#define HEX_RECORD_ADDRES              2    // size byte

#define HEX_RECORD_TYPE_POS            3   // size 1 bite
#define HEX_RECORD_TYPE                1    // size byte

#define HEX_RECORD_DATA_POS            4   // size 1 bite

#define HEX_LINE_MAX                   16

#define HEX_RECORD_CKECKSUM_POS(DATASIZE)   (HEX_RECORD_DATA_POS + DATASIZE)   // size 1 bite
#define HEX_RECORD_CKECKSUM               1    // size byte



void HEX_voidParseFrame(u8 *Array_u8RecivedArray, u16 *ptr_u16ReturnAddress,
		u8 *ptr_u8Data, u8 *ptr_u8SizeData, u8 *ptr_u8checkSum,
		u8 *ptr_u8DataType);


void RedesignHex2Bytes(u8 *CopyStringHex, u16 *OutArray,u16 Copy_u16MaxArraySize) ;
void RedesignHex1Bytes(u8 *CopyStringHex, u8 *OutArray, u8 Copy_u8Size);
u8 DataCeckSum(u8 *ptrArraySum, u8 Copy_u8Size, u8 Copy_u8Checksum);

#endif /* HEXSERV_INTERFACE_H_ */
