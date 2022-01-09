################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/syscalls.c \
../src/wait.c 

S_UPPER_SRCS += \
../src/startup_MLDR187.S 

OBJS += \
./src/main.o \
./src/startup_MLDR187.o \
./src/syscalls.o \
./src/wait.o 

S_UPPER_DEPS += \
./src/startup_MLDR187.d 

C_DEPS += \
./src/main.d \
./src/syscalls.d \
./src/wait.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	echo -mcpu=cortex-m3 -mthumb -O2  -g -I"/home/evg/Рабочий стол/Примеры Миландр/watchdog/MLDR187_SPL/inc" -I"/home/evg/Рабочий стол/Примеры Миландр/watchdog/src" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.S src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross Assembler'
	echo -mcpu=cortex-m3 -mthumb -O2  -g -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


