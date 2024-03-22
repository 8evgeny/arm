#!/usr/bin/bash
#docker build --no-cache -t build_bb_kernel  ${PWD}
docker build -t buildroot_bb_kernel  ${PWD}
#docker run --name bb_uboot build_bb_kernel
#mkdir -p SDCARD_BOOT/BOOT
#docker cp bb_uboot:/home/evg/u-boot/u-boot.img SDCARD_BOOT/BOOT
#docker cp bb_uboot:/home/evg/u-boot/MLO SDCARD_BOOT/BOOT
#docker rm bb_uboot 


