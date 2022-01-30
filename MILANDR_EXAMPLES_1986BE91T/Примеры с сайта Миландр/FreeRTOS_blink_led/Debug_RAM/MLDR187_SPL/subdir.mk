################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../MLDR187_SPL/MLDR187_cryptoAes.S \
../MLDR187_SPL/MLDR187_cryptoKuz.S \
../MLDR187_SPL/MLDR187_math.S 

OBJS += \
./MLDR187_SPL/MLDR187_cryptoAes.o \
./MLDR187_SPL/MLDR187_cryptoKuz.o \
./MLDR187_SPL/MLDR187_math.o 

S_UPPER_DEPS += \
./MLDR187_SPL/MLDR187_cryptoAes.d \
./MLDR187_SPL/MLDR187_cryptoKuz.d \
./MLDR187_SPL/MLDR187_math.d 


# Each subdirectory must supply rules for building sources it contributes
MLDR187_SPL/%.o: ../MLDR187_SPL/%.S MLDR187_SPL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv-none-embed-gcc -march=rv32imc -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -x assembler-with-cpp -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/MLDR187_SPL/inc" -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/src" -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/FreeRTOS/include" -I"/home/evg/SOFT/Github/Arm/MILANDR_EXAMPLES_1986BE91T/Примеры с сайта Миландр/FreeRTOS_blink_led/FreeRTOS/portable/GCC/RISC-V" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


