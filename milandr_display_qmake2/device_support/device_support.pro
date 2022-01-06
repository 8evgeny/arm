# Ни гуи, ни ядра Qt нам не надо!
QT -= gui core
CONFIG -= qt
# Шаблон проекта - статическая библиотека
TEMPLATE = lib
CONFIG += staticlib
# Целевой каталог и имя 
DESTDIR = ../lib
TARGET = dev_support

include(../common/alias.pri)
include(../common/includepath.pri)
include(../common/gcc.pri)

HEADERS += $$files($$DevSupport/startup/arm/system_MDR32F9Qx.h)

SOURCES += $$files($$DevSupport/startup/arm/system_MDR32F9Qx.c)



