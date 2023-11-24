################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bootloader/Bootloader_Prog.c 

OBJS += \
./Bootloader/Bootloader_Prog.o 

C_DEPS += \
./Bootloader/Bootloader_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
Bootloader/%.o Bootloader/%.su Bootloader/%.cyclo: ../Bootloader/%.c Bootloader/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall /home/hosam/Desktop/STM_Porject/NTI4month/Src -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Bootloader

clean-Bootloader:
	-$(RM) ./Bootloader/Bootloader_Prog.cyclo ./Bootloader/Bootloader_Prog.d ./Bootloader/Bootloader_Prog.o ./Bootloader/Bootloader_Prog.su

.PHONY: clean-Bootloader

