# Useful locations
MBED = ../../mbed/build/mbed

# MCU
MANUFACTURER=STM
FAMILY=STM32F4XX
MCU=STM32F407

# Files
SRC = $(wildcard *.cc)
OBJ = $(SRC:.cc=.o)
ELF = $(SRC:.cc=.elf)
BIN = $(SRC:.cc=.bin)
MBED_OBJ = $(wildcard $(MBED)/TARGET_$(MCU)/TOOLCHAIN_GCC_ARM/*.o)

# Applications
CXX = arm-none-eabi-g++
LD = arm-none-eabi-gcc

OBJCOPY = arm-none-eabi-objcopy
FLASHER = st-flash

# Common flags
INC =
CXXFLAGS = -g -std=c++11 -Werror -Wall -pedantic
LDFLAGS =
LIB =

# Platform-specific flags
CXXFLAGS += -Os -fno-common -fmessage-length=0 -fno-exceptions -mcpu=cortex-m4 -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -mthumb -ffunction-sections -fdata-sections  -DTARGET_$(MANUFACTURER) -DTARGET_FAMILY -DTARGET_$(MCU) -DTOOLCHAIN_GCC_ARM -DNDEBUG
INC += -I$(MBED) -I$(MBED)/TARGET_$(MCU) -I$(MBED)/TARGET_$(MCU)/TOOLCHAIN_GCC_ARM
LIB += -lmbed -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys
LDFLAGS +=  -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Wl,--gc-sections --specs=nano.specs -u _printf_float -u _scanf_float -T$(MBED)/TARGET_$(MCU)/TOOLCHAIN_GCC_ARM/$(MCU).ld -L$(MBED) -L$(MBED)/TARGET_$(MCU) -L$(MBED)/TARGET_$(MCU)/TOOLCHAIN_GCC_ARM

all: $(BIN)

$(ELF): $(OBJ)
	$(LD) $(LDFLAGS) $^ $(MBED_OBJ) -o $@ $(LIB) $(LIB)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

.cc.o:
	$(CXX) -c $(INC) $(CXXFLAGS) $< -o $@

install: $(BIN) flash

flash:
	$(FLASHER)  write $(BIN) 0x08000000 

clean:
	rm -f $(BIN) $(ELF) $(OBJ)
