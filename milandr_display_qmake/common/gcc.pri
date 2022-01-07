# Настройки компилятора C
QMAKE_CC = arm-none-eabi-gcc
QMAKE_CC =/home/evg/toolchain/gcc-arm-none-eabi-new/bin/arm-none-eabi-gcc
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

