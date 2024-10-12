#!/usr/bin/bash
#docker build --no-cache -t orange_pi_one_image  ${PWD}
docker build -t buildroot_raspberry_pi4_image  ${PWD}
docker run --name rpi4_image   buildroot_raspberry_pi4_image
rm -rf images
docker cp rpi4_image:/home/evg/buildroot/output/images .
docker rm rpi4_image 


