#!/usr/bin/bash
cd /home/evg/SOFT/Github/Arm/Embedded_Linux/LEARN/2024_03_15_Kernel_BB_in_Docker/build_localy
arm-linux-gnueabihf-gcc --version

# если нет папки u-boot

git clone --single-branch --branch u-boot-2016.09.y --progress git://git.denx.de/u-boot.git u-boot/
cd u-boot
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- am335x_boneblack_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
