################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MT48LC4M32B2.c \
../Src/ethernetif.c \
../Src/font12.c \
../Src/font16.c \
../Src/font20.c \
../Src/font24.c \
../Src/font8.c \
../Src/freertos.c \
../Src/ltdc.c \
../Src/lwip.c \
../Src/main.c \
../Src/stm32f7xx_hal_msp.c \
../Src/stm32f7xx_hal_timebase_tim.c \
../Src/stm32f7xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f7xx.c 

OBJS += \
./Src/MT48LC4M32B2.o \
./Src/ethernetif.o \
./Src/font12.o \
./Src/font16.o \
./Src/font20.o \
./Src/font24.o \
./Src/font8.o \
./Src/freertos.o \
./Src/ltdc.o \
./Src/lwip.o \
./Src/main.o \
./Src/stm32f7xx_hal_msp.o \
./Src/stm32f7xx_hal_timebase_tim.o \
./Src/stm32f7xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f7xx.o 

C_DEPS += \
./Src/MT48LC4M32B2.d \
./Src/ethernetif.d \
./Src/font12.d \
./Src/font16.d \
./Src/font20.d \
./Src/font24.d \
./Src/font8.d \
./Src/freertos.d \
./Src/ltdc.d \
./Src/lwip.d \
./Src/main.d \
./Src/stm32f7xx_hal_msp.d \
./Src/stm32f7xx_hal_timebase_tim.d \
./Src/stm32f7xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Inc -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../Drivers/CMSIS/Include -O2 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/MT48LC4M32B2.d ./Src/MT48LC4M32B2.o ./Src/ethernetif.d ./Src/ethernetif.o ./Src/font12.d ./Src/font12.o ./Src/font16.d ./Src/font16.o ./Src/font20.d ./Src/font20.o ./Src/font24.d ./Src/font24.o ./Src/font8.d ./Src/font8.o ./Src/freertos.d ./Src/freertos.o ./Src/ltdc.d ./Src/ltdc.o ./Src/lwip.d ./Src/lwip.o ./Src/main.d ./Src/main.o ./Src/stm32f7xx_hal_msp.d ./Src/stm32f7xx_hal_msp.o ./Src/stm32f7xx_hal_timebase_tim.d ./Src/stm32f7xx_hal_timebase_tim.o ./Src/stm32f7xx_it.d ./Src/stm32f7xx_it.o ./Src/syscalls.d ./Src/syscalls.o ./Src/system_stm32f7xx.d ./Src/system_stm32f7xx.o

.PHONY: clean-Src

