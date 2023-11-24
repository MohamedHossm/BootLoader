################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../NVIC/NVIC_Prog.c 

OBJS += \
./NVIC/NVIC_Prog.o 

C_DEPS += \
./NVIC/NVIC_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
NVIC/%.o NVIC/%.su NVIC/%.cyclo: ../NVIC/%.c NVIC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-NVIC

clean-NVIC:
	-$(RM) ./NVIC/NVIC_Prog.cyclo ./NVIC/NVIC_Prog.d ./NVIC/NVIC_Prog.o ./NVIC/NVIC_Prog.su

.PHONY: clean-NVIC

