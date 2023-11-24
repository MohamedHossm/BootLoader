################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/RCC/RCC_Prog.c 

OBJS += \
./Inc/RCC/RCC_Prog.o 

C_DEPS += \
./Inc/RCC/RCC_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/RCC/%.o Inc/RCC/%.su Inc/RCC/%.cyclo: ../Inc/RCC/%.c Inc/RCC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall /home/hosam/Desktop/STM_Porject/NTI4month/Src -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-RCC

clean-Inc-2f-RCC:
	-$(RM) ./Inc/RCC/RCC_Prog.cyclo ./Inc/RCC/RCC_Prog.d ./Inc/RCC/RCC_Prog.o ./Inc/RCC/RCC_Prog.su

.PHONY: clean-Inc-2f-RCC

