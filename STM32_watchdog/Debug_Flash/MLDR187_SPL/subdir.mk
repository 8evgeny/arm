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
	@echo 'Invoking: GNU Arm Cross Assembler'
	echo -mcpu=cortex-m3 -mthumb -O2  -g -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


