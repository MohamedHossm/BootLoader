################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Flash/FLASH_Prog.c 

OBJS += \
./Flash/FLASH_Prog.o 

C_DEPS += \
./Flash/FLASH_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
Flash/%.o Flash/%.su Flash/%.cyclo: ../Flash/%.c Flash/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall /home/hosam/Desktop/STM_Porject/NTI4month/Src -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Flash

clean-Flash:
	-$(RM) ./Flash/FLASH_Prog.cyclo ./Flash/FLASH_Prog.d ./Flash/FLASH_Prog.o ./Flash/FLASH_Prog.su

.PHONY: clean-Flash

