#!/usr/bin/bash
docker build --no-cache -t orange_pi_one_image  ${PWD}
#docker build -t buildroot_raspberry_pi4_image  ${PWD}
docker run --name orange_pi_one_image   orange_pi_one_image
rm -rf images
docker cp orange_pi_one_image:/home/user/buildroot/output/images .
docker rm orange_pi_one_image 


