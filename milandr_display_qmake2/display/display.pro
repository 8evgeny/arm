# Ни гуи, ни ядра Qt нам не надо!
QT -= gui core
CONFIG -= qt
# Шаблон проекта - приложение, будет собираться исполняемый файл формата ELF
TEMPLATE = app
#Задаем каталог для собранного бинарника и его имя
DESTDIR = ../bin
TARGET = display

include(../common/alias.pri)
include(../common/includepath.pri)
include(../common/gcc.pri)
include(../common/g++.pri)

## Настройки компоновщика
#QMAKE_LINK = /usr/bin/avr-gcc
#QMAKE_LFLAGS = -w -Os -Wl,--gc-sections -mmcu=$$ARDUINO_MCU
#QMAKE_LIBS = -lm

INCLUDEPATH += ./inc
HEADERS += $$files(./inc/*.h)

#INCLUDEPATH += ./src
SOURCES += $$files(./src/*.c)
SOURCES += $$files(./src/*.cpp)

#QMAKE_LINK = /home/evg/toolchain/gcc-arm-none-eabi-new/bin/arm-none-eabi-g++
#QMAKE_LIBS += -lm
#QMAKE_LIBS += -lspl
#QMAKE_LIBS += -ldev_support
#QMAKE_LIBS += -lstartup_support
#QMAKE_LIBS += -lusb
#LIBS += -lm

LIBS += -L../build/lib -lspl
LIBS += -L../build/lib -ldev_support
LIBS += -L../build/lib -lstartup_support
LIBS += -L../build/lib -lusb

#Настраиваем постобработку ELF-файла, с целью перекрутить его в Intel HEX для последующей прошивки в плату
#QMAKE_POST_LINK += arm-none-eabi-objcopy -O ihex -j .text -j .data -S ${TARGET} ${TARGET}.hex


#unix:!macx: LIBS += -L$$PWD/../../../../toolchain/gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi/lib/ -lstdc++

#INCLUDEPATH += $$PWD/../../../../toolchain/gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi/include
#DEPENDPATH += $$PWD/../../../../toolchain/gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi/include

#unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../toolchain/gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi/lib/libstdc++.a
