#$ sudo pacman -S arduino arduino-avr-core
#нам понадобятся ещё компилятор, ассемблер, компоновщик и стандартная библиотека C для AVR, поэтому ставим и их
#$ sudo pacman -S avr-gcc avr-binutils avr-libc
#Отладчик и эмулятор , поэтому установим ещё такие пакеты
#$ sudo pacman -S avr-gdb simavr

#    # Определяем переменные окружения сборки
#    # Корневой каталог исходников Arduino Core
#    ARDUINO_DIR=/usr/share/arduino/hardware/archlinux-arduino/avr/
#    # Выбираем целевой контроллер (Arduino Uno, Nano, Mini)
#    ARDUINO_MCU=atmega328p
#    # Частота тактирования контроллера
#    ARDUINO_FCPU = 16000000L

# Ни гуи, ни ядра Qt нам не надо!
QT -= gui core
CONFIG -= qt

# Шаблон проекта - приложение, будет собираться исполняемый файл формата ELF
TEMPLATE = app

#Задаем каталог для собранного бинарника и его имя
DESTDIR = ../bin
TARGET = S-789

#Дальше подключим директории поиска заголовочных файлов
# Подключаем заголовочные файлы
INCLUDEPATH += $$ARDUINO_DIR/cores/arduino
INCLUDEPATH += $$ARDUINO_DIR/variants/standard
INCLUDEPATH += $$ARDUINO_DIR/libraries
INCLUDEPATH += /usr/avr/include
INCLUDEPATH += $$ARDUINO_DIR/libraries/Grove_4-Digit_Display

#Задаем компилятор C и его ключи
QMAKE_CC = /usr/bin/avr-gcc
QMAKE_CFLAGS += -c -g -Os -w -ffunction-sections -fdata-sections
QMAKE_CFLAGS += -MMD -mmcu=$$ARDUINO_MCU -DF_CPU=$$ARDUINO_FCPU
QMAKE_CFLAGS += -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR
#и компилятор C++ и его ключи
QMAKE_CXX = /usr/bin/avr-g++
QMAKE_CXXFLAGS += -c -g -Os -w  -ffunction-sections -fdata-sections
QMAKE_CXXFLAGS += -fno-exceptions -fno-threadsafe-statics
QMAKE_CXXFLAGS += -MMD -mmcu=$$ARDUINO_MCU -DF_CPU=$$ARDUINO_FCPU
QMAKE_CXXFLAGS += -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR

#задаем компоновщик и его ключи
QMAKE_LINK = /usr/bin/avr-gcc
QMAKE_LFLAGS = -w -Os -Wl,--gc-sections -mmcu=$$ARDUINO_MCU
QMAKE_LIBS = -lm

#Настраиваем постобработку ELF-файла, с целью перекрутить его в Intel HEX для последующей прошивки в плату
QMAKE_POST_LINK += /usr/bin/avr-objcopy -O ihex -j .text -j .data -S ${TARGET} ${TARGET}.hex

# Заголовки Arduino Core
HEADERS += $$files($$ARDUINO_DIR/cores/arduino/*.h) \
    include/S-789.h
HEADERS += $$files($$ARDUINO_DIR/variants/standard/*.h)


# Исходники Arduino Core
SOURCES += $$files($$ARDUINO_DIR/cores/arduino/*.c)
SOURCES += $$files($$ARDUINO_DIR/cores/arduino/*.cpp)


#Заголовки проекта

INCLUDEPATH += ./include
HEADERS += $$files(./include/*.h)

# Исходники проекта
SOURCES += $$files(./src/*.cpp)
