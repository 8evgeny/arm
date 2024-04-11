#!/usr/bin/bash
#docker build --no-cache -t yocto_rpi_image  ${PWD}
#docker build -t --build-arg "host_uid=$(id -u)" --build-arg "host_gid=$(id -g)" --tag "yocto_rpi_image:latest" ${PWD}
docker build -t yocto_rpi_image  ${PWD}
docker run -it --name rpi_image yocto_rpi_image
# rm -rf images
# docker cp rpi_image:/home/evg/buildroot/output/images .
docker rm rpi_image 


