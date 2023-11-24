################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../EXIT/EXTI_Prog.c 

OBJS += \
./EXIT/EXTI_Prog.o 

C_DEPS += \
./EXIT/EXTI_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
EXIT/%.o EXIT/%.su EXIT/%.cyclo: ../EXIT/%.c EXIT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-EXIT

clean-EXIT:
	-$(RM) ./EXIT/EXTI_Prog.cyclo ./EXIT/EXTI_Prog.d ./EXIT/EXTI_Prog.o ./EXIT/EXTI_Prog.su

.PHONY: clean-EXIT

