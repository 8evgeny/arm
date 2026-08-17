#!/usr/bin/bash 
sudo dd if=/dev/zero of=/dev/$1 bs=1M count=10
#This is a very important step!
sudo dd if=$2/BOOT/MLO of=/dev/$1 count=1 seek=1 bs=128k
sudo dd if=$2/BOOT/u-boot.img of=/dev/$1 count=2 seek=1 bs=384k
sudo dd if=$2/BOOT/uEnv.txt of=/dev/$1 
