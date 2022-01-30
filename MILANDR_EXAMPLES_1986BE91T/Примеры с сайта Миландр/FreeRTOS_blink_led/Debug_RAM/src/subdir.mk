################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hooks.c \
../src/init.c \
../src/main.c \
../src/syscalls.c 

S_UPPER_SRCS += \
../src/startup_MLDR187.S 

OBJS += \
./src/hooks.o \
./src/init.o \
./src/main.o \
./src/startup_MLDR187.o \
./src/syscalls.o 

S_UPPER_DEPS += \
./src/startup_MLDR187.d 

C_DEPS += \
./src/hooks.d \
./src/init.d \
./src/main.d \
./src/syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imc -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/MLDR187_SPL/inc" -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/src" -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/FreeRTOS/include" -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/FreeRTOS/portable/GCC/RISC-V" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.S src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv-none-embed-gcc -march=rv32imc -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -x assembler-with-cpp -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/MLDR187_SPL/inc" -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/src" -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/FreeRTOS/include" -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/FreeRTOS/portable/GCC/RISC-V" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


