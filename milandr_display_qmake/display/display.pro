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

INCLUDEPATH += ./inc
HEADERS += $$files(./inc/*.h)

INCLUDEPATH += ./src
SOURCES += $$files(./src/*.c)
SOURCES += $$files(./src/*.cpp)

#QMAKE_LINK = /home/evg/toolchain/gcc-arm-none-eabi-new/bin/arm-none-eabi-g++
INCLUDEPATH += /home/evg/SOFT/Github/Arm/milandr_display_qmake2/build/lib
#QMAKE_LIBS += -lm
#QMAKE_LIBS += -L../build/lib -lspl
#QMAKE_LIBS += -ldev_support
#QMAKE_LIBS += -lusb
#LIBS += -lm

LIBS += -L../../build/lib -lspl
LIBS += -L../../build/lib -ldev_support
LIBS += -L../../build/lib -lusb

#Настраиваем постобработку ELF-файла, с целью перекрутить его в Intel HEX для последующей прошивки в плату
QMAKE_POST_LINK += arm-none-eabi-objcopy -O ihex -j .text -j .data -S ${TARGET} ${TARGET}.hex


