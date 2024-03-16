#!/usr/bin/bash
# docker build --no-cache -t build_bb_kernel  /home/evg/SOFT/Github/Arm/Embedded_Linux/LEARN/2024_03_15_Kernel_BB_in_Docker/build_in_Docker
docker build -t build_bb_kernel  /home/evg/SOFT/Github/Arm/Embedded_Linux/LEARN/2024_03_15_Kernel_BB_in_Docker/build_in_Docker
docker run --name bb_uboot build_bb_kernel
mkdir -p SDCARD_BOOT
docker cp bb_uboot:/home/evg/u-boot/u-boot.img SDCARD_BOOT
docker cp bb_uboot:/home/evg/u-boot/MLO SDCARD_BOOT
docker rm bb_uboot 
cd SDCARD_BOOT
touch uEnv.txt
echo "console=ttyS0,115200n8" > uEnv.txt
echo "netargs=setenv bootargs console=ttyO0,115200n8 root=/dev/mmcblk0p2 ro rootfstype=ext4 rootwait debug earlyprintk mem=512M" >> uEnv.txt
echo "netboot=echo Booting from microSD ...; setenv autoload no ; load mmc 0:1 ${loadaddr} uImage ; load mmc 0:1 ${fdtaddr} am335x-boneblack.dtb ; run netargs ; bootm ${loadaddr} - ${fdtaddr}" >> uEnv.txt
echo "uenvcmd=run netboot" >> uEnv.txt
echo "Files for BOOT create in folder SDCARD_BOOT"
