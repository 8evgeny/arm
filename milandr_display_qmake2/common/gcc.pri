# Настройки компилятора C
QMAKE_CC = arm-none-eabi-gcc
QMAKE_CFLAGS += -mcpu=cortex-m3
QMAKE_CFLAGS += -mthumb
QMAKE_CFLAGS += -O2
QMAKE_CFLAGS += -ffunction-sections
QMAKE_CFLAGS += -fdata-sections
QMAKE_CFLAGS += -Wall
QMAKE_CFLAGS += -Wextra
QMAKE_CFLAGS += -Wshadow
QMAKE_CFLAGS += -Wredundant-decls
QMAKE_CFLAGS += -Wno-missing-field-initializers
QMAKE_CFLAGS += -Wconversion
QMAKE_CFLAGS += -Wno-packed-bitfield-compat
QMAKE_CFLAGS += -pipe
QMAKE_CFLAGS += -std=c99
QMAKE_CFLAGS += -DUSE_MDR1986VE9x
QMAKE_CFLAGS += -D__STARTUP_CLEAR_BSS
QMAKE_CFLAGS += -D__START=main
QMAKE_CFLAGS += --specs=nosys.specs
QMAKE_CFLAGS += --specs=nano.specs
#QMAKE_CFLAGS += -D__HEAP_SIZE=0x0000
#QMAKE_CFLAGS += -D__STACK_SIZE=0x0100

# Настройки компилятора C++
QMAKE_CXX = arm-none-eabi-g++
QMAKE_CXXFLAGS += -fno-rtti
QMAKE_CXXFLAGS += -fno-exceptions
QMAKE_CXXFLAGS += -fno-threadsafe-statics
QMAKE_CXXFLAGS += -DUSE_MDR1986VE9x
QMAKE_CXXFLAGS += -D__STARTUP_CLEAR_BSS
QMAKE_CXXFLAGS += --specs=nano.specs
QMAKE_CXXFLAGS += --specs=nosys.specs
QMAKE_CXXFLAGS += -mcpu=cortex-m3
QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS += -Wl,-Map=${PROJECT_NAME}.map
QMAKE_CXXFLAGS += -Wl,--print-memory-usage
QMAKE_CXXFLAGS += -Wl,--defsym=__STACK_SIZE=0x0100
QMAKE_CXXFLAGS += -Wl,--defsym=__HEAP_SIZE=0x0000
QMAKE_CXXFLAGS += -Wl,--gc-sections
QMAKE_CXXFLAGS += -ffreestanding

# Настройки линковщика
QMAKE_LINK = arm-none-eabi-g++
QMAKE_LFLAGS += -T $$LINKER_SCRIPT
