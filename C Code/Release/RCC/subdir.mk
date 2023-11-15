################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RCC/RCC_Prog.c 

OBJS += \
./RCC/RCC_Prog.o 

C_DEPS += \
./RCC/RCC_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
RCC/%.o RCC/%.su RCC/%.cyclo: ../RCC/%.c RCC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"/home/hosam/Desktop/STM_Porject/NTI4month/Flash" -I"/home/hosam/Desktop/STM_Porject/NTI4month/GPIO" -I"/home/hosam/Desktop/STM_Porject/NTI4month/LIBS" -I"/home/hosam/Desktop/STM_Porject/NTI4month/RCC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-RCC

clean-RCC:
	-$(RM) ./RCC/RCC_Prog.cyclo ./RCC/RCC_Prog.d ./RCC/RCC_Prog.o ./RCC/RCC_Prog.su

.PHONY: clean-RCC

