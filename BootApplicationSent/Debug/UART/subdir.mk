################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UART/UART_Prog.c 

OBJS += \
./UART/UART_Prog.o 

C_DEPS += \
./UART/UART_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
UART/%.o UART/%.su UART/%.cyclo: ../UART/%.c UART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-UART

clean-UART:
	-$(RM) ./UART/UART_Prog.cyclo ./UART/UART_Prog.d ./UART/UART_Prog.o ./UART/UART_Prog.su

.PHONY: clean-UART

