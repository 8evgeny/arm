#!/usr/bin/bash
cd /home/evg/SOFT/Github/Arm/Embedded_Linux/LEARN/2024_03_15_Kernel_BB/build_localy
arm-linux-gnueabihf-gcc --version

if [[ ! -d u-boot ]]; then # если нет папки u-boot
    echo clone to u-boot
    git clone --single-branch --branch u-boot-2016.09.y --progress git://git.denx.de/u-boot.git u-boot/
    cd u-boot
    make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- am335x_boneblack_defconfig
    make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
    cd ..
else
    echo u-boot exist
fi

if [[ ! -d SDCARD ]]; then  # создаю директорию SDCARD 
    echo create SDCARD
    mkdir SDCARD
fi
mkdir -p SDCARD/BOOT/ 
cp -f u-boot/MLO SDCARD/BOOT/
cp -f u-boot/u-boot.img SDCARD/BOOT/
cd SDCARD/BOOT
touch uEnv.txt
echo "console=ttyS0,115200n8" > uEnv.txt
echo "netargs=setenv bootargs console=ttyO0,115200n8 root=/dev/mmcblk0p2 ro rootfstype=ext4 rootwait debug earlyprintk mem=512M" >> uEnv.txt
echo "netboot=echo Booting from microSD ...; setenv autoload no ; load mmc 0:1 ${loadaddr} uImage ; load mmc 0:1 ${fdtaddr} am335x-boneblack.dtb ; run netargs ; bootm ${loadaddr} - ${fdtaddr}" >> uEnv.txt
echo "uenvcmd=run netboot" >> uEnv.txt
echo "Files for BOOT create in folder SDCARD"
cd ../..
# ls


#Переходим к RFS

#sudo mkdir /media/RFS
#sudo mount /dev/sdc2 /media/RFS/
#sudo tar -xvf rootfs.tar.xz -C /media/RFS/
#cd /media/RFS/rootfs/
#sudo mv ./* ../
#cd ../
#sudo rmdir rootfs

rm -R SDCARD/RFS
mkdir -p SDCARD/RFS
tar -xvf rootfs.tar.xz -C SDCARD/RFS/
cd SDCARD/RFS/rootfs/
mv ./* ../
cd ../
rmdir rootfs
cd ../..


if [[ ! -d linux ]]; then 
    echo clone to linux
    git clone --single-branch --branch beaglev-v5.10.113-1.1.2-ubuntu  --progress  https://github.com/beagleboard/linux.git

else
    echo linux exist
fi

#Копируем внутрь linux ранее созданный файл .config
cp .config linux/
cd linux
# make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- omap2plus_defconfig
# make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- uImage dtbs LOADADDR=0x80008000 -j4
# make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j4 modules
# make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=../SDCARD/RFS/ modules_install
pwd
# cp -f arch/arm/boot/uImage ../SDCARD/RFS/boot
# cp -f arch/arm/boot/dts/am335x-boneblack.dtb ../SDCARD/RFS/boot
cp -f arch/arm/boot/uImage ../SDCARD/BOOT
cp -f arch/arm/boot/dts/am335x-boneblack.dtb ../SDCARD/BOOT


