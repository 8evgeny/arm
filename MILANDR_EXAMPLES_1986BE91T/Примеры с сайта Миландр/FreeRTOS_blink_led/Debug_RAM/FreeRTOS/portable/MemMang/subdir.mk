################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/portable/MemMang/heap_3.c 

OBJS += \
./FreeRTOS/portable/MemMang/heap_3.o 

C_DEPS += \
./FreeRTOS/portable/MemMang/heap_3.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/MemMang/%.o: ../FreeRTOS/portable/MemMang/%.c FreeRTOS/portable/MemMang/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imc -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/MLDR187_SPL/inc" -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/src" -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/FreeRTOS/include" -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/FreeRTOS/portable/GCC/RISC-V" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


