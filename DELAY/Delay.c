/*****************************************************************************/
/* Auther         : Mohamed Hoasm                                                    */
/* Date           : 26/7/2023                                                        */
/* Version        : 1.0                                                              */
/*sw              : DELAY                                                             */
/*****************************************************************************/
#include "../LIBS/STD_TYPES.h"
#include "../LIBS/BIT_MATH.h"

#include "Delay.h"

void Delay(u32 local_u32Time_delay) {

	for (u32 local_index = 0; local_index <= local_u32Time_delay;
			local_index++) {
		for (u32 local_index = 0; local_index <= local_u32Time_delay;
				local_index++)
			asm("NOP");
	}
}
