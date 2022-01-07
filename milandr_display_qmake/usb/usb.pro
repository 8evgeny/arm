# Ни гуи, ни ядра Qt нам не надо!
QT -= gui core
CONFIG -= qt
# Шаблон проекта - статическая библиотека
TEMPLATE = lib
CONFIG += staticlib
# Целевой каталог и имя
DESTDIR = ../lib
TARGET = usb

include(../common/alias.pri)
include(../common/includepath.pri)
include(../common/gcc.pri)

#HEADERS += $$files($$SPL/inc/USB_Library/MDR32F9Qx_usb_CDC.h)
#HEADERS += $$files($$SPL/inc/USB_Library/MDR32F9Qx_usb_device.h)
HEADERS += $$files($$SPL/inc/USB_Library/*.h)

#SOURCES += $$files($$SPL/src/USB_Library/MDR32F9Qx_usb_CDC.c)
#SOURCES += $$files($$SPL/src/USB_Library/MDR32F9Qx_usb_device.c)
SOURCES += $$files($$SPL/src/USB_Library/*.c)




