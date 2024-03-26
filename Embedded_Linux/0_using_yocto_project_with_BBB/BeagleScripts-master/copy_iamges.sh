#!/bin/bash
# Simple script for preparing your card for beaglebone
set -x
IMAGE_DIR=${1:-/media/evg/2dc37701-cfd3-4f22-ab8d-a974188c77e7/deploy/images/beaglebone-yocto}
ROOTFS_IMAGE=$(ls -ltr ${IMAGE_DIR}*.bz2 | tail -1 | awk '{print $9}')
#Clean Previous images on card if any
BOOT_PART="BOOT"
ROOTFS_PART="ROOT"
[ -e /media/${USER}/${BOOT_PART}/ ] && sudo rm -rf /media/$USER/${BOOT_PART}/*
[ -e /media/${USER}/${ROOTFS_PART}/ ] && sudo rm -rf /media/$USER/${ROOTFS_PART}/*

cp ${IMAGE_DIR}/{MLO,u-boot.img,uImage} /media/${USER}/${BOOT_PART}/
sudo tar -xf ${ROOTFS_IMAGE} -C /media/$USER/${ROOTFS_PART}/
sync
