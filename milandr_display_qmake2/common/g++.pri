# Настройки компилятора C++
#QMAKE_CXX = arm-none-eabi-g++
QMAKE_CXX =/home/evg/toolchain/gcc-arm-none-eabi-new/bin/arm-none-eabi-g++
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
