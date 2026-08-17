#!/usr/bin/bash
#первый параметр - тулчейн  
#второй - имя ветки в репозитории https://github.com/beagleboard/linux
#третий - имя папки с файлами для SD

#ветки
#beaglebone-3.2
#beaglev-v5.10.113-1.1.2
#beaglev-v5.10.113-1.1.2-ubuntu

 ./build.sh arm-linux-gnueabihf- beaglev-v5.10.113-1.1.2-ubuntu  SD_BB
#./build.sh arm-cortex_a8-linux-gnueabihf- beaglev-v5.10.113-1.1.2-ubuntu 
