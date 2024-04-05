#!/usr/bin/bash
#docker build --no-cache -t build_bb_kernel  ${PWD}
docker build -t buildroot_rpi_kernel  ${PWD}
docker run --name rpi_image buildroot_rpi_kernel
rm -rf images
docker cp rpi_image:/home/evg/buildroot/output/images .
docker rm rpi_image 


