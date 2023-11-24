################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GPIO/GPIO_CONF.c \
../GPIO/GPIO_Prog.c 

OBJS += \
./GPIO/GPIO_CONF.o \
./GPIO/GPIO_Prog.o 

C_DEPS += \
./GPIO/GPIO_CONF.d \
./GPIO/GPIO_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
GPIO/%.o GPIO/%.su GPIO/%.cyclo: ../GPIO/%.c GPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall /home/hosam/Desktop/STM_Porject/NTI4month/Src -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-GPIO

clean-GPIO:
	-$(RM) ./GPIO/GPIO_CONF.cyclo ./GPIO/GPIO_CONF.d ./GPIO/GPIO_CONF.o ./GPIO/GPIO_CONF.su ./GPIO/GPIO_Prog.cyclo ./GPIO/GPIO_Prog.d ./GPIO/GPIO_Prog.o ./GPIO/GPIO_Prog.su

.PHONY: clean-GPIO

