################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Uart_Service/Uart_Service_Prog.c 

OBJS += \
./Uart_Service/Uart_Service_Prog.o 

C_DEPS += \
./Uart_Service/Uart_Service_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
Uart_Service/%.o Uart_Service/%.su Uart_Service/%.cyclo: ../Uart_Service/%.c Uart_Service/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Uart_Service

clean-Uart_Service:
	-$(RM) ./Uart_Service/Uart_Service_Prog.cyclo ./Uart_Service/Uart_Service_Prog.d ./Uart_Service/Uart_Service_Prog.o ./Uart_Service/Uart_Service_Prog.su

.PHONY: clean-Uart_Service

