#!/usr/bin/bash
cd /home/evg/SOFT/Github/Arm/Embedded_Linux/LEARN/2024_03_15_Kernel_BB/build_localy
$1gcc --version

if [[ ! -d u-boot ]]; then # если нет папки u-boot
    echo clone to u-boot
    git clone --single-branch --branch u-boot-2016.09.y --progress git://git.denx.de/u-boot.git u-boot/
    cd u-boot
    make ARCH=arm CROSS_COMPILE=$1 am335x_boneblack_defconfig
    make ARCH=arm CROSS_COMPILE=$1
    cd ..
else
    echo u-boot exist
fi
if [[ ! -d $3 ]]; then  # создаю директорию $3 
    echo create $3
    mkdir $3
fi
mkdir -p $3/BOOT/ 
cp -f u-boot/MLO $3/BOOT/
cp -f u-boot/u-boot.img $3/BOOT/
cd $3/BOOT
touch uEnv.txt
echo "console=ttyS0,115200n8" > uEnv.txt
echo "netargs=setenv bootargs console=ttyO0,115200n8 root=/dev/mmcblk0p2 ro rootfstype=ext4 rootwait debug earlyprintk mem=512M" >> uEnv.txt
echo "netboot=echo Booting from microSD ...; setenv autoload no ; load mmc 0:1 ${loadaddr} uImage ; load mmc 0:1 ${fdtaddr} am335x-boneblack.dtb ; run netargs ; bootm ${loadaddr} - ${fdtaddr}" >> uEnv.txt
echo "uenvcmd=run netboot" >> uEnv.txt
echo "Files for BOOT create in folder $3"
cd ../..

#Переходим к RFS
#sudo mkdir /media/RFS
#sudo mount /dev/sdc2 /media/RFS/
#sudo tar -xvf rootfs.tar.xz -C /media/RFS/
#cd /media/RFS/rootfs/
#sudo mv ./* ../
#cd ../
#sudo rmdir rootfs

rm -R $3/RFS
mkdir -p $3/RFS
tar -xvf rootfs.tar.xz -C $3/RFS/
cd $3/RFS/rootfs/
mv ./* ../
cd ../
rmdir rootfs
cd ../..

if [[ ! -d linux ]]; then 
    #    echo clone to linux
    #    git clone --single-branch --branch $2  --progress  https://github.com/beagleboard/linux.git
    if [[ ! -f linux.zip ]]; then 
        wget -c -O linux.zip https://github.com/beagleboard/linux/archive/refs/heads/$2.zip  
    fi
    7z x -y linux.zip 
    rm linux.zip
    mv linux-$2 linux
else
    echo linux exist
fi

#Копируем внутрь linux ранее созданный файл .config
cp .config linux/
cd linux
# make ARCH=arm CROSS_COMPILE=$1 omap2plus_defconfig
# make ARCH=arm CROSS_COMPILE=$1 menuconfig
#make ARCH=arm CROSS_COMPILE=$1 uImage dtbs LOADADDR=0x80008000 -j4 
make ARCH=arm CROSS_COMPILE=$1 uImage dtbs -j4 
#&>../log.txt 
make ARCH=arm CROSS_COMPILE=$1 -j4 modules 
#&>>../log.txt 
make ARCH=arm CROSS_COMPILE=$1 INSTALL_MOD_PATH=../$3/RFS/ modules_install 
#&>>../log.txt 
pwd
# cp -f arch/arm/boot/uImage ../$3/RFS/boot
# cp -f arch/arm/boot/dts/am335x-boneblack.dtb ../$3/RFS/boot
cp -f arch/arm/boot/uImage ../$3/BOOT
cp -f arch/arm/boot/dts/am335x-boneblack.dtb ../$3/BOOT

# ручная очистка     cd linux && make ARCH=arm CROSS_COMPILE=$1 clean && cd ..
