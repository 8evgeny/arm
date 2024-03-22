#!/usr/bin/bash
#docker build --no-cache -t build_bb_kernel  ${PWD}
docker build -t buildroot_bbb_kernel  ${PWD}
docker run --name bbb_image buildroot_bbb_kernel
mkdir -p images
docker cp bbb_image:/home/evg/buildroot/output/images .
docker rm bbb_image 


