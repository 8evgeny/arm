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


# Each subdirectory must supply rules for building sources it contributes
MLDR187_SPL/%.o: ../MLDR187_SPL/%.S MLDR187_SPL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


