################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/dht22/dht22.c 

OBJS += \
./Core/Inc/dht22/dht22.o 

C_DEPS += \
./Core/Inc/dht22/dht22.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/dht22/%.o Core/Inc/dht22/%.su Core/Inc/dht22/%.cyclo: ../Core/Inc/dht22/%.c Core/Inc/dht22/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-dht22

clean-Core-2f-Inc-2f-dht22:
	-$(RM) ./Core/Inc/dht22/dht22.cyclo ./Core/Inc/dht22/dht22.d ./Core/Inc/dht22/dht22.o ./Core/Inc/dht22/dht22.su

.PHONY: clean-Core-2f-Inc-2f-dht22

