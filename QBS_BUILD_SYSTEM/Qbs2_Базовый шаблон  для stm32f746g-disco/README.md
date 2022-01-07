# Базовый шаблон проекта для stm32f746g-disco (qbs)

Установите следующие пакеты:
* libtool
* eclipse-cdt-autotools
* libusb-1.0-0-dev

Установка openocd:
* git clone http://openocd.zylin.com/openocd 
* cd openocd
* git fetch http://openocd.zylin.com/openocd refs/changes/18/3918/16 && git checkout FETCH_HEAD
* ./bootstrap 
* ./configure --enable-ft2232_ftd2xx 
* make 
* sudo make install



Подключите stm32f746g-disco к ПК, откройте терминал и выполните следующую команду: 

* openocd -f board/stm32f746g-disco.cfg -c "init" -c "reset init" -c "reset" -c "shutdown" 

Вы должны увидеть информацию следующего характера:
~~~~
Open On-Chip Debugger 0.10.0+dev-00208-gc892814 (2018-04-02-12:10)
Licensed under GNU GPL v2
For bug reports, read
        http://openocd.org/doc/doxygen/bugs.html
Info : The selected transport took over low-level target control. The results might differ compared to plain JTAG/SWD
adapter speed: 2000 kHz
adapter_nsrst_delay: 100
srst_only separate srst_nogate srst_open_drain connect_deassert_srst
Info : Unable to match requested speed 2000 kHz, using 1800 kHz
Info : Unable to match requested speed 2000 kHz, using 1800 kHz
Info : clock speed 1800 kHz
Info : STLINK v2 JTAG v25 API v2 SWIM v14 VID 0x0483 PID 0x374B
Info : using stlink api v2
Info : Target voltage: 3.231073
Warn : Silicon bug: single stepping will enter pending exception handler!
Info : stm32f7x.cpu: hardware has 8 breakpoints, 4 watchpoints
target halted due to debug-request, current mode: Thread 
xPSR: 0x01000000 pc: 0x0802a0b8 msp: 0x2004c000
adapter speed: 4000 kHz
shutdown command invoked 
~~~~

При сборке проекта происходит прошивка внутренней и внешней памяти (openocd должен быть отключен).

Для отладки должен быть выбран debug режим и запущен openocd, для запуска выполните команду в терминале:
* openocd -f board/stm32f746g-disco.cfg -c "init" -c "reset init"


Добавьте файл openocd.udev в /etc/udev/rules.d/, после перезапустите правила

sudo udevadm control --reload-rules
