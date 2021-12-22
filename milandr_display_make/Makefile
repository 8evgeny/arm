CXX		= arm-none-eabi-g++
CC		= arm-none-eabi-gcc
LD		= arm-none-eabi-gcc
OBJCOPY		= arm-none-eabi-objcopy
SIZE		= arm-none-eabi-size
STFLASH		= st-flash
OPENOCD		= openocd
STUTIL		= st-flash

OUTPUT_DIR	= bin
OBJ_DIR         = obj

TARGET_NAME     = display

TARGET_BINARY	= $(TARGET_NAME).elf
TARGET_HEX	= $(TARGET_NAME).hex

vpath %.c ./src

SOURCES	= \
main.c \
gpio.c \
logic.c \
mt20s4.c \
rcc_delay.c \
usb.c \
var.c

LDFLAGS_DEBUG =  
CDFLAGS_DEBUG = -g3 -O0

LDFLAGS_RELEASE = 
CDFLAGS_RELEASE = -O2

CFLAGS		= -Wall \
-mcpu=cortex-m3 \
-mthumb \
-D__HEAP_SIZE=0x0000 \
-D__STACK_SIZE=0x0100 \
-mfloat-abi=soft \
-fno-strict-aliasing \
-fdata-sections \
-ffunction-sections \
-DSTM32F103C8 \
-DSTM32F10X_MD \
-DUSE_STDPERIPH_DRIVER

TARGET	= $(OUTPUT_DIR)/$(TARGET_BINARY)

LIBS = -lm

LDFLAGS		= \
--specs=nosys.specs \
--specs=nano.specs \
-mcpu=cortex-m3 \
-mthumb \
-Wl,--defsym=__HEAP_SIZE=0x0000 \
-Wl,--defsym=__STACK_SIZE=0x0100 \
-mfloat-abi=soft \
-fno-strict-aliasing \
-fdata-sections \
-ffunction-sections  \
-Wl,--gc-sections \
-Wl,-script="./hardware/stm32f103c8_flash.ld" \
-Wl,-Map=$(TARGET).map
#-u _printf_float 

INCLUDES	= \
-I. \
-I./include \
-I./hardware/include \
-I./hardware/include/cmsis \
-I./hardware/SPL/include

#STARUPFILE = hardware/src/startup_MDR32F9Qx.s
STARUPFILE = hardware/src/startup_stm32f10x_md.S

SOURCES_SPL	= \
#MDR32F9Qx_iwdg.c \
MDR32F9Qx_port.c \
MDR32F9Qx_rst_clk.c \
MDR32F9Qx_timer.c \
MDR32F9Qx_usb.c \
MDR32F9Qx_usb_CDC.c \
#system_MDR32F9Qx.c \
MDR32F9Qx_usb_device.c \



################################################################


SOURCES	+= $(addprefix hardware/SPL/src/, $(SOURCES_SPL))
#SOURCES	+= hardware/src/system_stm32f10x.c

HEX	= $(OUTPUT_DIR)/$(TARGET_HEX)

STARTUPOBJ = $(notdir $(STARUPFILE))
STARTUPOBJ := $(patsubst %.S, $(OBJ_DIR)/%.S.o, $(STARTUPOBJ))

OBJECTS	= $(patsubst %, $(OBJ_DIR)/%.o, $(SOURCES))
OBJECTS += $(STARTUPOBJ)

DEPS	= $(OBJECTS:.o=.d)



all: release

release: LDFLAGS+=$(LDFLAGS_RELEASE)
release: CFLAGS+=$(CDFLAGS_RELEASE)
release: _firmware

debug: LDFLAGS+=$(LDFLAGS_DEBUG)
debug: CFLAGS+=$(CDFLAGS_DEBUG)
debug: _firmware
	

_firmware: $(TARGET) $(HEX)


$(TARGET): $(OBJECTS) | $(OUTPUT_DIR) $(OBJ_DIR)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)
	$(SIZE) --format=berkeley $(TARGET) 

obj/%.cpp.o: %.cpp
ifeq ($(OS), Windows_NT)
	$(eval dirname=$(subst /,\\,$(dir $@)))
	@ if NOT EXIST $(dirname) mkdir $(dirname)
else
	@mkdir -p $(dir $@) $(TO_NULL) 
endif
	$(CXX) -c -MMD -MP $(CFLAGS) $(INCLUDES) $< -o $@

obj/%.c.o: %.c
ifeq ($(OS), Windows_NT)
	$(eval dirname=$(subst /,\\,$(dir $@)))
	@ if NOT EXIST $(dirname) mkdir $(dirname)
else
	@mkdir -p $(dir $@) $(TO_NULL) 
endif
	$(CC) -c -MMD -MP $(CFLAGS) $(INCLUDES) $< -o $@

$(STARTUPOBJ):
	$(CC) -c -MMD -MP $(CFLAGS) $(INCLUDES) $(STARUPFILE) -o $(STARTUPOBJ)

$(HEX): $(TARGET)
	$(OBJCOPY) -O ihex $(TARGET) $(HEX)

$(OUTPUT_DIR):
	@mkdir $(OUTPUT_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

_size: $(TARGET)
	$(SIZE) --format=berkeley $(TARGET) 


flash: flash-ocd

flash-stutil:
	$(STFLASH) --format ihex write $(HEX)

flash-ocd:
	$(OPENOCD) -f interface/stlink-v2.cfg -f target/stm32f1x.cfg -c "program $(TARGET) verify reset exit"

srclist:
	@echo $(SOURCES)

objlist:
	@echo $(OBJECTS)

clean:

ifeq ($(OS), Windows_NT)
	-del $(subst /,\\,$(OBJECTS))
	-del $(subst /,\\,$(DEPS))
	-rmdir /S /Q $(OBJ_DIR)
	-del /Q /F $(OUTPUT_DIR)\\$(TARGET_BINARY)
	-del /Q /F $(OUTPUT_DIR)\\$(TARGET_BINARY).map
	-del /Q /F $(OUTPUT_DIR)\\$(TARGET_HEX)
else
	-rm -f $(OBJECTS)
	-rm -f $(DEPS)
	-rm -rf $(OBJ_DIR)
	-rm -f $(OUTPUT_DIR)/$(TARGET_BINARY)
	-rm -f $(OUTPUT_DIR)/$(TARGET_BINARY).map
	-rm -f $(OUTPUT_DIR)/$(TARGET_HEX)
endif	

-include $(DEPS)
