# Ни гуи, ни ядра Qt нам не надо!
QT -= gui core
CONFIG -= qt
# Шаблон проекта - статическая библиотека
TEMPLATE = lib
CONFIG += staticlib
# Целевой каталог и имя 
DESTDIR = ../lib
TARGET = startup_support

include(../common/alias.pri)
include(../common/includepath.pri)
include(../common/gcc.pri)

SOURCES += ../../Milandr_MCU_1986x_Standard_Peripherals_Library/CMSIS/CM3/DeviceSupport/MDR32F9Qx/startup/gcc/startup_MDR32F9Qx.S



