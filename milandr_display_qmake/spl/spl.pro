# Ни гуи, ни ядра Qt нам не надо!
QT -= gui core
CONFIG -= qt
# Шаблон проекта - статическая библиотека
TEMPLATE = lib
CONFIG += staticlib
# Целевой каталог и имя
DESTDIR = ../lib
TARGET = spl

include(../common/alias.pri)
include(../common/includepath.pri)
include(../common/gcc.pri)

HEADERS += $$files($$SPL/inc/MDR32F9Qx_iwdg.h)
HEADERS += $$files($$SPL/inc/MDR32F9Qx_port.h)
HEADERS += $$files($$SPL/inc/MDR32F9Qx_rst_clk.h)
HEADERS += $$files($$SPL/inc/MDR32F9Qx_timer.h)
HEADERS += $$files($$SPL/inc/MDR32F9Qx_usb.h)
#HEADERS += $$files($$SPL/inc/*.h)
HEADERS += $$files($$SPL/MDR32F9Qx_config.h)
HEADERS += /home/evg/SOFT/Github/Arm/CMSIS_Version_5/CMSIS/DAP/Firmware/Validation/MDK5/RTE/_CMSIS_DAP/RTE_Components.h

SOURCES += $$files($$SPL/src/MDR32F9Qx_iwdg.c)
SOURCES += $$files($$SPL/src/MDR32F9Qx_port.c)
SOURCES += $$files($$SPL/src/MDR32F9Qx_rst_clk.c)
SOURCES += $$files($$SPL/src/MDR32F9Qx_timer.c)
SOURCES += $$files($$SPL/src/MDR32F9Qx_usb.c)
#SOURCES += $$files($$SPL/inc/*.h)

