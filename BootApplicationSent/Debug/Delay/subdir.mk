################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Delay/Delay.c 

OBJS += \
./Delay/Delay.o 

C_DEPS += \
./Delay/Delay.d 


# Each subdirectory must supply rules for building sources it contributes
Delay/%.o Delay/%.su Delay/%.cyclo: ../Delay/%.c Delay/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Delay

clean-Delay:
	-$(RM) ./Delay/Delay.cyclo ./Delay/Delay.d ./Delay/Delay.o ./Delay/Delay.su

.PHONY: clean-Delay
