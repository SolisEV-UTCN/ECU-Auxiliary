################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/tasks/can_rx.c \
../Core/Src/tasks/can_tx.c \
../Core/Src/tasks/loop.c \
../Core/Src/tasks/mode.c \
../Core/Src/tasks/update.c 

OBJS += \
./Core/Src/tasks/can_rx.o \
./Core/Src/tasks/can_tx.o \
./Core/Src/tasks/loop.o \
./Core/Src/tasks/mode.o \
./Core/Src/tasks/update.o 

C_DEPS += \
./Core/Src/tasks/can_rx.d \
./Core/Src/tasks/can_tx.d \
./Core/Src/tasks/loop.d \
./Core/Src/tasks/mode.d \
./Core/Src/tasks/update.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/tasks/%.o Core/Src/tasks/%.su Core/Src/tasks/%.cyclo: ../Core/Src/tasks/%.c Core/Src/tasks/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-tasks

clean-Core-2f-Src-2f-tasks:
	-$(RM) ./Core/Src/tasks/can_rx.cyclo ./Core/Src/tasks/can_rx.d ./Core/Src/tasks/can_rx.o ./Core/Src/tasks/can_rx.su ./Core/Src/tasks/can_tx.cyclo ./Core/Src/tasks/can_tx.d ./Core/Src/tasks/can_tx.o ./Core/Src/tasks/can_tx.su ./Core/Src/tasks/loop.cyclo ./Core/Src/tasks/loop.d ./Core/Src/tasks/loop.o ./Core/Src/tasks/loop.su ./Core/Src/tasks/mode.cyclo ./Core/Src/tasks/mode.d ./Core/Src/tasks/mode.o ./Core/Src/tasks/mode.su ./Core/Src/tasks/update.cyclo ./Core/Src/tasks/update.d ./Core/Src/tasks/update.o ./Core/Src/tasks/update.su

.PHONY: clean-Core-2f-Src-2f-tasks

