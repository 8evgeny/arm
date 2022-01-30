################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/croutine.c \
../FreeRTOS/event_groups.c \
../FreeRTOS/list.c \
../FreeRTOS/queue.c \
../FreeRTOS/stream_buffer.c \
../FreeRTOS/tasks.c \
../FreeRTOS/timers.c 

OBJS += \
./FreeRTOS/croutine.o \
./FreeRTOS/event_groups.o \
./FreeRTOS/list.o \
./FreeRTOS/queue.o \
./FreeRTOS/stream_buffer.o \
./FreeRTOS/tasks.o \
./FreeRTOS/timers.o 

C_DEPS += \
./FreeRTOS/croutine.d \
./FreeRTOS/event_groups.d \
./FreeRTOS/list.d \
./FreeRTOS/queue.d \
./FreeRTOS/stream_buffer.d \
./FreeRTOS/tasks.d \
./FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/%.o: ../FreeRTOS/%.c FreeRTOS/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imc -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/MLDR187_SPL/inc" -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/src" -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/FreeRTOS/include" -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/FreeRTOS/portable/GCC/RISC-V" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


