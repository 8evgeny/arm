#!/usr/bin/bash
#docker build --no-cache -t build_bb_kernel  ${PWD}
docker build -t yocto_rpi_image  ${PWD}
docker run -it --name rpi_image yocto_rpi_image
rm -rf images
# docker cp rpi_image:/home/evg/buildroot/output/images .
docker rm rpi_image 


